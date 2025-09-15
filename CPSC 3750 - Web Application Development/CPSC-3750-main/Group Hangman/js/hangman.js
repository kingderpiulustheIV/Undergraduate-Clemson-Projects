// Sean Farrell
// 7/5/2025
// CPSC 3750 Wooster
// ASSIGNMENT: Group: Hangman
// DESCRIPTION: A website using html, css and javascript and php of an online game of hangman.
// this is the .js file that contains the client side logic of the game.

// Game state variables
let currentWord = '';
let guessedLetters = [];
let incorrectGuesses = 0;
const maxGuesses = 6;

// Function to start a new game
function startGame() {
    // Reset game state
    guessedLetters = [];
    incorrectGuesses = 0;
    
    // Reset gallows drawing
    drawGallows();
    
    // Fetch a new word from the server
fetch('getWord.php', {
    headers: {
        'X-Requested-With': 'XMLHttpRequest'
    }
})
    .then(response => response.json())
    .then(data => {
        if(data.word) {
            currentWord = data.word.toLowerCase();
            
            // Show word if cheat mode is enabled
            if(document.getElementById('cheat-mode').checked) {
                alert(`The word is: ${currentWord}`);
            }
            
            setupGame(currentWord);
        } else {
            console.error('Error fetching word:', data.error);
        }
    })
    .catch(error => console.error('Error:', error));
}

// Function to set up the game UI
function setupGame(word) {
    // Display blanks for the word
    updateWordDisplay();
    
    // Generate letter buttons in a 5x6 grid
    generateLetterButtons();
    
    // Reset button states
    const buttons = document.querySelectorAll('#letters-grid button');
    buttons.forEach(button => {
        button.disabled = false;
    });
}

// Function to generate letter buttons
function generateLetterButtons() {
    const letters = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ';
    const lettersGrid = document.getElementById('letters-grid');
    lettersGrid.innerHTML = ''; // Clear previous buttons
    
    letters.split('').forEach(letter => {
        const button = document.createElement('button');
        button.textContent = letter;
        button.onclick = () => guessLetter(letter.toLowerCase());
        lettersGrid.appendChild(button);
    });
}

// Function to handle letter guessing
function guessLetter(letter) {
    // If letter was already guessed, do nothing
    if (guessedLetters.includes(letter)) {
        return;
    }
    
    // Add to guessed letters
    guessedLetters.push(letter);
    
    // Disable the clicked button
    const buttons = document.querySelectorAll('#letters-grid button');
    buttons.forEach(button => {
        if (button.textContent.toLowerCase() === letter) {
            button.disabled = true;
        }
    });
    
    // Check if the letter is in the word
    if (currentWord.includes(letter)) {
        // Update displayed word
        updateWordDisplay();
        
        // Check if the game is won
        if (!updateWordDisplay().includes('_')) {
            setTimeout(() => {
                alert('Congratulations! You won!');
                startGame();
            }, 500);
        }
    } else {
        // Wrong guess
        incorrectGuesses++;
        updateGallows();
        
        // Check if game is over
        if (incorrectGuesses >= maxGuesses) {
            setTimeout(() => {
                alert(`Game over! The word was: ${currentWord}`);
                startGame();
            }, 500);
        }
    }
}

// Function to update the displayed word
function updateWordDisplay() {
    const wordToGuess = document.getElementById('wordToGuess');
    const displayWord = currentWord.split('').map(letter => 
        guessedLetters.includes(letter) ? letter : '_'
    ).join(' ');
    
    wordToGuess.textContent = displayWord;
    return displayWord;
}

// Function to draw the gallows
function drawGallows() {
    const canvas = document.getElementById('gallows');
    const ctx = canvas.getContext('2d');
    
    // Clear the canvas
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    
    // Draw the gallows base
    ctx.strokeStyle = '#333';
    ctx.lineWidth = 3;
    
    // Base horizontal line
    ctx.beginPath();
    ctx.moveTo(20, 230);
    ctx.lineTo(180, 230);
    ctx.stroke();
    
    // Vertical bar
    ctx.beginPath();
    ctx.moveTo(40, 230);
    ctx.lineTo(40, 30);
    ctx.stroke();
    
    // Top horizontal bar
    ctx.beginPath();
    ctx.moveTo(40, 30);
    ctx.lineTo(120, 30);
    ctx.stroke();
    
    // Rope
    ctx.beginPath();
    ctx.moveTo(120, 30);
    ctx.lineTo(120, 50);
    ctx.stroke();
}

// Function to update the gallows based on incorrect guesses
function updateGallows() {
    const canvas = document.getElementById('gallows');
    const ctx = canvas.getContext('2d');
    
    switch(incorrectGuesses) {
        case 1:
            // Head
            ctx.beginPath();
            ctx.arc(120, 70, 20, 0, Math.PI * 2);
            ctx.stroke();
            break;
        case 2:
            // Body
            ctx.beginPath();
            ctx.moveTo(120, 90);
            ctx.lineTo(120, 150);
            ctx.stroke();
            break;
        case 3:
            // Left arm
            ctx.beginPath();
            ctx.moveTo(120, 100);
            ctx.lineTo(80, 130);
            ctx.stroke();
            break;
        case 4:
            // Right arm
            ctx.beginPath();
            ctx.moveTo(120, 100);
            ctx.lineTo(160, 130);
            ctx.stroke();
            break;
        case 5:
            // Left leg
            ctx.beginPath();
            ctx.moveTo(120, 150);
            ctx.lineTo(90, 200);
            ctx.stroke();
            break;
        case 6:
            // Right leg
            ctx.beginPath();
            ctx.moveTo(120, 150);
            ctx.lineTo(150, 200);
            ctx.stroke();
            break;
    }
}

// Initially start the game when page loads
window.onload = function() {
    drawGallows();
    startGame();
};