SELECT people.name FROM people JOIN movies ON movies.id = people.id JOIN stars ON stars.person_id = people.id AND stars.movie_id = movies.id
AND people.name = "Kevin Bacon";