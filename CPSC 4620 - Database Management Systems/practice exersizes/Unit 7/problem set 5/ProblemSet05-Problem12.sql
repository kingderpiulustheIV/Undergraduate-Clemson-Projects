-- ## Problem 12
-- 
-- Write a query to display the book number, title, subject, average cost of books within that 
-- subject (AVGCOST), and the difference between each book’s cost and the average cost of books 
-- in that subject. Sort the results by book title.
-- 
-- +------------+-----------------------------------------------------------------------+----------------+-----------+--------------+
-- |   BOOK_NUM | BOOK_TITLE                                                            | BOOK_SUBJECT   |   AVGCOST |   DIFFERENCE |
-- |------------+-----------------------------------------------------------------------+----------------+-----------+--------------|
-- |       5235 | Beginner's Guide to JAVA                                              | Programming    |     66.62 |        -6.67 |
-- |       5252 | Beyond the Database Veil                                              | Database       |     84.95 |       -15    |
-- |       5242 | C# in Middleware Deployment                                           | Middleware     |     89.95 |       -30    |
-- |       5246 | Capture the Cloud                                                     | Cloud          |     72.45 |        -2.5  |
-- |       5244 | Cloud-based Mobile Applications                                       | Cloud          |     72.45 |        -2.5  |
-- |       5254 | Coding Style for Maintenance                                          | Programming    |     66.62 |       -16.67 |
-- |       5238 | Conceptual Programming                                                | Programming    |     66.62 |        -6.67 |
-- |       5236 | Database in the Cloud                                                 | Cloud          |     72.45 |         7.5  |
-- |       5243 | DATABASES in Theory                                                   | Database       |     84.95 |        45    |
-- |       5240 | iOS Programming                                                       | Programming    |     66.62 |        13.33 |
-- |       5239 | J++ in Mobile Apps                                                    | Programming    |     66.62 |       -16.67 |
-- |       5241 | JAVA First Steps                                                      | Programming    |     66.62 |       -16.67 |
-- |       5237 | Mastering the database environment                                    | Database       |     84.95 |         5    |
-- |       5250 | Reengineering the Middle Tier                                         | Middleware     |     89.95 |         0    |
-- |       5247 | Shining Through the Cloud: Sun Programming                            | Programming    |     66.62 |        43.33 |
-- |       5249 | Starlight Applications                                                | Cloud          |     72.45 |        -2.5  |
-- |       5245 | The Golden Road to Platform independence                              | Middleware     |     89.95 |        30    |
-- |       5251 | Thoughts on Revitalizing Ruby                                         | Programming    |     66.62 |        -6.67 |
-- |       5253 | Virtual Programming for Virtual Environments                          | Programming    |     66.62 |        13.33 |
-- |       5248 | What You Always Wanted to Know About Database, But Were Afraid to Ask | Database       |     84.95 |       -35    |
-- +------------+-----------------------------------------------------------------------+----------------+-----------+--------------+
-- 

/* YOUR SOLUTION HERE */
SELECT
  BOOK_NUM,
  BOOK_TITLE,
  BOOK_SUBJECT,
  ROUND(AVG(BOOK_COST) OVER (PARTITION BY BOOK_SUBJECT), 2) AS "AVGCOST",
  ROUND(BOOK_COST - AVG(BOOK_COST) OVER (PARTITION BY BOOK_SUBJECT), 2) AS "DIFFERENCE"
FROM BOOK
GROUP BY BOOK_NUM, BOOK_TITLE, BOOK_SUBJECT, BOOK_COST
ORDER BY BOOK_TITLE;
