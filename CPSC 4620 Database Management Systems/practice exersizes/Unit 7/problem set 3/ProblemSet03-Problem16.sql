-- ## Problem 16
-- 
-- Write a query to display the book number, title, and subject for all books that contain the 
-- word "Database" in the title, regardless of how it is capitalized.  Sort the results by 
-- book number.
-- 
-- +------------+-----------------------------------------------------------------------+----------------+
-- |   BOOK_NUM | BOOK_TITLE                                                            | BOOK_SUBJECT   |
-- |------------+-----------------------------------------------------------------------+----------------|
-- |       5236 | Database in the Cloud                                                 | Cloud          |
-- |       5237 | Mastering the database environment                                    | Database       |
-- |       5243 | DATABASES in Theory                                                   | Database       |
-- |       5248 | What You Always Wanted to Know About Database, But Were Afraid to Ask | Database       |
-- |       5252 | Beyond the Database Veil                                              | Database       |
-- +------------+-----------------------------------------------------------------------+----------------+

/* YOUR SOLUTION HERE */
SELECT BOOK_NUM, 
	BOOK_TITLE,
    BOOK_SUBJECT
FROM BOOK
WHERE BOOK_TITLE like '%Database%'
ORDER BY BOOK_NUM ASC;
