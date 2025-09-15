// Sean Farrell
// 6/14/2025
// CPSC 3750
// ASSIGNMENT: Card object 
// DESCRIPTION: This .js file defines a Card object and provides functionality to create, display, and manage contact cards.

// Function to print the card details
function printCard() {
   var nameLine = "<strong>Name: </strong>" + this.name + "<br>";
   var emailLine = "<strong>Email: </strong>" + this.email + "<br>";
   var addressLine = "<strong>Address: </strong>" + this.address + "<br>";
   var phoneLine = "<strong>Phone: </strong>" + this.phone + "<hr>";
   var birthdateLine = "<strong>Birthdate: </strong>" + this.birthdate + "<hr>";
   document.write(nameLine, emailLine, addressLine, phoneLine, birthdateLine);
}

// Constructor function for Card object
function Card(name,email,address,phone, birthdate) {
   this.name = name;
   this.email = email;
   this.address = address;
   this.phone = phone;
   this.birthdate = birthdate;
   this.printCard = printCard;
}

// Array to hold card objects
var cards = [];

// Create the objects from the sample code
var sue = new Card("Sue Suthers", "sue@suthers.com", "123 Elm Street, Yourtown ST 99999", "555-555-9876");
var fred = new Card("Fred Fanboy", "fred@fanboy.com", "233 Oak Lane, Sometown ST 99399", "555-555-4444");
var jimbo = new Card("Jimbo Jones", "jimbo@jones.com", "233 Walnut Circle, Anotherville ST 88999", "555-555-1344");

// Add the initial cards to the array
cards.push(sue);
cards.push(fred);
cards.push(jimbo);



// Function to display all cards in a table
function displayAllCards() {
   var table = "<table border='1'><tr><th>Name</th><th>Email</th><th>Address</th><th>Phone</th><th>Birthdate</th></tr>";
   cards.forEach(function (card) {
      table += `<tr>
         <td>${card.name}</td>
         <td>${card.email}</td>
         <td>${card.address}</td>
         <td>${card.phone}</td>
         <td>${card.birthdate}</td>
      </tr>`;
   });
   table += "</table>";
   document.getElementById("cardDisplay").innerHTML = table;
}

// Function to add a new card
function addNewCard() {
   var name = document.getElementById("name").value;
   var email = document.getElementById("email").value;
   var address = document.getElementById("address").value;
   var phone = document.getElementById("phone").value;
   var birthdate = document.getElementById("birthdate").value;

     // Validate inputs
     if (!name || !email || !address || !phone || !birthdate) {
      alert("Please fill in all fields");
      return;
   }

   var newCard = new Card(name, email, address, phone, birthdate);
   cards.push(newCard);

   // Clear the form
   document.getElementById("cardForm").reset();
   alert("New card added!");
}