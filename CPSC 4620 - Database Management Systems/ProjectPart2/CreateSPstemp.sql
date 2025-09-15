-- CreateSPs.sql
-- Author: Sean Farrell 

USE PizzaDB;

DELIMITER //

-- Update inventory when a pizza is ordered
CREATE PROCEDURE UpdateInventory(IN p_pizza_id INT)
BEGIN
    DECLARE done INT DEFAULT FALSE;
    DECLARE t_id INT;
    DECLARE is_extra BOOL;
    DECLARE p_size VARCHAR(10);
    DECLARE units_needed DECIMAL(5,2);
    
    -- Cursor for toppings on the pizza
    DECLARE topping_cursor CURSOR FOR 
        SELECT pt.topping_TopID, pt.pizza_topping_IsDouble
        FROM pizza_topping pt 
        WHERE pt.pizza_PizzaID = PizzaID;
    
    DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;
    
    -- Get pizza size
    SELECT bp.basepice_Size INTO p_size 
    FROM pizza p
    JOIN baseprice bp ON p.pizza_BusPrice = bp.baseprice_BusPrice
    WHERE p.pizza_PizzaID = p_pizza_id;
    
    OPEN topping_cursor;

    read_loop: LOOP
        FETCH topping_cursor INTO t_id, is_extra;
        IF done THEN
            LEAVE read_loop;
        END IF;
        
        -- Determine units needed based on size and extra
        IF p_size = 'Small' THEN
            SET units_needed = (SELECT topping_SmallAMT FROM topping WHERE TopID = t_id);
        ELSEIF p_size = 'Medium' THEN
            SET units_needed = (SELECT topping_MedAMT FROM topping WHERE TopID = t_id);
        ELSEIF p_size = 'Large' THEN
            SET units_needed = (SELECT topping_LgAMT FROM topping WHERE TopID = t_id);
        ELSEIF p_size = 'XLarge' THEN
            SET units_needed = (SELECT topping_XLAMT FROM topping WHERE TopID = t_id);
        END IF;
        
        IF is_extra THEN
            SET units_needed = units_needed * 2;
        END IF;
        
        -- Update inventory
        UPDATE topping 
        SET inventory = inventory - units_needed 
        WHERE TopID = t_id;
    END LOOP;
    
    CLOSE topping_cursor;
END //

-- Stored Procedure 2: Apply discounts to a pizza
CREATE PROCEDURE ApplyPizzaDiscounts(IN p_pizza_id INT, IN p_price DECIMAL(5,2), OUT final_price DECIMAL(5,2))
BEGIN
    DECLARE dollar_off_total DECIMAL(5,2) DEFAULT 0;
    DECLARE percent_off_total DECIMAL(5,2) DEFAULT 0;
    DECLARE temp_price DECIMAL(5,2);
    
    -- Calculate total dollar discounts
    SELECT COALESCE(SUM(d.discount_Amount), 0) INTO dollar_off_total
    FROM pizza_discount pd
    JOIN discount d ON pd.discount_DiscountID = d.discount_DiscountID
    WHERE pd.pizza_PizzaID = p_pizza_id AND d.discount_Ammount IS NOT NULL;
    
    -- Apply dollar discounts first
    SET temp_price = p_price - dollar_off_total;
    
    -- Calculate total percent discounts (multiplicative)
    SELECT COALESCE(1 - PRODUCT(1 - (d.discount_IsPercent/100)), 0) INTO percent_off_total
    FROM pizza_discount pd
    JOIN discount d ON pd.discount_DiscountID = d.discount_DiscountID
    WHERE pd.pizza_PizzaID = p_pizza_id AND d.discount_IsPercent IS NOT NULL;
    
    -- Apply percent discounts
    SET final_price = temp_price * (1 - percent_off_total);
END //

-- Stored Function 1: Calculate pizza price before discounts (how much to sell the pizza to the customer)
CREATE FUNCTION CalculatePizzaPrice(p_pizza_id INT) RETURNS DECIMAL(5,2)
DETERMINISTIC
BEGIN
    DECLARE base_price DECIMAL(5,2);
    DECLARE topping_total DECIMAL(5,2) DEFAULT 0;
    DECLARE p_size VARCHAR(30);
    DECLARE done INT DEFAULT FALSE;
    DECLARE t_id INT;
    DECLARE is_extra BOOL;
    DECLARE t_price DECIMAL(5,2);
    DECLARE units_needed DECIMAL(5,2);
    
    -- Cursor for toppings
    DECLARE topping_cursor CURSOR FOR 
        SELECT pt.topping_TopID, pt.pizza_topping_IsDouble
        FROM pizza_topping pt 
        WHERE pt.PizzaID = p_pizza_id;
    
    DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;
    
    -- Get base price and size
    SELECT bp.baseprice_BusPrice, bp.baseprice_Size INTO base_price, p_size 
    FROM pizza p
    JOIN baseprice bp ON p.pizza_BusPrice = bp.baseprice_BusPrice
    WHERE p.pizza_PizzaID = PizzaID;
    OPEN topping_cursor;
    
    read_loop: LOOP
        FETCH topping_cursor INTO t_id, is_extra;
        IF done THEN
            LEAVE read_loop;
        END IF;
        
        -- Get topping price and units needed
        SELECT topping_CustPrice INTO t_price FROM topping WHERE TopID = t_id;
        
        IF p_size = 'Small' THEN
            SET units_needed = (SELECT topping_SmallAMT FROM topping WHERE TopID = t_id);
        ELSEIF p_size = 'Medium' THEN
            SET units_needed = (SELECT topping_MedAMT FROM topping WHERE TopID = t_id);
        ELSEIF p_size = 'Large' THEN
            SET units_needed = (SELECT topping_LgAMT FROM topping WHERE TopID = t_id);
        ELSEIF p_size = 'XLarge' THEN
            SET units_needed = (SELECT topping_XLAMT FROM topping WHERE TopID = t_id);
        END IF;
        
        IF is_extra THEN
            SET units_needed = units_needed * 2;
        END IF;
        
        SET topping_total = topping_total + (t_price * units_needed);
    END LOOP;
    
    CLOSE topping_cursor;
    
    RETURN base_price + topping_total;
END //

-- Stored Function 2: Calculate pizza cost (how much it costs for the busness to make the pizza)
CREATE FUNCTION CalculatePizzaCost(p_pizza_id INT) RETURNS DECIMAL(5,2)
DETERMINISTIC
BEGIN
    DECLARE base_cost DECIMAL(5,2);
    DECLARE topping_total DECIMAL(5,2) DEFAULT 0;
    DECLARE p_size VARCHAR(30);
    DECLARE done INT DEFAULT FALSE;
    DECLARE t_id INT;
    DECLARE is_extra BOOL;
    DECLARE t_cost DECIMAL(5,2);
    DECLARE units_needed DECIMAL(5,2);
    
    -- Cursor for toppings
    DECLARE topping_cursor CURSOR FOR 
        SELECT pt.topping_TopID, pt.pizza_topping_IsDouble 
        FROM pizza_topping pt 
        WHERE pt.pizza_PizzaID = p_pizza_id;
    
    DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;
    
    -- Get base cost and size
    SELECT bp.baseprice_BusCost, bp.baseprice_Size INTO base_cost, p_size 
    FROM pizza p
    JOIN baseprice bp ON p.pizza_BusPrice = bp.baseprice_BusPrice
    WHERE p.pizza_PizzaID = p_pizza_id;
    
    OPEN topping_cursor;
    
    read_loop: LOOP
        FETCH topping_cursor INTO t_id, is_extra;
        IF done THEN
            LEAVE read_loop;
        END IF;
        
        -- Get topping cost and units needed
        SELECT topping_BusCost INTO t_cost FROM topping WHERE TopID = t_id;
        
        IF p_size = 'Small' THEN
            SET units_needed = (SELECT topping_SmallAMT FROM topping WHERE TopID = t_id);
        ELSEIF p_size = 'Medium' THEN
            SET units_needed = (SELECT topping_MedAMT FROM topping WHERE TopID = t_id);
        ELSEIF p_size = 'Large' THEN
            SET units_needed = (SELECT topping_LgAMT FROM topping WHERE TopID = t_id);
        ELSEIF p_size = 'XLarge' THEN
            SET units_needed = (SELECT topping_XLAMT FROM topping WHERE TopID = t_id);
        END IF;
        
        IF is_extra THEN
            SET units_needed = units_needed * 2;
        END IF;
        
        SET topping_total = topping_total + (t_cost * units_needed);
    END LOOP;
    
    CLOSE topping_cursor;
    
    RETURN base_cost + topping_total;
END //

-- Trigger 1: Update pizza price and cost when toppings are added
CREATE TRIGGER after_pizzatopping_insert
AFTER INSERT ON pizza_topping
FOR EACH ROW
BEGIN
    DECLARE pizza_price DECIMAL(5,2);
    DECLARE pizza_cost DECIMAL(5,2);
    DECLARE final_price DECIMAL(5,2);
    
    SET pizza_price = CalculatePizzaPrice(NEW.pizza_PizzaID);
    SET pizza_cost = CalculatePizzaCost(NEW.pizza_PizzaID);
    
    CALL ApplyPizzaDiscounts(NEW.pizza_PizzaID, pizza_price, final_price);
    
    UPDATE pizza 
    SET pizza_CustPrice = final_price, pizza_BusPrice = pizza_cost 
    WHERE pizza_id = NEW.pizza_PizzaID;
END //

-- Trigger 2: Update pizza price and cost when toppings are updated
CREATE TRIGGER after_pizzatopping_update
AFTER UPDATE ON pizza_topping
FOR EACH ROW
BEGIN
    DECLARE pizza_price DECIMAL(5,2);
    DECLARE pizza_cost DECIMAL(5,2);
    DECLARE final_price DECIMAL(5,2);
    
    SET pizza_price = CalculatePizzaPrice(NEW.pizza_PizzaID);
    SET pizza_cost = CalculatePizzaCost(NEW.pizza_PizzaID);
    
    CALL ApplyPizzaDiscounts(NEW.pizza_PizzaID, pizza_price, final_price);
    
    UPDATE pizza 
    SET pizza_CustPrice = final_price, pizza_BusPrice = pizza_cost 
    WHERE pizza_PizzaID = NEW.pizza_PizzaID;
END //

-- Trigger 3: Update order when pizza is marked complete
CREATE TRIGGER after_pizza_complete
AFTER UPDATE ON pizza
FOR EACH ROW
BEGIN
    DECLARE all_complete INT;
    DECLARE order_complete INT;
    
    IF NEW.pizza_PizzaState = 'complete' AND OLD.pizza_PizzaState = 'preparing' THEN
        -- Check if all pizzas in the order are complete
        SELECT COUNT(*) INTO all_complete
        FROM pizza
        WHERE ordertable_OrderID = NEW.ordertable_OrderID AND pizza_PizzaState = 'complete';
        
        SELECT COUNT(*) INTO order_complete
        FROM pizza
        WHERE ordertable_OrderID = NEW.ordertable_OrderID;
        
        IF all_complete = order_complete THEN
            UPDATE ordertable SET ordertable_IsComplete = TRUE WHERE ordertable_OrderID = NEW.ordertable_OrderID;
        END IF;
    END IF;
END //

-- Trigger 4: Apply order discounts when added
CREATE TRIGGER after_orderdiscount_insert
AFTER INSERT ON order_discount
FOR EACH ROW
BEGIN
    DECLARE order_price DECIMAL(5,2);
    DECLARE dollar_off_total DECIMAL(5,2) DEFAULT 0;
    DECLARE percent_off_total DECIMAL(5,2) DEFAULT 0;
    
    -- Get current order price
    SELECT SUM(pizza_CustPrice) INTO order_price
    FROM pizza
    WHERE ordertable_OrderID = NEW.ordertable_OrderID;
    
    -- Calculate total dollar discounts
    SELECT COALESCE(SUM(d.discount_Amount), 0) INTO dollar_off_total
    FROM order_discount od
    JOIN discount d ON od.discount_DiscountID = d.discount_DiscountID
    WHERE od.ordertable_OrderID = NEW.ordertable_OrderID AND d.discount_Amount IS NOT NULL;
    
    -- Calculate total percent discounts (multiplicative)
    SELECT COALESCE(1 - PRODUCT(1 - (d.discount_IsPercent/100)), 0) INTO percent_off_total
    FROM order_discount od
    JOIN discount d ON od.discount_DiscountID = d.discount_DiscountID
    WHERE od.ordertable_OrderID = NEW.ordertable_OrderID AND d.discount_IsPercent IS NOT NULL;
    
    -- Apply discounts to all pizzas in the order
    UPDATE pizza
    SET pizza_CustPrice = (pizza_CustPrice - (pizza_CustPrice/order_price)*dollar_off_total) * (1 - percent_off_total)
    WHERE ordertable_OrderID = NEW.ordertable_OrderID;
END //

DELIMITER ;