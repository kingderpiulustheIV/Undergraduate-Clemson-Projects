-- ## Problem 10
-- 
-- The Binder Prime Company wants to recognize the employee who sold the most of its products during
--  a specified period. Write a query to display the employee number, employee first name, employee
-- last name, email address, and total units sold for the employee who sold the most Binder Prime
-- brand products between November 1, 2021, and December 5, 2021. 
-- 
-- If there is a tie for most units sold, sort the output by employee last name.
-- 
-- Your results should look like this:
-- +-----------+-------------+-------------+--------------------------+---------+
-- |   EMP_NUM | EMP_FNAME   | EMP_LNAME   | EMP_EMAIL                |   TOTAL |
-- |-----------+-------------+-------------+--------------------------+---------|
-- |     84134 | ROSALIE     | GARLAND     | G.ROSALI98@LGCOMPANY.COM |      23 |
-- |     83850 | RUSTY       | MILES       | M.RUSTY95@LGCOMPANY.COM  |      23 |
-- +-----------+-------------+-------------+--------------------------+---------+
-- 

/* YOUR SOLUTION HERE */
SELECT e.EMP_NUM, 
	e.EMP_FNAME, 
	e.EMP_LNAME,
	e.EMP_EMAIL, 
	sum(l.LINE_QTY) AS TOTAL 
FROM LGEMPLOYEE e, LGINVOICE i, LGLINE l, LGPRODUCT p, LGBRAND b 
WHERE b.BRAND_ID = p.BRAND_ID AND p.PROD_SKU = l.PROD_SKU AND l.INV_NUM = i.INV_NUM   
AND i.EMPLOYEE_ID = e.EMP_NUM AND b.BRAND_NAME = "Binder Prime" AND INV_DATE between '2021-11-01' AND '2021-12-05' 
GROUP BY EMP_NUM ORDER BY TOTAL DESC, EMP_LNAME LIMIT 2;
