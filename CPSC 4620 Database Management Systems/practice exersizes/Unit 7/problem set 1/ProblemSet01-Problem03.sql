-- ## Problem 3
-- 
-- Write the SQL code that will produce the same information that was shown in Problem 2, 
-- but sorted by the employee’s last name. 
-- 
-- Display the results as shown below:
-- 
--    +--------------+------------+--------------+------------+-----------+-------------+----------+---------------------+--------------+
--    |  PROJ_NAME   | PROJ_VALUE | PROJ_BALANCE | EMP_LNAME  | EMP_FNAME | EMP_INITIAL | JOB_CODE |   JOB_DESCRIPTION   | JOB_CHG_HOUR |
--    +--------------+------------+--------------+------------+-----------+-------------+----------+---------------------+--------------+
--    |  Starflight  | 2650500.00 |  2309880.00  |   Alonzo   |   Maria   |      D      |   500    |     Programmer      |    35.75     |
--    |  Evergreen   | 1453500.00 |  1002350.00  |  Arbough   |   June    |      E      |   503    | Electrical Engineer |    84.50     |
--    | Rolling Tide | 805000.00  |  500345.20   |   Senior   |   David   |      H      |   501    |   Systems Analyst   |    96.75     |
--    |  Amber Wave  | 3500500.00 |  2110346.00  | Washington |   Ralph   |      B      |   501    |   Systems Analyst   |    96.75     |
--    +--------------+------------+--------------+------------+-----------+-------------+----------+---------------------+--------------+

/* YOUR SOLUTION HERE */
SELECT 
	p.PROJ_NAME, p.PROJ_VALUE, p.PROJ_BALANCE, e.EMP_LNAME, e.EMP_FNAME, e.EMP_INITIAL, j.JOB_CODE, j.JOB_DESCRIPTION, j.JOB_CHG_HOUR
FROM 
	PROJECT p
JOIN EMPLOYEE e ON p.EMP_NUM = e.EMP_NUM
JOIN JOB j ON e.JOB_CODE = j.JOB_CODE
ORDER BY e.EMP_LNAME;