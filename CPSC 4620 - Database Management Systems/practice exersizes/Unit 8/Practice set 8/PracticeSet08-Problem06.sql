-- ## Problem 6:
-- 
-- The Marketing team requested to create an email list with combining all the email addresses with
-- a semi-colon (;).  You need to create a procedure called OwnerEmailList that uses a CURSOR to
-- iterate all over the emails in the OWNER table.  Use an INOUT paramter to the stored PROCEDURE
-- to retreive the results.  The emails should be ordered by the owner's id number.
-- 
-- Once created, you should test it by calling the procedure like:
-- 	SET @ownerEmailList = "";
-- 	CALL OwnerEmailList(@ownerEmailList);
-- 	SELECT @ownerEmailList;
-- 
-- This is a good example of using the MySQL variables in your development process.
-- 
-- If the procedure worked correctly, the results should look like:
-- +------------------------------------------------------------------------------------------------------------------------------------------------------+
-- | @ownerEmailList                                                                                                                                      |
-- |------------------------------------------------------------------------------------------------------------------------------------------------------|
-- | ece.yilmaz@xmail.com;d.schmidt@xmail.com;r.snow@xmail.com;a.webber@xmail.au;k.jones@xmail.com;a.burke@xmail.com;r.gibbs@xmail.com;k.logan@xmail.com; |
-- +------------------------------------------------------------------------------------------------------------------------------------------------------+

/* YOUR SOLUTION HERE */
DELIMITER //
CREATE PROCEDURE OwnerEmailList(INOUT emailList VARCHAR(1000))
BEGIN
    DECLARE done INT DEFAULT FALSE;
    DECLARE email VARCHAR(255);
    DECLARE emailCursor CURSOR FOR 
        SELECT OwnerEmail 
        FROM OWNER 
        ORDER BY OwnerID DESC;
    DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;
    SET emailList = '';
    OPEN emailCursor;
    read_loop: LOOP
        FETCH emailCursor INTO email;
        IF done THEN
            LEAVE read_loop;
        END IF;
        SET emailList = CONCAT(emailList, email, ';');
    END LOOP;
    CLOSE emailCursor;
END //
DELIMITER ;
