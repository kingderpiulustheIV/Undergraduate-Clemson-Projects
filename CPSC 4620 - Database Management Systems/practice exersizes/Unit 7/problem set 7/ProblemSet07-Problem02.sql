-- ## Problem 2
-- 
-- Write a query to display the vendor ID, vendor name, brand name, and number of products of each
-- brand supplied by each vendor. Sort the output by vendor name and then by brand name.
-- 
-- Your results should look like this:
-- -----------+-----------------------------------+-------------------+---------------+
-- |   VEND_ID | VEND_NAME                         | BRAND_NAME        |   NUMPRODUCTS |
-- |-----------+-----------------------------------+-------------------+---------------|
-- |         8 | Baltimore Paints Consolidated     | BINDER PRIME      |            27 |
-- |         8 | Baltimore Paints Consolidated     | FORESTERS BEST    |             1 |
-- |         8 | Baltimore Paints Consolidated     | HOME COMFORT      |            36 |
-- |         8 | Baltimore Paints Consolidated     | LE MODE           |             3 |
-- |         8 | Baltimore Paints Consolidated     | LONG HAUL         |             3 |
-- |         8 | Baltimore Paints Consolidated     | VALU-MATTE        |             1 |
-- |        13 | Boykin Chemical Workshop          | BUSTERS           |             1 |
-- |        13 | Boykin Chemical Workshop          | LE MODE           |             2 |
-- |        13 | Boykin Chemical Workshop          | LONG HAUL         |             2 |
-- |        13 | Boykin Chemical Workshop          | OLDE TYME QUALITY |             2 |
-- |        13 | Boykin Chemical Workshop          | STUTTENFURST      |             1 |
-- |        13 | Boykin Chemical Workshop          | VALU-MATTE        |             1 |
-- |         9 | Donahue Solubles of West Virginia | BINDER PRIME      |            27 |
-- |         9 | Donahue Solubles of West Virginia | BUSTERS           |             1 |
-- |         9 | Donahue Solubles of West Virginia | HOME COMFORT      |            36 |
-- |         9 | Donahue Solubles of West Virginia | LE MODE           |             1 |
-- ...
-- |         2 | Warren Paints Consolidated        | STUTTENFURST      |             1 |
-- |         2 | Warren Paints Consolidated        | VALU-MATTE        |             2 |
-- |        14 | Watkins Wholesale Warehouse       | BINDER PRIME      |            27 |
-- |        14 | Watkins Wholesale Warehouse       | BUSTERS           |             1 |
-- |        14 | Watkins Wholesale Warehouse       | HOME COMFORT      |            36 |
-- |        14 | Watkins Wholesale Warehouse       | LE MODE           |             2 |
-- |        14 | Watkins Wholesale Warehouse       | LONG HAUL         |             2 |
-- |        14 | Watkins Wholesale Warehouse       | STUTTENFURST      |             2 |
-- |        14 | Watkins Wholesale Warehouse       | VALU-MATTE        |             3 |
-- +-----------+-----------------------------------+-------------------+---------------+
-- 

/* YOUR SOLUTION HERE */
SELECT v.VEND_ID,
    v.VEND_NAME,
    b.BRAND_NAME,
    COUNT(DISTINCT p.PROD_SKU) AS NUMPRODUCTS
FROM LGVENDOR v
JOIN LGSUPPLIES s ON v.VEND_ID = s.VEND_ID
JOIN LGPRODUCT p ON s.PROD_SKU = p.PROD_SKU
JOIN LGBRAND b ON p.BRAND_ID = b.BRAND_ID
GROUP BY v.VEND_ID, v.VEND_NAME, b.BRAND_NAME
ORDER BY v.VEND_NAME, b.BRAND_NAME;

