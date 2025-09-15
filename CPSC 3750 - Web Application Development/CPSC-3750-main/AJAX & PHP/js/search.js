// Sean Farrell
// 7/5/2025
// CPSC 3750 Wooster
// ASSIGNMENT: AJAX & PHP
// DESCRIPTION: showcases use of ajax and php to search state capitals
// .js file that handles client side search functionality for state capitals

// Wait for DOM to be fully loaded
document.addEventListener("DOMContentLoaded", function() {
    // Get reference to the search input and results list
    const searchInput = document.getElementById("searchlive");
    const resultsList = document.getElementById("list");
    
    // Add event listener for input changes
    searchInput.addEventListener("input", function() {
      const query = this.value.trim();
      
      // Clear results if query is empty
      if (query === "") {
        resultsList.innerHTML = "<li>[Search results will display here.]</li>";
        return;
      }
      
      // Make AJAX request with the query
      ajaxCallback = function() {
        displayResults();
      };
      
      ajaxRequest("/search.php?query=" + encodeURIComponent(query));
    });
    
    // Function to parse and display results
    function displayResults() {
      const xmlDoc = ajaxreq.responseXML;
      const states = xmlDoc.getElementsByTagName("state");
      
      // Clear previous results
      resultsList.innerHTML = "";
      
      if (states.length === 0) {
        resultsList.innerHTML = "<li>No matching states found</li>";
        return;
      }
      
      // Add each state and its capital to the results list
      for (let i = 0; i < states.length; i++) {
        const stateName = states[i].getElementsByTagName("name")[0].textContent;
        const stateCapital = states[i].getElementsByTagName("capital")[0].textContent;
        
        const listItem = document.createElement("li");
        listItem.innerHTML = `<strong>${stateName}</strong>: ${stateCapital}`;
        resultsList.appendChild(listItem);
      }
    }
  });