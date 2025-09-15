-- ## Problem 12
-- 
-- LargeCo is planning a new promotion in Alabama (AL) and wants to know about the largest purchases
-- made by customers in that state. Write a query to display the customer code, customer first name,
-- last name, full address, invoice date, and invoice total of the largest purchase made by each
-- customer in Alabama. Be certain to include any customers in Alabama who have never made a purchase;
-- their invoice dates should be NULL and the invoice totals should display as 0. 
-- 
-- Sort the results by customer last name and then first name.
-- 
-- Your results should look like this:
-- +-------------+--------------+--------------+----------------------------+------------------+--------------+------------+------------+-------------------+
-- |   CUST_CODE | CUST_FNAME   | CUST_LNAME   | CUST_STREET                | CUST_CITY        | CUST_STATE   |   CUST_ZIP | INV_DATE   |   Largest Invoice |
-- |-------------+--------------+--------------+----------------------------+------------------+--------------+------------+------------+-------------------|
-- |         903 | ROBIN        | ADDISON      | 323 LORETTA PLACE          | Mobile           | AL           |      36693 | 2021-08-26 |            230.63 |
-- |         643 | NINA         | ALLEN        | 680 RED TALON DRIVE        | Robertsdale      | AL           |      36574 | 2021-06-21 |             11.99 |
-- |         295 | DORTHY       | AUSTIN       | 829 BIG BEND LOOP          | Diamond Shamrock | AL           |      36614 | 2021-04-24 |            589.75 |
-- |         393 | FOSTER       | BERNAL       | 1299 EAST 3RD AVENUE       | Birmingham       | AL           |      35280 |            |              0    |
-- |         853 | GAYLORD      | BOLTON       | 1069 LUGENE LANE           | Montgomery       | AL           |      36131 | 2021-11-25 |            372.68 |
-- |         925 | ALANA        | BOOKER       | 1874 I STREET              | Mccullough       | AL           |      36502 | 2021-12-12 |            208.85 |
-- |        1248 | LISA         | BRADY        | 491 LOWLAND AVENUE         | Daphne           | AL           |      36577 | 2021-12-05 |            414.47 |
-- |         538 | CHIQUITA     | CALDWELL     | 1501 BRIGGS COURT          | Normal           | AL           |      35762 | 2021-05-26 |            143.9  |
-- |          89 | MONICA       | CANTRELL     | 697 ADAK CIRCLE            | Loachapoka       | AL           |      36865 | 2021-03-31 |            516.58 |
-- |        1233 | NATHALIE     | CHURCH       | 1802 SNOWY OWL CIRCLE      | Napier Field     | AL           |      36303 | 2021-11-24 |            160.96 |
-- |         304 | GERTRUDE     | CONNORS      | 1042 PLEASANT DRIVE        | Georgiana        | AL           |      36033 | 2021-12-29 |            376.32 |
-- |        1131 | CARMA        | CORNETT      | 767 CHISANA WAY            | Killen           | AL           |      35645 | 2021-10-25 |            265.12 |
-- |        1407 | FELICIA      | CRUZ         | 643 TURNAGAIN PARKWAY      | Coalburg         | AL           |      35068 | 2022-01-06 |            387.93 |
-- ...
-- |         219 | CATHI        | WHITEHEAD    | 760 WOODCLIFF DRIVE        | Huntsville       | AL           |      35893 | 2021-11-19 |            273.23 |
-- |         152 | LISETTE      | WHITTAKER    | 339 NORTHPARK DRIVE        | Montgomery       | AL           |      36197 | 2021-04-23 |            418.83 |
-- +-------------+--------------+--------------+----------------------------+------------------+--------------+------------+------------+-------------------+
-- 

/* YOUR SOLUTION HERE */
SELECT c.CUST_CODE,
CUST_FNAME,
CUST_LNAME,
CUST_STREET,
CUST_CITY,
CUST_STATE,
CUST_ZIP,
INV_DATE,
INV_TOTAL AS "Largest Invoice"
FROM LGCUSTOMER c
JOIN LGINVOICE i
ON c.CUST_CODE = i.CUST_CODE
WHERE CUST_STATE = 'AL'
AND INV_TOTAL = (SELECT Max(INV_TOTAL)
FROM LGINVOICE i2
WHERE i2.CUST_CODE = c.CUST_CODE)
UNION
SELECT CUST_CODE,
CUST_FNAME,
CUST_LNAME,
CUST_STREET,
CUST_CITY,
CUST_STATE,
CUST_ZIP,
NULL, 0
FROM LGCUSTOMER
WHERE CUST_STATE = 'AL'
AND CUST_CODE NOT IN (SELECT CUST_CODE FROM LGINVOICE)
ORDER BY CUST_LNAME, CUST_FNAME
