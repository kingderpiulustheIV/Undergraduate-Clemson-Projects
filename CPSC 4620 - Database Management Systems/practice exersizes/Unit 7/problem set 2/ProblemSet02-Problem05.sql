-- ## Problem 5
-- 
-- Write a query to display the customer code, balance, and total purchases for each customer. 
-- Total purchase is calculated by summing the line subtotals 
-- for each customer. Sort the results by customer code, and use aliases as shown below.
-- 
-- +----------+-------------+-----------------+
-- | CUS_CODE | CUS_BALANCE | Total Purchases |
-- +----------+-------------+-----------------+
-- |  10011   |    0.00     |     444.00      |
-- |  10012   |   345.86    |     153.85      |
-- |  10014   |    0.00     |     422.77      |
-- |  10015   |    0.00     |      34.97      |
-- |  10018   |   216.55    |      70.44      |
-- +----------+-------------+-----------------+
-- 
/* YOUR SOLUTION HERE */
SELECT c.CUS_CODE, 
       c.CUS_BALANCE, 
       ROUND(SUM(l.LINE_UNITS * l.LINE_PRICE), 2) AS "Total Purchases"
FROM CUSTOMER c
JOIN INVOICE i ON c.CUS_CODE = i.CUS_CODE
JOIN LINE l ON i.INV_NUMBER = l.INV_NUMBER
GROUP BY c.CUS_CODE, c.CUS_BALANCE
ORDER BY c.CUS_CODE;