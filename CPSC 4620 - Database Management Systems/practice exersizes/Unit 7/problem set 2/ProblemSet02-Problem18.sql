-- ## Problem 18
-- 
-- Find the total value of the product inventory. The results are shown below.
-- 
-- +--------------------------+
-- | Total Value of Inventory |
-- +--------------------------+
-- |         15084.52         |
-- +--------------------------+
-- 
/* YOUR SOLUTION HERE */
SELECT SUM(P_QOH * P_PRICE) AS "Total Value of Inventory"
FROM PRODUCT;