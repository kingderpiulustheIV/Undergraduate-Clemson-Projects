-- ## Problem 09
-- 
-- Write a query to display the number of products in each category that have a water base, 
-- sorted by category.
-- 
-- Your results should look like this:
-- +-----------------+---------------+
-- | PROD_CATEGORY   |   NUMPRODUCTS |
-- |-----------------+---------------|
-- | Cleaner         |             2 |
-- | Filler          |             2 |
-- | Primer          |            16 |
-- | Sealer          |             1 |
-- | Top Coat        |            81 |
-- +-----------------+---------------+
-- 

/* YOUR SOLUTION HERE */
SELECT PROD_CATEGORY,
    COUNT(*) AS NUMPRODUCTS
FROM LGPRODUCT
WHERE PROD_BASE = 'Water'
GROUP BY PROD_CATEGORY
ORDER BY PROD_CATEGORY;
