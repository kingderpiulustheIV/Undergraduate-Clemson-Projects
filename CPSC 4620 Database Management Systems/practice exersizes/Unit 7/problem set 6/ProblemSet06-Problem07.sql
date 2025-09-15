-- ## Problem 07
-- 
-- Write a query to display the employee number, last name, email address, title, and department name
-- of each employee whose job title ends in the word “ASSOCIATE.” Sort the output by department name,
-- employee title, and employee number.
-- 
-- Your results should look like this:
-- +-----------+---------------+--------------------------+------------------+------------------+
-- |   EMP_NUM | EMP_LNAME     | EMP_EMAIL                | EMP_TITLE        | DEPT_NAME        |
-- |-----------+---------------+--------------------------+------------------+------------------|
-- |     83378 | DUNHAM        | F.DUNHAM5@LGCOMPANY.COM  | ASSOCIATE        | ACCOUNTING       |
-- |     83517 | ALBRIGHT      | SO.ALBRI96@LGCOMPANY.COM | ASSOCIATE        | ACCOUNTING       |
-- |     83583 | ROLLINS       | M.ROLLIN99@LGCOMPANY.COM | ASSOCIATE        | ACCOUNTING       |
-- |     83661 | FINN          | D.FINN87@LGCOMPANY.COM   | ASSOCIATE        | ACCOUNTING       |
-- |     84386 | RIVERA        | D.RIVERA76@LGCOMPANY.COM | ASSOCIATE        | ACCOUNTING       |
-- |     84526 | LASSITER      | F.LASSIT8@LGCOMPANY.COM  | ASSOCIATE        | ACCOUNTING       |
-- |     83341 | CORTEZ        | C.CORTEZ85@LGCOMPANY.COM | ASSOCIATE        | CUSTOMER SERVICE |
-- ...
-- |     84543 | GOODMAN       | K.GOODMA96@LGCOMPANY.COM | ASSOCIATE        | WAREHOUSE        |
-- |     84545 | BURKETT       | I.BURKET9@LGCOMPANY.COM  | ASSOCIATE        | WAREHOUSE        |
-- +-----------+---------------+--------------------------+------------------+------------------+
-- 

/* YOUR SOLUTION HERE */
SELECT e.EMP_NUM,
    e.EMP_LNAME,
    e.EMP_EMAIL,
    e.EMP_TITLE,
    d.DEPT_NAME
FROM  LGEMPLOYEE e
JOIN LGDEPARTMENT d ON e.DEPT_NUM = d.DEPT_NUM
WHERE  e.EMP_TITLE LIKE '%ASSOCIATE'
ORDER BY d.DEPT_NAME, e.EMP_TITLE, e.EMP_NUM;
