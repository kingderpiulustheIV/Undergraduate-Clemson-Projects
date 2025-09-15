-- ## Problem 11
-- 
-- Write a query to display the book number, title, and cost for all books in the "Database" 
-- subject sorted by book number.
-- 
-- +------------+-----------------------------------------------------------------------+-------------+
-- |   BOOK_NUM | BOOK_TITLE                                                            |   BOOK_COST |
-- |------------+-----------------------------------------------------------------------+-------------|
-- |       5237 | Mastering the database environment                                    |       89.95 |
-- |       5243 | DATABASES in Theory                                                   |      129.95 |
-- |       5248 | What You Always Wanted to Know About Database, But Were Afraid to Ask |       49.95 |
-- |       5252 | Beyond the Database Veil                                              |       69.95 |
-- +------------+-----------------------------------------------------------------------+-------------+

/* YOUR SOLUTION HERE */
SELECT BOOK_NUM,
	BOOK_TITLE,
    BOOK_COST
FROM BOOK
WHERE BOOK_SUBJECT = 'Database'
ORDER BY BOOK_NUM ASC;

