-- ## Problem 10
-- 
-- Write a query to display the author ID and the number of books written by that author. 
-- Sort the results in descending order by number of books, then in ascending order by author ID.
-- 
-- +-------+---------------+
-- | AU_ID | Books Written |
-- +-------+---------------+
-- |  262  |       3       |
-- |  460  |       3       |
-- |  185  |       2       |
-- |  229  |       2       |
-- |  251  |       2       |
-- |  383  |       2       |
-- |  394  |       2       |
-- |  559  |       2       |
-- |  218  |       1       |
-- |  273  |       1       |
-- |  284  |       1       |
-- |  438  |       1       |
-- |  581  |       1       |
-- |  592  |       1       |
-- |  603  |       1       |
-- +-------+---------------+

/* YOUR SOLUTION HERE */
-- Select the author ID and count of books written by each author
SELECT a.AU_ID, 
	COUNT(*) AS 'Books Written'
FROM AUTHOR a
JOIN WRITES w ON a.AU_ID = w.AU_ID
GROUP BY a.AU_ID
ORDER BY COUNT(*) DESC, a.AU_ID ASC;