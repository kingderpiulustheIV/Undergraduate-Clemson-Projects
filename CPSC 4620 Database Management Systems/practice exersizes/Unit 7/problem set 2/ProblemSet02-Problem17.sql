-- ## Problem 17
-- 
-- Create a query that summarizes the value of products currently in inventory. 
-- 
-- Note that the value of each product is a result of multiplying the units currently in 
-- inventory by the unit price. 
-- 
-- Sort the results in descending order by subtotal, as shown here.
-- 
-- +-------------------------------------+-------+---------+----------+
-- |             P_DESCRIPT              | P_QOH | P_PRICE | Subtotal |
-- +-------------------------------------+-------+---------+----------+
-- |       Hicut chain saw, 16 in.       |  11   | 256.99  | 2826.89  |
-- | Steel matting, 4'x8'x1/6", .5" mesh |  18   | 119.95  | 2159.10  |
-- |        2.5-in. wd. screw, 50        |  237  |  8.45   | 2002.65  |
-- |      1.25-in. metal screw, 25       |  172  |  6.99   | 1202.28  |
-- |       PVC pipe, 3.5-in., 8-ft       |  188  |  5.87   | 1103.56  |
-- |      Hrd. cloth, 1/2-in., 3x50      |  23   |  43.99  | 1011.77  |
-- |  Power painter, 15 psi., 3-nozzle   |   8   | 109.99  |  879.92  |
-- |      B&D jigsaw, 12-in. blade       |   8   | 109.92  |  879.36  |
-- |      Hrd. cloth, 1/4-in., 2x50      |  15   |  39.95  |  599.25  |
-- |       B&D jigsaw, 8-in. blade       |   6   |  99.87  |  599.22  |
-- |       7.25-in. pwr. saw blade       |  32   |  14.99  |  479.68  |
-- |     B&D cordless drill, 1/2-in.     |  12   |  38.95  |  467.40  |
-- |       9.00-in. pwr. saw blade       |  18   |  17.49  |  314.82  |
-- |             Claw hammer             |  23   |  9.95   |  228.85  |
-- |     Rat-tail file, 1/8-in. fine     |  43   |  4.99   |  214.57  |
-- |        Sledge hammer, 12 lb.        |   8   |  14.40  |  115.20  |
-- +-------------------------------------+-------+---------+----------+
-- 
/* YOUR SOLUTION HERE */
SELECT P_DESCRIPT, 
P_QOH, 
P_PRICE,
       ROUND(P_QOH * P_PRICE, 2) AS Subtotal
FROM PRODUCT 
ORDER BY Subtotal DESC;