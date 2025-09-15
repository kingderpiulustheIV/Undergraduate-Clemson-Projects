-- CreateTables.sql
-- Author: Sean Farrell 

CREATE SCHEMA IF NOT EXISTS PizzaDB;
USE PizzaDB;

-- topping table - sores infromation of pizza toppings
CREATE TABLE topping (
    topping_TopID INT AUTO_INCREMENT PRIMARY KEY,
    topping_TopName VARCHAR(30) NOT NULL,
	topping_SmallAMT DECIMAL(5,2) NOT NULL,
    topping_MedAMT DECIMAL(5,2) NOT NULL,
	topping_lgAMT DECIMAL(5,2) NOT NULL,
    topping_XLAMT DECIMAL(5,2) NOT NULL,
    topping_CustPrice DECIMAL(5,2) NOT NULL,
    topping_BusPrice DECIMAL(5,2) NOT NULL,
	topping_MinINVT INT NOT NULL,
    topping_CurINVT INT NOT NULL
);

-- discount table - stores percentages and discount amounts and names of discounts
CREATE TABLE discount (
    discount_DiscountID INT AUTO_INCREMENT PRIMARY KEY NOT NULL,
    discount_DiscountName VARCHAR(30) NOT NULL,
    discount_Amount DECIMAL(5,2) NOT NULL,
    discount_IsPercent TINYINT NOT NULL
);

-- baseprice table - stores crust type, size, and price for base pizzas.
CREATE TABLE baseprice (
    baseprice_Size VARCHAR(30) NOT NULL,
    baseprice_CrustType VARCHAR(30) NOT NULL,
    PRIMARY KEY (baseprice_Size, baseprice_CrustType),
    baseprice_CustPrice DECIMAL(5,2) NOT NULL,
    baseprice_BusPrice DECIMAL(5,2) NOT NULL
);
-- adds indexes for curst type and size so this table can work with pizza table
ALTER TABLE baseprice ADD INDEX (baseprice_CrustType);
ALTER TABLE baseprice ADD INDEX (baseprice_Size);

-- customer table - For pickup or delivery - or dine in.
CREATE TABLE customer (
    customer_CustID INT AUTO_INCREMENT PRIMARY KEY NOT NULL,
    customer_FNAME VARCHAR(30) NOT NULL,
    customer_LNAME VARCHAR(30) NOT NULL,
    customer_PhoneNum VARCHAR(30) NOT NULL
);

-- Ordertable stores infromation of order total and is complete
CREATE TABLE ordertable (
    ordertable_OrderID INT AUTO_INCREMENT PRIMARY KEY NOT NULL,
    customer_CustID INT,
	FOREIGN KEY (customer_CustID) REFERENCES customer(customer_CustID),
    ordertable_OrderType VARCHAR(30) NOT NULL,
    ordertable_OrderDateTime DATETIME NOT NULL,
    ordertable_CustPrice DECIMAL (5,2) NOT NULL, 
    ordertable_BusPrice DECIMAL (5,2) NOT NULL,
    ordertable_isComplete BOOLEAN DEFAULT FALSE
    );

-- Pizza table stores size toppings, crust type and price of pizza. 
CREATE TABLE pizza (
    pizza_PizzaID INT AUTO_INCREMENT PRIMARY KEY NOT NULL,
    pizza_CrustType VARCHAR(30) NOT NULL,
	pizza_Size VARCHAR(30) NOT NULL,
	FOREIGN KEY (pizza_CrustType) REFERENCES baseprice(baseprice_CrustType),
	FOREIGN KEY (pizza_Size) REFERENCES baseprice(baseprice_Size),
	pizza_PizzaState VARCHAR(30),
    pizza_PizzaDate DATETIME NOT NULL,
    pizza_CustPrice DECIMAL(5,2) NOT NULL,
    pizza_BusPrice DECIMAL(5,2) NOT NULL,
    ordertable_OrderID INT NOT NULL,
    FOREIGN KEY (ordertable_OrderID) REFERENCES ordertable(ordertable_OrderID)
);

-- pizza_topping table
CREATE TABLE pizza_topping (
    pizza_PizzaID INT NOT NULL,
    topping_TopID INT NOT NULL,
    PRIMARY KEY (pizza_PizzaID, topping_TopID),
    FOREIGN KEY (pizza_PizzaID) REFERENCES pizza(pizza_PizzaID),
	FOREIGN KEY (topping_TopID) REFERENCES topping(topping_TopID),
    pizza_topping_IsDouble INT NOT NULL
);

-- pizza_discount table
CREATE TABLE pizza_discount (
	pizza_PizzaID INT NOT NULL,
	discount_DiscountID INT NOT NULL,
    PRIMARY KEY (pizza_PizzaID, discount_DiscountID),
    FOREIGN KEY (pizza_PizzaID) REFERENCES pizza(pizza_PizzaID),
	FOREIGN KEY (discount_DiscountID) REFERENCES discount(discount_DiscountID)
);

-- order_discount table
CREATE TABLE order_discount (
	ordertable_OrderID INT NOT NULL,
	discount_DiscountID INT NOT NULL,
	PRIMARY KEY (ordertable_OrderID, discount_DiscountID),
    FOREIGN KEY (ordertable_OrderID) REFERENCES ordertable(ordertable_OrderID),
	FOREIGN KEY (discount_DiscountID) REFERENCES discount(discount_DiscountID)
);

-- pickup table
 CREATE TABLE pickup(
	ordertable_OrderID INT PRIMARY KEY NOT NULL,
    FOREIGN KEY (ordertable_OrderID) REFERENCES ordertable(ordertable_OrderID),
    pickup_IsPickedUp BOOLEAN NOT NULL DEFAULT FALSE
 );
 -- delivery table
 CREATE TABLE delivery(
 	ordertable_OrderID INT PRIMARY KEY NOT NULL,
    FOREIGN KEY (ordertable_OrderID) REFERENCES ordertable(ordertable_OrderID),
    delivery_HouseNum INT NOT NULL,
    delivery_Street VARCHAR(30) NOT NULL,
    delivery_City VARCHAR(30) NOT NULL,
    delivery_State VARCHAR(2) NOT NULL,
    delivery_Zip INT NOT NULL,
    delivery_IsDelivered BOOLEAN NOT NULL DEFAULT FALSE
 );

-- dinein table
CREATE TABLE dinein (
 	ordertable_OrderID INT PRIMARY KEY NOT NULL,
    FOREIGN KEY (ordertable_OrderID) REFERENCES ordertable(ordertable_OrderID),
    dinein_TableNum INT NOT NULL
);
