/*
    script.js - JavaScript for My Website
*/

// Wait for the DOM to be fully loaded
document.addEventListener("DOMContentLoaded", function() {
    // Get the navigation links
    var navLinks = document.querySelectorAll("nav a");

    /*
        Attach click event listeners to each navigation link
    */
    navLinks.forEach(function(link) {
        link.addEventListener("click", function(event) {
            event.preventDefault(); // Prevent the default link behavior
            var targetSection = document.querySelector(this.getAttribute("href"));
            if (targetSection) {
                scrollToSection(targetSection);
            }
        });
    });
});

// Function to scroll to a specific section smoothly
function scrollToSection(section) {
    var scrollOptions = {
        behavior: "smooth",
        block: "start"
    };
    section.scrollIntoView(scrollOptions);
}
