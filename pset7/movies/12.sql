-- Stackoverflow solution https://stackoverflow.com/questions/4047484/selecting-with-multiple-where-conditions-on-same-column
SELECT title FROM movies JOIN
stars ON movies.id = stars.movie_id
JOIN people ON stars.person_id = people.id
WHERE name IN ("Johnny Depp", "Helena Bonham Carter")
GROUP BY title
HAVING count(*) = 2;