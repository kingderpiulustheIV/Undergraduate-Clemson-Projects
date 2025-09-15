<!-- 
Sean Farrell
7/12/2025
CPSC 3750 Wooster
ASSIGNMENT: Group Session
DESCRIPTION: This PHP script creates a simple car selection page where users can select multiple cars from a dropdown list. 
The selected cars are submitted to another PHP script for processing. If there are any selected cars, a link is provided to view the selected cars on another page.

This is display.php file displaying the car selections made by the user.
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
    <title>Car Display Page</title>
    <style>
        body { font-family: Arial, sans-serif; margin: 20px; }
        h1 { color: #333; }
        ul { list-style-type: none; padding: 0; }
        li { padding: 8px 0; border-bottom: 1px solid #ddd; }
        .buttons { margin-top: 20px; }
        .buttons a, .buttons form button { 
            display: inline-block; 
            margin-right: 10px; 
            padding: 8px 15px; 
            text-decoration: none;
            color: white;
            border: none;
            cursor: pointer;
        }
        .back { background-color: #4CAF50; }
        .clear { background-color: #f44336; }
        .no-cars { color: #666; font-style: italic; }
    </style>
</head>
<body>
    <h1>Car Display Page</h1>
    
    <?php if (isset($_SESSION['cars']) && !empty($_SESSION['cars'])): ?>
        <h2>Your Selected Cars:</h2>
        <ul>
            <?php foreach ($_SESSION['cars'] as $car): ?>
                <li><?php echo htmlspecialchars($car); ?></li>
            <?php endforeach; ?>
        </ul>
    <?php else: ?>
        <p class="no-cars">No cars have been selected.</p>
    <?php endif; ?>
    
    <div class="buttons">
        <a href="goup_selection.php" class="back">Back to Selection Page</a>
        
        <form action="clear.php" method="post" style="display: inline;">
            <button type="submit" class="clear">Clear All Selections</button>
        </form>
    </div>
</body>
</html>