-- ## Problem 03
-- 
-- Write a query to display the first name, last name, and email address of employees hired from 
-- May 1, 2011, to December 31, 2012. Sort the output by last name and then by first name.
-- 
-- Your results should look like this:
-- +-------------+-------------+-------------------------+
-- | EMP_FNAME   | EMP_LNAME   | EMP_EMAIL               |
-- |-------------+-------------+-------------------------|
-- | DOUG        | CAUDILL     | C.DOUG0@LGCOMPANY.COM   |
-- | OLIVIA      | DELEON      | O.DELEON0@LGCOMPANY.COM |
-- | GALE        | DEWITT      | G.DEWITT1@LGCOMPANY.COM |
-- | FRANCESCO   | ELLIOT      | F.ELLIOT1@LGCOMPANY.COM |
-- | PRECIOUS    | FARMER      | P.FARMER1@LGCOMPANY.COM |
-- | JANNETTE    | HARRISON    | J.HARRIS0@LGCOMPANY.COM |
-- | HAL         | HINKLE      | H.HINKLE0@LGCOMPANY.COM |
-- | WILLARD     | LONG        | W.LONG1@LGCOMPANY.COM   |
-- | YONG        | MCDONALD    | Y.MCDONA1@LGCOMPANY.COM |
-- | DENNA       | MCGRAW      | D.MCGRAW1@LGCOMPANY.COM |
-- | RASHIDA     | MCNEAL      | R.MCNEAL0@LGCOMPANY.COM |
-- | GIL         | OSBORN      | G.OSBORN0@LGCOMPANY.COM |
-- | TONJA       | PERKINS     | T.PERKIN0@LGCOMPANY.COM |
-- | STELLA      | PHELPS      | S.PHELPS1@LGCOMPANY.COM |
-- | MITCHELL    | ROLAND      | M.ROLAND0@LGCOMPANY.COM |
-- | DARRON      | TILLEY      | D.TILLEY1@LGCOMPANY.COM |
-- | ALEJANDRA   | WHALEY      | W.ALEJAN0@LGCOMPANY.COM |
-- | ALYSON      | WILLARD     | A.WILLAR1@LGCOMPANY.COM |
-- +-------------+-------------+-------------------------+
-- 

/* YOUR SOLUTION HERE */
SELECT EMP_FNAME,
	EMP_LNAME,
    EMP_EMAIL
FROM LGEMPLOYEE
WHERE EMP_HIREDATE BETWEEN '2011-05-01' AND '2012-12-31'
ORDER BY EMP_LNAME, EMP_FNAME;
