// Sean Farrell
// 06/05/2025
// ASSIGNMENT: Javascript Sort
// CPSC 3750 Wooster
// FILE: sort.js
// Description: This script sorts names entered in a text field and displays them in a numbered list format.

// initialize the counter and the array
var numbernames = 0;
var names = new Array();

function SortNames() {
   // Get the name from the text field
   thename = document.theform.newname.value.trim();
   
   // Only proceed if the name is not empty
   if (thename) {
      // Convert name to uppercase before adding it
      thename = thename.toUpperCase();
      
      // Add the name to the array
      names[numbernames] = thename;
      
      // Increment the counter
      numbernames++;
      
      // Sort the array
      names.sort();
      
      // Display names as a numbered list
      let numberedList = "";
      for (let i = 0; i < names.length; i++) {
         numberedList += (i + 1) + ". " + names[i] + "\n";
      }
      
      document.theform.sorted.value = numberedList;
      
      // Clear the input field
      document.theform.newname.value = "";
   }
   
   // Prevent form submission (which would cause page reload)
   return false;
}

// Add event listener for the Enter key
function setupEnterKey() {
   document.theform.newname.addEventListener("keypress", function(event) {
      if (event.key === "Enter") {
         event.preventDefault();
         SortNames();
      }
   });
}

// Initialize the event listener when the page loads
window.onload = setupEnterKey;
