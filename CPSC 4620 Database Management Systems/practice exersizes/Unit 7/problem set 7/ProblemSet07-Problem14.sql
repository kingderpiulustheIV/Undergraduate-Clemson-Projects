-- ## Problem 14
-- 
-- The purchasing manager is still concerned about the impact of price on sales. Write a query to
-- display the brand name, brand type, product SKU, product description, and price of any products
-- that are not a premium brand, but that cost more than the most expensive premium brand products.
-- 
-- Your results should look like this:
-- +--------------+--------------+------------+--------------------------------------------+--------------+
-- | BRAND_NAME   | BRAND_TYPE   | PROD_SKU   | PROD_DESCRIPT                              |   PROD_PRICE |
-- |--------------+--------------+------------+--------------------------------------------+--------------|
-- | LONG HAUL    | CONTRACTOR   | 1964-OUT   | Fire Resistant Top Coat, for Interior Wood |        78.49 |
-- +--------------+--------------+------------+--------------------------------------------+--------------+
-- 

/* YOUR SOLUTION HERE */
SELECT b.Brand_Name,
	b.Brand_Type,
	p.Prod_SKU,
	p.Prod_Descript,
	p.Prod_Price
FROM LGPRODUCT AS p
JOIN LGBRAND AS b ON p.Brand_ID = b.Brand_ID
WHERE b.Brand_Type != 'Premium' AND p.Prod_Price > (SELECT MAX(Prod_Price)
	FROM LGPRODUCT AS p2
	JOIN LGBRAND AS b2 ON p2.Brand_ID = b2.Brand_ID
	WHERE b2.Brand_Type = 'Premium');

