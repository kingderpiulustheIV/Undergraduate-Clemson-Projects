<!--
Sean Farrell
7/26/2025
CPSC 3750 Wooster
ASSiGNMENT: Intergrate with DB
DESCRIPTION: This is a php website thats integrated with a database to manage person records. It allows adding, displaying, and searching for persons by last name.
FILE DESCRPTION: This db_config.php file contains the database connection configuration for the application.
-->
<?php
// note: Theses variables are blank due to privacy and security reasons on the public repository.
$servername = "localhost";
$username = "";
$password = "";
$dbname = "person_db";

try {
    $pdo = new PDO("mysql:host=$servername;dbname=$dbname", $username, $password);
    $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
} catch(PDOException $e) {
    die("Connection failed: " . $e->getMessage());
}
?>