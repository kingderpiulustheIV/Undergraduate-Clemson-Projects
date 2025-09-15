-- ## Problem 11
-- 
-- Write a query to display the author ID, first and last name for all authors who have never 
-- written a book with the subject Programming. Sort the results by author last name.
-- 
-- +---------+------------+------------+
-- |   AU_ID | AU_FNAME   | AU_LNAME   |
-- |---------+------------+------------|
-- |     581 | Manish     | Aggerwal   |
-- |     251 | Hugo       | Bruer      |
-- |     262 | Xia        | Chiang     |
-- |     438 | Perry      | Pearson    |
-- |     284 | Trina      | Tankersly  |
-- |     383 | Neal       | Walsh      |
-- +---------+------------+------------+
-- 

/* YOUR SOLUTION HERE */
SELECT a.AU_ID, 
	a.AU_FNAME, 
    a.AU_LNAME
FROM AUTHOR a
WHERE a.AU_ID NOT IN (
    SELECT DISTINCT w.AU_ID
    FROM WRITES w
    JOIN BOOK b ON w.BOOK_NUM = b.BOOK_NUM
    WHERE b.BOOK_SUBJECT = 'Programming'
)
ORDER BY a.AU_LNAME;