from flask import Blueprint, flash, g, redirect, render_template, request, url_for

from werkzeug.exceptions import abort
from website.auth import login_required
from website.db import get_db
from nltk.sentiment.vader import SentimentIntensityAnalyzer

views = Blueprint("views", __name__)

# adjust this variable between -1 and +1 to change allowable sentiment
SENTIMENT_MIN = 0

def test_sentiment(phrase):
    error = None
    sid = SentimentIntensityAnalyzer()
    analyzed = sid.polarity_scores(phrase)

    if analyzed["compound"] < SENTIMENT_MIN:
        error = "Input wasn't kind enough"
    
    return error

@views.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

    

@views.route('/', methods=["GET", "POST"])
@login_required
def index():
    db = get_db()
    posts = db.execute(
        'SELECT p.id, body, created, author_id, community_name, username'
        ' FROM POST p JOIN user u ON p.author_id = u.id'
        ' ORDER BY created DESC'
    ).fetchall()

    posts = db.execute(
        'SELECT p.id, body, created, author_id, community_name, username'
        ' FROM POST p JOIN user u ON p.author_id = u.id WHERE p.community_name'
        ' IN ( SELECT name FROM community c JOIN community_user ON c.name = community_user.community_name'
        ' WHERE community_user.user_id = ?) ORDER BY created DESC',(g.user['id'],)
    ).fetchall()

    return render_template('views/index.html', posts=posts)
    


@views.route('/create', methods=('GET','POST'))
@login_required
def create():
    if request.method == 'POST':
        body = request.form['body']
        community = request.form['communitylist']
        error = None

        if not body:
            error = 'body is required'

        # insert sentiment logic
        error = test_sentiment(body)

        if error is not None:
            flash(error)

        else:
            db = get_db()
            db.execute(
                'INSERT INTO post (body, author_id, community_name)'
                'VALUES ( ?, ?, ?)',
                (body, g.user['id'], community)
            )
            db.commit()
            return redirect(url_for('views.index'))
    
    db = get_db()
    communities = db.execute(
        'SELECT name FROM community c '
        'JOIN community_user ON c.name = community_user.community_name '
        'WHERE community_user.user_id = ?',(g.user['id'],)
    ).fetchall()

    return render_template('views/create.html', communities=communities)


@views.route('/functionality', methods=('GET', 'POST'))
def functionality():
    if request.method == "POST":
        
        phrase = request.form.get("phrase")
        
        sid = SentimentIntensityAnalyzer()
        analyzed = sid.polarity_scores(phrase)

        if analyzed["compound"] > 0:
            phrase = ":)"
        elif analyzed["compound"] == 0:
            phrase = ":|"
        else:
            phrase = ":("

        return render_template("views/functionality.html", analyzed=analyzed, phrase=phrase)

    else:
        return render_template("views/functionality.html")



# define get post ( for udpating and deletion)
def get_post(id, check_author=True):
    post = get_db().execute(
        'SELECT p.id, body, created, author_id, community_name, username'
        ' FROM post p JOIN user u ON p.author_id = u.id'
        ' WHERE p.id = ?',
        (id,)
    ).fetchone()

    if post is None:
        abort(404, f"Post id {id} doesn't exist.")

    if check_author and post['author_id'] != g.user['id']:
        abort(403)

    return post


# update post
@views.route('/<int:id>/update', methods=('GET','POST'))
@login_required
def update(id):
    post = get_post(id)

    if request.method == 'POST':
        body = request.form['body']
        error = None

        if not body:
            error = 'body is required.'

         # insert sentiment logic
        error = test_sentiment(body)

        if error is not None:
            flash(error)
        else:
            db = get_db()
            db.execute(
                'UPDATE post SET body = ?'
                ' WHERE id = ?',
                ( body, id)
            )
            db.commit()
            return redirect(url_for('views.index'))
    return render_template('views/update.html', post=post)

@views.route('/<int:id>/delete', methods=('POST',))
@login_required
def delete(id):
    get_post(id)
    db = get_db()
    db.execute('DELETE FROM post WHERE id = ?', (id,))
    db.commit()
    return redirect(url_for('views.index'))

