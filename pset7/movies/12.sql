SELECT DISTINCT title
  FROM movies
       JOIN stars
       ON movies.id = stars.movie_id
       JOIN people
       ON stars.person_id = people.id
          AND name ='Helena Bonham Carter'
  WHERE title IN
        (SELECT title FROM movies
                JOIN stars
                ON stars.movie_id = movies.id
                JOIN people
                ON people.id = stars.person_id
         WHERE name = 'Johnny Depp');