<!-- 
Sean Farrell
7/18/25
CPSC 3750 Wooster
ASSIGNMENT: Exam 2
DESCRIPTION: A web application that allows users to view words based on their vowel counts, 
drag and drop words into a designated area, and see a count of the dropped words. 
The application fetches data from a PHP backend that processes a text file containing words.
FILE INFO: This is the main PHP backend file exam2.php that handles requests to fetch and process words from a text file.
 -->
<?php
// Set headers for JSON response and CORS
header('Content-Type: application/json');
header('Access-Control-Allow-Origin: *');
header('Access-Control-Allow-Methods: GET, POST');
header('Access-Control-Allow-Headers: Content-Type');

// WordProcessor class to handle word processing logic
class WordProcessor {
    private $wordsFile;
    private $vowels = ['A', 'E', 'I', 'O', 'U'];
    
    //Constructor to initialize the words file
    public function __construct($wordsFile = 'words.txt') {
        $this->wordsFile = $wordsFile;
    }
    
    //Count vowels in a word
    private function countVowels($word) {
        $count = 0;
        $word = strtoupper($word);
        
        for ($i = 0; $i < strlen($word); $i++) {
            if (in_array($word[$i], $this->vowels)) {
                $count++;
            }
        }
        
        return $count;
    }
    
    //Read words from file and organize by vowel count
    public function processWords() {
        if (!file_exists($this->wordsFile)) {
            return ['error' => 'Words file not found'];
        }
        
        $content = file_get_contents($this->wordsFile);
        $words = array_filter(array_map('trim', explode("\n", $content)));
        
        $wordsByVowels = [];
        
        foreach ($words as $word) {
            $vowelCount = $this->countVowels($word);
            
            if (!isset($wordsByVowels[$vowelCount])) {
                $wordsByVowels[$vowelCount] = [];
            }
            
            $wordsByVowels[$vowelCount][] = $word;
        }
        
        // Sort words within each vowel count group by length (shortest to longest)
        foreach ($wordsByVowels as $vowelCount => $wordList) {
            usort($wordsByVowels[$vowelCount], function($a, $b) {
                return strlen($a) - strlen($b);
            });
        }
        
        // Sort vowel counts for consistent button order
        ksort($wordsByVowels);
        
        return $wordsByVowels;
    }
    
     // Get available vowel counts for button generation
        public function getVowelCounts() {
        $wordsByVowels = $this->processWords();
        
        if (isset($wordsByVowels['error'])) {
            return $wordsByVowels;
        }
        
        return array_keys($wordsByVowels);
    }
}

// Handle different API endpoints
$action = $_GET['action'] ?? 'getWords';

$processor = new WordProcessor();

// switch case to handle different actions
switch ($action) {
    case 'getWords':
        echo json_encode($processor->processWords());
        break;
        
    case 'getVowelCounts':
        echo json_encode($processor->getVowelCounts());
        break;
        
    default:
        echo json_encode(['error' => 'Invalid action']);
        break;
}
?>
