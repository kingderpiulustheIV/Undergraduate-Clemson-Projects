-- ## Problem 5
-- 
-- Write a query to display the different years in which books have been published. 
-- Include each year only once and sort the results by year.
-- 
-- +-----------+
-- | BOOK_YEAR |
-- +-----------+
-- |   2018    |
-- |   2019    |
-- |   2020    |
-- |   2021    |
-- +-----------+

/* YOUR SOLUTION HERE */

SELECT DISTINCT BOOK_YEAR
FROM BOOK
ORDER BY BOOK_YEAR ASC;