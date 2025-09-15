-- ## Problem 5
-- 
-- Write a query to display the author ID, author last name, book title, checkout date, and 
-- patron last name for all the books written by authors with the last name “Bruer” that have 
-- ever been checked out by patrons with the last name "Miles." 
-- Sort the results by check out date.
-- 
-- +-------+----------+-------------------+----------------+-----------+
-- | AU_ID | AU_LNAME |    BOOK_TITLE     | CHECK_OUT_DATE | PAT_LNAME |
-- +-------+----------+-------------------+----------------+-----------+
-- |  251  |  Bruer   | Capture the Cloud |   2021-04-21   |   Miles   |
-- |  251  |  Bruer   | Capture the Cloud |   2021-05-15   |   Miles   |
-- +-------+----------+-------------------+----------------+-----------+
-- 

/* YOUR SOLUTION HERE */
SELECT a.AU_ID,
       a.AU_LNAME,
       b.BOOK_TITLE,
       c.CHECK_OUT_DATE,
       p.PAT_LNAME
FROM AUTHOR a
JOIN WRITES w ON a.AU_ID = w.AU_ID
JOIN BOOK b ON w.BOOK_NUM = b.BOOK_NUM
JOIN CHECKOUT c ON b.BOOK_NUM = c.BOOK_NUM
JOIN PATRON p ON c.PAT_ID = p.PAT_ID
WHERE a.AU_LNAME = 'Bruer'
AND p.PAT_LNAME = 'Miles'
ORDER BY c.CHECK_OUT_DATE;