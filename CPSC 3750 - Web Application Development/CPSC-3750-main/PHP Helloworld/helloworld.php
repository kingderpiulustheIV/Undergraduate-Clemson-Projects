<!-- 
Sean Farrell
5/31/2025
CPSC 3750 Wooster
ASSIGNMENT: PHP Hello World -->
<!doctype html>
<html>
<head>
        <!-- This is a simple PHP script that outputs "Hello, World!" and some server information. -->
        <title>Hello World PHP Example</title>
        <style>
                body {
                        /* CSS formatting and style for the page*/
                        font-family: Arial, sans-serif;
                        margin: 40px;
                        line-height: 1.6;
                        background-color: black;
                        color: white;
                }
        </style>

</head>
<head>
    <div id="navbar"></div>
    <script src="navbar.js"></script> 
 </head>
<body>
        <h1>Hello, World!</h1>
        <p>PHP is working correctly on this server.</p>
        <!-- Display the current date and time with PHP -->
        <p>Accessed on : <?php echo date('m/d/Y H:i:s'); ?></p>
        <!-- Tells the user what version of PHP the server is running -->
        <p>PHP version: <?php echo phpversion(); ?></p>
</body>
</html>