-- ## Problem 08
-- 
-- Write a query to display a brand name and the number of products of that brand that are in 
-- the database. Sort the output by the brand name.
-- 
-- Your results should look like this:
-- +-------------------+---------------+
-- | BRAND_NAME        |   NUMPRODUCTS |
-- |-------------------+---------------|
-- | BINDER PRIME      |            27 |
-- | BUSTERS           |            25 |
-- | FORESTERS BEST    |            15 |
-- | HOME COMFORT      |            36 |
-- | LE MODE           |            36 |
-- | LONG HAUL         |            41 |
-- | OLDE TYME QUALITY |            27 |
-- | STUTTENFURST      |            27 |
-- | VALU-MATTE        |            18 |
-- +-------------------+---------------+
-- 

/* YOUR SOLUTION HERE */
SELECT 
    b.BRAND_NAME,
    COUNT(p.PROD_SKU) AS NUMPRODUCTS
FROM LGBRAND b
JOIN  LGPRODUCT p ON b.BRAND_ID = p.BRAND_ID
GROUP BY b.BRAND_NAME
ORDER BY b.BRAND_NAME;
