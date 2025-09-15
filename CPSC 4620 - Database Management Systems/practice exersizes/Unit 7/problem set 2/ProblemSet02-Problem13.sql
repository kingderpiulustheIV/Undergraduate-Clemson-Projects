-- ## Problem 13
-- 
-- Provide a summary of customer balance characteristics for customers who made purchases. 
-- Include the minimum balance, maximum balance, and average balance, as shown below.
-- 
-- +-----------------+-----------------+-----------------+
-- | Minimum Balance | Maximum Balance | Average Balance |
-- +-----------------+-----------------+-----------------+
-- |      0.00       |     345.86      |      70.30      |
-- +-----------------+-----------------+-----------------+
-- 
/* YOUR SOLUTION HERE */
SELECT MIN(CUS_BALANCE) AS 'Minimum Balance', 
MAX(CUS_BALANCE) AS 'Maximum Balance', 
ROUND(AVG(CUS_BALANCE),2) AS 'Average Balance' 
FROM CUSTOMER 
WHERE CUS_CODE IN (SELECT CUS_CODE FROM INVOICE);