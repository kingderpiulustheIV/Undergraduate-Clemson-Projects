-- ## Problem 19
-- Write a query to display the author ID, first and last name of all authors whose year 
-- of birth is unknown. Sort the results by author ID.
-- 
-- +---------+------------+------------+
-- |   AU_ID | AU_FNAME   | AU_LNAME   |
-- |---------+------------+------------|
-- |     229 | Carmine    | Salvadore  |
-- |     262 | Xia        | Chiang     |
-- |     559 | Rachel     | McGill     |
-- +---------+------------+------------+

/* YOUR SOLUTION HERE */
SELECT AU_ID,
	AU_FNAME,
	AU_LNAME
FROM AUTHOR
WHERE AU_BIRTHYEAR IS NULL
ORDER BY AU_ID ASC;

