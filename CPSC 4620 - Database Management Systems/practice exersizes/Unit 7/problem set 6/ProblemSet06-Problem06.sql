-- ## Problem 06
-- 
-- Write a query to display the first name, last name, street, city, state, and zip code of any
-- customer who purchased a Foresters Best brand top coat between July 15, 2021, and July 31, 2021. 
-- If a customer purchased more than one such product, display the customer’s information only once 
-- in the output. Sort the output by state, last name, and then first name.
-- 
-- Your results should look like this:
-- +--------------+--------------+---------------------------+---------------+--------------+------------+
-- | CUST_FNAME   | CUST_LNAME   | CUST_STREET               | CUST_CITY     | CUST_STATE   |   CUST_ZIP |
-- |--------------+--------------+---------------------------+---------------+--------------+------------|
-- | LUPE         | SANTANA      | 1292 WEST 70TH PLACE      | Phenix City   | AL           |      36867 |
-- | HOLLIS       | STILES       | 1493 DOLLY MADISON CIRCLE | Snow Hill     | AL           |      36778 |
-- | LISETTE      | WHITTAKER    | 339 NORTHPARK DRIVE       | Montgomery    | AL           |      36197 |
-- | DEANDRE      | JAMISON      | 1571 HANES STREET         | Miami         | FL           |      33169 |
-- | CATHLEEN     | WHITMAN      | 1712 NORTHFIELD DRIVE     | Marshallville | GA           |      31057 |
-- ...
-- | RENATE       | LADD         | 652 LEWIS STREET          | Crystal City  | VA           |      22202 |
-- | MELONIE      | JIMENEZ      | 848 DOWNEY FINCH LANE     | East Monkton  | VT           |      05443 |
-- +--------------+--------------+---------------------------+---------------+--------------+------------+
-- 

/* YOUR SOLUTION HERE */
-- SELECT DISTINCT C.CUST_FNAME, C.CUST_LNAME, C.CUST_STREET, C.CUST_CITY, C.CUST_STATE, C.CUST_ZIP
-- FROM LGCUSTOMER C
-- JOIN LGINVOICE O ON C.CUST_NUM = O.CUST_NUM
-- JOIN LGLINE OL ON O.ORD_NUM = OL.ORD_NUM
-- JOIN LGPRODUCT P ON OL.PROD_NUM = P.PROD_NUM
-- JOIN LGBRAND B ON P.BRAND_ID = B.BRAND_ID
-- WHERE B.BRAND_NAME = 'Foresters Best'
-- AND P.PROD_TYPE = 'top coat'
-- AND O.ORD_DATE BETWEEN '2021-07-15' AND '2021-07-31'
-- ORDER BY C.CUST_STATE, C.CUST_LNAME, C.CUST_FNAME;
-- SELECT DISTINCT
--     CUST_FNAME,
--     CUST_LNAME,
--     CUST_STREET,
--     CUST_CITY,
--     CUST_STATE,
--     CUST_ZIP
-- FROM
--     LGCUSTOMER c
-- JOIN
--     LGINVOICE p ON c.customer_id = p.customer_id
-- WHERE
--     p.product_name = 'Foresters Best top coat'
--     AND p.purchase_date BETWEEN '2017-07-15' AND '2017-07-31'
-- ORDER BY
--     c.state,
--     c.last_name,
--     c.first_name;

SELECT DISTINCT
    c.CUST_FNAME,
    c.CUST_LNAME,
    c.CUST_STREET,
    c.CUST_CITY,
    c.CUST_STATE,
    c.CUST_ZIP
FROM
    LGCUSTOMER c
JOIN LGINVOICE i ON c.CUST_CODE = i.CUST_CODE
JOIN LGLINE l ON i.INV_NUM = l.INV_NUM
JOIN LGPRODUCT p ON l.PROD_SKU = p.PROD_SKU
JOIN LGBRAND b ON p.BRAND_ID = b.BRAND_ID
WHERE
    b.BRAND_NAME = 'FORESTERS BEST'
    AND p.PROD_CATEGORY = 'Top Coat'
    AND i.INV_DATE BETWEEN '2021-07-15' AND '2021-07-31'
ORDER BY c.CUST_STATE, c.CUST_LNAME, c.CUST_FNAME;
