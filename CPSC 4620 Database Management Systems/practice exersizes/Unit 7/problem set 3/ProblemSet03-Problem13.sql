-- ## Problem 13
-- 
-- Write a query to display the book number, title, and year of all books published after 
-- 2015 and on the "Programming" subject sorted by book number.
-- 
-- +------------+----------------------------------------------+-------------+
-- |   BOOK_NUM | BOOK_TITLE                                   |   BOOK_YEAR |
-- |------------+----------------------------------------------+-------------|
-- |       5235 | Beginner's Guide to JAVA                     |        2018 |
-- |       5238 | Conceptual Programming                       |        2019 |
-- |       5239 | J++ in Mobile Apps                           |        2019 |
-- |       5240 | iOS Programming                              |        2019 |
-- |       5241 | JAVA First Steps                             |        2019 |
-- |       5247 | Shining Through the Cloud: Sun Programming   |        2020 |
-- |       5251 | Thoughts on Revitalizing Ruby                |        2020 |
-- |       5253 | Virtual Programming for Virtual Environments |        2020 |
-- |       5254 | Coding Style for Maintenance                 |        2021 |
-- +------------+----------------------------------------------+-------------+

/* YOUR SOLUTION HERE */
SELECT BOOK_NUM,
	BOOK_TITLE,
    BOOK_YEAR
FROM BOOK
WHERE BOOK_YEAR > 2015 AND BOOK_SUBJECT = 'Programming'
ORDER BY BOOK_NUM ASC;
