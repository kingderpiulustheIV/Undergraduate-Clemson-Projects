<!-- 
Sean Farrell
7/12/2025
CPSC 3750 Wooster
ASSIGNMENT: Group Session
DESCRIPTION: This PHP script creates a simple car selection page where users can select multiple cars from a dropdown list. 
The selected cars are submitted to another PHP script for processing. If there are any selected cars, a link is provided to view the selected cars on another page.

This is process.php file processing the car selections made by the user.
-->
<?php
// Start session
session_start();

// Check if form was submitted
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    // Check if cars were selected
    if (isset($_POST['cars']) && !empty($_POST['cars'])) {
        // Store selected cars in session
        $_SESSION['cars'] = $_POST['cars'];
        
        // Redirect to display page
        header("Location: display.php");
        exit();
    } else {
        // No cars selected, redirect back to selection page
        $_SESSION['error'] = "Please select at least one car.";
        header("Location: group_selection.php");
        exit();
    }
} else {
    // If not POST request, redirect to index
    header("Location: index.php");
    exit();
}
?>