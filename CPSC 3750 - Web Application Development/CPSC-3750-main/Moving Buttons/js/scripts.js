/* Sean Farrell
 06/05/2025
 CPSC 3750 Wooster
 ASSIGNMENT: Moving Buttons
 FILE: scripts.js
 Description: This script creates a dynamic button interface where buttons can be created, moved, and clicked to change color and update a total.
*/
const viewingArea = document.getElementById('viewingArea');
const makeButton = document.getElementById('makeButton');
const colorDropdown = document.getElementById('colorDropdown');
const movePauseButton = document.getElementById('movePauseButton');
const totalLabel = document.getElementById('totalLabel');

let total = 0;
let buttons = [];
let moving = false;
let intervalId;

// Initialize the move/pause button to "MOVE" state
movePauseButton.textContent = 'MOVE';

// Generate a random integer within a range
function getRandomInt(min, max) {
        return Math.floor(Math.random() * (max - min + 1)) + min;
}

// Create a new button
makeButton.addEventListener('click', () => {
        const color = colorDropdown.value;
        const randomNumber = getRandomInt(1, 100);
        const button = document.createElement('button');
        button.textContent = randomNumber;
        button.style.backgroundColor = color;
        button.style.position = 'absolute';
        button.style.left = `${getRandomInt(0, viewingArea.clientWidth - 50)}px`;
        button.style.top = `${getRandomInt(0, viewingArea.clientHeight - 50)}px`;

        // Ensure button stays within bounds
        button.style.left = Math.min(
                parseInt(button.style.left),
                viewingArea.clientWidth - 50
        ) + 'px';
        button.style.top = Math.min(
                parseInt(button.style.top),
                viewingArea.clientHeight - 50
        ) + 'px';

        // Change color on click and update total
        button.addEventListener('click', () => {
                button.style.backgroundColor = colorDropdown.value;
                total += parseInt(button.textContent);
                totalLabel.textContent = `Total: ${total}`;
        });

        viewingArea.appendChild(button);
        
        // Ensure buttons have non-zero velocity
        let dx = getRandomInt(-2, 2);
        let dy = getRandomInt(-2, 2);
        
        // If both velocities are 0, give a random non-zero value
        if (dx === 0 && dy === 0) {
                dx = Math.random() > 0.5 ? 1 : -1;
        }
        buttons.push({ element: button, dx: dx, dy: dy });
});

// Move buttons
function moveButtons() {
        buttons.forEach((btn) => {
                
                // Get current position from CSS properties
                let currentLeft = parseInt(btn.element.style.left) || 0;
                let currentTop = parseInt(btn.element.style.top) || 0;

                // Calculate new position
                let newLeft = currentLeft + btn.dx;
                let newTop = currentTop + btn.dy;

                // Get button dimensions (assuming 50px width/height based on initial positioning)
                const buttonWidth = 50;
                const buttonHeight = 50;

                // Check for collisions with edges and bounce
                if (newLeft <= 0 || newLeft + buttonWidth >= viewingArea.clientWidth) {
                        btn.dx *= -1;
                        
                        // Ensure velocity has sufficient magnitude
                        
                        if (Math.abs(btn.dx) < 1) btn.dx = btn.dx >= 0 ? 1 : -1;
                        // Keep button within bounds
                        newLeft = newLeft <= 0 ? 1 : viewingArea.clientWidth - buttonWidth - 1;
                }
                if (newTop <= 0 || newTop + buttonHeight >= viewingArea.clientHeight) {
                        btn.dy *= -1;
                        
                        // Ensure velocity has sufficient magnitude
                        
                        if (Math.abs(btn.dy) < 1) btn.dy = btn.dy >= 0 ? 1 : -1;
                        // Keep button within bounds
                        newTop = newTop <= 0 ? 1 : viewingArea.clientHeight - buttonHeight - 1;
                }

                btn.element.style.left = `${newLeft}px`;
                btn.element.style.top = `${newTop}px`;
        });
}

// Toggle MOVE/PAUSE
movePauseButton.addEventListener('click', () => {
        if (moving) {
                clearInterval(intervalId);
                movePauseButton.textContent = 'MOVE';
        } else {
                intervalId = setInterval(moveButtons, 50);
                movePauseButton.textContent = 'PAUSE';
        }
        moving = !moving;
});