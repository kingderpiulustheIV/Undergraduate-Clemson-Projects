-- ## Problem 4
-- 
-- Write a query to display the book number, title, and number of times each book has been 
-- checked out. Limit the results to books that have been checked out more than five times. 
-- Sort the results in descending order by the number of times checked out and then by title.
-- 
-- +------------+--------------------------+---------------------+
-- |   BOOK_NUM | BOOK_TITLE               |   Times Checked Out |
-- |------------+--------------------------+---------------------|
-- |       5236 | Database in the Cloud    |                  12 |
-- |       5235 | Beginner's Guide to JAVA |                   9 |
-- |       5240 | iOS Programming          |                   7 |
-- |       5238 | Conceptual Programming   |                   6 |
-- +------------+--------------------------+---------------------+
-- 

/* YOUR SOLUTION HERE */
SELECT b.BOOK_NUM,
       b.BOOK_TITLE,
       COUNT(c.BOOK_NUM) AS "Times Checked Out"
FROM BOOK b
JOIN CHECKOUT c ON b.BOOK_NUM = c.BOOK_NUM
GROUP BY b.BOOK_NUM, b.BOOK_TITLE
HAVING COUNT(c.BOOK_NUM) > 5
ORDER BY COUNT(c.BOOK_NUM) DESC, b.BOOK_TITLE;
