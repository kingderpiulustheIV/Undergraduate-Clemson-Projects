-- ## Problem 11
-- 
-- Write a query to generate the total number of invoices, the invoice total for all of the 
-- invoices, the smallest of the customer purchase amounts, the largest of the customer purchase
-- amounts, and the average of all the customer purchase amounts. 
-- 
-- Your output must match the results show below.
-- 
-- +----------------+-------------+----------------------------+----------------------------+----------------------------+
-- | Total Invoices | Total Sales | Minimum Customer Purchases | Largest Customer Purchases | Average Customer Purchases |
-- +----------------+-------------+----------------------------+----------------------------+----------------------------+
-- |       8        |   1126.03   |           34.97            |           444.00           |           225.21           |
-- +----------------+-------------+----------------------------+----------------------------+----------------------------+
-- 
-- 
/* YOUR SOLUTION HERE */
SELECT COUNT(DISTINCT i.INV_NUMBER) AS "Total Invoices",
       ROUND(SUM(l.LINE_UNITS * l.LINE_PRICE), 2) AS "Total Sales",
       (SELECT MIN(CUS_TOTAL) 
        FROM (SELECT ROUND(SUM(l2.LINE_UNITS * l2.LINE_PRICE), 2) AS CUS_TOTAL
              FROM CUSTOMER c2
              JOIN INVOICE i2 ON c2.CUS_CODE = i2.CUS_CODE
              JOIN LINE l2 ON i2.INV_NUMBER = l2.INV_NUMBER
              GROUP BY c2.CUS_CODE) AS MIN_TOTAL) AS "Minimum Customer Purchases",
       (SELECT MAX(CUS_TOTAL) 
        FROM (SELECT ROUND(SUM(l3.LINE_UNITS * l3.LINE_PRICE), 2) AS CUS_TOTAL
              FROM CUSTOMER c3
              JOIN INVOICE i3 ON c3.CUS_CODE = i3.CUS_CODE
              JOIN LINE l3 ON i3.INV_NUMBER = l3.INV_NUMBER
              GROUP BY c3.CUS_CODE) AS MAX_TOTAL) AS "Largest Customer Purchases",
       (SELECT ROUND(AVG(CUS_TOTAL), 2)
        FROM (SELECT SUM(l4.LINE_UNITS * l4.LINE_PRICE) AS CUS_TOTAL
              FROM CUSTOMER c4
              JOIN INVOICE i4 ON c4.CUS_CODE = i4.CUS_CODE
              JOIN LINE l4 ON i4.INV_NUMBER = l4.INV_NUMBER
              GROUP BY c4.CUS_CODE) AS AVG_TOTAL) AS "Average Customer Purchases"
FROM INVOICE i
JOIN LINE l ON i.INV_NUMBER = l.INV_NUMBER;