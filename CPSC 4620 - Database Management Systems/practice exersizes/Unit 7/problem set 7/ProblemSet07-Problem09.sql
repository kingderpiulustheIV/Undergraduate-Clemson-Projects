-- ## Problem 9
-- 
-- Write a query to display the invoice number, line numbers, product SKUs, product descriptions, 
-- and brand ID for sales of sealer and top coat products of the same brand on the same invoice. 
-- Sort the results by invoice number in ascending order, first line number in ascending order, 
-- and then by second line number in descending order.
-- 
-- Your results should look like this:
-- +-----------+------------+------------+---------------------------------------------------------+------------+------------+--------------------------------------------------------------------------------------+------------+
-- |   INV_NUM |   LINE_NUM | PROD_SKU   | PROD_DESCRIPT                                           |   LINE_NUM | PROD_SKU   | PROD_DESCRIPT                                                                        |   BRAND_ID |
-- |-----------+------------+------------+---------------------------------------------------------+------------+------------+--------------------------------------------------------------------------------------+------------|
-- |       115 |          2 | 5140-RTG   | Fire Resistant Sealer, for Exterior Wood (ULC Approved) |          1 | 1203-AIS   | Fire Retardant Coating, Latex, Interior, Flat (ULC Approved)                         |         35 |
-- |       118 |          2 | 5140-RTG   | Fire Resistant Sealer, for Exterior Wood (ULC Approved) |          5 | 5046-TTC   | Aluminum Paint, Heat Resistant (Up to 427°C - 800°F)                                 |         35 |
-- |       135 |          5 | 3036-PCT   | Sealer, for Knots                                       |          2 | 1074-VVJ   | Light Industrial Coating, Exterior, Water Based (eggshell-like - MPI Gloss Level 3)  |         25 |
-- |       153 |          2 | 3701-YAW   | Sealer, Solvent Based, for Concrete Floors              |          1 | 3955-NWD   | Water Repellant, Clear (Not Paintable)                                               |         30 |
-- |       222 |          1 | 1336-FVM   | Alkyd, Sanding Sealer, Clear                            |          3 | 8199-YRF   | Varnish, Exterior, Water Based, (Satin-Like) MPI Gloss Level 4                       |         33 |
-- |       234 |          4 | 5728-ZPO   | Shop Coat, Quick Dry, for Interior Steel                |          3 | 9272-LTP   | Varnish, Marine Spar, Exterior, Gloss (MPI Gloss Level 6)                            |         27 |
-- |       234 |          4 | 5728-ZPO   | Shop Coat, Quick Dry, for Interior Steel                |          2 | 9126-PWF   | Latex, Recycled (Consolidated), Interior (MPI Gloss Level 3)                         |         27 |
-- |       243 |          1 | 4072-SWV   | Sealer, Solvent Based, for Concrete Floors              |          3 | 5653-RTU   | Aluminum Paint                                                                       |         23 |
-- |       287 |          1 | 8894-LUR   | Lacquer, Sanding Sealer, Clear                          |          5 | 9838-FUF   | Fire Retardant Top-Coat, Clear, Alkyd, Interior (ULC Approved)                       |         27 |
-- |       333 |          1 | 3701-YAW   | Sealer, Solvent Based, for Concrete Floors              |          6 | 2584-CIJ   | Stain, for Exterior Wood Decks                                                       |         30 |
-- |       333 |          1 | 3701-YAW   | Sealer, Solvent Based, for Concrete Floors              |          5 | 4784-SLU   | Lacquer, Clear, Flat                                                                 |         30 |
-- |       369 |          2 | 1403-TUY   | Sealer, Water Based, for Concrete Floors                |          1 | 8726-ZNM   | Floor Paint, Alkyd, Low Gloss                                                        |         29 |
-- ...
-- |      3399 |          5 | 1403-TUY   | Sealer, Water Based, for Concrete Floors                |          2 | 5496-MRA   | Bituminous Coating                                                                   |         29 |
-- |      3412 |          3 | 5140-RTG   | Fire Resistant Sealer, for Exterior Wood (ULC Approved) |          2 | 7804-ZVW   | Water Repellent, Clear (Paintable)                                                   |         35 |
-- +-----------+------------+------------+---------------------------------------------------------+------------+------------+--------------------------------------------------------------------------------------+------------+
-- 

/* YOUR SOLUTION HERE */
SELECT l.INV_NUM, 
	l.LINE_NUM, 
    p.PROD_SKU,
	p.PROD_DESCRIPT,
    l2.LINE_NUM,
    p2.PROD_SKU,
	p2.PROD_DESCRIPT, 
	p.Brand_ID
FROM (LGLINE AS l INNER JOIN LGPRODUCT AS p ON l.PROD_SKU = p.PROD_SKU)
INNER JOIN (LGLINE AS l2 INNER JOIN LGPRODUCT AS p2 ON l2.PROD_SKU = p2.PROD_SKU) ON l.INV_NUM = l2.INV_NUM
WHERE p.Brand_ID = p2.Brand_ID AND p.Prod_Category = 'Sealer' AND p2.Prod_Category = 'Top Coat'
ORDER BY l.INV_NUM ASC, l.LINE_NUM ASC, l2.LINE_NUM DESC;
