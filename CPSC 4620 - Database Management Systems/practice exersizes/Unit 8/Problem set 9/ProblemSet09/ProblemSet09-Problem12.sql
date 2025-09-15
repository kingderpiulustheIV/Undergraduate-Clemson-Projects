-- ## Problem 12
-- 
-- Write a procedure named prc_cust_add to add a new customer to the CUSTOMER table. 
-- The procedure must have parameters of the appropriate types for fields CUST_NUM, 
-- CUST_LNAME, CUST_FNAME, and CUST_BALANCE.
-- 
-- Test the procedure by calling it with following values:
-- 
-- +------------+--------------+--------------+----------------+
-- |   CUST_NUM | CUST_LNAME   | CUST_FNAME   |   CUST_BALANCE |
-- |------------+--------------+--------------+----------------+
-- |       1002 | Rauthor      | Peter        |        1351.83 |
-- +------------+--------------+--------------+----------------+
-- 
-- Note: You should execute the procedure and verify that the new customer was added to ensure your code is correct!
-- 
-- Make sure you include the appropriate DELIMITER statements in your solution! 
-- 

/* YOUR SOLUTION HERE */
DELIMITER //

CREATE PROCEDURE prc_cust_add(
    IN p_cust_num INT,
    IN p_cust_lname VARCHAR(30),
    IN p_cust_fname VARCHAR(30),
    IN p_cust_balance DECIMAL(10,2)
)
BEGIN
    INSERT INTO CUSTOMER (CUST_NUM, CUST_LNAME, CUST_FNAME, CUST_BALANCE)
    VALUES (p_cust_num, p_cust_lname, p_cust_fname, p_cust_balance);
END//

DELIMITER ;

CALL prc_cust_add(1002, 'Rauthor', 'Peter', 1351.83);
