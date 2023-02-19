SELECT movies.title FROM movies JOIN ratings ON movies.id = ratings.movie_id WHERE movies.id IN (SELECT movie_id FROM ratings WHERE movie_id IN (SELECT movie_id FROM stars WHERE person_id = (SELECT id FROM people WHERE name = "Chadwick Boseman")) ORDER BY rating DESC LIMIT 5) ORDER BY ratings.rating DESC;


/* SELECT movies.title, ratings.rating FROM movies JOIN ratings ON movies.id = ratings.movie_id JOIN stars ON movies.id = stars.movie_id JOIN people ON stars.person_id = people.id WHERE people.name = "Chadwick Boseman" ORDER BY ratings.rating DESC;
Alternate method, slower but able to get more info by joining all the tables. */