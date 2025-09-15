-- ## Problem 6
-- 
-- Write a query to display the different subjects on which FACT has books. 
-- Include each subject only once and sort the results by subject.
-- 
-- +----------------+
-- | BOOK_SUBJECT   |
-- |----------------|
-- | Cloud          |
-- | Database       |
-- | Middleware     |
-- | Programming    |
-- +----------------+

/* YOUR SOLUTION HERE */
SELECT DISTINCT BOOK_SUBJECT
FROM BOOK
ORDER BY BOOK_SUBJECT ASC;
