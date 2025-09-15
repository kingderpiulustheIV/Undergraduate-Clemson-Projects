// Sean Farrell
// 6/14/2025
// CPSC 3750
// program exam #1 
// Attempted to complete grade A
// clarifications:
// This program generates a list of prime and non-prime numbers based on user input, displays them, and calculates their sums. 
// It also includes a color animation for the lists.

// this javascript code defines a class `PrimeGenerator` that handles the generation of prime and non-prime numbers, their display, and sum calculation. 
// It also includes an animation feature to change the colors of the lists periodically.
class PrimeGenerator {    

        //  object constructor to generate prime and non-prime numbers, display them, and calculate their sums.
        constructor() {
            this.primeNumbers = [];
            this.nonPrimeNumbers = [];
            this.colorInterval = null;
            this.initializeEventListeners();
        }
    
        // Initialize event listeners for buttons
        initializeEventListeners() {
            document.getElementById('startButton').addEventListener('click', () => this.generateLists());
            document.getElementById('primeSumButton').addEventListener('click', () => this.calculateSum('prime'));
            document.getElementById('nonPrimeSumButton').addEventListener('click', () => this.calculateSum('nonPrime'));
        }
        // Function to check if a number is prime
        isPrime(num) {
            
            // special cases for numbers less than 2
            if (num < 2) 
                return false;

            // Special case for 2
            if (num === 2) 
                return true;
            // case for all numbers greater than 2 that are even
            if (num % 2 === 0) 
                return false;
            
            // Check for factors from 3 to the square root of num, skipping even numbers
            for (let i = 3; i <= Math.sqrt(num); i += 2) {
                if (num % i === 0) 
                    return false;
            }
            // If no factors found, the number is prime
            return true;
        }
    
        // Function to generate lists of prime and non-prime numbers based on user input
        generateLists() {
            
            // Get the input number from the user
            const inputNumber = parseInt(document.getElementById('numberInput').value);
            
            // Validate input to ensure it's a number greater than 0
            if (!inputNumber || inputNumber < 1) {
                alert('Please enter a valid number greater than 0');
                return;
            }

            // initialize the prime and non-prime lists
            this.primeNumbers = [];
            this.nonPrimeNumbers = [];
    
            // Generate prime and non-prime numbers from 1 to the input number
            for (let i = 1; i <= inputNumber; i++) {
                if (this.isPrime(i)) {
                    this.primeNumbers.push(i);
                } 
                else {
                    this.nonPrimeNumbers.push(i);
                }

            }
            // Display the generated lists and show sum buttons
            this.displayLists();
            this.showSumButtons();
            this.startColorAnimation();
        }
    
        // Function to display the prime and non-prime numbers in the respective sections
        displayLists() {

            // get the list elements from the DOM
            const primeListElement = document.getElementById('primeList');
            const nonPrimeListElement = document.getElementById('nonPrimeList');
    
            // Display prime numbers
            primeListElement.innerHTML = this.primeNumbers
                .map(num => `<span class="number-item">${num}</span>`)
                .join('');
    
            // Display non-prime numbers
            nonPrimeListElement.innerHTML = this.nonPrimeNumbers
                .map(num => `<span class="number-item">${num}</span>`)
                .join('');
        }
    
        // Function to show the sum buttons and hide previous results
        showSumButtons() {
    
            // Show the sum buttons for prime and non-prime numbers
            document.getElementById('primeSumButton').style.display = 'block';
            document.getElementById('nonPrimeSumButton').style.display = 'block';
            
            // Hide previous sum results
            document.getElementById('primeSumResult').style.display = 'none';
            document.getElementById('nonPrimeSumResult').style.display = 'none';
        }
        
        // Function to calculate the sum of prime or non-prime numbers and display the result
        calculateSum(type) {

            // create variables to hold the sum and result element based on the type
            let sum, resultElement;

            // If type is prime, calculate the sum of prime numbers
            if (type === 'prime') {
                sum = this.primeNumbers.reduce((acc, num) => acc + num, 0);
                resultElement = document.getElementById('primeSumResult');
            }
            // If type is non-prime, calculate the sum of non-prime numbers
            else {
                sum = this.nonPrimeNumbers.reduce((acc, num) => acc + num, 0);
                resultElement = document.getElementById('nonPrimeSumResult');
            }

            // Display the sum results for prime or non-prime numbers
            resultElement.textContent = `Sum: ${sum}`;
            resultElement.style.display = 'block';
        }
    
        // Function to start the color animation for the prime and non-prime sections
        startColorAnimation() {
            
            // Clear any existing interval
            if (this.colorInterval)
                clearInterval(this.colorInterval);
            
            // Get the prime and non-prime sections from the DOM
            const primeSection = document.getElementById('primeSection');
            const nonPrimeSection = document.getElementById('nonPrimeSection');
            
            // Initialize a state variable to toggle colors
            let colorState = false;
        
            // Set an interval to change the colors of the sections every 5 seconds
            this.colorInterval = setInterval(() => {
                
                // switch the class names of the sections based on the color state
                if (colorState) {
                    primeSection.className = 'list-section prime-color-1';
                    nonPrimeSection.className = 'list-section non-prime-color-1';
                } 
                else {
                    primeSection.className = 'list-section prime-color-2';
                    nonPrimeSection.className = 'list-section non-prime-color-2';
                }
                // toggle the color state for the next interval
                colorState = !colorState;
            }, 5000);
        }
    }
    
    // Initialize the application when the page loads
    document.addEventListener('DOMContentLoaded', () => {
        new PrimeGenerator();
    });