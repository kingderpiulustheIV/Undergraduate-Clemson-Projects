-- ## Problem 9
-- 
-- Write a query to display the patron ID and the average number of days that patron keeps 
-- books during a checkout. Limit the results to only patrons who have at least three checkouts. 
-- Sort the results in descending order by the average days the book is kept, and then in 
-- ascending order by patron ID.
-- 
-- +----------+---------------------+
-- |   PAT_ID |   Average Days Kept |
-- |----------+---------------------|
-- |     1160 |                7    |
-- |     1185 |                6.67 |
-- |     1165 |                5.67 |
-- |     1207 |                5.5  |
-- |     1209 |                5.33 |
-- |     1172 |                4.5  |
-- |     1183 |                4.33 |
-- |     1171 |                3.67 |
-- |     1181 |                3.67 |
-- |     1161 |                3.33 |
-- |     1210 |                2.33 |
-- |     1229 |                2    |
-- +----------+---------------------+
-- 
/* YOUR SOLUTION HERE */
SELECT PAT_ID, 
	ROUND(AVG(DATEDIFF(CHECK_IN_DATE, CHECK_OUT_DATE)), 2) AS 'Average Days Kept'
FROM CHECKOUT
GROUP BY PAT_ID
HAVING COUNT(*) >= 3
ORDER BY AVG(DATEDIFF(CHECK_IN_DATE, CHECK_OUT_DATE)) DESC, PAT_ID ASC;