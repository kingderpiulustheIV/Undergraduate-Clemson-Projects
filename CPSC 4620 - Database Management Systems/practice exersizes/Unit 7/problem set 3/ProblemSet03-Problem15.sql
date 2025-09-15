-- ## Problem 15
-- 
-- Write a query to display the author ID, first name, last name, and year of birth for all 
-- authors born in the decade of the 1980s sorted by author ID.
-- 
-- +---------+------------+------------+----------------+
-- |   AU_ID | AU_FNAME   | AU_LNAME   |   AU_BIRTHYEAR |
-- |---------+------------+------------+----------------|
-- |     218 | Rachel     | Beatney    |           1983 |
-- |     383 | Neal       | Walsh      |           1980 |
-- |     394 | Robert     | Lake       |           1982 |
-- |     438 | Perry      | Pearson    |           1986 |
-- |     460 | Connie     | Paulsen    |           1983 |
-- |     581 | Manish     | Aggerwal   |           1984 |
-- |     603 | Julia      | Palca      |           1988 |
-- +---------+------------+------------+----------------+

/* YOUR SOLUTION HERE */
SELECT *
FROM AUTHOR
WHERE AU_BIRTHYEAR BETWEEN 1980 AND 1989
ORDER BY AU_ID ASC
