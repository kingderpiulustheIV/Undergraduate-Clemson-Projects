-- ## Problem 3
-- 
-- Write a query to display the checkout number, checkout date, and due date for every 
-- book that has been checked out sorted by checkout number. (68 rows)
-- 
-- [NOTE: Rows omitted from the target results for clarity.  
--  The autograder will check for  ALL required output.]
-- 
-- +-----------+----------------+----------------+
-- | CHECK_NUM | CHECK_OUT_DATE | CHECK_DUE_DATE |
-- +-----------+----------------+----------------+
-- |   91001   |   2021-03-31   |   2021-04-14   |
-- |   91002   |   2021-03-31   |   2021-04-07   |
-- |   91003   |   2021-03-31   |   2021-04-14   |
-- |   91004   |   2021-03-31   |   2021-04-14   |
-- |   91005   |   2021-03-31   |   2021-04-07   |
-- |   91006   |   2021-04-05   |   2021-04-12   |
-- |   91007   |   2021-04-05   |   2021-04-12   |
-- |   91008   |   2021-04-05   |   2021-04-12   |
-- ... rows ommitted...
-- |   91061   |   2021-05-15   |   2021-05-22   |
-- |   91062   |   2021-05-15   |   2021-05-22   |
-- |   91063   |   2021-05-15   |   2021-05-22   |
-- |   91064   |   2021-05-17   |   2021-05-31   |
-- |   91065   |   2021-05-17   |   2021-05-24   |
-- |   91066   |   2021-05-19   |   2021-05-26   |
-- |   91067   |   2021-05-24   |   2021-05-31   |
-- |   91068   |   2021-05-24   |   2021-05-31   |
-- +-----------+----------------+----------------+

/* YOUR SOLUTION HERE */
SELECT CHECK_NUM, CHECK_OUT_DATE, CHECK_DUE_DATE
FROM CHECKOUT
ORDER BY CHECK_NUM ASC;


