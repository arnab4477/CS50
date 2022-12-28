SELECT movies.title FROM movies JOIN stars ON movies.id = stars.movie_id JOIN people ON stars.person_id = people.id
AND people.name = "Johnny Depp" AND people.name = "Helena Bonham Carter";