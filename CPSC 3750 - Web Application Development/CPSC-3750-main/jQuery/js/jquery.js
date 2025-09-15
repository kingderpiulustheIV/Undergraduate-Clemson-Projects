/* Sean Farrell
6/28/2025
CPSC 3750 Wooster
ASSIGNMENT: jQuery  
DESCRIPTION: This assignment showcases using jquery library buy using, cursor interaction, fade methods datepicker and accordion methods.
This jquery.js uses and provides client sided logic to showcase the use of the jQuery library.*/
$(document).ready(function(){
        
      // 1. Hover effect for divs
        $("div.hover-div").hover(
          function() {
            $(this).css("background-color", "yellow");
          },
          function() {
            $(this).css("background-color", "#2d2d2d");
          }
        );
        
        // 2. Fade buttons functionality
        $("#fade-div1").click(function(){
          $("#div1").fadeOut();
        });
        
        $("#fade-div2").click(function(){
          $("#div2").fadeOut();
        });
        
        $("#fade-div3").click(function(){
          $("#div3").fadeOut();
        });
        
        // 3. Initialize datepicker
        $("#datepicker").datepicker();
        
        // 4. Initialize accordion
        $("#accordion").accordion({
          collapsible: true
        });
        
        // 5. Initialize and animate progressbar
        $("#progressbar").progressbar({
          value: 0
        });
        
        // Add label inside the progress bar
        $("#progressbar").append("<div class='progress-label'>0%</div>");
        $(".progress-label").css({
                position: "absolute",
                left: "50%",
                top: "4px",
                transform: "translateX(-50%)",
                fontWeight: "bold",
                textShadow: "1px 1px 0 #000"
        });
        
        let progress = 0;
        const interval = setInterval(function() {
                progress += 5;
                
                // Update progressbar value
                $("#progressbar").progressbar("value", progress);
                
                // Update both labels
                $(".progress-label").text(progress + "%");
                $("#progress-label").text(progress + "%");
                
                // Change color based on progress
                let r = Math.floor(255 - (progress * 2.55));
                let g = Math.floor(progress * 2.55);
                $(".ui-progressbar-value").css({
                "background": `linear-gradient(to right, #2d2d2d, rgb(${r}, ${g}, 80))`,
                "transition": "width 0.5s ease"
                });
                
                if (progress >= 100) {
                clearInterval(interval);
                $("#progress-complete").text("Process Complete!");
                $(".progress-label").css("color", "#fff");
                }

        }, 1000); // Update every second for 20 seconds
      });