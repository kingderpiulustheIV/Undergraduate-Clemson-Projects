-- PopulateData.sql
-- Author: Sean Farrell
USE PizzaDB;

-- Insert toppings
INSERT INTO topping(topping_TopName, topping_CustPrice, topping_BusPrice, topping_CurINVT, topping_MININVT, topping_SmallAMT, topping_MedAMT, topping_LgAMT, topping_XLAMT) VALUES
('Pepperoni', 1.25, 0.20, 100, 50, 2, 2.75, 3.5, 4.5),
('Sausage', 1.25, 0.15, 100, 50, 2.5, 3, 3.5, 4.25),
('Ham', 1.50, 0.15, 78, 25, 2, 2.5, 3.25, 4),
('Chicken', 1.75, 0.25, 56, 25, 1.5, 2, 2.25, 3),
('Green Pepper', 0.50, 0.02, 79, 25, 1, 1.5, 2, 2.5),
('Onion', 0.50, 0.02, 85, 25, 1, 1.5, 2, 2.75),
('Roma Tomato', 0.75, 0.03, 86, 10, 2, 3, 3.5, 4.5),
('Mushrooms', 0.75, 0.10, 52, 50, 1.5, 2, 2.5, 3),
('Black Olives', 0.60, 0.10, 39, 25, 0.75, 1, 1.5, 2),
('Pineapple', 1.00, 0.25, 15, 0, 1, 1.25, 1.75, 2),
('Jalapenos', 0.50, 0.05, 64, 0, 0.5, 0.75, 1.25, 1.75),
('Banana Peppers', 0.50, 0.05, 36, 0, 0.6, 1, 1.3, 1.75),
('Regular Cheese', 0.50, 0.12, 250, 50, 2, 3.5, 5, 7),
('Four Cheese Blend', 1.00, 0.15, 150, 25, 2, 3.5, 5, 7),
('Feta Cheese', 1.50, 0.18, 75, 0, 1.75, 3, 4, 5.5),
('Goat Cheese', 1.50, 0.20, 54, 0, 1.6, 2.75, 4, 5.5),
('Bacon', 1.50, 0.25, 89, 0, 1, 1.5, 2, 3);

-- Insert discounts
INSERT INTO discount(discount_DiscountName, discount_IsPercent, discount_Amount) VALUES
('Employee', 1, 15),
('Lunch Special Medium', 0, 1.00),
('Lunch Special Large', 0, 2.00),
('Specialty Pizza', 0, 1.50),
('Happy Hour', 1, 10),
('Gameday Special', 1, 20);

-- Insert base prices
INSERT INTO baseprice(baseprice_Size, baseprice_CrustType, baseprice_CustPrice, baseprice_BusPrice) VALUES
('Small', 'Thin', 3.00, 0.50),
('Small', 'Original', 3.00, 0.75),
('Small', 'Pan', 3.50, 1.00),
('Small', 'Gluten-Free', 4.00, 2.00),
('Medium', 'Thin', 5.00, 1.00),
('Medium', 'Original', 5.00, 1.50),
('Medium', 'Pan', 6.00, 2.25),
('Medium', 'Gluten-Free', 6.25, 3.00),
('Large', 'Thin', 8.00, 1.25),
('Large', 'Original', 8.00, 2.00),
('Large', 'Pan', 9.00, 3.00),
('Large', 'Gluten-Free', 9.50, 4.00),
('XLarge', 'Thin', 10.00, 2.00),
('XLarge', 'Original', 10.00, 3.00),
('XLarge', 'Pan', 11.50, 4.50),
('XLarge', 'Gluten-Free', 12.50, 6.00);

-- Insert customers
INSERT INTO customer(customer_FName, customer_LName, customer_PhoneNum) VALUES
('Andrew', 'Wilkes-Krier', '8642545861'),
('Matt', 'Engers', '8644749953'),
('Frank',  'Turner', '8642328944'),
('Milo', 'Auckerman', '8648785679');

-- Order 1: Dine-in on March 5th at 12:03 pm

-- Inserts order infromation
INSERT INTO ordertable(ordertable_OrderID, ordertable_OrderType, ordertable_OrderDateTime, ordertable_CustPrice, ordertable_BusPrice, ordertable_IsComplete)
VALUES (1, 'dinein', '2025-03-05 12:03:00', 19.75, 3.68, TRUE);

-- inserts dine in infromation
INSERT INTO dinein(ordertable_OrderID, dinein_TableNum)
VALUES (1, 21);

-- inserts pizza infromation
INSERT INTO pizza(pizza_PizzaID, pizza_Size, pizza_CrustType, pizza_PizzaDate, pizza_CustPrice, pizza_BusPrice, ordertable_OrderID, pizza_PizzaState)
VALUES (1, 'Large', 'Thin', '2025-03-05 12:03:00', 19.75, 3.68, 1, 'completed');

-- inserts topping infromation
INSERT INTO pizza_topping(pizza_PizzaID, topping_TopID, pizza_topping_IsDouble) VALUES
(1, 13, 1),
(1, 1, 0),
(1, 2, 0);

-- inserts discount infromation
INSERT INTO pizza_discount(pizza_PizzaID, discount_DiscountID)
VALUES (1, 3);

-- Order 2: Dine-in on April 3rd at 12:05pm

-- inserts order infromation
INSERT INTO ordertable(ordertable_OrderID, ordertable_OrderType, ordertable_OrderDateTime, ordertable_CustPrice, ordertable_BusPrice, ordertable_IsComplete)
VALUES (2, 'dinein', '2025-04-03 12:05:00', 19.78, 4.63, TRUE);

INSERT INTO dinein(ordertable_OrderID, dinein_TableNum)
VALUES (2, 4);

-- inserts pizza data for the two pizzas
INSERT INTO pizza(pizza_PizzaID, pizza_Size, pizza_CrustType, pizza_PizzaDate, pizza_CustPrice, pizza_BusPrice, ordertable_OrderID, pizza_PizzaState)
VALUES 
(2, 'Medium', 'Pan', '2025-04-03 12:05:00', 12.85, 3.23, 2, 'completed'),
(3, 'Small', 'Original', '2025-04-03 12:05:00', 6.93, 1.40, 2, 'completed');

INSERT INTO pizza_topping(pizza_PizzaID, topping_TopID, pizza_topping_IsDouble) VALUES
-- inserts toppings data for pizza 1
(2, 15, 0),
(2, 9, 0),
(2, 7, 0), 
(2, 8, 0),
(2, 12, 0),

-- inserts toppings data for pizza 2
(3, 13, 0),
(3, 4, 0),
(3, 12, 0);

-- inserts discounts data for pizzas
INSERT INTO pizza_discount(pizza_PizzaID, discount_DiscountID) VALUES
(2, 2),
(2, 4);

-- Order 3: Pickup on March 3rd at 9:30 pm (6 identical pizzas)

-- inserts order information
INSERT INTO ordertable(ordertable_OrderID, customer_CustID, ordertable_OrderType, ordertable_OrderDateTime, ordertable_CustPrice, ordertable_BusPrice, ordertable_IsComplete)
VALUES (3, 1, 'pickup', '2025-03-03 21:30:00', 89.28, 19.80, TRUE);

-- inserts pickup information
INSERT INTO pickup (ordertable_OrderID, pickup_IsPickedUp)
VALUES (3, 1);

-- inserts pizza information
INSERT INTO pizza(pizza_PizzaID, pizza_Size, pizza_CrustType, pizza_PizzaDate, pizza_CustPrice, pizza_BusPrice, ordertable_OrderID, pizza_PizzaState)
VALUES 
(4, 'Large', 'Original', '2025-03-03 21:30:00', 14.88, 3.30, 3, 'completed'),
(5, 'Large', 'Original', '2025-03-03 21:30:00', 14.88, 3.30, 3, 'completed'),
(6, 'Large', 'Original', '2025-03-03 21:30:00', 14.88, 3.30, 3, 'completed'),
(7, 'Large', 'Original', '2025-03-03 21:30:00', 14.88, 3.30, 3, 'completed'),
(8, 'Large', 'Original', '2025-03-03 21:30:00', 14.88, 3.30, 3, 'completed'),
(9, 'Large', 'Original', '2025-03-03 21:30:00', 14.88, 3.30, 3, 'completed');

-- Inserts topping information
INSERT INTO pizza_topping(pizza_PizzaID, topping_TopID, pizza_topping_IsDouble)
SELECT p.pizza_PizzaID, t.topping_TopID, 0
FROM pizza p

-- Uses cross join insetead of reentering redudanant code for inserting toppins
CROSS JOIN (SELECT topping_TopID FROM topping WHERE topping_TopName IN ('Regular Cheese', 'Pepperoni')) t
WHERE p.pizza_PizzaID BETWEEN 4 AND 9;

-- Order 4: Delivery on April 20th at 7:11 pm

-- inserts order information
INSERT INTO ordertable(ordertable_OrderID, customer_CustID, ordertable_OrderType, ordertable_OrderDateTime, ordertable_CustPrice, ordertable_BusPrice, ordertable_IsComplete)
VALUES (4, 1, 'delivery', '2025-04-20 19:11:00', 68.95, 20.99, TRUE);

-- inserts delivery information
INSERT INTO delivery(ordertable_OrderID, delivery_HouseNum, delivery_Street, delivery_City, delivery_State, delivery_Zip, delivery_IsDelivered)
VALUES (4, 115, 'Party Blvd', 'Anderson', 'SC', 29621, TRUE);

-- inserts pizza infromation
INSERT INTO pizza(pizza_PizzaID, pizza_Size, pizza_CrustType, pizza_PizzaDate, pizza_CustPrice, pizza_BusPrice, ordertable_OrderID, pizza_PizzaState)
VALUES 
(10, 'XLarge', 'Original', '2025-04-20 19:11:00', 27.94, 9.19, 4, 'completed'),
(11, 'XLarge', 'Original', '2025-04-20 19:11:00', 31.50, 6.25, 4, 'completed'),
(12, 'XLarge', 'Original', '2025-04-20 19:11:00', 26.75, 5.55, 4, 'completed');

-- inserts topping infromation
INSERT INTO pizza_topping(pizza_PizzaID, topping_TopID, pizza_topping_IsDouble) VALUES
-- inserts topping data for pizza with peperoni and sausage.
(10, 14, 0),
(10, 1, 0),
(10, 2, 0),

-- inserts topping data for pizza with ham and pineapple.
(11, 14, 0),
(11, 3, 1),
(11, 10, 1),

-- inserts topping data for pizza with chicken and bacon.
(12, 14, 0),
(12, 4, 0),
(12, 17, 0);

-- inserts order discount information
INSERT INTO order_discount(ordertable_OrderID, discount_DiscountID)
VALUES (4, 5);

-- inserts pizza discount infrormation
INSERT INTO pizza_discount(pizza_PizzaID, discount_DiscountID)
VALUES (11, 4);

-- Order 5: Pickup on March 2nd at 5:30 pm

-- inserts order information
INSERT INTO ordertable(ordertable_OrderID, customer_CustID, ordertable_OrderType, ordertable_OrderDateTime, ordertable_CustPrice, ordertable_BusPrice, ordertable_IsComplete)
VALUES (5, 2, 'pickup', '2025-03-02 17:30:00', 28.70, 7.84, TRUE);

-- inserts pickup infromation
INSERT INTO pickup(ordertable_OrderID, pickup_IsPickedUp)
VALUES (5, 1);

-- inserts pizza infromation
INSERT INTO pizza(pizza_PizzaID, pizza_Size, pizza_CrustType, pizza_PizzaDate, pizza_CustPrice, pizza_BusPrice, ordertable_OrderID, pizza_PizzaState)
VALUES (13, 'XLarge', 'Gluten-Free', '2025-03-02 17:30:00', 28.70, 7.84, 5, 'completed');

-- inserts toppings data for goat cheese vegitarian pizza
INSERT INTO pizza_topping(pizza_PizzaID, topping_TopID, pizza_topping_IsDouble) VALUES
(13, 16, 0),
(13, 5, 0),
(13, 6, 0),
(13, 7, 0),
(13, 8, 0),
(13, 9, 0);

-- inserts discount data.
INSERT INTO pizza_discount(pizza_PizzaID, discount_DiscountID)
VALUES (13, 4);

-- Order 6: Delivery on March 2nd at 6:17 pm


-- inserts order data
INSERT INTO ordertable(ordertable_OrderID, customer_CustID, ordertable_OrderType, ordertable_OrderDateTime, ordertable_CustPrice, ordertable_BusPrice, ordertable_IsComplete)
VALUES (6, 3, 'delivery', '2025-03-02 18:17:00', 25.81, 3.64, TRUE);

-- inserts delivery data
INSERT INTO delivery(ordertable_OrderID, delivery_HouseNum, delivery_Street, delivery_City, delivery_State, delivery_Zip, delivery_IsDelivered)
VALUES (6, 6745, 'Wessex St', 'Anderson', 'SC', 29621, 1);

-- Inserts data for pizza infromation
INSERT INTO pizza(pizza_PizzaID, pizza_Size, pizza_CrustType, pizza_PizzaDate, pizza_CustPrice, pizza_BusPrice, ordertable_OrderID, pizza_PizzaState)
VALUES (14, 'Large', 'Thin', '2025-03-02 18:17:00', 25.81, 3.64, 6, 'completed');

-- inserts topping data for veggie chicken pizza
INSERT INTO pizza_topping(pizza_PizzaID, topping_TopID, pizza_topping_IsDouble) VALUES
(14, 14, 1),
(14, 4, 0),
(14, 5, 0),
(14, 6, 0),
(14, 8, 0);

-- Order 7: Delivery on April 13th at 8:32 pm

INSERT INTO ordertable(ordertable_OrderID, customer_CustID, ordertable_OrderType, ordertable_OrderDateTime, ordertable_CustPrice, ordertable_BusPrice, ordertable_IsComplete)
VALUES (7, 4, 'delivery', '2025-04-13 20:32:00', 31.66, 6.00, 1);

INSERT INTO delivery(ordertable_OrderID, delivery_HouseNum, delivery_Street, delivery_City, delivery_State, delivery_Zip, delivery_IsDelivered)
VALUES (7, 8879, 'Suburban', 'Anderson', 'SC', 29621, 1);

INSERT INTO pizza(pizza_PizzaID, pizza_Size, pizza_CrustType, pizza_PizzaDate, pizza_CustPrice, pizza_BusPrice, ordertable_OrderID, pizza_PizzaState)
VALUES 
(15, 'Large', 'Thin', '2025-04-13 20:32:00', 18.00, 2.75, 7,'completed'),
(16, 'Large', 'Thin', '2025-04-13 20:32:00', 19.25, 3.25, 7, 'completed');

INSERT INTO pizza_topping(pizza_PizzaID, topping_TopID, pizza_topping_IsDouble) VALUES
-- inserts topping data for cheese pizza
(15, 14, 1),
-- inserts topping data for peporoni pizza
(16, 13, 0),
(16, 1, 1);

INSERT INTO order_discount(ordertable_OrderID, discount_DiscountID)
VALUES (7, 1);