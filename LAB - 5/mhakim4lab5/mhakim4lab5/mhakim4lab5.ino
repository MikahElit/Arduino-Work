/*
   1- Author: Muhammad Hakim (as shown in Blackboard) - UIN : 667621373
   2- Lab: Lab 5 - Communication 
   3- Description: In your own words, what is this code supposed to do?
    The code is for a game called the "Even-Odd Game" that involves taking user input from the Serial Monitor and controlling a servo motor.
    The game asks the user to choose a number between 1 and 5 and to choose whether they think the sum of that number and a randomly generated number will be even or odd.
    The servo motor moves like a radar while the random number is generated and then points towards a green LED if the user wins or a red LED if the user loses.
    The game then restarts for another round.
   4-Lab Questions:
                  What function did you use to change the servo position?To change the servo position, the servo.write() function was used.
                  What are the angles of the servo motor for the three directions? 0,90,180
                  What functions/methods did you use to take input? Serial.read() was used to read input from the Serial Monitor. Additionally, the Serial.available() function was used to check if there were any bytes available to be read from the serial port.
   5- References:https://docs.arduino.cc/learn/electronics/servo-motors
                 https://www.tutorialspoint.com/arduino/arduino_servo_motor.htm
                 http://arduino.cc/en/Reference/Serial#.UwYyzfldV8E
                 http://arduino.cc/en/Serial/Available#.UwYy2PldV8E
   6- Demo: "Demonstration uploaded to VoiceThread"
*/

#include <Servo.h>

Servo myServo;
int angle = 90; // initialize the servo angle to 90 degrees (neutral position)

const int greenLedPin = 9;
const int redLedPin = 10;

void setup() {
  Serial.begin(9600); // initialize serial communication at 9600 baud rate
  myServo.attach(3); // attach the servo to pin 3
  pinMode(greenLedPin, OUTPUT); // set the green LED pin as output
  pinMode(redLedPin, OUTPUT); // set the red LED pin as output
  digitalWrite(greenLedPin, LOW); // turn off the green LED
  digitalWrite(redLedPin, LOW); // turn off the red LED
  myServo.write(angle); // move the servo to the neutral position
}

void loop() {
  int userNumber;
  String userChoice;

  Serial.println("Welcome to even odd game!!");
  Serial.println("Enter a number betweeen 1 to 5!!");
  // STEP 6: Take input for the user's number choice
  while(Serial.available() <= 0); // wait until input is available
  String input = Serial.readStringUntil('\n');
  if (input.toInt() == 0 && input != "0") {
    Serial.println("Invalid input. Please enter a number betweeen 1 to 5!!");
    return;
  }
  userNumber = input.toInt();
  Serial.print("I received: ");
  Serial.println(userNumber);
  
  // validate user input
  if(userNumber < 1 || userNumber > 5) {
    Serial.println("Invalid input.Please enter a number betweeen 1 to 5!!");
    return;
  }

  Serial.println("Now Choose odd or even! Type Even or Odd");
  
  // STEP 7: Take input for the user's even/odd choice
  while(Serial.available() <= 0); // wait until input is available
  userChoice = Serial.readStringUntil('\n'); // read the input as a string
  userChoice.trim(); // remove any whitespace
  Serial.print("I received: ");
  Serial.println(userChoice);
  
  // validate user input
  if(userChoice != "Even" && userChoice != "Odd" && userChoice != "odd" && userChoice != "even" && userChoice != "ODD" && userChoice != "EVEN") {
    Serial.println("Invalid input. Please input either Odd or Even");
    return;
  }

  Serial.println("Generating...");  
  
  // STEP 8: Move servo motor like radar
  for(int i = 0; i < 2; i++) { // move the servo back and forth twice
    for(angle = 90; angle <= 180; angle++) { // move servo from neutral position to 180 degrees
      myServo.write(angle); // write the new servo angle
      delay(15); // wait for the servo to move to the new angle
    }
    for(angle = 180; angle >= 90; angle--) { // move servo from 180 degrees to neutral position
      myServo.write(angle); // write the new servo angle
      delay(15); // wait for the servo to move to the new angle
    }
  }
  
  // STEP 9: Generate a random number and sum with user's number choice
  int randomNumber = random(1, 6); // generate a random number between 1 and 5
  int sum = userNumber + randomNumber;
  Serial.print("My Number number: ");
  Serial.println(randomNumber);
  Serial.print("Sum is ");
  Serial.println(sum);
  
  // determine if the sum is even or odd
  bool isEven = sum % 2 == 0;
  bool userWins = (isEven && userChoice == "Even") || (!isEven && userChoice == "Odd") || (isEven && userChoice == "EVEN");
  
  // STEP 10: Print result and move servo motor to the corresponding LED
  if(userWins) {
    Serial.println("Congratulations! You won!");
    digitalWrite(greenLedPin, HIGH); // turn on the green LED
    digitalWrite(redLedPin, LOW); // turn off the red LED
        angle = 0;
    myServo.write(angle); // move the servo to the green LED position
    delay(1000); // wait for 1 second
    digitalWrite(greenLedPin, LOW); // turn off the green LED
    digitalWrite(redLedPin, LOW); // turn off the red LED
    myServo.write(90); // move the servo back to the neutral position
  }
  else {
    Serial.println("Sorry, you lost. Better luck next time!");
    digitalWrite(greenLedPin, LOW); // turn off the green LED
    digitalWrite(redLedPin, HIGH); // turn on the red LED
    angle = 180; // set the servo angle to 180 degrees
    myServo.write(angle); // move the servo to the red LED position
    delay(1000); // wait for 1 second
    digitalWrite(greenLedPin, LOW); // turn off the green LED
    digitalWrite(redLedPin, LOW); // turn off the red LED
    myServo.write(90); // move the servo back to the neutral position
  }
}

