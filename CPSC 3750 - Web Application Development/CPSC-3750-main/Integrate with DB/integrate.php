
<!--
Sean Farrell
7/26/2025
CPSC 3750 Wooster
ASSiGNMENT: Intergrate with DB
DESCRIPTION: This is a php website thats integrated with a database to manage person records. It allows adding, displaying, and searching for persons by last name.
FILE DESCRPTION: This integrate.php file contains html styling and logic to manage person records in a database. 
It includes functionality to add new persons, display all records sorted by last name, and search for persons by last name.
-->
<?php
require_once 'db_config.php';

// Handle form submission for adding new person
if ($_POST['action'] === 'add' && !empty($_POST['first_name']) && !empty($_POST['last_name']) && !empty($_POST['email'])) {
    try {
        $stmt = $pdo->prepare("INSERT INTO Person (first_name, last_name, email) VALUES (?, ?, ?)");
        $stmt->execute([$_POST['first_name'], $_POST['last_name'], $_POST['email']]);
        $message = "Person added successfully!";
    } catch(PDOException $e) {
        $error = "Error adding person: " . $e->getMessage();
    }
}

// Handle display all records
$displayAll = false;
$persons = [];
if ($_POST['action'] === 'display') {
    try {
        $stmt = $pdo->query("SELECT * FROM Person ORDER BY last_name");
        $persons = $stmt->fetchAll(PDO::FETCH_ASSOC);
        $displayAll = true;
    } catch(PDOException $e) {
        $error = "Error retrieving records: " . $e->getMessage();
    }
}

// Handle search by last name
$searchResults = [];
$showSearch = false;
if ($_POST['action'] === 'search' && !empty($_POST['search_lastname'])) {
    try {
        $stmt = $pdo->prepare("SELECT first_name, last_name, email FROM Person WHERE LOWER(last_name) = LOWER(?) ORDER BY last_name");
        $stmt->execute([$_POST['search_lastname']]);
        $searchResults = $stmt->fetchAll(PDO::FETCH_ASSOC);
        $showSearch = true;
    } catch(PDOException $e) {
        $error = "Error searching records: " . $e->getMessage();
    }
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Person Database Manager</title>
    <style>
    /* dark theme styling for website */
    #navbar-container {
        position: fixed;
        top: 0;
        left: 0;
        width: 100%;
        background-color: #333;
        border-bottom: 1px solid #444;
        z-index: 1000;
        margin: 0 !important;
        padding: 0 !important;
        box-sizing: border-box;
    }

    #navbar {
        margin: 0 !important;
        padding: 10px 20px;
        width: 100%;
        box-sizing: border-box;
    }

    body { 
        font-family: Arial, sans-serif; 
        max-width: 800px; 
        margin: 0 auto; 
        padding: 80px 20px 20px 20px; 
        background-color: #1a1a1a; 
        color: #e0e0e0; 
    }
        
    .form-group { 
        margin-bottom: 15px; 
    }
    
    label { 
        display: block; 
        margin-bottom: 5px; 
        font-weight: bold; 
        color: #f0f0f0; 
    }
    
    input[type="text"], input[type="email"] { 
        width: 300px; 
        padding: 8px; 
        border: 1px solid #444; 
        border-radius: 4px; 
        background-color: #2a2a2a; 
        color: #e0e0e0; 
    }
    
    button { 
        background-color: #0078d4; 
        color: white; 
        padding: 10px 20px; 
        border: none; 
        border-radius: 4px; 
        cursor: pointer; 
        margin: 5px; 
    }
    
    button:hover { 
        background-color: #106ebe; 
    }
    
    .message { 
        background-color: #1e4d40; 
        color: #4caf50; 
        padding: 10px; 
        border-radius: 4px; 
        margin: 10px 0; 
        border: 1px solid #4caf50; 
    }
    
    .error { 
        background-color: #4d1e1e; 
        color: #f44336; 
        padding: 10px; 
        border-radius: 4px; 
        margin: 10px 0; 
        border: 1px solid #f44336; 
    }
    
    table { 
        width: 100%; 
        border-collapse: collapse; 
        margin-top: 20px; 
    }
    
    th, td { 
        border: 1px solid #444; 
        padding: 12px; 
        text-align: left; 
    }
    
    th { 
        background-color: #333; 
        color: #f0f0f0; 
    }
    
    .section { 
        margin: 30px 0; 
        padding: 20px; 
        border: 1px solid #444; 
        border-radius: 8px; 
        background-color: #2a2a2a; 
    }
    </style>
    <script src="navbar.js"></script>
</head>
<body>
    <div id="navbar-container">
        <nav id="navbar">
        </nav>
    </div>
    
    <h1>Person Database Manager</h1>

    <!-- Display messages or errors if any -->
    <?php if (isset($message)): ?>
        <div class="message"><?php echo htmlspecialchars($message); ?></div>
    <?php endif; ?>

    <?php if (isset($error)): ?>
        <div class="error"><?php echo htmlspecialchars($error); ?></div>
    <?php endif; ?>

    <!-- Add New Person Form -->
    <div class="section">
        <h2>Add New Person</h2>
        <form method="POST">
            <input type="hidden" name="action" value="add">
            
            <div class="form-group">
                <label for="first_name">First Name:</label>
                <input type="text" id="first_name" name="first_name" required>
            </div>
            
            <div class="form-group">
                <label for="last_name">Last Name:</label>
                <input type="text" id="last_name" name="last_name" required>
            </div>
            
            <div class="form-group">
                <label for="email">Email Address:</label>
                <input type="email" id="email" name="email" required>
            </div>
            
            <button type="submit">Add Person</button>
        </form>
    </div>

    <!-- Display and Search Controls -->
    <div class="section">
        <h2>Database Operations</h2>
        
        <form method="POST" style="display: inline;">
            <input type="hidden" name="action" value="display">
            <button type="submit">Display All Records (Sorted by Last Name)</button>
        </form>
        
        <form method="POST" style="display: inline; margin-left: 20px;">
            <input type="hidden" name="action" value="search">
            <input type="text" name="search_lastname" placeholder="Enter last name to search" style="width: 200px;">
            <button type="submit">Search by Last Name</button>
        </form>
    </div>

    <!-- Display All Records -->
    <?php if ($displayAll): ?>
        <div class="section">
            <h2>All Person Records (Sorted by Last Name)</h2>
            <?php if (count($persons) > 0): ?>
                <table>
                    <thead>
                        <tr>
                            <th>ID</th>
                            <th>First Name</th>
                            <th>Last Name</th>
                            <th>Email</th>
                        </tr>
                    </thead>
                    <tbody>
                        <?php foreach ($persons as $person): ?>
                            <tr>
                                <td><?php echo htmlspecialchars($person['id']); ?></td>
                                <td><?php echo htmlspecialchars($person['first_name']); ?></td>
                                <td><?php echo htmlspecialchars($person['last_name']); ?></td>
                                <td><?php echo htmlspecialchars($person['email']); ?></td>
                            </tr>
                        <?php endforeach; ?>
                    </tbody>
                </table>
            <?php else: ?>
                <p>No records found.</p>
            <?php endif; ?>
        </div>
    <?php endif; ?>

    <!-- Search Results -->
    <?php if ($showSearch): ?>
        <div class="section">
            <h2>Search Results for "<?php echo htmlspecialchars($_POST['search_lastname']); ?>"</h2>
            <?php if (count($searchResults) > 0): ?>
                <table>
                    <thead>
                        <tr>
                            <th>First Name</th>
                            <th>Last Name</th>
                            <th>Email</th>
                        </tr>
                    </thead>
                    <tbody>
                        <?php foreach ($searchResults as $person): ?>
                            <tr>
                                <td><?php echo htmlspecialchars($person['first_name']); ?></td>
                                <td><?php echo htmlspecialchars($person['last_name']); ?></td>
                                <td><?php echo htmlspecialchars($person['email']); ?></td>
                            </tr>
                        <?php endforeach; ?>
                    </tbody>
                </table>
            <?php else: ?>
                <p>No records found with that last name.</p>
            <?php endif; ?>
        </div>
    <?php endif; ?>
</body>
</html>

<?php
// Check if Person table exists, if not create it
try {
    $stmt = $pdo->query("SHOW TABLES LIKE 'Person'");
    if ($stmt->rowCount() == 0) {
        $sql = "CREATE TABLE Person (
            id INT AUTO_INCREMENT PRIMARY KEY,
            first_name VARCHAR(50) NOT NULL,
            last_name VARCHAR(50) NOT NULL,
            email VARCHAR(100) NOT NULL
        )";
        $pdo->exec($sql);
    }
} catch(PDOException $e) {
    error_log("Error checking/creating Person table: " . $e->getMessage());
}
?>
