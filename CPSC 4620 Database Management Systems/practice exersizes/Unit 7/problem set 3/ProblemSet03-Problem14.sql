-- ## Problem 14
-- 
-- Write a query to display the book number, title, subject, and cost for all books that are 
-- on the subjects of "Middleware" or "Cloud" and  cost more than $70 sorted by book number.
-- 
-- +------------+------------------------------------------+----------------+-------------+
-- |   BOOK_NUM | BOOK_TITLE                               | BOOK_SUBJECT   |   BOOK_COST |
-- |------------+------------------------------------------+----------------+-------------|
-- |       5236 | Database in the Cloud                    | Cloud          |       79.95 |
-- |       5245 | The Golden Road to Platform independence | Middleware     |      119.95 |
-- |       5250 | Reengineering the Middle Tier            | Middleware     |       89.95 |
-- +------------+------------------------------------------+----------------+-------------+

/* YOUR SOLUTION HERE */
SELECT BOOK_NUM,
	BOOK_TITLE,
    BOOK_SUBJECT,
    BOOK_COST
FROM BOOK
WHERE (BOOK_SUBJECT = 'Middleware' OR BOOK_SUBJECT = 'Cloud') AND BOOK_COST > 70.00
ORDER BY BOOK_NUM ASC;

