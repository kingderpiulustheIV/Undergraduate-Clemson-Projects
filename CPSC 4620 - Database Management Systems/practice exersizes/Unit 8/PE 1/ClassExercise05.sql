-- ## Task 1:
-- 
-- The InstantRide Management team founded a new team for car maintenance. The new team is 
-- responsible for the small maintenance operations for the cars in the InstantRide system. 
-- The main idea is to take actions faster and minimize the time spent for the maintenance.
--  Therefore, the Car Maintenance team wants to store MAINTENANCE_TYPE_ID char(5)) and a 
-- MAINTENANCE_TYPE_DESCRIPTION varchar(30)) in the database. Using MAINTENANCE_TYPE_ID as 
-- the PRIMARY KEY, create a new table, MAINTENANCE_TYPES and send the table description 
-- with the column names and types to the Car Maintenance team.
-- 


CREATE TABLE MAINTENANCE_TYPES (
    MAINTENANCE_TYPE_ID CHAR(5) PRIMARY KEY NOT NULL,
    MAINTENANCE_TYPE_DESCRIPTION VARCHAR(30) NOT NULL
);
-- ## Task 2:
-- 
-- The Car Maintenance team also wants to store the actual maintenance operations in the database. 
-- The team wants to start with a table to store CAR_ID CHAR(5), MAINTENANCE_TYPE_ID CHAR(5) and
-- MAINTENANCE_DUE DATE date for the operation. Create a new table named MAINTENANCES. 
-- The PRIMARY_KEY should be the combination of the three fields. The CAR_ID and
-- MAINTENANCE_TYPE_ID should be foreign keys to their original tables. Cascade update and 
-- cascade delete the foreign keys.
-- 
CREATE TABLE MAINTENANCES (
    CAR_ID CHAR(5) NOT NULL,
    MAINTENANCE_TYPE_ID CHAR(5) NOT NULL,
    MAINTENANCE_DUE DATE NOT NULL,
    PRIMARY KEY (CAR_ID, MAINTENANCE_TYPE_ID, MAINTENANCE_DUE),
   FOREIGN KEY (CAR_ID)
        REFERENCES CARS (CAR_ID)
        ON DELETE CASCADE ON UPDATE CASCADE,
    FOREIGN KEY (MAINTENANCE_TYPE_ID)
        REFERENCES MAINTENANCE_TYPES (MAINTENANCE_TYPE_ID)
        ON DELETE CASCADE ON UPDATE CASCADE
);

-- ## Task 3:
-- 
-- The Driver Relationship team wants to create some workshops and increase communication with the
-- active drivers in InstantRide. Therefore, they requested a new database table to store the 
-- driver details of the drivers that have had at least one ride in the system. Create a new table,
-- ACTIVE_DRIVERS from the DRIVERS and TRAVELS tables which contains the following fields:
-- 
-- - DRIVER_ID CHAR(5) (Primary key)
-- - DRIVER_FIRST_NAME VARCHAR(20)
-- - DRIVER_LAST_NAME VARCHAR(20)
-- - DRIVER_DRIVING_LICENSE_ID VARCHAR(10)
-- - DRIVER_DRIVING_LICENSE_CHECKED BOOL
-- - DRIVER_RATING DECIMAL(2,1)
-- 
CREATE TABLE ACTIVE_DRIVERS (
    DRIVER_ID CHAR(5) PRIMARY KEY,
    DRIVER_FIRST_NAME VARCHAR(20),
    DRIVER_LAST_NAME VARCHAR(20),
    DRIVER_DRIVING_LICENSE_ID VARCHAR(10),
    DRIVER_DRIVING_LICENSE_CHECKED BOOL,
    DRIVER_RATING DECIMAL
) AS SELECT DRIVER_ID,
    DRIVER_FIRST_NAME,
    DRIVER_LAST_NAME,
    DRIVER_DRIVING_LICENSE_ID,
    DRIVER_DRIVING_LICENSE_CHECKED,
    DRIVER_RATING FROM
    DRIVERS
WHERE
    DRIVER_ID IN (SELECT DISTINCT DRIVER_ID FROM TRAVELS);
			
-- ## Task 4:
-- 
-- The Driver Relationship team wants to have quick search options for the active drivers. The 
-- team specifically mentioned that they are using first name, last name and driving license ID 
-- to search the drivers. Create an index called NameSearch on the ACTIVE_DRIVERS table created 
-- in task 3.
-- 
CREATE INDEX NameSearch 
	ON ACTIVE_DRIVERS(DRIVER_FIRST_NAME, DRIVER_LAST_NAME, DRIVER_DRIVING_LICENSE_ID);

-- ## Task 5:
-- 
-- The Driver Relationship team requested to ensure that there will be no duplicates in the active
-- drivers tables in terms of first name, last name and driving license ID. You need to create a
-- constraint in the ACTIVE_DRIVERS table, called DuplicateCheck to ensure the first name, 
-- last name, and the driving license ID are unique.
--
ALTER TABLE ACTIVE_DRIVERS 
	ADD CONSTRAINT DuplicateCheck 
		UNIQUE (DRIVER_FIRST_NAME, DRIVER_LAST_NAME, DRIVER_DRIVING_LICENSE_ID);


-- ## Task 6:
-- 
-- The Car Maintenance team considered that the available maintenance tasks should also have the 
-- price information in the database. Alter the MAINTENANCE_TYPES table to include a new column
-- named MAINTENANCE_PRICE of type DECIMAL(5,2). 
--
ALTER TABLE MAINTENANCE_TYPES 
	ADD COLUMN MAINTENANCE_PRICE DECIMAL(5,2);
