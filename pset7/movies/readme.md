<h1>CS50x 2022 Problem set 7 - movies</h1>

https://cs50.harvard.edu/x/2022/psets/7/movies/

For each of the following problems, you should write a single SQL query that outputs the results specified by each problem.

<ol>
  <li>In <code class="language-plaintext highlighter-rouge">1.sql</code>, write a SQL query to list the titles of all movies released in 2008.
    <ul class="fa-ul">
      <li data-marker="*"><span class="fa-li"><i class="fas fa-square"></i></span>Your query should output a table with a single column for the title of each movie.</li>
    </ul>
  </li><br>
  <li>In <code class="language-plaintext highlighter-rouge">2.sql</code>, write a SQL query to determine the birth year of Emma Stone.
    <ul class="fa-ul">
      <li data-marker="*"><span class="fa-li"><i class="fas fa-square"></i></span>Your query should output a table with a single column and a single row (not counting the header) containing Emma Stone’s birth year.</li>
      <li data-marker="*"><span class="fa-li"><i class="fas fa-square"></i></span>You may assume that there is only one person in the database with the name Emma Stone.</li>
    </ul>
  </li><br>
  <li>In <code class="language-plaintext highlighter-rouge">3.sql</code>, write a SQL query to list the titles of all movies with a release date on or after 2018, in alphabetical order.
    <ul class="fa-ul">
      <li data-marker="*"><span class="fa-li"><i class="fas fa-square"></i></span>Your query should output a table with a single column for the title of each movie.</li>
      <li data-marker="*"><span class="fa-li"><i class="fas fa-square"></i></span>Movies released in 2018 should be included, as should movies with release dates in the future.</li>
    </ul>
  </li><br>
  <li>In <code class="language-plaintext highlighter-rouge">4.sql</code>, write a SQL query to determine the number of movies with an IMDb rating of 10.0.
    <ul class="fa-ul">
      <li data-marker="*"><span class="fa-li"><i class="fas fa-square"></i></span>Your query should output a table with a single column and a single row (not counting the header) containing the number of movies with a 10.0 rating.</li>
    </ul>
  </li><br>
  <li>In <code class="language-plaintext highlighter-rouge">5.sql</code>, write a SQL query to list the titles and release years of all Harry Potter movies, in chronological order.
    <ul class="fa-ul">
      <li data-marker="*"><span class="fa-li"><i class="fas fa-square"></i></span>Your query should output a table with two columns, one for the title of each movie and one for the release year of each movie.</li>
      <li data-marker="*"><span class="fa-li"><i class="fas fa-square"></i></span>You may assume that the title of all Harry Potter movies will begin with the words “Harry Potter”, and that if a movie title begins with the words “Harry Potter”, it is a Harry Potter movie.</li>
    </ul>
  </li><br>
  <li>In <code class="language-plaintext highlighter-rouge">6.sql</code>, write a SQL query to determine the average rating of all movies released in 2012.
    <ul class="fa-ul">
      <li data-marker="*"><span class="fa-li"><i class="fas fa-square"></i></span>Your query should output a table with a single column and a single row (not counting the header) containing the average rating.</li>
    </ul>
  </li><br>
  <li>In <code class="language-plaintext highlighter-rouge">7.sql</code>, write a SQL query to list all movies released in 2010 and their ratings, in descending order by rating. For movies with the same rating, order them alphabetically by title.
    <ul class="fa-ul">
      <li data-marker="*"><span class="fa-li"><i class="fas fa-square"></i></span>Your query should output a table with two columns, one for the title of each movie and one for the rating of each movie.</li>
      <li data-marker="*"><span class="fa-li"><i class="fas fa-square"></i></span>Movies that do not have ratings should not be included in the result.</li>
    </ul>
  </li><br>
  <li>In <code class="language-plaintext highlighter-rouge">8.sql</code>, write a SQL query to list the names of all people who starred in Toy Story.
    <ul class="fa-ul">
      <li data-marker="*"><span class="fa-li"><i class="fas fa-square"></i></span>Your query should output a table with a single column for the name of each person.</li>
      <li data-marker="*"><span class="fa-li"><i class="fas fa-square"></i></span>You may assume that there is only one movie in the database with the title Toy Story.</li>
    </ul>
  </li><br>
  <li>In <code class="language-plaintext highlighter-rouge">9.sql</code>, write a SQL query to list the names of all people who starred in a movie released in 2004, ordered by birth year.
    <ul class="fa-ul">
      <li data-marker="*"><span class="fa-li"><i class="fas fa-square"></i></span>Your query should output a table with a single column for the name of each person.</li>
      <li data-marker="*"><span class="fa-li"><i class="fas fa-square"></i></span>People with the same birth year may be listed in any order.</li>
      <li data-marker="*"><span class="fa-li"><i class="fas fa-square"></i></span>No need to worry about people who have no birth year listed, so long as those who do have a birth year are listed in order.</li>
      <li data-marker="*"><span class="fa-li"><i class="fas fa-square"></i></span>If a person appeared in more than one movie in 2004, they should only appear in your results once.</li>
    </ul>
  </li><br>
  <li>In <code class="language-plaintext highlighter-rouge">10.sql</code>, write a SQL query to list the names of all people who have directed a movie that received a rating of at least 9.0.
    <ul class="fa-ul">
      <li data-marker="*"><span class="fa-li"><i class="fas fa-square"></i></span>Your query should output a table with a single column for the name of each person.</li>
      <li data-marker="*"><span class="fa-li"><i class="fas fa-square"></i></span>If a person directed more than one movie that received a rating of at least 9.0, they should only appear in your results once.</li>
    </ul>
  </li><br>
  <li>In <code class="language-plaintext highlighter-rouge">11.sql</code>, write a SQL query to list the titles of the five highest rated movies (in order) that Chadwick Boseman starred in, starting with the highest rated.
    <ul class="fa-ul">
      <li data-marker="*"><span class="fa-li"><i class="fas fa-square"></i></span>Your query should output a table with a single column for the title of each movie.</li>
      <li data-marker="*"><span class="fa-li"><i class="fas fa-square"></i></span>You may assume that there is only one person in the database with the name Chadwick Boseman.</li>
    </ul>
  </li><br>
  <li>In <code class="language-plaintext highlighter-rouge">12.sql</code>, write a SQL query to list the titles of all movies in which both Johnny Depp and Helena Bonham Carter starred.
    <ul class="fa-ul">
      <li data-marker="*"><span class="fa-li"><i class="fas fa-square"></i></span>Your query should output a table with a single column for the title of each movie.</li>
      <li data-marker="*"><span class="fa-li"><i class="fas fa-square"></i></span>You may assume that there is only one person in the database with the name Johnny Depp.</li>
      <li data-marker="*"><span class="fa-li"><i class="fas fa-square"></i></span>You may assume that there is only one person in the database with the name Helena Bonham Carter.</li>
    </ul>
  </li><br>
  <li>In <code class="language-plaintext highlighter-rouge">13.sql</code>, write a SQL query to list the names of all people who starred in a movie in which Kevin Bacon also starred.
    <ul class="fa-ul">
      <li data-marker="*"><span class="fa-li"><i class="fas fa-square"></i></span>Your query should output a table with a single column for the name of each person.</li>
      <li data-marker="*"><span class="fa-li"><i class="fas fa-square"></i></span>There may be multiple people named Kevin Bacon in the database. Be sure to only select the Kevin Bacon born in 1958.</li>
      <li data-marker="*"><span class="fa-li"><i class="fas fa-square"></i></span>Kevin Bacon himself should not be included in the resulting list.</li>
    </ul>
  </li>
</ol>
