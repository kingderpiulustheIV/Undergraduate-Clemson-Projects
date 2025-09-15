-- ## Problem 17
-- 
-- Write a query to display the patron ID, first and last name of all patrons who are 
-- students, sorted by patron ID. (44 rows)
-- 
-- [NOTE: Rows omitted from the target results for clarity.  
--  The autograder will check for  ALL required output.]
-- 
-- +----------+-------------+-------------+
-- |   PAT_ID | PAT_FNAME   | PAT_LNAME   |
-- |----------+-------------+-------------|
-- |     1166 | Vera        | Alvarado    |
-- |     1171 | Peggy       | Marsh       |
-- |     1172 | Tony        | Miles       |
-- |     1174 | Betsy       | Malone      |
-- |     1180 | Nadine      | Blair       |
-- |     1181 | Allen       | Horne       |
-- |     1182 | Jamal       | Melendez    |
-- |     1184 | Jimmie      | Love        |
-- ... rows ommitted...
-- |     1242 | Mario       | King        |
-- |     1243 | Roberto     | Kennedy     |
-- |     1244 | Leon        | Richmond    |
-- +----------+-------------+-------------+

/* YOUR SOLUTION HERE */
SELECT PAT_ID,
	PAT_FNAME,
    PAT_LNAME
FROM PATRON
WHERE PAT_TYPE LIKE 'student'
ORDER BY PAT_ID ASC;
