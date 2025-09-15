-- ## Problem 10
-- 
-- Write a query to produce the number of invoices and the total purchase amounts by customer.
-- Use the results shown below as your guide. 
-- 
-- Note the results are sorted by customer code.
-- 
-- +----------+--------------------+--------------------------+
-- | CUS_CODE | Number of Invoices | Total Customer Purchases |
-- +----------+--------------------+--------------------------+
-- |  10011   |         3          |          444.00          |
-- |  10012   |         1          |          153.85          |
-- |  10014   |         2          |          422.77          |
-- |  10015   |         1          |          34.97           |
-- |  10018   |         1          |          70.44           |
-- +----------+--------------------+--------------------------+
-- 
/* YOUR SOLUTION HERE */
SELECT c.CUS_CODE,
	COUNT(DISTINCT i.INV_NUMBER) AS 'Number of Invoices',
	ROUND(SUM(l.LINE_UNITS * l.LINE_PRICE), 2) AS 'Total Customer Purchases'
FROM CUSTOMER c
JOIN INVOICE i ON c.CUS_CODE = i.CUS_CODE
JOIN LINE l on i.INV_NUMBER = l.INV_NUMBER
GROUP BY c.CUS_CODE
ORDER BY c.CUS_CODE;