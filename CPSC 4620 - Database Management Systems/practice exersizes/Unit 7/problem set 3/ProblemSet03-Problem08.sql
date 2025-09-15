-- ## Problem 8
-- 
-- Write a query to display the checkout number, book number, patron ID, checkout date, and due date
-- for every checkout that has ever occurred in the system. Sort the results by checkout date in
-- descending order and then by checkout number in ascending order.
-- 
-- [NOTE: Rows omitted from the target results for clarity.  
--  The autograder will check for  ALL required output.]
--  
-- +-----------+----------+--------+----------------+----------------+
-- | CHECK_NUM | BOOK_NUM | PAT_ID | CHECK_OUT_DATE | CHECK_DUE_DATE |
-- +-----------+----------+--------+----------------+----------------+
-- |   91067   |   5252   |  1229  |   2021-05-24   |   2021-05-31   |
-- |   91068   |   5238   |  1229  |   2021-05-24   |   2021-05-31   |
-- |   91066   |   5242   |  1228  |   2021-05-19   |   2021-05-26   |
-- |   91064   |   5236   |  1183  |   2021-05-17   |   2021-05-31   |
-- |   91065   |   5244   |  1210  |   2021-05-17   |   2021-05-24   |
-- |   91060   |   5235   |  1209  |   2021-05-15   |   2021-05-22   |
-- |   91061   |   5246   |  1172  |   2021-05-15   |   2021-05-22   |
-- |   91062   |   5254   |  1223  |   2021-05-15   |   2021-05-22   |
-- |   91063   |   5243   |  1223  |   2021-05-15   |   2021-05-22   |
-- |   91056   |   5254   |  1224  |   2021-05-10   |   2021-05-17   |
-- |   91057   |   5238   |  1224  |   2021-05-10   |   2021-05-17   |
-- |   91058   |   5252   |  1171  |   2021-05-10   |   2021-05-17   |
-- ... rows ommitted...
-- |   91001   |   5235   |  1165  |   2021-03-31   |   2021-04-14   |
-- |   91002   |   5238   |  1209  |   2021-03-31   |   2021-04-07   |
-- |   91003   |   5240   |  1160  |   2021-03-31   |   2021-04-14   |
-- |   91004   |   5237   |  1160  |   2021-03-31   |   2021-04-14   |
-- |   91005   |   5236   |  1202  |   2021-03-31   |   2021-04-07   |
-- +-----------+----------+--------+----------------+----------------+

/* YOUR SOLUTION HERE */
SELECT CHECK_NUM, 
	BOOK_NUM, 
    PAT_ID, 
    CHECK_OUT_DATE, 
    CHECK_DUE_DATE
FROM CHECKOUT
ORDER BY CHECK_OUT_DATE DESC, CHECK_NUM ASC;
