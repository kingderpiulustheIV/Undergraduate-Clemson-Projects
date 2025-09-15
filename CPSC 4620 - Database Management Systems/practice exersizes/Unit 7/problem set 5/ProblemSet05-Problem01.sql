-- ## Problem 1
-- 
-- Write a query to display the author ID, first and last name, book number, and book title of 
-- all books in the subject "Cloud". Sort the results by book title and then by author last name.
-- 
-- +---------+------------+------------+------------+---------------------------------+
-- |   AU_ID | AU_FNAME   | AU_LNAME   |   BOOK_NUM | BOOK_TITLE                      |
-- |---------+------------+------------+------------+---------------------------------|
-- |     251 | Hugo       | Bruer      |       5246 | Capture the Cloud               |
-- |     262 | Xia        | Chiang     |       5244 | Cloud-based Mobile Applications |
-- |     284 | Trina      | Tankersly  |       5244 | Cloud-based Mobile Applications |
-- |     383 | Neal       | Walsh      |       5236 | Database in the Cloud           |
-- |     262 | Xia        | Chiang     |       5249 | Starlight Applications          |
-- +---------+------------+------------+------------+---------------------------------+
-- 

/* YOUR SOLUTION HERE */
SELECT a.AU_ID,
       a.AU_FNAME,
       a.AU_LNAME,
       b.BOOK_NUM,
       b.BOOK_TITLE
FROM AUTHOR a
JOIN WRITES w ON a.AU_ID = w.AU_ID
JOIN BOOK b ON w.BOOK_NUM = b.BOOK_NUM
WHERE b.BOOK_SUBJECT = 'Cloud'
ORDER BY b.BOOK_TITLE, a.AU_LNAME;