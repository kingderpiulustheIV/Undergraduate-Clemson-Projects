-- ## Problem 9
-- 
-- Write a query to display the book title, year, and subject for every book. 
-- Sort the results by book subject in ascending order, year in descending order, and then 
-- title in ascending order.
-- 
-- +-----------------------------------------------------------------------+-------------+----------------+
-- | BOOK_TITLE                                                            |   BOOK_YEAR | BOOK_SUBJECT   |
-- |-----------------------------------------------------------------------+-------------+----------------|
-- | Capture the Cloud                                                     |        2020 | Cloud          |
-- | Starlight Applications                                                |        2020 | Cloud          |
-- | Cloud-based Mobile Applications                                       |        2019 | Cloud          |
-- | Database in the Cloud                                                 |        2018 | Cloud          |
-- | Beyond the Database Veil                                              |        2020 | Database       |
-- | What You Always Wanted to Know About Database, But Were Afraid to Ask |        2020 | Database       |
-- | DATABASES in Theory                                                   |        2019 | Database       |
-- | Mastering the database environment                                    |        2019 | Database       |
-- | Reengineering the Middle Tier                                         |        2020 | Middleware     |
-- | The Golden Road to Platform independence                              |        2020 | Middleware     |
-- | C# in Middleware Deployment                                           |        2019 | Middleware     |
-- | Coding Style for Maintenance                                          |        2021 | Programming    |
-- | Shining Through the Cloud: Sun Programming                            |        2020 | Programming    |
-- | Thoughts on Revitalizing Ruby                                         |        2020 | Programming    |
-- | Virtual Programming for Virtual Environments                          |        2020 | Programming    |
-- | Conceptual Programming                                                |        2019 | Programming    |
-- | iOS Programming                                                       |        2019 | Programming    |
-- | J++ in Mobile Apps                                                    |        2019 | Programming    |
-- | JAVA First Steps                                                      |        2019 | Programming    |
-- | Beginner's Guide to JAVA                                              |        2018 | Programming    |
-- +-----------------------------------------------------------------------+-------------+----------------+

/* YOUR SOLUTION HERE */
SELECT BOOK_TITLE, 
	BOOK_YEAR, 
	BOOK_SUBJECT
FROM BOOK
ORDER BY BOOK_SUBJECT ASC, BOOK_YEAR DESC, BOOK_TITLE ASC;

