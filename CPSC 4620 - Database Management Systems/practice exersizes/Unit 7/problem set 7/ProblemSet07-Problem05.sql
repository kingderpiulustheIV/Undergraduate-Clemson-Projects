-- ## Problem 5
-- 
-- Write a query to display the brand ID, brand name, brand type, and average price of products 
-- for the brand that has the largest average product price.
-- 
-- Your results should look like this:
-- +------------+--------------+--------------+------------+
-- |   BRAND_ID | BRAND_NAME   | BRAND_TYPE   |   AVGPRICE |
-- |------------+--------------+--------------+------------|
-- |         29 | BUSTERS      | VALUE        |      22.59 |
-- +------------+--------------+--------------+------------+
-- 

/* YOUR SOLUTION HERE */
SELECT 
b.BRAND_ID,
    b.BRAND_NAME,
    b.BRAND_TYPE,
    ROUND(AVG(p.PROD_PRICE), 2) AS AVGPRICE
FROM LGBRAND b
JOIN LGPRODUCT p ON b.BRAND_ID = p.BRAND_ID
GROUP BY b.BRAND_ID, b.BRAND_NAME, b.BRAND_TYPE
HAVING AVG(p.PROD_PRICE) = (
	SELECT MAX(avg_price)
    FROM(SELECT 
		BRAND_ID, 
		AVG(PROD_PRICE) AS avg_price
		FROM LGPRODUCT
		GROUP BY BRAND_ID) AS brand_averages)
ORDER BY AVGPRICE DESC;