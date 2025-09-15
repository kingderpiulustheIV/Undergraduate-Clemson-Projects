-- ## Problem 7
-- 
-- Write a query to display the book number, title, and cost of each book sorted by book number.
-- 
-- 
-- +------------+-----------------------------------------------------------------------+-------------+
-- |   BOOK_NUM | BOOK_TITLE                                                            |   BOOK_COST |
-- |------------+-----------------------------------------------------------------------+-------------|
-- |       5235 | Beginner's Guide to JAVA                                              |       59.95 |
-- |       5236 | Database in the Cloud                                                 |       79.95 |
-- |       5237 | Mastering the database environment                                    |       89.95 |
-- |       5238 | Conceptual Programming                                                |       59.95 |
-- |       5239 | J++ in Mobile Apps                                                    |       49.95 |
-- |       5240 | iOS Programming                                                       |       79.95 |
-- |       5241 | JAVA First Steps                                                      |       49.95 |
-- |       5242 | C# in Middleware Deployment                                           |       59.95 |
-- |       5243 | DATABASES in Theory                                                   |      129.95 |
-- |       5244 | Cloud-based Mobile Applications                                       |       69.95 |
-- |       5245 | The Golden Road to Platform independence                              |      119.95 |
-- |       5246 | Capture the Cloud                                                     |       69.95 |
-- |       5247 | Shining Through the Cloud: Sun Programming                            |      109.95 |
-- |       5248 | What You Always Wanted to Know About Database, But Were Afraid to Ask |       49.95 |
-- |       5249 | Starlight Applications                                                |       69.95 |
-- |       5250 | Reengineering the Middle Tier                                         |       89.95 |
-- |       5251 | Thoughts on Revitalizing Ruby                                         |       59.95 |
-- |       5252 | Beyond the Database Veil                                              |       69.95 |
-- |       5253 | Virtual Programming for Virtual Environments                          |       79.95 |
-- |       5254 | Coding Style for Maintenance                                          |       49.95 |
-- +------------+-----------------------------------------------------------------------+-------------+

/* YOUR SOLUTION HERE */
SELECT  BOOK_NUM, BOOK_TITLE, BOOK_COST
FROM BOOK
ORDER BY BOOK_NUM ASC;
