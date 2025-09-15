-- ## Problem 13
-- 
-- Write a query to display the book number, title, subject, author last name, and the number of 
-- books written by that author. Limit the results to books in the Cloud subject. 
-- Sort the results by book title and then author last name.
-- 
-- +------------+---------------------------------+----------------+------------+-----------------------+
-- |   BOOK_NUM | BOOK_TITLE                      | BOOK_SUBJECT   | AU_LNAME   |   Num Books by Author |
-- |------------+---------------------------------+----------------+------------+-----------------------|
-- |       5246 | Capture the Cloud               | Cloud          | Bruer      |                     2 |
-- |       5244 | Cloud-based Mobile Applications | Cloud          | Chiang     |                     3 |
-- |       5244 | Cloud-based Mobile Applications | Cloud          | Tankersly  |                     1 |
-- |       5236 | Database in the Cloud           | Cloud          | Walsh      |                     2 |
-- |       5249 | Starlight Applications          | Cloud          | Chiang     |                     3 |
-- +------------+---------------------------------+----------------+------------+-----------------------+
-- 

/* YOUR SOLUTION HERE */
SELECT b.BOOK_NUM, 
       b.BOOK_TITLE, 
       b.BOOK_SUBJECT, 
       a.AU_LNAME,
       COUNT(w2.BOOK_NUM) AS "Num Books by Author"
FROM BOOK b
JOIN WRITES w ON b.BOOK_NUM = w.BOOK_NUM
JOIN AUTHOR a ON w.AU_ID = a.AU_ID
JOIN WRITES w2 ON a.AU_ID = w2.AU_ID
WHERE b.BOOK_SUBJECT = 'Cloud'
GROUP BY b.BOOK_NUM, b.BOOK_TITLE, b.BOOK_SUBJECT, a.AU_LNAME
ORDER BY b.BOOK_TITLE, a.AU_LNAME;