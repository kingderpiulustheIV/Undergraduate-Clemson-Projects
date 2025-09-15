<!-- 
Sean Farrell
7/12/2025
CPSC 3750 Wooster
ASSIGNMENT: Group Session
DESCRIPTION: This PHP script creates a simple car selection page where users can select multiple cars from a dropdown list. 
The selected cars are submitted to another PHP script for processing. If there are any selected cars, a link is provided to view the selected cars on another page.

This is clear.php file clearing the car selections made by the user.
-->
<?php
// Start session
session_start();

// Clear the cars array from session
if (isset($_SESSION['cars'])) {
    unset($_SESSION['cars']);
}

// Redirect back to display page
header("Location: display.php");
exit();
?>