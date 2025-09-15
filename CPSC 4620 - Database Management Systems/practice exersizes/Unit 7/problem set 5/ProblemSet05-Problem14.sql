-- ## Problem 14
-- 
-- Write a query to display the lowest average cost of books within a subject and the highest 
-- average cost of books within a subject.
-- 
-- +-----------------+------------------+
-- | Lowest Avg Cost | Highest Avg Cost |
-- +-----------------+------------------+
-- |      66.62      |      89.95       |
-- +-----------------+------------------+
-- 
/* YOUR SOLUTION HERE */
SELECT 
    ROUND(MIN(avg_cost), 2) AS "Lowest Avg Cost",
    ROUND(MAX(avg_cost), 2) AS "Highest Avg Cost"
FROM (
    SELECT 
        B.BOOK_SUBJECT,
        AVG(B.BOOK_COST) AS avg_cost
    FROM BOOK B
    GROUP BY B.BOOK_SUBJECT
) AS subject_costs;