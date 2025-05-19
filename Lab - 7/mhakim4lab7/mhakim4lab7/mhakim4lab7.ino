/*
   1- Author: Muhammad Hakim - UIN: 667621373
   2- Lab: Lab 7 - Interrupts 
   3- Description:The code is designed to implement a game with a seven-segment display, a push button, and a serial monitor.
      The seven-segment display will loop through digits 0-9, incrementing twice every second.
      The serial monitor will randomly select a number from 0-9 and display it.
      When the push button is pressed, an interrupt function will be called. 
      If the random number displayed on the seven-segment display is 7 and the button is pressed at that moment,
      the serial monitor will display the message "Congratulations! You pressed at the correct number."
      and a new random number will be displayed on the monitor to start the game again.
      If the button is pressed at any other time or the random number displayed is not 7,
      the serial monitor will display the message "Oops! You stopped at the wrong number. Resuming the game."
      but the game will continue with the same random number until the button is pressed at the correct time.
   4-Lab Questions:
      What is the purpose of a current-limiting resistor in a seven-segment display circuit? - The purpose of a current-limiting resistor in a seven-segment display circuit is to limit the amount of current flowing through the LEDs in the display.
        LEDs are current-controlled devices,which means that the amount of current flowing through them determines the amount of light they emit.
        If too much current flows through the LEDs, they can be damaged or even destroyed.
        Therefore, a current-limiting resistor is placed in series with each LED segment in the seven-segment display to ensure that the current through the LED is limited to a safe value.
        The value of the resistor is chosen such that the voltage drop across it and the voltage drop across the LED add up to the supply voltage.
        This ensures that the current through the LED is limited to a safe value.
      Can you display special characters? If yes, How? - Yes, it is possible to display special characters on a seven-segment display.
       This can be done by using a microcontroller to control the individual segments of the display and programming it to display the desired characters. 
      What are some common applications of seven-segment displays? -Digital clocks: Seven-segment displays are widely used in digital clocks to display the current time in hours and minutes.
        Calculators: Seven-segment displays are used in calculators to display numerical values, mathematical operations, and other functions.
        Counters: Seven-segment displays can be used to count and display the number of items produced in a factory or the number of people who have entered a building.
        Measuring instruments: Seven-segment displays can be used in various measuring instruments like multimeters, voltmeters, ammeters, and frequency meters to display the measured values.
        Automotive displays: Seven-segment displays can be used in automobiles to display the speedometer, tachometer, and fuel level.
        Scoreboards: Seven-segment displays can be used in sports scoreboards to display the score, time remaining, and other important information.
   5- References: https://www.electronics-tutorials.ws/blog/7-segment-display-tutorial.html
      https://lastminuteengineers.com/seven-segment-arduino-tutorial/
      https://www.youtube.com/watch?v=QhIm6e5AH44&ab_channel=PaulMcWhorter	
      https://www.youtube.com/watch?v=9VZUb5cMrV0&ab_channel=CoreElectronics
   6- Demo: "Demonstration uploaded to VoiceThread"
*/
#include <SevSeg.h>

SevSeg sevseg; // Create an instance of the SevSeg library

int buttonPin = 2; // Set the button pin to digital pin 2
int randomNumber; // Variable to store the random number
int currentNumber = 0; // Variable to keep track of the current number on the display

void setup() {
  //Set to 1 for single digit display
	byte numDigits = 1;
  //defines common pins while using multi-digit display. Left empty as we have a single digit display
	byte digitPins[] = {};
  //Defines arduino pin connections in order: A, B, C, D, E, F, G, DP
	byte segmentPins[] = {4, 3, 5, 6, 7, 8, 9, 10};
	bool resistorsOnSegments = true;
  randomSeed(analogRead(0)); // Seed the random number generator with an analog value
  randomNumber = random(10); // Generate a random number between 0 and 9
  Serial.begin(9600); // Initialize serial communication
  Serial.print("The selected random Number is : "); // Print the random number to the serial monitor
  Serial.println(randomNumber);
  sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins, resistorsOnSegments); // Initialize the SevSeg library
  pinMode(buttonPin, INPUT_PULLUP); // Set the button pin to INPUT_PULLUP mode to use internal pull-up resistor
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonInterrupt, FALLING); // Attach the button interrupt to the FALLING edge of the button pin
}

void loop() {
  sevseg.setNumber(currentNumber); // Set the current number to be displayed on the seven-segment display
  sevseg.refreshDisplay(); // Refresh the display to show the current number

  currentNumber++; // Increment the current number
  if (currentNumber > 9) { // If the current number goes over 9, reset it to 0
    currentNumber = 0;
  }

  delay(500); // Delay for 500 milliseconds to create a two-second cycle
}

void buttonInterrupt() {
  int buttonState = digitalRead(buttonPin); // Read the button state
  if (buttonState == LOW) { // If the button is pressed
    if (currentNumber == randomNumber) { // If the current number matches the random number
      Serial.println("Congratulations! You pressed at the correct number."); // Print the success message
      Serial.println("Game is restarting...");
      randomNumber = random(10); // Generate a new random number
      Serial.print("The selected random Number is : "); // Print the new random number
      Serial.println(randomNumber);
      currentNumber = 0; // Reset the current number to 0
    } else { // If the current number does not match the random number
      Serial.println("Oops! You stopped at the wrong number. Resuming the game."); // Print the failure message
      Serial.print("The selected random Number is : ");
      Serial.println(randomNumber);
    }
  }
}



