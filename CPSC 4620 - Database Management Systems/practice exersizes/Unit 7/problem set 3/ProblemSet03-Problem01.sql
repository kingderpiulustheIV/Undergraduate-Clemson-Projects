-- ## Problem 1
-- 
-- Write a query that displays the book title, cost and year of publication for every book in
-- the system. Sort the results by book title. 
-- 
-- +-----------------------------------------------------------------------+-------------+-------------+
-- | BOOK_TITLE                                                            |   BOOK_COST |   BOOK_YEAR |
-- |-----------------------------------------------------------------------+-------------+-------------|
-- | Beginner's Guide to JAVA                                              |       59.95 |        2018 |
-- | Beyond the Database Veil                                              |       69.95 |        2020 |
-- | C# in Middleware Deployment                                           |       59.95 |        2019 |
-- | Capture the Cloud                                                     |       69.95 |        2020 |
-- | Cloud-based Mobile Applications                                       |       69.95 |        2019 |
-- | Coding Style for Maintenance                                          |       49.95 |        2021 |
-- | Conceptual Programming                                                |       59.95 |        2019 |
-- | Database in the Cloud                                                 |       79.95 |        2018 |
-- | DATABASES in Theory                                                   |      129.95 |        2019 |
-- | iOS Programming                                                       |       79.95 |        2019 |
-- | J++ in Mobile Apps                                                    |       49.95 |        2019 |
-- | JAVA First Steps                                                      |       49.95 |        2019 |
-- | Mastering the database environment                                    |       89.95 |        2019 |
-- | Reengineering the Middle Tier                                         |       89.95 |        2020 |
-- | Shining Through the Cloud: Sun Programming                            |      109.95 |        2020 |
-- | Starlight Applications                                                |       69.95 |        2020 |
-- | The Golden Road to Platform independence                              |      119.95 |        2020 |
-- | Thoughts on Revitalizing Ruby                                         |       59.95 |        2020 |
-- | Virtual Programming for Virtual Environments                          |       79.95 |        2020 |
-- | What You Always Wanted to Know About Database, But Were Afraid to Ask |       49.95 |        2020 |
-- +-----------------------------------------------------------------------+-------------+-------------+
--

/* YOUR SOLUTION HERE */
SELECT BOOK_TITLE,
BOOK_COST, BOOK_YEAR
FROM BOOK
ORDER BY BOOK_TITLE ASC;