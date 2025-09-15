-- ## Problem 13
-- 
-- Write a procedure named prc_invoice_add to add a new invoice record to the INVOICE table.
-- The procedure must have parameters of the appropriate types for fields INV_NUM, CUST_NUM, 
-- INV_DATE, and INV_AMOUNT.  
-- 
-- Test the procedure by calling it with following values:
-- 
-- Use the following values in the new record:
-- 
-- +-----------+------------+------------+--------------+
-- |   INV_NUM |   CUST_NUM | INV_DATE   |   INV_AMOUNT |
-- |-----------+------------+------------+--------------|
-- |      8006 |       1000 | 2022-04-30 |       301.72 |
-- +-----------+------------+------------+--------------+
-- 
-- Note: You should execute the procedure and verify that the new invoice was added to ensure your code is correct.
-- 
-- Make sure you include the appropriate DELIMITER statements in your solution! 
-- 

/* YOUR SOLUTION HERE */
DELIMITER //

CREATE PROCEDURE prc_invoice_add(
    IN p_inv_num INT,
    IN p_cust_num INT,
    IN p_inv_date DATE,
    IN p_inv_amount DECIMAL(10,2)
)
BEGIN
    INSERT INTO INVOICE (INV_NUM, CUST_NUM, INV_DATE, INV_AMOUNT)
    VALUES (p_inv_num, p_cust_num, p_inv_date, p_inv_amount);
END//

DELIMITER ;

CALL prc_invoice_add(8006, 1000, '2022-04-30', 301.72);
