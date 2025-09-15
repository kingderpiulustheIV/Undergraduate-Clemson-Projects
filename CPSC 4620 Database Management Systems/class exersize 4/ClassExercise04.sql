-- ## Task 1:
-- 
-- The InstantRide Driver Relationship team wants the details of the drivers and the number of 
-- cars they use. 
-- 
-- Calculate the count of the CAR_ID field in the TRAVELS table and return  a table 
-- grouped by DRIVER_ID and in descending order by the calculated COUNT column, 
-- displayed as CARS.
-- 

SELECT
    DRIVER_ID, COUNT(CAR_ID) AS CARS
FROM
    TRAVELS
GROUP BY DRIVER_ID
ORDER BY COUNT(CAR_ID) DESC;

-- ## Task 2:
-- 
-- The InstantRide Driver Relationship team requires the detail of the drivers who has used 
-- more than one car for rides more than twice. 
-- 
-- Send them the DRIVER_ID with the calculated COUNT of used cars, displayed as CARS 
-- in decreasing order.
-- 

SELECT
    DRIVER_ID, COUNT(CAR_ID) AS CARS
FROM
    TRAVELS
GROUP BY DRIVER_ID
HAVING COUNT(CAR_ID) > 1
ORDER BY COUNT(CAR_ID) DESC;

-- ## Task 3:
-- 
-- The InstantRide Marketing team is planning to create a heatmap of the start locations of 
-- the travels in InstantRide. 
-- 
-- The team requires the DISTINCT TRAVEL_START_LOCATION values for all travels in the system.
-- 

SELECT DISTINCT
    TRAVEL_START_LOCATION
FROM
    TRAVELS;
	
-- ## Task 4:
-- 
-- The InstantRide User Satisfaction team requires the average and maximum number of rides users 
-- have taken so far with InstantRide. In addition, they would like to know the total number of 
-- travels. However, they need these details with the corresponding column names Average, 
-- Maximum and Total by using the AVG, MAX and SUM functions. 
-- 
-- In order to accomplish this, you will first need to create a derived table from the TRAVELS 
-- table to pass the TRAVEL_ID count to the three mathematical functions.
-- 

SELECT
    AVG(Travels) AS Average,
    MAX(Travels) AS Maximum,
    SUM(Travels) AS Total
FROM
    (SELECT
        USER_ID, COUNT(TRAVEL_ID) AS Travels
    FROM
        TRAVELS
GROUP BY USER_ID) TRAVEL_SUMMARY;

-- ## Task 5:
-- 
-- The InstantRide Driver Relationship team wants to learn how many travels each driver has done 
-- in the month of October. You need to send them the DRIVER_ID and two calculated columns: 
-- DAY and RIDES. The DAY column is calculated using the DAY() function with the 
-- TRAVEL_START_TIME as the argument. The RIDES column is calculated by using the COUNT() 
-- function to determine the number of rides given for each day. Filter the results with the 
-- MONTH function.
-- 

SELECT
    DRIVER_ID, DAY(TRAVEL_START_TIME) AS DAY, COUNT(*) AS RIDES
FROM
    TRAVELS
WHERE
    MONTH((TRAVEL_START_TIME)) = 10
GROUP BY DRIVER_ID , DAY(TRAVEL_START_TIME);

-- ## Task 6:
-- 
-- The InstantRide User Satisfaction team received a phone call from a user who might have left 
-- her wallet in the car. She indicated that the license plate of the car was starting with BB-883 
-- but unfortunately, she could not remember the full license plate number. The team wants to 
-- get all travel information for the cars with the license plate starting with BB-883. 
-- 
-- You need to return all travel data from the TRAVELS table for the CAR_ID which has a 
-- plate number compared with SUBSTR and UPPER functions.
-- 

SELECT
    *
FROM
    TRAVELS
WHERE
        CAR_ID IN (SELECT CAR_ID
    FROM
        CARS
    WHERE
        (SUBSTR(UPPER(CAR_PLATE), 1, 6)) = 'BB-883');
		