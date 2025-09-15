/*
 * Author: Sean Farrell
 * 4/22/2025
 * CPSC 4620 - Project 3 Java Implementation
 */
package cpsc4620;
import java.io.IOException;
import java.sql.*;
import java.util.*;
/*
 * This file is where you will implement the methods needed to support this application.
 * You will write the code to retrieve and save information to the database and use that
 * information to build the various objects required by the applicaiton.
 * 
 * The class has several hard coded static variables used for the connection, you will need to
 * change those to your connection information
 * 
 * This class also has static string variables for pickup, delivery and dine-in. 
 * DO NOT change these constant values.
 * 
 * You can add any helper methods you need, but you must implement all the methods
 * in this class and use them to complete the project.  The autograder will rely on
 * these methods being implemented, so do not delete them or alter their method
 * signatures.
 * 
 * Make sure you properly open and close your DB connections in any method that
 * requires access to the DB.
 * Use the connect_to_db below to open your connection in DBConnector.
 * What is opened must be closed!
 */

/*
 * A utility class to help add and retrieve information from the database
 */

public final class DBNinja {
	private static Connection conn;

	// DO NOT change these variables!
	public final static String pickup = "pickup";
	public final static String delivery = "delivery";
	public final static String dine_in = "dinein";

	public final static String size_s = "Small";
	public final static String size_m = "Medium";
	public final static String size_l = "Large";
	public final static String size_xl = "XLarge";

	public final static String crust_thin = "Thin";
	public final static String crust_orig = "Original";
	public final static String crust_pan = "Pan";
	public final static String crust_gf = "Gluten-Free";

	public enum order_state {
		PREPARED,
		DELIVERED,
		PICKEDUP
	}


	private static boolean connect_to_db() throws SQLException, IOException 
	{

		try {
			conn = DBConnector.make_connection();
			return true;
		} catch (SQLException e) {
			return false;
		} catch (IOException e) {
			return false;
		}

	}

	public static void addOrder(Order o) throws SQLException, IOException {
		/*
		 * add code to add the order to the DB. Remember that we're not just
		 * adding the order to the order DB table, but we're also recording
		 * the necessary data for the delivery, dinein, pickup, pizzas, toppings
		 * on pizzas, order discounts and pizza discounts.
		 * 
		 * This is a KEY method as it must store all the data in the Order object
		 * in the database and make sure all the tables are correctly linked.
		 * 
		 * Remember, if the order is for Dine In, there is no customer...
		 * so the cusomter id coming from the Order object will be -1.
		 * 
		 */
		// Connect to the database
		connect_to_db();
		// Initialize orderID to -1
		int orderID = -1;

		// query to insert the order
		String orderQuery = "INSERT INTO ordertable (customer_CustID, ordertable_OrderType, ordertable_OrderDateTime, " +
				"ordertable_CustPrice, ordertable_BusPrice, ordertable_isComplete) " +
				"VALUES (?, ?, ?, ?, ?, ?)";
		// execute the query and populate the order object
		try (PreparedStatement orderStmt = conn.prepareStatement(orderQuery, Statement.RETURN_GENERATED_KEYS)) {
			// Set the customer ID to null if it's a Dine-In order
			if (o.getCustID() == -1) {
				orderStmt.setNull(1, java.sql.Types.INTEGER); // Null for Dine-In orders
			} else {
				orderStmt.setInt(1, o.getCustID());
			}
			// Set the parameters for the order
			orderStmt.setString(2, o.getOrderType());
			orderStmt.setString(3, o.getDate());
			orderStmt.setDouble(4, o.getCustPrice());
			orderStmt.setDouble(5, o.getBusPrice());
			orderStmt.setBoolean(6, o.getIsComplete());
			//checks to see if order was inserted to database
			int rowsInserted = orderStmt.executeUpdate();
			if (rowsInserted == 0) {
				throw new SQLException("Failed to insert the order into the database.");
			}

			// Retrieve generated order ID
			try (ResultSet generatedKeys = orderStmt.getGeneratedKeys()) {
				if (generatedKeys.next()) {
					orderID = generatedKeys.getInt(1);
				} else {
					throw new SQLException("Failed to retrieve the generated order ID.");
				}
			}
		}

		// Insert order-specific data based on subtype
		switch (o.getOrderType()) {
			// Insert data for dine-in orders
			case dine_in:
				if (o instanceof DineinOrder) {
					// query to insert the dine-in order
					String dineinQuery = "INSERT INTO dinein (ordertable_OrderID, dinein_TableNum) " +
							"VALUES (?, ?)";
					// execute the query and populate the dine-in object
					try (PreparedStatement dineinStmt = conn.prepareStatement(dineinQuery)) {
						dineinStmt.setInt(1, orderID);
						dineinStmt.setInt(2, ((DineinOrder) o).getTableNum());
						dineinStmt.executeUpdate();
					}
				}
				break;
			// Insert data for delivery orders
			case delivery:
				if (o.getOrderType().equals(delivery)) {
					// query to insert the delivery order
					String deliveryQuery = "INSERT INTO delivery (ordertable_OrderID, delivery_HouseNum, " +
							"delivery_Street, delivery_City, delivery_State, delivery_Zip, delivery_isDelivered) " +
							"VALUES (?, ?, ?, ?, ?, ?, ?)";
					// execute the query and populate the delivery object
					try (PreparedStatement deliveryStmt = conn.prepareStatement(deliveryQuery)) {
						DeliveryOrder deliveryOrder = (DeliveryOrder) o;
						String[] addressParts = deliveryOrder.getAddress().split("\t");
						deliveryStmt.setInt(1, orderID);
						deliveryStmt.setInt(2, Integer.parseInt(addressParts[0]));
						deliveryStmt.setString(3, addressParts[1]);
						deliveryStmt.setString(4, addressParts[2]);
						deliveryStmt.setString(5, addressParts[3]);
						deliveryStmt.setInt(6, Integer.parseInt(addressParts[4]));
						deliveryStmt.setBoolean(7, deliveryOrder.getIsComplete());
						deliveryStmt.executeUpdate();
					}
				}
				break;
			// Insert data for pickup orders
			case pickup:
				if (o instanceof PickupOrder) {
					// query to insert the pickup order
					String pickupQuery = "INSERT INTO pickup (ordertable_OrderID, pickup_IsPickedUp) " +
							"VALUES (?, ?)";
					// execute the query and populate the pickup object
					try (PreparedStatement pickupStmt = conn.prepareStatement(pickupQuery)) {
						pickupStmt.setInt(1, orderID);
						pickupStmt.setBoolean(2, ((PickupOrder) o).getIsPickedUp());
						pickupStmt.executeUpdate();
					}
				}
				break;
		}

		// Insert pizzas
		for (Pizza pizza : o.getPizzaList()) {
			pizza.setOrderID(orderID);
			addPizza(java.sql.Timestamp.valueOf(o.getDate()), orderID, pizza);
		}
		// query to insert the order discount
		connect_to_db();
		String discountQuery = "INSERT INTO order_discount (ordertable_OrderID, discount_DiscountID) " +
				"VALUES (?, ?)";
		// execute the query and populate the discount object
		try (PreparedStatement discountStmt = conn.prepareStatement(discountQuery)) {
			for (Discount discount : o.getDiscountList()) {
				discountStmt.setInt(1, orderID);
				discountStmt.setInt(2, discount.getDiscountID());
				discountStmt.executeUpdate();
			}
		}

		close_connection();
	}

		// This helper function was added to close connections to the database
		private static int connectionRefCount = 0;

		private static void close_connection() throws SQLException {
			connectionRefCount--;
			if (connectionRefCount <= 0 && conn != null && !conn.isClosed()) {
				conn.close();
				conn = null; // Resets connection for safety
				connectionRefCount = 0;
			}
		}
	
	public static int addPizza(java.util.Date d, int orderID, Pizza p) throws SQLException, IOException {
		/*
		* Add the code needed to insert the pizza into into the database.
		* Keep in mind you must also add the pizza discounts and toppings 
		* associated with the pizza.
		* 
		* NOTE: there is a Date object passed into this method so that the Order
		* and ALL its Pizzas can be assigned the same DTS.
		* 
		* This method returns the id of the pizza just added.
		* 
		*/
		// Connect to the database
		connect_to_db();
		// Initialize pizzaID to -1
		int pizzaID = -1;
 
		// query to insert the pizza
		String pizzaQuery = "INSERT INTO pizza (pizza_Size, pizza_CrustType, ordertable_OrderID, " +
				"pizza_PizzaState, pizza_PizzaDate, pizza_CustPrice, pizza_BusPrice) " +
				"VALUES (?, ?, ?, ?, ?, ?, ?)";
		// execute the query and populate the pizza object
		try (PreparedStatement pizzaStmt = conn.prepareStatement(pizzaQuery, Statement.RETURN_GENERATED_KEYS)) {
			// Set the parameters for the pizza
			pizzaStmt.setString(1, p.getSize());
			pizzaStmt.setString(2, p.getCrustType());
			pizzaStmt.setInt(3, orderID);
			pizzaStmt.setString(4, p.getPizzaState());
			pizzaStmt.setTimestamp(5, new java.sql.Timestamp(d.getTime()));
			pizzaStmt.setDouble(6, p.getCustPrice());
			pizzaStmt.setDouble(7, p.getBusPrice());
			int rowsInserted = pizzaStmt.executeUpdate();
			// Check if the pizza was inserted successfully
			if (rowsInserted == 0) {
				throw new SQLException("Failed to insert pizza into the database.");
			}
 
			// Retrieve generated pizza ID
			try (ResultSet generatedKeys = pizzaStmt.getGeneratedKeys()) {
				if (generatedKeys.next()) {
					pizzaID = generatedKeys.getInt(1);
				} else {
					throw new SQLException("Failed to retrieve the generated pizza ID.");
				}
			}
		}
 
		 // Query to insert toppings on pizza
		String toppingQuery = "INSERT INTO pizza_topping (pizza_PizzaID, topping_TopID, pizza_topping_isDouble) " +
				"VALUES (?, ?, ?)";
		// execute the query and populate the topping object
		try (PreparedStatement toppingStmt = conn.prepareStatement(toppingQuery)) {
			for (Topping t : p.getToppings()) {
				// Set the parameters for the topping
				toppingStmt.setInt(1, pizzaID);
				toppingStmt.setInt(2, t.getTopID());
				toppingStmt.setBoolean(3, t.getDoubled());
				toppingStmt.executeUpdate();
 
				// Update topping inventory
				String updateInventoryQuery = "UPDATE topping " +
						"SET topping_CurINVT = topping_CurINVT - ? " +
						"WHERE topping_TopID = ?";
				try (PreparedStatement updateStmt = conn.prepareStatement(updateInventoryQuery)) {
					Double num_toppings = 0.0;
					// Get the number of toppings based on the pizza size
					switch (p.getSize()) {
						case size_s:
							num_toppings = t.getSmallAMT();
							break;
						case size_m:
							num_toppings = t.getMedAMT();
							break;
						case size_l:
							num_toppings = t.getLgAMT();
							break;
						case size_xl:
							num_toppings = t.getXLAMT();
							break;
						default:
							throw new IllegalArgumentException("Invalid pizza size: " + p.getSize());
					}
					// Double the number of toppings if applicable
					if (t.getDoubled()) {
						num_toppings = num_toppings * 2;
					}
 
					// Round up the number of toppings 
					num_toppings = Math.ceil(num_toppings);
					// updates the extra toppings on the pizza
					updateStmt.setDouble(1, num_toppings);
					updateStmt.setInt(2, t.getTopID());
					updateStmt.executeUpdate();
				}
			}
		}
 
		 // Insert discounts for pizza
		 String discountQuery = "INSERT INTO pizza_discount (pizza_PizzaID, discount_DiscountID) " +
				"VALUES (?, ?)";
		 // Loop through the discounts and insert them
		 try (PreparedStatement discountStmt = conn.prepareStatement(discountQuery)) {
			for (Discount di : p.getDiscounts()) {
				discountStmt.setInt(1, pizzaID);
				discountStmt.setInt(2, di.getDiscountID());
 				 discountStmt.executeUpdate();
			}
		}
 
		close_connection();
		return pizzaID;
	}
	
	public static int addCustomer(Customer c) throws SQLException, IOException {
		/*
		* This method adds a new customer to the database.
		* 
		*/
		// Connect to the database
		connect_to_db();
		// query to insert the customer
		String query = "INSERT INTO customer (customer_FName, customer_LName, customer_PhoneNum) " +
				"VALUES (?, ?, ?)";
		// execute the query and populate the customer object
		try (PreparedStatement stmt = conn.prepareStatement(query, Statement.RETURN_GENERATED_KEYS)) {
			stmt.setString(1, c.getFName());
			stmt.setString(2, c.getLName());
			stmt.setString(3, c.getPhone());
 
			int rowsInserted = stmt.executeUpdate();
			if (rowsInserted == 0) {
				throw new SQLException("Failed to add the customer.");
			}
 
			// Retrieve generated customer ID
			try (ResultSet generatedKeys = stmt.getGeneratedKeys()) {
				if (generatedKeys.next()) {
					return generatedKeys.getInt(1);
				} else {
					throw new SQLException("Failed to retrieve the customer ID.");
				}
			}
		} finally {
			close_connection();
		}
	}

	public static void completeOrder(int OrderID, order_state newState ) throws SQLException, IOException {
		/*
		 * Mark that order as complete in the database.
		 * Note: if an order is complete, this means all the pizzas are complete as well.
		 * However, it does not mean that the order has been delivered or picked up!
		 *
		 * For newState = PREPARED: mark the order and all associated pizza's as completed
		 * For newState = DELIVERED: mark the delivery status
		 * FOR newState = PICKEDUP: mark the pickup status
		 * 
		 */
		// Connect to the database
		connect_to_db();
		// Update the order state based on the newState
		try {
			if (newState == order_state.PREPARED) {
				// Mark the order as complete
				String orderQuery = "UPDATE ordertable " +
						"SET ordertable_isComplete = 1 " +
						"WHERE ordertable_OrderID = ?";
				try (PreparedStatement orderStmt = conn.prepareStatement(orderQuery)) {
					orderStmt.setInt(1, OrderID);
					orderStmt.executeUpdate();
				}

				// Mark all pizzas in the order as prepared
				String pizzaQuery = "UPDATE pizza SET " +
						"pizza_PizzaState = 'Prepared' " +
						"WHERE ordertable_OrderID = ?";
				try (PreparedStatement pizzaStmt = conn.prepareStatement(pizzaQuery)) {
					pizzaStmt.setInt(1, OrderID);
					pizzaStmt.executeUpdate();
				}
			} else if (newState == order_state.PICKEDUP) {
				// Mark the pickup order as picked up
				String pickupQuery = "UPDATE pickup " +
						"SET pickup_IsPickedUp = 1 " +
						"WHERE ordertable_OrderID = ?";
				try (PreparedStatement pickupStmt = conn.prepareStatement(pickupQuery)) {
					pickupStmt.setInt(1, OrderID);
					pickupStmt.executeUpdate();
				}
			} else if (newState == order_state.DELIVERED) {
				// Mark the delivery order as delivered
				String deliveryQuery = "UPDATE delivery " +
						"SET delivery_IsDelivered = 1 " +
						"WHERE ordertable_OrderID = ?";
				try (PreparedStatement deliveryStmt = conn.prepareStatement(deliveryQuery)) {
					deliveryStmt.setInt(1, OrderID);
					deliveryStmt.executeUpdate();
				}
			} else {
				// Invalid order state
				throw new IllegalArgumentException("Invalid order state provided.");
			}
		} finally {
			close_connection();
		}
	}


	public static ArrayList<Order> getOrders(int status) throws SQLException, IOException {
		/*
		 * Return an ArrayList of orders.
		 * 	status   == 1 => return a list of open (ie oder is not completed)
		 *           == 2 => return a list of completed orders (ie order is complete)
		 *           == 3 => return a list of all the orders
		 * Remember that in Java, we account for supertypes and subtypes
		 * which means that when we create an arrayList of orders, that really
		 * means we have an arrayList of dineinOrders, deliveryOrders, and pickupOrders.
		 *
		 * You must fully populate the Order object, this includes order discounts,
		 * and pizzas along with the toppings and discounts associated with them.
		 *
		 * Don't forget to order the data coming from the database appropriately.
		 *
		 */
		// Connect to the database
		connect_to_db();
		// Initialize an empty list of orders
		ArrayList<Order> ordersList = new ArrayList<>();

		// variables to hold the order information and order types and status
		DeliveryOrder Deliveryorder;
		DineinOrder DineInorder;
		PickupOrder Pickuporder;
		PreparedStatement stmtDelivery = null;
		PreparedStatement stmtDineIn = null;
		PreparedStatement stmtPickUp = null;
		PreparedStatement stmt = null;
		ResultSet rsOrder = null;
		ResultSet rsDelivery = null;
		ResultSet rsDineIn = null;
		ResultSet rsPickUp = null;
		int tableNum = -1;
		boolean ispickedUp = true;

		String queryOrder = null;
		// Query to retrieve orders based on status
		if(status == 1){
			queryOrder = "SELECT * FROM ordertable WHERE ordertable_isComplete = 0 ORDER BY ordertable_OrderDateTime ASC";
		} else if (status == 2){
			queryOrder = "SELECT * FROM ordertable WHERE ordertable_isComplete = 1 ORDER BY ordertable_OrderDateTime ASC";
		} else if (status == 3){
			queryOrder = "SELECT * FROM ordertable ORDER BY ordertable_OrderDateTime ASC";
		}
		// Execute the query and populate the order list
		stmt = conn.prepareStatement(queryOrder);
		rsOrder = stmt.executeQuery();

		// Loop through the result set and create order objects
		while(rsOrder.next()){
			int OrderID = rsOrder.getInt("ordertable_OrderID");
			int CustID = rsOrder.getInt("customer_CustID");
			String OrderType = rsOrder.getString("ordertable_OrderType");
			String OrderString = rsOrder.getString("ordertable_OrderDateTime");
			java.sql.Date orderDate = rsOrder.getDate("ordertable_OrderDateTime");
			double CustPrice = rsOrder.getDouble("ordertable_CustPrice");
			double BusPrice = rsOrder.getDouble("ordertable_BusPrice");
			boolean isComplete = rsOrder.getBoolean("ordertable_isComplete");

			// if order type is delivery, get the delivery information
			if(OrderType.equals(delivery)){
				connect_to_db();
				// query to get the delivery information
				String queryOrderDelivery = "SELECT delivery_HouseNum, delivery_Street, delivery_City, delivery_State, delivery_Zip, delivery_IsDelivered FROM delivery WHERE ordertable_OrderID = ?";
			
				stmtDelivery = conn.prepareStatement(queryOrderDelivery);
				stmtDelivery.setInt(1, OrderID);
				rsDelivery = stmtDelivery.executeQuery();
				// check if the delivery information is present
				if(rsDelivery.next()){
					int houseNum = rsDelivery.getInt("delivery_HouseNum");
					String street = rsDelivery.getString("delivery_Street");
					String city = rsDelivery.getString("delivery_City");
					String state = rsDelivery.getString("delivery_State");
					int zipCode = rsDelivery.getInt("delivery_Zip");
					boolean IsDelivered = rsDelivery.getBoolean("delivery_IsDelivered");


					String address = String.format("%d\t%s\t%s\t%s\t%d", houseNum, street, city, state, zipCode);
					// create the delivery order object for the order list
					Deliveryorder = new  DeliveryOrder(OrderID, CustID, orderDate.toString(), CustPrice, BusPrice, isComplete, IsDelivered, address);
					ArrayList<Discount> discountList = new ArrayList<>();
					discountList = getDiscounts(Deliveryorder);
					Deliveryorder.setDiscountList(discountList);

					//populate the pizza list for the order
					ArrayList<Pizza> pizzasList = new ArrayList<>();
					pizzasList = getPizzas(Deliveryorder);
					Deliveryorder.setPizzaList(pizzasList);

					ordersList.add(Deliveryorder);
				}
				// If order type is dine-in, get the dine-in information
			} else if(OrderType.equals(dine_in)){
				connect_to_db();
				// Query to get the dine-in information
				String queryOrderDineIn = "SELECT dinein_TableNum FROM dinein WHERE ordertable_OrderID = ?";
				// gather the dine-in information
				stmtDineIn = conn.prepareStatement(queryOrderDineIn);
				stmtDineIn.setInt(1, OrderID);
				rsDineIn = stmtDineIn.executeQuery();

				if(rsDineIn.next()){
					tableNum = rsDineIn.getInt("dinein_TableNum");
				}
				// create the dine-in order object for the order list
				DineInorder = new DineinOrder(OrderID, CustID, OrderString, CustPrice, BusPrice, isComplete, tableNum);

				ArrayList<Discount> discountList = new ArrayList<>();
				discountList = getDiscounts(DineInorder);
				DineInorder.setDiscountList(discountList);



				//populate the pizza for the order
				ArrayList<Pizza> pizzasList = new ArrayList<>();
				pizzasList = getPizzas(DineInorder);
				DineInorder.setPizzaList(pizzasList);

				ordersList.add(DineInorder);
			// If order type is pickup, get the pickup information
			} else if(OrderType.equals(pickup)){
				connect_to_db();
				// Query to get the pickup information
				String queryOrderPickup = "SELECT pickup_IsPickedUp FROM pickup WHERE ordertable_OrderID = ?";
				// gather the pickup information
				stmtPickUp = conn.prepareStatement(queryOrderPickup);
				stmtPickUp.setInt(1, OrderID);
				rsPickUp = stmtPickUp.executeQuery();
				if(rsPickUp.next()){
					ispickedUp = rsPickUp.getBoolean("pickup_IsPickedUP");
				}
				// create the pickup order object for the order list
				Pickuporder = new PickupOrder(OrderID, CustID, OrderString, CustPrice, BusPrice, ispickedUp, isComplete);

				ArrayList<Discount> discountList = new ArrayList<>();
				discountList = getDiscounts(Pickuporder);
				Pickuporder.setDiscountList(discountList);



				//populate the pizza list for the order
				ArrayList<Pizza> pizzasList = new ArrayList<>();
				pizzasList = getPizzas(Pickuporder);
				Pickuporder.setPizzaList(pizzasList);

				ordersList.add(Pickuporder);
			}

		}
		// return the order list
		// Sort orders by their order ID
		Collections.sort(ordersList, (o1, o2) -> Integer.compare(o1.getOrderID(), o2.getOrderID()));
		return ordersList;
	}

	public static Order getLastOrder() throws SQLException, IOException {
		/*
		 * Query the database for the LAST order added
		 * then return an Order object for that order.
		 * NOTE...there will ALWAYS be a "last order"!
		 */
		// Connect to the database
		connect_to_db();

		// Query to retrieve the last order
		String latestQuery = "SELECT * FROM ordertable ORDER BY ordertable_OrderDateTime DESC LIMIT 1";
		Order order = null;
		PreparedStatement stmtLatestOrder = conn.prepareStatement(latestQuery);
		ResultSet rsLatest = stmtLatestOrder.executeQuery();

		// Check if a result is returned
		if (rsLatest.next()) {
			int orderID = rsLatest.getInt("ordertable_OrderID");
			int customerID = rsLatest.getInt("customer_CustID");
			String orderType = rsLatest.getString("ordertable_OrderType");
			java.sql.Date orderDate = rsLatest.getDate("ordertable_OrderDateTime");
			String date = orderDate.toString();
			double custPrice = rsLatest.getDouble("ordertable_CustPrice");
			double busPrice = rsLatest.getDouble("ordertable_BusPrice");
			boolean isComplete = rsLatest.getBoolean("ordertable_isComplete");

			//If order type is pickup, get the pickup information
			if(orderType.equals(pickup)){
				// Query to get the pickup information
				String queryOrderPickup = "SELECT pickup_IsPickedUp FROM pickup WHERE ordertable_OrderID = ?";
				// gather the pickup information
				PreparedStatement stmtPickUp = conn.prepareStatement(queryOrderPickup);
				stmtPickUp.setInt(1, orderID);
				ResultSet rsPickUp = stmtPickUp.executeQuery();

				boolean isPickedUp = false;
				if(rsPickUp.next()){
					isPickedUp = rsPickUp.getBoolean("pickup_IsPickedUP");
				}
				// create the pickup order object for the last order to be returned
				PickupOrder latest = new PickupOrder(orderID, customerID, date, custPrice, busPrice, isPickedUp, isComplete);
				//populate the discount list for the last order
				ArrayList<Discount> discountList = new ArrayList<>();
				discountList = getDiscounts(latest);
				latest.setDiscountList(discountList);

				//populate the pizza list for the last order
				ArrayList<Pizza> pizzasList = new ArrayList<>();
				pizzasList = getPizzas(latest);
				latest.setPizzaList(pizzasList);
				// return the pickup order object
				return latest;
			// If order type is dine-in, get the dine-in information
			} else if(orderType.equals(dine_in)){
				String queryOrderDineIn = "SELECT dinein_TableNum FROM dinein WHERE ordertable_OrderID = ?";
				// gather the dine-in information
				PreparedStatement stmtDineIn = conn.prepareStatement(queryOrderDineIn);
				stmtDineIn.setInt(1, orderID);
				ResultSet rsDineIn = stmtDineIn.executeQuery();

				int tableNum = 0;

				if(rsDineIn.next()){
					tableNum = rsDineIn.getInt("dinein_TableNum");
				}
				// create the dine in order object for the last order to be returned
				DineinOrder latest = new DineinOrder(orderID, customerID, date, custPrice, busPrice, isComplete, tableNum);
				// populate the discount list for the last order
				ArrayList<Discount> discountList = new ArrayList<>();
				discountList = getDiscounts(latest);
				latest.setDiscountList(discountList);

				//populate the pizza list for the last order
				ArrayList<Pizza> pizzasList = new ArrayList<>();
				pizzasList = getPizzas(latest);
				latest.setPizzaList(pizzasList);
				// return the dine in order object
				return latest;
			// If order type is delivery, get the delivery information
			}else if(orderType.equals(delivery)){
				// Query to get the delivery information
				String queryOrderDelivery = "SELECT delivery_HouseNum, delivery_Street, delivery_City, delivery_State, delivery_Zip, delivery_IsDelivered FROM delivery WHERE ordertable_OrderID = ?";
				// gather the delivery information
				PreparedStatement stmtDelivery = conn.prepareStatement(queryOrderDelivery);
				stmtDelivery.setInt(1, orderID);
				ResultSet rsDelivery = stmtDelivery.executeQuery();
				// check if the delivery information is present
				if(rsDelivery.next()){
					// retrieve the delivery information
					int houseNum = rsDelivery.getInt("delivery_HouseNum");
					String street = rsDelivery.getString("delivery_Street");
					String city = rsDelivery.getString("delivery_City");
					String state = rsDelivery.getString("delivery_State");
					int zipCode = rsDelivery.getInt("delivery_Zip");
					boolean IsDelivered = rsDelivery.getBoolean("delivery_IsDelivered");


					String address = String.format("%d\t%s\t%s\t%s\t%d", houseNum, street, city, state, zipCode);
					// create the delivery order object for the last order to be returned
					DeliveryOrder latest = new DeliveryOrder(orderID, customerID, date, custPrice, busPrice, isComplete, IsDelivered, address);
					// populate the discount list for the last order
					ArrayList<Discount> discountList = new ArrayList<>();
					discountList = getDiscounts(latest);
					latest.setDiscountList(discountList);

					//populate the pizza  list for the last order
					ArrayList<Pizza> pizzasList = new ArrayList<>();
					pizzasList = getPizzas(latest);
					latest.setPizzaList(pizzasList);
					// return the delivery order object
					return latest;
				}

			}
		}
		// return the order object 
		return order;

	}


	public static ArrayList<Order> getOrdersByDate(String date) throws SQLException, IOException {
		/*
		 * Query the database for ALL the orders placed on a specific date
		 * and return a list of those orders.
		 *
		 */
		// Connect to the database
		connect_to_db();
		// Initialize an empty list of orders
		ArrayList<Order> dateOrder = new ArrayList<>(); 
		// variables to hold the order information and order types
		PreparedStatement stmtDatedOrders = null;
		ResultSet rsDatedOrders = null;
		DeliveryOrder Deliveryorder;
		DineinOrder DineInorder;
		PickupOrder Pickuporder;

		// Query to get all orders placed on the specific date
		String datedQuery = "SELECT * FROM ordertable WHERE DATE(ordertable_OrderDateTime) = ?";

		stmtDatedOrders = conn.prepareStatement(datedQuery);
		stmtDatedOrders.setString(1, date);  // Set the date parameter for the query
		rsDatedOrders = stmtDatedOrders.executeQuery();

		// Loop through the results and add each order to the ArrayList
		while (rsDatedOrders.next()) {
			// Retrieve order information from the result set
			int orderID = rsDatedOrders.getInt("ordertable_OrderID");
			int customerID = rsDatedOrders.getInt("customer_CustID");
			String orderType = rsDatedOrders.getString("ordertable_OrderType");
			java.sql.Date orderDate = rsDatedOrders.getDate("ordertable_OrderDateTime");
			String orderDateString = orderDate.toString();
			double custPrice = rsDatedOrders.getDouble("ordertable_CustPrice");
			double busPrice = rsDatedOrders.getDouble("ordertable_BusPrice");
			boolean isComplete = rsDatedOrders.getBoolean("ordertable_isComplete");
			// If order type is pickup, get the pickup information
			if(orderType.equals(pickup)){
				// Query to get the pickup information
				String queryOrderPickup = "SELECT pickup_IsPickedUp FROM pickup WHERE ordertable_OrderID = ?";
				// gather the pickup information
				PreparedStatement stmtPickUp = conn.prepareStatement(queryOrderPickup);
				stmtPickUp.setInt(1, orderID);
				ResultSet rsPickUp = stmtPickUp.executeQuery();

				boolean isPickedUp = false;
				if(rsPickUp.next()){
					isPickedUp = rsPickUp.getBoolean("pickup_IsPickedUP");
				}
				// create the pickup order object for the order list by date
				Pickuporder = new PickupOrder(orderID, customerID, date, custPrice, busPrice, isPickedUp, isComplete);
				// populate the discount list for the order
				ArrayList<Discount> discountList = new ArrayList<>();
				discountList = getDiscounts(Pickuporder);
				Pickuporder.setDiscountList(discountList);

				//populate the pizza list for the order list by date
				ArrayList<Pizza> pizzasList = new ArrayList<>();
				pizzasList = getPizzas(Pickuporder);
				Pickuporder.setPizzaList(pizzasList);

				dateOrder.add(Pickuporder);
			// If order type is dine-in, get the dine-in information
			} else if(orderType.equals(dine_in)){
				// Query to get the dine-in information
				String queryOrderDineIn = "SELECT dinein_TableNum FROM dinein WHERE ordertable_OrderID = ?";
				// gather the dine-in information
				PreparedStatement stmtDineIn = conn.prepareStatement(queryOrderDineIn);
				stmtDineIn.setInt(1, orderID);
				ResultSet rsDineIn = stmtDineIn.executeQuery();

				int tableNum = 0;

				if(rsDineIn.next()){
					tableNum = rsDineIn.getInt("dinein_TableNum");
				}
				// create the dine in order object for the order list by date
				DineInorder = new DineinOrder(orderID, customerID, date, custPrice, busPrice, isComplete, tableNum);
				// populate the discount list for the order by date list
				ArrayList<Discount> discountList = new ArrayList<>();
				discountList = getDiscounts(DineInorder);
				DineInorder.setDiscountList(discountList);

				//populate the pizza list for the order list by date list
				ArrayList<Pizza> pizzasList = new ArrayList<>();
				pizzasList = getPizzas(DineInorder);
				DineInorder.setPizzaList(pizzasList);

				dateOrder.add(DineInorder);

			// If order type is delivery, get the delivery information
			}else if(orderType.equals(delivery)){
				// Query to get the delivery information
				String queryOrderDelivery = "SELECT delivery_HouseNum, delivery_Street, delivery_City, delivery_State, delivery_Zip, delivery_IsDelivered FROM delivery WHERE ordertable_OrderID = ?";
				// gather the delivery information
				connect_to_db();
				PreparedStatement stmtDelivery = conn.prepareStatement(queryOrderDelivery);
				stmtDelivery.setInt(1, orderID);
				ResultSet rsDelivery = stmtDelivery.executeQuery();
				// check if the delivery information is present
				if(rsDelivery.next()){
					// retrieve the delivery information
					int houseNum = rsDelivery.getInt("delivery_HouseNum");
					String street = rsDelivery.getString("delivery_Street");
					String city = rsDelivery.getString("delivery_City");
					String state = rsDelivery.getString("delivery_State");
					int zipCode = rsDelivery.getInt("delivery_Zip");
					boolean IsDelivered = rsDelivery.getBoolean("delivery_IsDelivered");


					String address = String.format("%d\t%s\t%s\t%s\t%d", houseNum, street, city, state, zipCode);
					// create the delivery order object for the order list by date
					Deliveryorder = new DeliveryOrder(orderID, customerID, orderDateString, custPrice, busPrice, isComplete, IsDelivered, address);
					// populate the discount list for the order by date list
					ArrayList<Discount> discountList = new ArrayList<>();
					discountList = getDiscounts(Deliveryorder);
					Deliveryorder.setDiscountList(discountList);

					//populate the pizza list for the order list by date list
					ArrayList<Pizza> pizzasList = new ArrayList<>();
					pizzasList = getPizzas(Deliveryorder);
					Deliveryorder.setPizzaList(pizzasList);

					dateOrder.add(Deliveryorder);
				}

			}
		}
		// return the order list by date
		return dateOrder;
	}

		
	public static ArrayList<Discount> getDiscountList() throws SQLException, IOException {
		/* 
		 * Query the database for all the available discounts and 
		 * return them in an arrayList of discounts ordered by discount name.
		 * 
		*/
		// Initialize an empty list of discounts
		ArrayList<Discount> discountList = new ArrayList<>();
		// Connect to the database
		connect_to_db();
		// Query to retrieve all discounts
		String query = "SELECT discount_DiscountID, discount_DiscountName, discount_Amount, discount_IsPercent " +
				"FROM discount " +
				"ORDER BY discount_DiscountName;";
		// Execute the query and populate the discount list
		try (PreparedStatement stmt = conn.prepareStatement(query); ResultSet rs = stmt.executeQuery()) {
			while (rs.next()) {
				// Retrieve discount details from the result set
				int discountID = rs.getInt("discount_DiscountID");
				String discountName = rs.getString("discount_DiscountName");
				double amount = rs.getDouble("discount_Amount");
				boolean isPercent = rs.getBoolean("discount_IsPercent");
				// Create and add a Discount object to the list
				Discount discount = new Discount(discountID, discountName, amount, isPercent);
				discountList.add(discount);
			}
			// Handle any SQL exceptions
		} catch (SQLException e) {
			e.printStackTrace();
			throw new SQLException("Error retrieving discount list", e);
		} finally {
			if (conn != null && !conn.isClosed()) {
				close_connection();
			}
		}

		return discountList;
	}

	public static Discount findDiscountByName(String name) throws SQLException, IOException {
		/*
		 * Query the database for a discount using it's name.
		 * If found, then return an OrderDiscount object for the discount.
		 * If it's not found....then return null
		 *  
		 */
		// connect to the database
		connect_to_db();
		// query to find the discount by name
		String query = "SELECT discount_DiscountID, discount_DiscountName, discount_Amount, discount_IsPercent " +
				"FROM discount " +
				"WHERE discount_DiscountName = ?;";
		// execute the query and populate the discount object
		try (PreparedStatement stmt = conn.prepareStatement(query)) {
			stmt.setString(1, name); // Sets the name parameter in the query
			try (ResultSet rs = stmt.executeQuery()) {
				if (rs.next()) {
					// Retrieve discount details from the result set
					int discountID = rs.getInt("discount_DiscountID");
					String discountName = rs.getString("discount_DiscountName");
					double amount = rs.getDouble("discount_Amount");
					boolean isPercent = rs.getBoolean("discount_IsPercent");
					// Create and return a Discount object with retrieved details
					return new Discount(discountID, discountName, amount, isPercent);
				}
			}
			// Handle any SQL exceptions
		} catch (SQLException e) {
			e.printStackTrace();
			throw new SQLException("Error retrieving discount by name", e);
		} finally {
			if (conn != null && !conn.isClosed()) {
				close_connection();
			}
		}

		return null;
	}


	public static ArrayList<Customer> getCustomerList() throws SQLException, IOException {
		/*
		 * Query the data for all the customers and return an arrayList of all the customers. 
		 * Don't forget to order the data coming from the database appropriately.
		 * 
		*/
		// Initialize an empty list of customers
		ArrayList<Customer> customerList = new ArrayList<>();
		// Connect to the database
		connect_to_db();
		// Query to retrieve all customers
		String query = "SELECT customer_CustID, customer_FName, customer_LName,customer_PhoneNum " +
				"FROM customer " +
				"ORDER BY customer_LName, customer_FName, customer_PhoneNum;";
		// Execute the query and populate the customer list
		try (PreparedStatement stmt = conn.prepareStatement(query); ResultSet rs = stmt.executeQuery()) {
			while (rs.next()) {
				// Retrieve customer details from the result set
				int custID = rs.getInt("customer_CustID");
				String fName = rs.getString("customer_FName");
				String lName = rs.getString("customer_LName");
				String phone = rs.getString("customer_PhoneNum");
				// Create and add a Customer object to the list
				Customer customer = new Customer(custID, fName, lName, phone);
				customerList.add(customer);
			}
			// Handle any SQL exceptions
		} catch (SQLException e) {
			e.printStackTrace();
			throw new SQLException("Error retrieving customer list", e);
		} finally {
			if (conn != null && !conn.isClosed()) {
				close_connection();
			}
		}

		return customerList;
	}

	public static Customer findCustomerByPhone(String phoneNumber)  throws SQLException, IOException {
		/*
		 * Query the database for a customer using a phone number.
		 * If found, then return a Customer object for the customer.
		 * If it's not found....then return null
		 *  
		 */
		// connect to the database
		connect_to_db();
		// query to find the customer by phone number
		String query = "SELECT customer_CustID, customer_FName, customer_LName, customer_PhoneNum " +
				"FROM customer " +
				"WHERE customer_PhoneNum = ?;";
		// execute the query and populate the customer object
		try (PreparedStatement stmt = conn.prepareStatement(query)) {
			stmt.setString(1, phoneNumber); // Set phone number parameter in the query
			try (ResultSet rs = stmt.executeQuery()) {
				if (rs.next()) {
					// Retrieve customer details from the result set
					int custID = rs.getInt("customer_CustID");
					String firstName = rs.getString("customer_FName");
					String lastName = rs.getString("customer_LName");
					String phone = rs.getString("customer_PhoneNum");
					// Create and return a Customer object with retrieved details
					return new Customer(custID, firstName, lastName, phone);
				}
			}
			// Handle any SQL exceptions
		} catch (SQLException e) {
			e.printStackTrace();
			throw new SQLException("Error retrieving customer by phone number", e);
		} finally {
			if (conn != null && !conn.isClosed()) {
				close_connection();
			}
		}

		return null;
	}

	public static String getCustomerName(int CustID) throws SQLException, IOException {
		/*
		 * COMPLETED...WORKING Example!
		 * 
		 * This is a helper method to fetch and format the name of a customer
		 * based on a customer ID. This is an example of how to interact with
		 * your database from Java.  
		 * 
		 * Notice how the connection to the DB made at the start of the 
		 *
		 */

		 connect_to_db();

		/* 
		 * an example query using a constructed string...
		 * remember, this style of query construction could be subject to sql injection attacks!
		 * 
		 */
		String cname1 = "";
		String cname2 = "";
		String query = "Select customer_FName, customer_LName From customer WHERE customer_CustID=" + CustID + ";";
		Statement stmt = conn.createStatement();
		ResultSet rset = stmt.executeQuery(query);
		
		while(rset.next())
		{
			cname1 = rset.getString(1) + " " + rset.getString(2); 
		}

		/* 
		* an BETTER example of the same query using a prepared statement...
		* with exception handling
		* 
		*/
		try {
			PreparedStatement os;
			ResultSet rset2;
			String query2;
			query2 = "Select customer_FName, customer_LName From customer WHERE customer_CustID=?;";
			os = conn.prepareStatement(query2);
			os.setInt(1, CustID);
			rset2 = os.executeQuery();
			while(rset2.next())
			{
				cname2 = rset2.getString("customer_FName") + " " + rset2.getString("customer_LName"); // note the use of field names in the getSting methods
			}
		} catch (SQLException e) {
			e.printStackTrace();
			// process the error or re-raise the exception to a higher level
		}

		conn.close();

		return cname1;
		// OR
		// return cname2;

	}


	public static ArrayList<Topping> getToppingList() throws SQLException, IOException 
	{
		/*
		 * Query the database for the aviable toppings and 
		 * return an arrayList of all the available toppings. 
		 * Don't forget to order the data coming from the database appropriately.
		 * 
		 */
		// Initialize an empty list of toppings
		ArrayList<Topping> toppingList = new ArrayList<>();
		// Connect to the database
		connect_to_db();
		// Query to retrieve all toppings
		String query = "SELECT topping_TopID, topping_TopName, topping_SmallAMT, topping_MedAMT, topping_LgAMT, " +
				"topping_XLAMT, topping_CustPrice, topping_BusPrice, topping_MinINVT, topping_CurINVT " +
				"FROM topping " +
				"ORDER BY topping_TopName;";
		// Execute the query and populate the topping list
		try (PreparedStatement stmt = conn.prepareStatement(query); ResultSet rs = stmt.executeQuery()) {
			while (rs.next()) {
				// Retrieve topping details from the result set
				int topID = rs.getInt("topping_TopID");
				String topName = rs.getString("topping_TopName");
				double smallAMT = rs.getDouble("topping_SmallAMT");
				double medAMT = rs.getDouble("topping_MedAMT");
				double lgAMT = rs.getDouble("topping_LgAMT");
				double xlAMT = rs.getDouble("topping_XLAMT");
				double custPrice = rs.getDouble("topping_CustPrice");
				double busPrice = rs.getDouble("topping_BusPrice");
				int minINVT = rs.getInt("topping_MinINVT");
				int curINVT = rs.getInt("topping_CurINVT");
				// Create a Topping object to represent the topping
				// and add it to the list
				Topping topping = new Topping(topID, topName, smallAMT, medAMT, lgAMT, xlAMT, custPrice, busPrice, minINVT, curINVT);
				toppingList.add(topping);
			}
			// Handle any SQL exceptions
		} catch (SQLException e) {
			e.printStackTrace();
			throw new SQLException("Error retrieving topping list", e);
		} finally {
			if (conn != null && !conn.isClosed()) {
				close_connection();
			}
		}

		return toppingList;
	}

	public static Topping findToppingByName(String name) throws SQLException, IOException {
		/*
		 * Query the database for the topping using it's name.
		 * If found, then return a Topping object for the topping.
		 * If it's not found....then return null
		 *  
		 */
		// Connect to the database
		connect_to_db();
		// Query to retrieve topping by name
		String query = "SELECT topping_TopID, topping_TopName, topping_SmallAMT, topping_MedAMT, topping_LgAMT, " +
				"topping_XLAMT, topping_CustPrice, topping_BusPrice, topping_MinINVT, topping_CurINVT " +
				"FROM topping " +
				"WHERE topping_TopName = ?;";
		// Execute the query
		try (PreparedStatement stmt = conn.prepareStatement(query)) {
			stmt.setString(1, name); // Set topping name parameter in the query
			try (ResultSet rs = stmt.executeQuery()) {
				if (rs.next()) {
					// Retrieve topping details from the result set
					int topID = rs.getInt("topping_TopID");
					String toppingName = rs.getString("topping_TopName");
					double smallAMT = rs.getDouble("topping_SmallAMT");
					double medAMT = rs.getDouble("topping_MedAMT");
					double lgAMT = rs.getDouble("topping_LgAMT");
					double xlAMT = rs.getDouble("topping_XLAMT");
					double custPrice = rs.getDouble("topping_CustPrice");
					double busPrice = rs.getDouble("topping_BusPrice");
					int minINVT = rs.getInt("topping_MinINVT");
					int curINVT = rs.getInt("topping_CurINVT");

					return new Topping(topID, toppingName, smallAMT, medAMT, lgAMT, xlAMT, custPrice, busPrice, minINVT, curINVT);
				}
			}
			// Handle any SQL exceptions
		} catch (SQLException e) {
			e.printStackTrace();
			throw new SQLException("Error retrieving topping by name", e);
		} finally {
			if (conn != null && !conn.isClosed()) {
				close_connection();
			}
		}

		return null;
	}


	public static ArrayList<Topping> getToppingsOnPizza(Pizza p) throws SQLException, IOException {
		/* 
		* This method builds an ArrayList of the toppings ON a pizza.
		* The list can then be added to the Pizza object elsewhere in the
		*/
		// Initialize an empty list of toppings
		ArrayList<Topping> toppings = new ArrayList<>();
		// Connect to the database
		connect_to_db();
		// Query to retrieve toppings associated with the pizza
		String query = "SELECT t.topping_TopID, t.topping_TopName, t.topping_SmallAMT, t.topping_MedAMT, " +
				"t.topping_LgAMT, t.topping_XLAMT, t.topping_CustPrice, t.topping_BusPrice, " +
				"t.topping_MinINVT, t.topping_CurINVT, pt.pizza_topping_IsDouble " +
				"FROM pizza_topping pt " +
				"JOIN topping t ON pt.topping_TopID = t.topping_TopID " +
				"WHERE pt.pizza_PizzaID = ?";
		// Execute the query and populate the toppings list
		 try (PreparedStatement stmt = conn.prepareStatement(query)) {
			stmt.setInt(1, p.getPizzaID()); // Set Pizza ID in the query
			try (ResultSet rs = stmt.executeQuery()) {
				while (rs.next()) {
					// Retrieve topping details from the result set
					int topID = rs.getInt("topping_TopID");
					String topName = rs.getString("topping_TopName");
					double smallAMT = rs.getDouble("topping_SmallAMT");
					double medAMT = rs.getDouble("topping_MedAMT");
					double lgAMT = rs.getDouble("topping_LgAMT");
					double xlAMT = rs.getDouble("topping_XLAMT");
					double custPrice = rs.getDouble("topping_CustPrice");
					double busPrice = rs.getDouble("topping_BusPrice");
					int minINVT = rs.getInt("topping_MinINVT");
					int curINVT = rs.getInt("topping_CurINVT");
					boolean isDouble = rs.getBoolean("pizza_topping_isDouble");
					// Create a Topping object to represent the topping on the pizza
					Topping topping = new Topping(topID, topName, smallAMT, medAMT, lgAMT, xlAMT, custPrice, busPrice, minINVT, curINVT);
					topping.setDoubled(isDouble);
					toppings.add(topping);
				}
			}
			// Handle any SQL exceptions
		} catch (SQLException e) {
			e.printStackTrace();
			throw new SQLException("Error retrieving toppings for the pizza", e);
		} finally {
			if (conn != null && !conn.isClosed()) {
				close_connection();
			}
		}
		return toppings;
	}

	public static void addToInventory(int toppingID, double quantity) throws SQLException, IOException {
		/*
		 * Updates the quantity of the topping in the database by the amount specified.
		 * 
		 */
		// Connect to the database
		connect_to_db();
		// Query to update the topping inventory
		String query = "UPDATE topping " +
				"SET topping_CurINVT = topping_CurINVT + ? " +
				"WHERE topping_TopID = ?";
		// Execute the update
		try (PreparedStatement stmt = conn.prepareStatement(query)) {
			stmt.setDouble(1, quantity);
			stmt.setInt(2, toppingID);
			// Execute the update and check if any rows were affected
			// If no rows were affected, it means the topping ID does not exist
			int rowsUpdated = stmt.executeUpdate();
			if (rowsUpdated == 0) {
				throw new SQLException("Topping with ID " + toppingID + " does not exist.");
			}
		} finally {
			close_connection();
		}
	}
	
	
	public static ArrayList<Pizza> getPizzas(Order o) throws SQLException, IOException {
		/*
		 * Build an ArrayList of all the Pizzas associated with the Order.
		 * 
		 */
		// Initialize an empty list of pizzas
		ArrayList<Pizza> pizzas = new ArrayList<>();
		// Connect to the database
		connect_to_db();
		// Query to retrieve pizzas associated with the order
		String query = "SELECT p.pizza_PizzaID, p.pizza_CrustType, p.pizza_Size, p.ordertable_OrderID, " +
				"p.pizza_PizzaState, p.pizza_PizzaDate, p.pizza_CustPrice, p.pizza_BusPrice " +
				"FROM pizza p " +
				"WHERE p.ordertable_OrderID = ?";
		// Execute the query and populate the pizzas list
		try (PreparedStatement stmt = conn.prepareStatement(query)) {
			stmt.setInt(1, o.getOrderID()); // Set Order ID in the query
			try (ResultSet rs = stmt.executeQuery()) {
				while (rs.next()) {
					// Retrieve pizza details from the result set
					int pizzaID = rs.getInt("pizza_PizzaID");
					String crustType = rs.getString("pizza_CrustType");
					String size = rs.getString("pizza_Size");
					int orderID = rs.getInt("ordertable_OrderID");
					String state = rs.getString("pizza_PizzaState");
					String date = rs.getString("pizza_PizzaDate");
					double custPrice = rs.getDouble("pizza_CustPrice");
					double busPrice = rs.getDouble("pizza_BusPrice");

					// Create a Pizza object
					Pizza pizza = new Pizza(pizzaID, size, crustType, orderID, state, date, custPrice, busPrice);

					// Populate toppings and discounts for the pizza
					ArrayList<Topping> toppings = getToppingsOnPizza(pizza);
					pizza.setToppings(toppings);

					ArrayList<Discount> discounts = getDiscounts(pizza);
					pizza.setDiscounts(discounts);

					// Add pizza to the list
					pizzas.add(pizza);
				}
			}
		// Handle any SQL exceptions
		} catch (SQLException e) {
			e.printStackTrace();
			throw new SQLException("Error retrieving pizzas for the order", e);
		} finally {
			if (conn != null && !conn.isClosed()) {
				close_connection();
			}
		}

		return pizzas;
	}

	public static ArrayList<Discount> getDiscounts(Order o) throws SQLException, IOException {
		/* 
		 * Build an array list of all the Discounts associted with the Order.
		 * 
		 */
		// Initialize an empty list of discounts
		ArrayList<Discount> discounts = new ArrayList<>();
		// Connect to the database
		connect_to_db();
		// Query to retrieve discounts associated with the order
		String query = "SELECT d.discount_DiscountID, d.discount_DiscountName, d.discount_Amount, d.discount_IsPercent " +
				"FROM order_discount od " +
				"JOIN discount d ON od.discount_DiscountID = d.discount_DiscountID " +
				"WHERE od.ordertable_OrderID = ?";
		// Execute the query and populate the discounts list
		try (PreparedStatement stmt = conn.prepareStatement(query)) {
			stmt.setInt(1, o.getOrderID()); // Set Order ID in the query
			try (ResultSet rs = stmt.executeQuery()) {
				while (rs.next()) {
					// Retrieve discount details from the result set
					int discountID = rs.getInt("discount_DiscountID");
					String discountName = rs.getString("discount_DiscountName");
					double amount = rs.getDouble("discount_Amount");
					boolean isPercent = rs.getBoolean("discount_IsPercent");
					// Create a Discount object and add it to the list
					Discount discount = new Discount(discountID, discountName, amount, isPercent);
					discounts.add(discount);
				}
			}
		// Handle any SQL exceptions	
		} catch (SQLException e) {
			e.printStackTrace();
			throw new SQLException("Error retrieving discounts for the order", e);
		} finally {
			if (conn != null && !conn.isClosed()) {
				close_connection();
			}
		}

		return discounts;
	}


	public static ArrayList<Discount> getDiscounts(Pizza p) throws SQLException, IOException {
		/* 
		 * Build an array list of all the Discounts associted with the Pizza.
		 * 
		 */
		// Initialize an empty list of discounts
		ArrayList<Discount> discounts = new ArrayList<>();
		// Connect to the database
		connect_to_db();
		// Query to retrieve discounts associated with the pizza
		String query = "SELECT d.discount_DiscountID, d.discount_DiscountName, d.discount_Amount, d.discount_IsPercent " +
				"FROM pizza_discount pd " +
				"JOIN discount d ON pd.discount_DiscountID = d.discount_DiscountID " +
				"WHERE pd.pizza_PizzaID = ?";
		// Execute the query and populate the discounts list
		try (PreparedStatement stmt = conn.prepareStatement(query)) {
			stmt.setInt(1, p.getPizzaID()); // Set Pizza ID in the query
			try (ResultSet rs = stmt.executeQuery()) {
				while (rs.next()) {
					// Retrieve discount details from the result set
					int discountID = rs.getInt("discount_DiscountID");
					String discountName = rs.getString("discount_DiscountName");
					double amount = rs.getDouble("discount_Amount");
					boolean isPercent = rs.getBoolean("discount_IsPercent");
					// Create a Discount object and add it to the list
					Discount discount = new Discount(discountID, discountName, amount, isPercent);
					discounts.add(discount);
				}
			}
		// Handle any SQL exceptions	
		} catch (SQLException e) {
			e.printStackTrace();
			throw new SQLException("Error retrieving discounts for the pizza", e);
		} finally {
			if (conn != null && !conn.isClosed()) {
				close_connection();
			}
		}

		return discounts;
	}

	public static double getBaseCustPrice(String size, String crust) throws SQLException, IOException {
		/* 
		 * Query the database fro the base customer price for that size and crust pizza.
		 * 
		*/
		// Initialize baseCustPrice to 0.0
		double baseCustPrice = 0.0;
		// Connect to the database
		connect_to_db();
		// Query to retrieve the base customer price
		String query = "SELECT baseprice_CustPrice " +
				"FROM baseprice " +
				"WHERE baseprice_Size = ? AND baseprice_CrustType = ?";
		// Execute the query and retrieve the result
		try (PreparedStatement stmt = conn.prepareStatement(query)) {
			stmt.setString(1, size);
			stmt.setString(2, crust);
			try (ResultSet rs = stmt.executeQuery()) {
				if (rs.next()) {
					baseCustPrice = rs.getDouble("baseprice_CustPrice");
				}
			}
		// Handle any SQL exceptions
		} catch (SQLException e) {
			e.printStackTrace();
			throw new SQLException("Error retrieving base customer price for size: " + size + " and crust: " + crust, e);
		} finally {
			if (conn != null && !conn.isClosed()) {
				close_connection();
			}
		}

		return baseCustPrice;
	}


	public static double getBaseBusPrice(String size, String crust) throws SQLException, IOException {
		/* 
		 * Query the database for the base business price for that size and crust pizza.
		 * 
		*/

		// Initialize baseBusPrice to 0.0
		double baseBusPrice = 0.0;
		// Connect to the database
		connect_to_db();
		// Query to retrieve the base business price
		String query = "SELECT baseprice_BusPrice " +
				"FROM baseprice " +
				"WHERE baseprice_Size = ? AND baseprice_CrustType = ?";
		
				// Execute the query and retrieve the result
		try (PreparedStatement stmt = conn.prepareStatement(query)) {
			stmt.setString(1, size);
			stmt.setString(2, crust);
			try (ResultSet rs = stmt.executeQuery()) {
				if (rs.next()) {
					baseBusPrice = rs.getDouble("baseprice_BusPrice");
				}
			}
		// Handle any SQL exceptions
		} catch (SQLException e) {
			e.printStackTrace();
			throw new SQLException("Error retrieving base business price for size: " + size + " and crust: " + crust, e);
		} finally {
			if (conn != null && !conn.isClosed()) {
				close_connection();
			}
		}

		return baseBusPrice;
	}

	
	public static void printToppingReport() throws SQLException, IOException {
		/*
		 * Prints the ToppingPopularity view. Remember that this view
		 * needs to exist in your DB, so be sure you've run your createViews.sql
		 * files on your testing DB if you haven't already.
		 * 
		 * The result should be readable and sorted as indicated in the prompt.
		 * 
		 * HINT: You need to match the expected output EXACTLY....I would suggest
		 * you look at the printf method (rather that the simple print of println).
		 * It operates the same in Java as it does in C and will make your code
		 * better.
		 * 
		 */

		// Connect to the database
		connect_to_db();
		// Query to retrieve data from the ToppingPopularity view
		String query = "SELECT Topping, ToppingCount " +
				"FROM ToppingPopularity";
		// Execute the query and print the results
		try (Statement stmt = conn.createStatement();
			 ResultSet rs = stmt.executeQuery(query)) {

			// Print header
			System.out.printf("%-19s %-15s%n", "Topping", "Topping Count");
			System.out.printf("%-19s %-15s%n", "-------", "-------------");

			// Print each row
			while (rs.next()) {
				String toppingName = rs.getString("Topping");
				int toppingCount = rs.getInt("ToppingCount");
				System.out.printf("%-19s %-15d%n", toppingName, toppingCount);
			}

		// Handle any SQL exceptions
		} catch (SQLException e) {
			e.printStackTrace();
			throw new SQLException("Error retrieving the ToppingPopularity report", e);
		} finally {
			if (conn != null && !conn.isClosed()) {
				close_connection();
			}
		}
	}
	
	public static void printProfitByPizzaReport() throws SQLException, IOException {
		/*
		 * Prints the ProfitByPizza view. Remember that this view
		 * needs to exist in your DB, so be sure you've run your createViews.sql
		 * files on your testing DB if you haven't already.
		 * 
		 * The result should be readable and sorted as indicated in the prompt.
		 * 
		 * HINT: You need to match the expected output EXACTLY....I would suggest
		 * you look at the printf method (rather that the simple print of println).
		 * It operates the same in Java as it does in C and will make your code
		 * better.
		 * 
		 */
		// Connect to the database
		connect_to_db();

		// Query to retrieve data from the ProfitByPizza view
		String query = "SELECT Size, Crust, Profit, OrderMonth " +
				"FROM ProfitByPizza";

		// Execute the query and print the results
		try (Statement stmt = conn.createStatement();
			 ResultSet rs = stmt.executeQuery(query)) {

			// Print header
			System.out.printf("%-12s %-12s %-10s %-15s%n", "Pizza Size", "Pizza Crust", "Profit", "Last Order Date");
			System.out.printf("%-12s %-12s %-10s %-15s%n", "----------", "-----------", "------", "---------------");

			// Prints each row
			while (rs.next()) {
				String pizzaSize = rs.getString("Size");
				String pizzaCrust = rs.getString("Crust");
				double profit = rs.getDouble("Profit");
				String lastOrderDate = rs.getString("OrderMonth");
				System.out.printf("%-12s %-12s %-9.2f %-15s%n", pizzaSize, pizzaCrust, profit, lastOrderDate);
			}

		// Handle any SQL exceptions
		} catch (SQLException e) {
			e.printStackTrace();
			throw new SQLException("Error retrieving the ProfitByPizza report", e);
		} finally {
			if (conn != null && !conn.isClosed()) {
				close_connection();
			}
		}
	}
	
	public static void printProfitByOrderTypeReport() throws SQLException, IOException {
		/*
		 * Prints the ProfitByOrderType view. Remember that this view
		 * needs to exist in your DB, so be sure you've run your createViews.sql
		 * files on your testing DB if you haven't already.
		 * 
		 * The result should be readable and sorted as indicated in the prompt.
		 *
		 * HINT: You need to match the expected output EXACTLY....I would suggest
		 * you look at the printf method (rather that the simple print of println).
		 * It operates the same in Java as it does in C and will make your code
		 * better.
		 * 
		 */
		// Connect to the database
		connect_to_db();
		
		// Query to retrieve data from the ProfitByOrderType view
		String query = "SELECT customerType, OrderMonth, TotalOrderPrice, TotalOrderCost, Profit " +
				"FROM ProfitByOrderType";
		// Execute the query and print the results
		try (Statement stmt = conn.createStatement();
			 ResultSet rs = stmt.executeQuery(query)) {

			// Print header with proper formatting
			System.out.printf("%-19s %-19s %-19s %-19s %-10s%n","Customer Type", "Order Month", "Total Order Price", "Total Order Cost", "Profit");
			System.out.printf("%-19s %-19s %-19s %-19s %-10s%n","-------------", "-----------", "-----------------", "----------------", "------");

			// Print each row with properly formatted columns
			while (rs.next()) {
				String customerType = rs.getString("customerType");
				String orderMonth = rs.getString("OrderMonth");
				double totalOrderPrice = rs.getDouble("TotalOrderPrice");
				double totalOrderCost = rs.getDouble("TotalOrderCost");
				double profit = rs.getDouble("Profit");

				// Format and print each row
				System.out.printf("%-19s %-19s %-19.2f %-19.2f %-10.2f%n",
						customerType != null ? customerType : "", // Handle NULL customerType
						orderMonth,
						totalOrderPrice,
						totalOrderCost,
						profit);
			}

		// Handle any SQL exceptions
		} catch (SQLException e) {
			e.printStackTrace();
			throw new SQLException("Error retrieving the ProfitByOrderType report", e);
		} finally {
			if (conn != null && !conn.isClosed()) {
				close_connection(); // Close the database connection
			}
		}
	}
	
	
	
	/*
	 * These private methods help get the individual components of an SQL datetime object. 
	 * You're welcome to keep them or remove them....but they are usefull!
	 */
	private static int getYear(String date)// assumes date format 'YYYY-MM-DD HH:mm:ss'
	{
		return Integer.parseInt(date.substring(0,4));
	}
	private static int getMonth(String date)// assumes date format 'YYYY-MM-DD HH:mm:ss'
	{
		return Integer.parseInt(date.substring(5, 7));
	}
	private static int getDay(String date)// assumes date format 'YYYY-MM-DD HH:mm:ss'
	{
		return Integer.parseInt(date.substring(8, 10));
	}

	public static boolean checkDate(int year, int month, int day, String dateOfOrder)
	{
		if(getYear(dateOfOrder) > year)
			return true;
		else if(getYear(dateOfOrder) < year)
			return false;
		else
		{
			if(getMonth(dateOfOrder) > month)
				return true;
			else if(getMonth(dateOfOrder) < month)
				return false;
			else
			{
				if(getDay(dateOfOrder) >= day)
					return true;
				else
					return false;
			}
		}
	}


}