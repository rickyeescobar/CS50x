SELECT DISTINCT people.name
FROM people
JOIN stars ON people.id = stars.person_id
JOIN movies ON movies.id = stars.movie_id
WHERE NOT people.name = "Kevin Bacon" AND stars.movie_id IN (

SELECT movies.id
FROM movies
JOIN stars ON movies.id = stars.movie_id
JOIN people on people.id = stars.person_id
where people.name = "Kevin Bacon" AND people.birth = "1958"
);