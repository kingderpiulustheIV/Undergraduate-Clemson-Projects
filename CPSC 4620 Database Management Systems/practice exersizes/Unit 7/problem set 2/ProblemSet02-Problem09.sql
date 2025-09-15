-- ## Problem 9
-- 
-- Write a query to show the invoices and invoice totals show below.
-- Sort the results by customer code and then by invoice number.
-- 
-- +----------+------------+---------------+
-- | CUS_CODE | INV_NUMBER | Invoice Total |
-- +----------+------------+---------------+
-- |  10011   |    1002    |     9.98      |
-- |  10011   |    1004    |     34.87     |
-- |  10011   |    1008    |    399.15     |
-- |  10012   |    1003    |    153.85     |
-- |  10014   |    1001    |     24.94     |
-- |  10014   |    1006    |    397.83     |
-- |  10015   |    1007    |     34.97     |
-- |  10018   |    1005    |     70.44     |
-- +----------+------------+---------------+
-- 
/* YOUR SOLUTION HERE */
SELECT i.CUS_CODE, 
	i.INV_NUMBER,
	ROUND(SUM(l.LINE_UNITS * l.LINE_PRICE), 2) AS 'Invoice Total'
FROM INVOICE i
JOIN LINE l ON i.INV_NUMBER = l.INV_NUMBER
GROUP BY i.INV_NUMBER
ORDER BY i.CUS_CODE;