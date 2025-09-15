-- ## Problem 10
-- 
-- Write a query to display the book number, title, and cost of books that have the lowest cost 
-- of any books in the system. Sort the results by book number.
-- 
-- [NOTE: Your SQL does not need to center any result output.]
-- 
-- +------------+-----------------------------------------------------------------------+-------------+
-- |   BOOK_NUM | BOOK_TITLE                                                            |   BOOK_COST |
-- |------------+-----------------------------------------------------------------------+-------------|
-- |       5239 | J++ in Mobile Apps                                                    |       49.95 |
-- |       5241 | JAVA First Steps                                                      |       49.95 |
-- |       5248 | What You Always Wanted to Know About Database, But Were Afraid to Ask |       49.95 |
-- |       5254 | Coding Style for Maintenance                                          |       49.95 |
-- +------------+-----------------------------------------------------------------------+-------------+
-- 

/* YOUR SOLUTION HERE */
SELECT BOOK_NUM, 
	BOOK_TITLE, 
	BOOK_COST
FROM BOOK
WHERE BOOK_COST = (SELECT MIN(BOOK_COST) FROM BOOK)
ORDER BY BOOK_NUM;