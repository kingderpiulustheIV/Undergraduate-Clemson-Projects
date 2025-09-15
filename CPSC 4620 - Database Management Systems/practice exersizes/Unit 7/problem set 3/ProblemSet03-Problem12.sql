-- ## Problem 12
-- 
-- Write a query to display the checkout number, book number, and checkout date of all books 
-- checked out before April 5, 20121sorted by checkout number.
-- 
-- +-----------+----------+----------------+
-- | CHECK_NUM | BOOK_NUM | CHECK_OUT_DATE |
-- +-----------+----------+----------------+
-- |   91001   |   5235   |   2021-03-31   |
-- |   91002   |   5238   |   2021-03-31   |
-- |   91003   |   5240   |   2021-03-31   |
-- |   91004   |   5237   |   2021-03-31   |
-- |   91005   |   5236   |   2021-03-31   |
-- +-----------+----------+----------------+

/* YOUR SOLUTION HERE */

SELECT CHECK_NUM, BOOK_NUM, CHECK_OUT_DATE
FROM CHECKOUT
WHERE CHECK_OUT_DATE < '2021-04-05';