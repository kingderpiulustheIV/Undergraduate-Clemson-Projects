<!-- 
Sean Farrell 
7/17/2025
CPSC 3750 Wooster
Assignment: Group: Zipcode Distance
DESCRIPTION: A website that calculates the distance between two US zip codes using PHP and HTML/CSS using php to access csv files.
CURRENT FILE: zipfunctions.php is a helper PHP file for functions used in zip.php. It loads the .csv file and
processes zip codes, calculates distance, and provides utility functions.
-->

<?php
// Read entire file at once
$data = file_get_contents('uszips.csv');

// Or read file line by line (better for large files)
$file = fopen('uszips.csv', 'r');
while (($line = fgetcsv($file)) !== FALSE) {
    // Process each line
    // $line[0] might be zip code, $line[1] might be latitude, etc. 
    // For the current file attached line[0] is zip, line[1] is lat, line[2] is lng, line[3] is city, line[5] is state.
}
fclose($file);

// Function to calculate distance in miles between two lat/lon points using Haversine formula 
function getDistance($lat1, $lon1, $lat2, $lon2) {
    // Radius of the Earth in miles
    $earthRadius = 3958.8;
    
    // Convert degrees to radians
    $lat1 = deg2rad($lat1);
    $lon1 = deg2rad($lon1);
    $lat2 = deg2rad($lat2);
    $lon2 = deg2rad($lon2);
    
    // Haversine formula
    $dlat = $lat2 - $lat1;
    $dlon = $lon2 - $lon1;
    $a = sin($dlat/2) * sin($dlat/2) + cos($lat1) * cos($lat2) * sin($dlon/2) * sin($dlon/2);
    $c = 2 * atan2(sqrt($a), sqrt(1-$a));
    $distance = $earthRadius * $c;
    
    return $distance;
}

// loads zip code data from CSV into an associative array
function loadZipCodeData() {
    $zipData = [];
    $file = fopen("uszips.csv", "r");
    
    // Skip header row if it exists
    fgetcsv($file);
    
    while (($line = fgetcsv($file)) !== FALSE) {
        // Assuming format: zip,city,state,lat,lng
        $zipcode = $line[0];
        $zipData[$zipcode] = [
            'lat' => (float)$line[1],
            'lng' => (float)$line[2],
            'city' => $line[3],
            'state' => $line[5],
        ];
    }
    fclose($file);
    
    return $zipData;
}

// simple function to  the specified find zip code details
function findZipCode($zipcode, $zipData) {
    return isset($zipData[$zipcode]) ? $zipData[$zipcode] : null;
}


 //Calculate distance between two zip codes
function calculateDistance($zip1, $zip2) {
    return getDistance(
        $zip1['lat'], $zip1['lng'],
        $zip2['lat'], $zip2['lng']
    );
}

?>