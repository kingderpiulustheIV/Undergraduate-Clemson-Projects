
<!--
Sean Farrell
7/5/2025
CPSC 3750 Wooster
ASSIGNMENT: Group: Hangman
DESCRIPTION: A website using html, css and javascript and php of an online game of hangman.
this is the .php file that contains the server side logic of the game. 
Mainly used to get random words as the word to guess for the hangman game. -->

<?php
// A simpler approach to prevent direct URL access
// This checks if the request is to this file directly
$requestedScript = basename($_SERVER['SCRIPT_FILENAME']);
$currentScript = basename(__FILE__);

if ($requestedScript === $currentScript) {
    
    // path of the words file for the words to guess in the game
    $wordsFile = "words.txt";
    
    // Check if the words file exists and is readable
    if(file_exists($wordsFile)) {
        
        // Read the words from the file and pick a random one for the current game
        $words = file($wordsFile, FILE_IGNORE_NEW_LINES | FILE_SKIP_EMPTY_LINES);
        if(count($words) > 0) {
            $randomWord = trim($words[array_rand($words)]);
            echo json_encode(['word' => $randomWord]);
        } else {
            
            // displays error codes if file is empty
            echo json_encode(['error' => 'Words file is empty']);
        }
            
        // displays error codes if file cant be fpunf
    } else {
        echo json_encode(['error' => 'Words file not found']);
    }
    
// displays error codes if file cant be accessed
} else {
    
    // If accessed in an unexpected way
    header('HTTP/1.0 403 Forbidden');
    echo json_encode(['error' => 'Access Forbidden']);
    exit;
}
?>