/*
    This JavaScript file calculates the factorial of a number.
    It demonstrates the use of loops and variables.
*/

// Function to calculate the factorial of a number
function factorial(n) {
    // Check if the number is negative
    if (n < 0) {
        console.error("Error: Factorial of a negative number is undefined");
        return;
    }

    // Initialize the factorial variable
    var result = 1;

    // Calculate the factorial using a for loop
    for (var i = 1; i <= n; i++) {
        result *= i; /* Analisando Ele */
    }

    // Return the factorial
    return result;
}

// Test the factorial function
var number = 5;
var factorialResult = factorial(number);

// Print the result to the console
console.log("The factorial of " + number + " is: " + factorialResult); // Testando ele

// End of the program
