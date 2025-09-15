<!-- 
Sean Farrell 
7/17/2025
CPSC 3750 Wooster
Assignment: Group: Zipcode Distance
DESCRIPTION: A website that calculates the distance between two US zip codes using PHP and HTML/CSS using php to access csv files.
CURRENT FILE: zip.php is the main PHP file for Zip Code Distance Calculator as it handles user input,
processes zip codes, calculates distance, and displays results, as well as the html.
-->
 
<?php
require_once 'zipfunctions.php';

// Debug mode toggle
$debug = isset($_GET['debug']) && $_GET['debug'] === '1';

// Process form submission
$result = null;
$zip1Info = null;
$zip2Info = null;
$zipData = loadZipCodeData();

// If form submitted via POST
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $zip1 = isset($_POST['zip1']) ? trim($_POST['zip1']) : '';
    $zip2 = isset($_POST['zip2']) ? trim($_POST['zip2']) : '';
    
    $zip1Info = findZipCode($zip1, $zipData);
    $zip2Info = findZipCode($zip2, $zipData);
    
    $errors = [];
    // Validate zip codes
    if (!$zip1Info) {
        $errors[] = "First zip code not found: $zip1";
    }
    
    if (!$zip2Info) {
        $errors[] = "Second zip code not found: $zip2";
    }
    // If no errors, calculate distance
    if (empty($errors)) {
        $distance = calculateDistance($zip1Info, $zip2Info);
        $result = [
            'zip1' => $zip1,
            'zip2' => $zip2,
            'zip1Info' => $zip1Info,
            'zip2Info' => $zip2Info,
            'distance' => $distance
        ];
    }
}
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Zip Code Distance Calculator</title>
    <link rel="stylesheet" href="zipstyles.css">
</head>
<body>
    <div class="container">
        <h1>Zip Code Distance Calculator</h1>
        
        <!-- Div form for user input for first zipcode -->
        <form method="post" action="">
            <div class="form-group">
                <label for="zip1">First Zip Code:</label>
                <input type="text" id="zip1" name="zip1" required 
                       value="<?php echo isset($_POST['zip1']) ? htmlspecialchars($_POST['zip1']) : ''; ?>">
            </div>

        <!-- Div form for user input for second zipcode -->
            <div class="form-group">
                <label for="zip2">Second Zip Code:</label>
                <input type="text" id="zip2" name="zip2" required
                       value="<?php echo isset($_POST['zip2']) ? htmlspecialchars($_POST['zip2']) : ''; ?>">
            </div>
            
            <button type="submit">Calculate Distance</button>
        </form>
        
        <!-- displays errors if any accordingly -->
        <?php if (isset($errors) && !empty($errors)): ?>
            <div class="error">
                <ul>
                    <?php foreach($errors as $error): ?>
                        <li><?php echo htmlspecialchars($error); ?></li>
                    <?php endforeach; ?>
                </ul>
            </div>
        <?php endif; ?>

        <!-- displays results if calculation was successful -->
        <?php if ($result): ?>

            <!-- Div for distance result-->
            <div class="result">
                <h2>Distance Result</h2>
                <p class="distance">
                    The distance between <?php echo htmlspecialchars($result['zip1']); ?> 
                    and <?php echo htmlspecialchars($result['zip2']); ?> is:
                    <span class="distance-value"><?php echo number_format($result['distance'], 2); ?> miles</span>
                </p>

                <!-- Div for zip details result-->
                <div class="zip-details">
                    <div class="zip-card">
                        <h3>Zip Code: <?php echo htmlspecialchars($result['zip1']); ?></h3>
                        <p>City: <?php echo htmlspecialchars($result['zip1Info']['city']); ?></p>
                        <p>State: <?php echo htmlspecialchars($result['zip1Info']['state']); ?></p>
                        <?php if($debug): ?>
                            <p>Latitude: <?php echo $result['zip1Info']['lat']; ?></p>
                            <p>Longitude: <?php echo $result['zip1Info']['lng']; ?></p>
                        <?php endif; ?>
                    </div>
                    
                    <!-- Div for the zip card-->
                    <div class="zip-card">
                        <h3>Zip Code: <?php echo htmlspecialchars($result['zip2']); ?></h3>
                        <p>City: <?php echo htmlspecialchars($result['zip2Info']['city']); ?></p>
                        <p>State: <?php echo htmlspecialchars($result['zip2Info']['state']); ?></p>
                        <?php if($debug): ?>
                            <p>Latitude: <?php echo $result['zip2Info']['lat']; ?></p>
                            <p>Longitude: <?php echo $result['zip2Info']['lng']; ?></p>
                        <?php endif; ?>
                    </div>
                </div>
            </div>
        <?php endif; ?>

        <!-- Div for Debug Information -->
        <?php if($debug): ?>
            <div class="debug">
                <h3>Debug Information</h3>
                <p>Total zip codes loaded: <?php echo count($zipData); ?></p>
                <?php if($zip1Info): ?>
                    <h4>First Zip Details:</h4>
                    <pre><?php print_r($zip1Info); ?></pre>
                <?php endif; ?>
                
                <?php if($zip2Info): ?>
                    <h4>Second Zip Details:</h4>
                    <pre><?php print_r($zip2Info); ?></pre>
                <?php endif; ?>
            </div>
        <?php endif; ?>
        
        <!-- Div for Debug toggle -->
        <div class="toggle-debug">
            <?php if($debug): ?>
                <a href="?debug=0">Disable Debug Mode</a>
            <?php else: ?>
                <a href="?debug=1">Enable Debug Mode</a>
            <?php endif; ?>
        </div>
    </div>
</body>
</html>