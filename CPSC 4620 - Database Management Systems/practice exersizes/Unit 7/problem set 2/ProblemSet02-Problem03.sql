-- ## Problem 3
-- 
-- Generate a listing of all purchases made by the customers, using the output shown 
-- below as your guide. Sort the results by customer code, invoice number, and product description.
-- 
-- +----------+------------+---------------------+-------------------------------------+------------+------------+
-- | CUS_CODE | INV_NUMBER |      INV_DATE       |             P_DESCRIPT              | LINE_UNITS | LINE_PRICE |
-- +----------+------------+---------------------+-------------------------------------+------------+------------+
-- |  10011   |    1002    | 2022-01-16 00:00:00 |     Rat-tail file, 1/8-in. fine     |    2.00    |    4.99    |
-- |  10011   |    1004    | 2022-01-17 00:00:00 |             Claw hammer             |    2.00    |    9.95    |
-- |  10011   |    1004    | 2022-01-17 00:00:00 |     Rat-tail file, 1/8-in. fine     |    3.00    |    4.99    |
-- |  10011   |    1008    | 2022-01-17 00:00:00 |             Claw hammer             |    1.00    |    9.95    |
-- |  10011   |    1008    | 2022-01-17 00:00:00 |       PVC pipe, 3.5-in., 8-ft       |    5.00    |    5.87    |
-- |  10011   |    1008    | 2022-01-17 00:00:00 | Steel matting, 4'x8'x1/6", .5" mesh |    3.00    |   119.95   |
-- |  10012   |    1003    | 2022-01-16 00:00:00 |       7.25-in. pwr. saw blade       |    5.00    |   14.99    |
-- |  10012   |    1003    | 2022-01-16 00:00:00 |     B&D cordless drill, 1/2-in.     |    1.00    |   38.95    |
-- |  10012   |    1003    | 2022-01-16 00:00:00 |      Hrd. cloth, 1/4-in., 2x50      |    1.00    |   39.95    |
-- |  10014   |    1001    | 2022-01-16 00:00:00 |       7.25-in. pwr. saw blade       |    1.00    |   14.99    |
-- |  10014   |    1001    | 2022-01-16 00:00:00 |             Claw hammer             |    1.00    |    9.95    |
-- |  10014   |    1006    | 2022-01-17 00:00:00 |      1.25-in. metal screw, 25       |    3.00    |    6.99    |
-- |  10014   |    1006    | 2022-01-17 00:00:00 |      B&D jigsaw, 12-in. blade       |    1.00    |   109.92   |
-- |  10014   |    1006    | 2022-01-17 00:00:00 |             Claw hammer             |    1.00    |    9.95    |
-- |  10014   |    1006    | 2022-01-17 00:00:00 |       Hicut chain saw, 16 in.       |    1.00    |   256.99   |
-- |  10015   |    1007    | 2022-01-17 00:00:00 |       7.25-in. pwr. saw blade       |    2.00    |   14.99    |
-- |  10015   |    1007    | 2022-01-17 00:00:00 |     Rat-tail file, 1/8-in. fine     |    1.00    |    4.99    |
-- |  10018   |    1005    | 2022-01-17 00:00:00 |       PVC pipe, 3.5-in., 8-ft       |   12.00    |    5.87    |
-- +----------+------------+---------------------+-------------------------------------+------------+------------+
-- 
/* YOUR SOLUTION HERE */
SELECT 
    CUSTOMER.Cus_Code, 
    INVOICE.Inv_Number, 
    INVOICE.INV_DATE,
    PRODUCT.P_Descript, 
    LINE.Line_Units, 
    LINE.Line_Price
FROM 
    CUSTOMER
JOIN 
    INVOICE ON CUSTOMER.Cus_Code = INVOICE.Cus_Code
JOIN 
    LINE ON INVOICE.Inv_Number = LINE.Inv_Number
JOIN 
    PRODUCT ON LINE.P_Code = PRODUCT.P_Code
ORDER BY 
    CUSTOMER.Cus_Code, 
    INVOICE.Inv_Number, 
    PRODUCT.P_Descript;