-- ## Problem 8

-- Write the SQL to generate the total hours worked and the total charges made by all employees. 
-- 
-- The results are shown here:
-- 
--    +------------------------+-------------------------+
--    | SumOfSumOfASSIGN_HOURS | SumOfSumOfASSIGN_CHARGE |
--    +------------------------+-------------------------+
--    |          90.6          |         7612.64         |
--    +------------------------+-------------------------+

/* YOUR SOLUTION HERE */
SELECT 
 ROUND(SUM(ASSIGN_HOURS), 1) AS SumOfSumOfASSIGN_HOURS,
 SUM(ASSIGN_CHARGE) AS SumOfSumOfASSIGN_CHARGE
FROM ASSIGNMENT;
