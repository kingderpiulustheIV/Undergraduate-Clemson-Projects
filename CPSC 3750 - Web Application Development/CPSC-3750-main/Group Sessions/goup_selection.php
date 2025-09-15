<!-- 
Sean Farrell
7/12/2025
CPSC 3750 Wooster
ASSIGNMENT: Group Session
DESCRIPTION: This PHP script creates a simple car selection page where users can select multiple cars from a dropdown list. 
The selected cars are submitted to another PHP script for processing. If there are any selected cars, a link is provided to view the selected cars on another page.

This is group_selection.php file allowing the user to select multiple cars from a dropdown list.
-->
<?php
// Start session
session_start();
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Car Selection Page</title>
    <style>
        body { font-family: Arial, sans-serif; margin: 20px; }
        h1 { color: #333; }
        form { margin-bottom: 20px; }
        select { width: 300px; padding: 5px; }
        button { padding: 8px 15px; background-color: #4CAF50; color: white; border: none; cursor: pointer; }
        a { display: inline-block; margin-top: 10px; color: #0066cc; text-decoration: none; }
        a:hover { text-decoration: underline; }
    </style>
</head>
<body>
    <h1>Car Selection Page</h1>
    
    <form action="process.php" method="post">
        <p>Hold down the Ctrl (Windows) or Command (Mac) button to select multiple cars:</p>
        <select name="cars[]" multiple size="7">
            <option value="Toyota Camry">Toyota Camry</option>
            <option value="Honda Civic">Honda Civic</option>
            <option value="Ford Mustang">Ford Mustang</option>
            <option value="Chevrolet Corvette">Chevrolet Corvette</option>
            <option value="Tesla Model 3">Tesla Model 3</option>
            <option value="BMW 3 Series">BMW 3 Series</option>
            <option value="Audi A4">Audi A4</option>
        </select>
        <p><button type="submit">Submit Selection</button></p>
    </form>
    
    <?php if (isset($_SESSION['cars']) && !empty($_SESSION['cars'])): ?>
        <p>You have cars in your selection. <a href="display.php">View selected cars</a></p>
    <?php endif; ?>
</body>
</html>