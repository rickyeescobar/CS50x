import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # get user name and cash balance
    username = db.execute("SELECT username FROM users WHERE id = ?", session["user_id"])[0]["username"]
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
    formatted_cash = usd(cash)

    # find which stocks the user owns
    portfolio = db.execute(
        "SELECT instrument, sum(size) AS position FROM transactions WHERE id = ? GROUP BY instrument HAVING position != 0", session["user_id"])

    # create empty list for storing portfolio data
    data_list = []
    total_account_value = 0

    # loop through users portfolio, calling API to find Data on each stock
    for stock in portfolio:
        data = lookup(stock["instrument"])
        data_list.append({"Instrument": stock["instrument"], "Name": data["name"],
                          "Position": stock["position"], "Last Price": data["price"]})
        total_account_value += (stock["position"] * data["price"])

    total_account_value += cash
    total_account_value = usd(total_account_value)

    # render the page
    return render_template("index.html", username=username, cash=cash, formatted_cash=formatted_cash, portfolio=data_list, total_account_value=total_account_value)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":

        symbol = request.form.get("symbol")
        size = request.form.get("shares")

        data = lookup(symbol)
        if not data:
            return apology("Invalid Stock Ticker")

        if not size.isnumeric() or int(size) <= 0 or size == None or "." in size:
            return apology("Size must be a positive integer")

        size = int(size)

        # check funds
        funds = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
        transaction = float(data["price"]) * size

        if funds <= transaction:
            return apology("Insufficient funds")

        else:
            new_balance = float(funds - transaction)

            try:
                # update users - withdraw money for purchase
                db.execute("UPDATE users SET cash = ? WHERE id = ?", new_balance, session["user_id"])
                # create transaction
                db.execute("INSERT INTO transactions ( id, transaction_date, transaction_type, size, instrument, instrument_price, cash_change ) VALUES( ? , datetime('now','localtime') , 'BUY' , ? , ? , ? , ? );",
                           session["user_id"], size, data["symbol"], data["price"], (-1 * transaction))

            except:
                return apology("Database incurred an error")

        return redirect("/")

    else:
        funds = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
        return render_template("buy.html", funds=usd(funds))


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    username = db.execute("SELECT username FROM users WHERE id = ?", session["user_id"])[0]["username"]
    transactions = db.execute("SELECT * FROM transactions WHERE id = ?", session["user_id"])

    return render_template("history.html", username=username, transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""
    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # POST
    if request.method == "POST":
        symbol = request.form.get("symbol")

        if "'" in symbol or ";" in symbol:
            return apology("Dangerous Characters in Submission")

        data = lookup(symbol)

        if not data:
            return apology("Stock Ticker Entered Does Not Exist")

        return render_template("quoted.html", data=data, price=usd(data["price"]))

    # GET
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":

        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # check for client side errors
        if not username:
            return apology("Must enter a username")

        if not password or not confirmation:
            return apology("Must fill all fields")

        if password != confirmation:
            return apology("Passwords did not match!")

        # check if username already exists
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
        if len(rows) > 0:
            return apology("Username Already Exists")

        # add user to database
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, generate_password_hash(password))

        # get user id and sign user in
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)
        session["user_id"] = rows[0]["id"]

        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

   # query for stocks in portfolio
    portfolio = db.execute(
        "SELECT instrument, sum(size) AS position FROM transactions GROUP BY instrument HAVING position != 0 and id = ? ", session["user_id"])

    if request.method == "POST":

        # get symbol and size from form
        symbol = request.form.get("symbol")
        size = request.form.get("shares")

        # handle size error
        if not size.isnumeric() or int(size) <= 0 or size == None or "." in size:
            return apology("Size must be a positive integer")

        size = int(size)
        # handle if the user tried to sell more shares than they own
        if size > int(portfolio[0]["position"]):
            return apology("Insufficent shares to complete transaction successfully")

        try:
            # lookup stock data
            data = lookup(symbol)

            # handle API error
            if not data:
                return apology("Invalid Stock Ticker")
        except:
            return apology("API error")

        # get cash balance of account
        funds = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]

        # compute transaction price
        transaction = float(data["price"]) * size

        # compute new_balance
        new_balance = float(funds + transaction)

        try:
            # create transaction
            db.execute("INSERT INTO transactions ( id, transaction_date, transaction_type, size, instrument, instrument_price, cash_change ) VALUES( ? , datetime('now','localtime') , 'SELL' , ? , ? , ? , ? );",
                       session["user_id"], (-1 * size), data["symbol"], data["price"], transaction)
            # update users - deposit money for purchase
            db.execute("UPDATE users SET cash = ? WHERE id = ?", new_balance, session["user_id"])
        except:
            return apology("Database incurred an error")

        return redirect("/")

    # GET
    else:
        return render_template("sell.html", portfolio=portfolio)

