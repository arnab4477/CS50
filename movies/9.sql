SELECT DISTINCT people.name FROM people JOIN stars ON stars.person_id = people.id JOIN movies ON movies.id = stars.movie_id
AND movies.year = 2004 ORDER BY people.birth;