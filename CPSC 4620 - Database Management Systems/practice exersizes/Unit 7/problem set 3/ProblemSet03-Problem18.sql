-- ## Problem 18
-- 
-- Write a query to display the patron ID, first and last name, and patron type for all 
-- patrons whose last name begins with the letter "C", sorted by patron ID.
-- 
-- +----------+-------------+-------------+------------+
-- |   PAT_ID | PAT_FNAME   | PAT_LNAME   | PAT_TYPE   |
-- |----------+-------------+-------------+------------|
-- |     1160 | robert      | carter      | Faculty    |
-- |     1208 | Ollie       | Cantrell    | Student    |
-- |     1210 | Keith       | Cooley      | STUdent    |
-- +----------+-------------+-------------+------------+

/* YOUR SOLUTION HERE */
SELECT PAT_ID,
	PAT_FNAME,
    PAT_LNAME,
    PAT_TYPE
FROM PATRON
WHERE PAT_LNAME LIKE 'C%'
ORDER BY PAT_ID;
