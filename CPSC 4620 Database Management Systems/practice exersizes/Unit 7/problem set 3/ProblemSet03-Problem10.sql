-- ## Problem 10
-- 
-- Write a query to display the book number, title, and cost for all books that 
-- cost $59.95 sorted by book number.
-- 
-- +------------+-------------------------------+-------------+
-- |   BOOK_NUM | BOOK_TITLE                    |   BOOK_COST |
-- |------------+-------------------------------+-------------|
-- |       5235 | Beginner's Guide to JAVA      |       59.95 |
-- |       5238 | Conceptual Programming        |       59.95 |
-- |       5242 | C# in Middleware Deployment   |       59.95 |
-- |       5251 | Thoughts on Revitalizing Ruby |       59.95 |
-- +------------+-------------------------------+-------------+

/* YOUR SOLUTION HERE */
SELECT BOOK_NUM,
	BOOK_TITLE,
    BOOK_COST
FROM BOOK
WHERE BOOK_COST = 59.95
ORDER BY BOOK_NUM ASC;

