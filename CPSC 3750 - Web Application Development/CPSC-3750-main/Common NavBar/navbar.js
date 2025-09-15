// Sean Farrell
// 5/31/2025
// CPSC 3750 Wooster
// ASSIGNMENT: Common NavBar
document.addEventListener('DOMContentLoaded', () => {
        fetch('navbar.html')
          .then(response => response.text())
          .then(data => {
            document.getElementById('navbar').innerHTML = data;
          })
          .catch(error => console.error('Error loading navigation bar:', error));
      });