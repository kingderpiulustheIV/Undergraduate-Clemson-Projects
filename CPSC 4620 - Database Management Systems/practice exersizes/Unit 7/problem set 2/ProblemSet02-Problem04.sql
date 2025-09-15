-- ## Problem 4
-- 
-- Using the output shown below as your guide, generate a list of customer purchases, 
-- including the subtotals for each of the invoice line numbers. The subtotal is a derived 
-- attribute calculated by multiplying LINE_UNITS by LINE_PRICE. Sort the output by customer code,
-- invoice number, and product description. Be certain to use the column aliases as shown.
-- 
-- +----------+------------+-------------------------------------+--------------+------------+----------+
-- | CUS_CODE | INV_NUMBER |             P_DESCRIPT              | Units Bought | Unit Price | Subtotal |
-- +----------+------------+-------------------------------------+--------------+------------+----------+
-- |  10011   |    1002    |     Rat-tail file, 1/8-in. fine     |     2.00     |    4.99    |   9.98   |
-- |  10011   |    1004    |             Claw hammer             |     2.00     |    9.95    |  19.90   |
-- |  10011   |    1004    |     Rat-tail file, 1/8-in. fine     |     3.00     |    4.99    |  14.97   |
-- |  10011   |    1008    |             Claw hammer             |     1.00     |    9.95    |   9.95   |
-- |  10011   |    1008    |       PVC pipe, 3.5-in., 8-ft       |     5.00     |    5.87    |  29.35   |
-- |  10011   |    1008    | Steel matting, 4'x8'x1/6", .5" mesh |     3.00     |   119.95   |  359.85  |
-- |  10012   |    1003    |       7.25-in. pwr. saw blade       |     5.00     |   14.99    |  74.95   |
-- |  10012   |    1003    |     B&D cordless drill, 1/2-in.     |     1.00     |   38.95    |  38.95   |
-- |  10012   |    1003    |      Hrd. cloth, 1/4-in., 2x50      |     1.00     |   39.95    |  39.95   |
-- |  10014   |    1001    |       7.25-in. pwr. saw blade       |     1.00     |   14.99    |  14.99   |
-- |  10014   |    1001    |             Claw hammer             |     1.00     |    9.95    |   9.95   |
-- |  10014   |    1006    |      1.25-in. metal screw, 25       |     3.00     |    6.99    |  20.97   |
-- |  10014   |    1006    |      B&D jigsaw, 12-in. blade       |     1.00     |   109.92   |  109.92  |
-- |  10014   |    1006    |             Claw hammer             |     1.00     |    9.95    |   9.95   |
-- |  10014   |    1006    |       Hicut chain saw, 16 in.       |     1.00     |   256.99   |  256.99  |
-- |  10015   |    1007    |       7.25-in. pwr. saw blade       |     2.00     |   14.99    |  29.98   |
-- |  10015   |    1007    |     Rat-tail file, 1/8-in. fine     |     1.00     |    4.99    |   4.99   |
-- |  10018   |    1005    |       PVC pipe, 3.5-in., 8-ft       |    12.00     |    5.87    |  70.44   |
-- +----------+------------+-------------------------------------+--------------+------------+----------+
--
/* YOUR SOLUTION HERE */
SELECT 
    CUSTOMER.CUS_CODE, 
    INVOICE.INV_NUMBER, 
    PRODUCT.P_DESCRIPT, 
    LINE.Line_Units as 'Units Bought', 
    LINE.Line_Price as 'Unit Price',
    ROUND((LINE.Line_Units * LINE.Line_Price), 2)AS Subtotal
FROM 
    CUSTOMER
JOIN 
    INVOICE ON CUSTOMER.CUS_CODE = INVOICE.CUS_CODE
JOIN 
    LINE ON INVOICE.INV_NUMBER = LINE.INV_NUMBER
JOIN 
    PRODUCT ON LINE.P_Code = PRODUCT.P_Code
ORDER BY 
    CUSTOMER.CUS_CODE, 
    INVOICE.INV_NUMBER, 
    PRODUCT.P_DESCRIPT;