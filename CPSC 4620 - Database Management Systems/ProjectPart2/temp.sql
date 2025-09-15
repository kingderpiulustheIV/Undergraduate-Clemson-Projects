INSERT INTO ordertable (ordertable_OrderID, customer_CustID, ordertable_OrderType, ordertable_OrderDateTime, ordertable_CustPrice, ordertable_BusPrice, ordertable_IsComplete)
VALUES (5, 2, 'pickup', '2025-03-02 17:30:00', 28.70, 7.84, TRUE);
INSERT INTO pickup (ordertable_OrderID, pickup_IsPickedUp)
VALUES (5, 1);
INSERT INTO pizza (pizza_PizzaID, pizza_Size, pizza_CrustType, pizza_PizzaDate, pizza_CustPrice, pizza_BusPrice, ordertable_OrderID)
VALUES (13, 'XLarge', 'Gluten-Free', '2024-03-02 17:30:00', 28.70, 7.84, 5);

INSERT INTO pizza_topping (pizza_PizzaID, topping_TopID, pizza_topping_IsDouble) VALUES
(13, 16, 0),
(13, 5, 0),
(13, 6, 0),
(13, 7, 0),
(13, 8, 0),
(13, 9, 0);

INSERT INTO pizza_discount (pizza_PizzaID, discount_DiscountID)
VALUES (13, 4);