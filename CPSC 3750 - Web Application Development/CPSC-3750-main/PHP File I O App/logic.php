<!-- 
Sean Farrell
7/12/2025
CPSC 3750 Wooster
ASSIGNMENT: PHP File I/O App
DESCRIPTION: This PHP application allows users to input numbers and categorize them as prime, Armstrong, Fibonacci, or none. 
It uses a form to submit the numbers and displays the results dynamically.
THIS FILE: logic.php contains the serverside php logic for finding numbers that are or not armstrong, primer of fibonacci.
-->
<?php
// Check if the cookie exists (first time user)
if (!isset($_COOKIE['number_categorizer_visited'])) {
    // Set the cookie for 30 days
    setcookie('number_categorizer_visited', 'true', time() + (86400 * 30), "/");
    
    // Create the four empty text files
    $files = ['prime.txt', 'armstrong.txt', 'fibonacci.txt', 'none.txt'];
    foreach ($files as $file) {
        file_put_contents($file, '');
    }
}

// Function to check if a number is prime
function isPrime($num) {
    if ($num <= 1) return false;
    if ($num <= 3) return true;
    if ($num % 2 == 0 || $num % 3 == 0) return false;
    
    $i = 5;
    while ($i * $i <= $num) {
        if ($num % $i == 0 || $num % ($i + 2) == 0) return false;
        $i += 6;
    }
    return true;
}

// Function to check if a number is an Armstrong number
function isArmstrong($num) {
    $sum = 0;
    $temp = $num;
    $digits = strlen((string)$num);
    
    while ($temp > 0) {
        $remainder = $temp % 10;
        $sum += pow($remainder, $digits);
        $temp = (int)($temp / 10);
    }
    
    return $sum == $num;
}

// Function to check if a number is a Fibonacci number
function isFibonacci($num) {
    // A number is Fibonacci if and only if one or both of (5*n^2 + 4) or (5*n^2 - 4) is a perfect square
    return isPerfectSquare(5 * $num * $num + 4) || isPerfectSquare(5 * $num * $num - 4);
}

function isPerfectSquare($num) {
    $sqrt = (int)sqrt($num);
    return ($sqrt * $sqrt == $num);
}

// Function to append a number to a file if it doesn't already exist
function appendToFile($file, $number) {
    $content = file_get_contents($file);
    $numbers = explode(',', $content);
    $numbers = array_filter($numbers); // Remove empty values
    
    if (!in_array($number, $numbers)) {
        if (!empty($content)) {
            $content .= ',';
        }
        $content .= $number;
        file_put_contents($file, $content);
    }
}

// Function to display numbers from a file
function displayNumbers($file, $type) {
    $content = file_get_contents($file);
    $numbers = explode(',', $content);
    $numbers = array_filter($numbers); // Remove empty values
    
    $html = "<h2>$type Numbers</h2>";
    
    if (empty($numbers)) {
        $html .= "<p>No $type numbers found.</p>";
    } else {
        foreach ($numbers as $number) {
            $html .= "<div class='number-item'>$number</div>";
        }
    }
    
    return $html;
}

$result_message = '';

// Check which action was requested
if (isset($_POST['action'])) {
    $action = $_POST['action'];
    
    switch ($action) {
        case 'check':
            // Process the numbers entered by the user
            if (isset($_POST['numbers']) && !empty(trim($_POST['numbers']))) {
                $input = $_POST['numbers'];
                // Extract numbers (separated by spaces, commas, or new lines)
                preg_match_all('/\d+/', $input, $matches);
                $numbers = $matches[0];
                
                foreach ($numbers as $number) {
                    if (isPrime($number)) {
                        appendToFile('prime.txt', $number);
                    }
                    if (isArmstrong($number)) {
                        appendToFile('armstrong.txt', $number);
                    }
                    if (isFibonacci($number)) {
                        appendToFile('fibonacci.txt', $number);
                    }
                    if (!isPrime($number) && !isArmstrong($number) && !isFibonacci($number)) {
                        appendToFile('none.txt', $number);
                    }
                }
                
                $result_message = "<h2>Numbers Processed</h2>";
                $result_message .= "<p>Your numbers have been processed and categorized.</p>";
            } else {
                $result_message = "<h2>Error</h2>";
                $result_message .= "<p>Please enter some numbers to check.</p>";
            }
            break;
            
        case 'prime':
            $result_message = displayNumbers('prime.txt', 'Prime');
            break;
            
        case 'armstrong':
            $result_message = displayNumbers('armstrong.txt', 'Armstrong');
            break;
            
        case 'fibonacci':
            $result_message = displayNumbers('fibonacci.txt', 'Fibonacci');
            break;
            
        case 'none':
            $result_message = displayNumbers('none.txt', 'None');
            break;
            
        case 'reset':
            // Delete all files and clear the cookie
            $files = ['prime.txt', 'armstrong.txt', 'fibonacci.txt', 'none.txt'];
            foreach ($files as $file) {
                file_put_contents($file, '');
            }
            setcookie('number_categorizer_visited', '', time() - 3600, "/");
            
            $result_message = "<h2>Reset Complete</h2>";
            $result_message .= "<p>All files have been reset and the cookie has been cleared.</p>";
            break;
    }
}

// Always include the HTML file
include 'PHPIO.html';
?>
