-- ## Problem 8
-- 
-- Write a query to display the average number of days a book is kept during a checkout.
-- 
-- +---------------------+
-- |   Average Days Kept |
-- |---------------------|
-- |                4.44 |
-- +---------------------+
-- 
/* YOUR SOLUTION HERE */
SELECT ROUND(AVG(DATEDIFF(IFNULL(CHECK_IN_DATE, CURRENT_DATE), CHECK_OUT_DATE)), 2) AS "Average Days Kept"
FROM CHECKOUT
WHERE CHECK_IN_DATE IS NOT NULL;