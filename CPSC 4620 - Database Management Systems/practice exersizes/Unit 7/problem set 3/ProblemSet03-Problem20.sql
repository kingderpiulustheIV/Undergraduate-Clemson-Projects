-- ## Problem 20
-- 
-- Write a query to display the author ID, first and last name of all authors whose year of 
-- birth is known. Ensure the results are sorted by author ID.
-- 
-- +---------+------------+------------+
-- |   AU_ID | AU_FNAME   | AU_LNAME   |
-- |---------+------------+------------|
-- |     185 | Benson     | Reeves     |
-- |     218 | Rachel     | Beatney    |
-- |     251 | Hugo       | Bruer      |
-- |     273 | Reba       | Durante    |
-- |     284 | Trina      | Tankersly  |
-- |     383 | Neal       | Walsh      |
-- |     394 | Robert     | Lake       |
-- |     438 | Perry      | Pearson    |
-- |     460 | Connie     | Paulsen    |
-- |     581 | Manish     | Aggerwal   |
-- |     592 | Lawrence   | Sheel      |
-- |     603 | Julia      | Palca      |
-- +---------+------------+------------+

/* YOUR SOLUTION HERE */

SELECT AU_ID,
	AU_FNAME,
	AU_LNAME
FROM AUTHOR
WHERE AU_BIRTHYEAR IS NOT NULL
ORDER BY AU_ID ASC;