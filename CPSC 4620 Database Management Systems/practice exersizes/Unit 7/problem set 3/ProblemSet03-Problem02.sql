-- ## Problem 2
-- 
-- Write a query that displays the first and last name of every patron, 
-- sorted by last name and then first name. Ensure the sort is case insensitive. (50 rows)
-- 
-- [NOTE: Rows omitted from the target results for clarity.  
--  The autograder will check for  ALL required output.]
--  
-- +-------------+-------------+
-- | PAT_FNAME   | PAT_LNAME   |
-- |-------------+-------------|
-- | Vera        | Alvarado    |
-- | Holly       | Anthony     |
-- | Cedric      | Baldwin     |
-- | Cory        | Barry       |
-- | Nadine      | Blair       |
-- | Erika       | Bowen       |
-- ... rows ommitted...
-- | Iva         | Ramos       |
-- | Leon        | Richmond    |
-- | Desiree     | Rivas       |
-- | Angel       | Terrell     |
-- | Lorenzo     | Torres      |
-- | Irene       | West        |
-- | Sandra      | Yang        |
-- +-------------+-------------+

/* YOUR SOLUTION HERE */
SELECT PAT_FNAME, 
	PAT_LNAME
FROM PATRON
ORDER BY PAT_LNAME ASC, PAT_FNAME ASC;