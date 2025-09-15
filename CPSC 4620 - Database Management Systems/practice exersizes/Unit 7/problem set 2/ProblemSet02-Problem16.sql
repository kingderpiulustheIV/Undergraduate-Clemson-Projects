-- ## Problem 16
-- 
-- Write a query to find the customer balance summary for all customers who have not made 
-- purchases during the current invoicing period. 
-- 
-- The results are shown here.
-- 
-- +---------------+-----------------+-----------------+-----------------+
-- | Total Balance | Minimum Balance | Maximum Balance | Average Balance |
-- +---------------+-----------------+-----------------+-----------------+
-- |    1526.87    |      0.00       |     768.93      |     305.37      |
-- +---------------+-----------------+-----------------+-----------------+
-- 
-- 
/* YOUR SOLUTION HERE */
SELECT SUM(c.CUS_BALANCE) AS "Total Balance",
       MIN(c.CUS_BALANCE) AS "Minimum Balance",
       MAX(c.CUS_BALANCE) AS "Maximum Balance",
       ROUND(AVG(c.CUS_BALANCE), 2) AS "Average Balance"
FROM CUSTOMER c
WHERE c.CUS_CODE NOT IN (SELECT DISTINCT i.CUS_CODE FROM INVOICE i);