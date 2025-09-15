-- ## Problem 4
-- 
-- Write a query to display the largest average product price of any brand.
-- 
-- Your results should look like this:
-- +-------------------+
-- |   LARGEST AVERAGE |
-- |-------------------|
-- |             22.59 |
-- +-------------------+
-- 

/* YOUR SOLUTION HERE */
SELECT MAX(AVG_PRICE) AS 'LARGEST AVERAGE'
FROM 
    (SELECT 
        b.BRAND_ID,
        b.BRAND_NAME,
        ROUND(AVG(p.PROD_PRICE), 2) AS AVG_PRICE
     FROM LGBRAND b
     JOIN LGPRODUCT p ON b.BRAND_ID = p.BRAND_ID
     GROUP BY b.BRAND_ID, b.BRAND_NAME) AS BrandAverages;
