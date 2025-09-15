-- ## Problem 8
-- 
-- Create a query to produce the total purchase per invoice, generating the results shown 
-- below , sorted by invoice number. The invoice total is the sum of the product purchases 
-- in the LINE that corresponds to the INVOICE.
-- 
-- +------------+---------------+
-- | INV_NUMBER | Invoice Total |
-- +------------+---------------+
-- |    1001    |     24.94     |
-- |    1002    |     9.98      |
-- |    1003    |    153.85     |
-- |    1004    |     34.87     |
-- |    1005    |     70.44     |
-- |    1006    |    397.83     |
-- |    1007    |     34.97     |
-- |    1008    |    399.15     |
-- +------------+---------------+
-- 
/* YOUR SOLUTION HERE */
SELECT i.INV_NUMBER,
	ROUND(SUM(l.LINE_UNITS * l.LINE_PRICE), 2) AS 'Invoice Total'
FROM INVOICE i
JOIN LINE l ON i.INV_NUMBER = l.INV_NUMBER
GROUP BY i.INV_NUMBER
ORDER BY i.INV_NUMBER;