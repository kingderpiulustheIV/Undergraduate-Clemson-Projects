-- ## Problem 6
-- 
-- Write a query to display the manager name, department name, department phone number, employee name,
-- customer name, invoice date, and invoice total for the department manager of the employee who made
-- a sale to a customer whose last name is Hagan on May 18, 2021.
-- 
-- Your results should look like this:
-- +-------------+-------------+-------------+--------------+-------------+-------------+--------------+--------------+------------+-------------+
-- | EMP_FNAME   | EMP_LNAME   | DEPT_NAME   | DEPT_PHONE   | EMP_FNAME   | EMP_LNAME   | CUST_FNAME   | CUST_LNAME   | INV_DATE   |   INV_TOTAL |
-- |-------------+-------------+-------------+--------------+-------------+-------------+--------------+--------------+------------+-------------|
-- | FRANKLYN    | STOVER      | SALES       | 555-2824     | THURMAN     | WILKINSON   | DARELL       | HAGAN        | 2021-05-18 |      315.04 |
-- +-------------+-------------+-------------+--------------+-------------+-------------+--------------+--------------+------------+-------------+
-- 

/* YOUR SOLUTION HERE */
SELECT m.EMP_FNAME,
    m.EMP_LNAME,
    d.DEPT_NAME,
    d.DEPT_PHONE,
    e.EMP_FNAME,
    e.EMP_LNAME,
    c.CUST_FNAME,
    c.CUST_LNAME,
    i.INV_DATE,
    i.INV_TOTAL
FROM LGINVOICE i
JOIN LGCUSTOMER c ON i.CUST_CODE = c.CUST_CODE
JOIN LGEMPLOYEE e ON i.EMPLOYEE_ID = e.EMP_NUM
JOIN LGDEPARTMENT d ON e.DEPT_NUM = d.DEPT_NUM
JOIN LGEMPLOYEE m ON d.EMP_NUM = m.EMP_NUM
WHERE c.CUST_LNAME = 'HAGAN' AND i.INV_DATE = '2021-05-18';