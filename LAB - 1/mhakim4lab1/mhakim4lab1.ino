// 1- Muhammad Hakim - 667621373
// 2- Lab 1 - Toggle button
// 3- Description - Implement an AND gate using Arduino.
// 4- PIN Numbers - Button 1 for Blue LED to the left is connected to pin 4 to provide input,Button 2 for Blue LED to the right is connected to pin 6 to provide input.LED red is connected to pin 7 show output for the choosen gate considering input from the two buttons.
// 5- References - Switches & Pushbuttons: Where To Use Each Type(https://www.youtube.com/watch?v=c7UZv6eH4YU),State Change Detection(https://docs.arduino.cc/built-in-examples/digital/StateChangeDetection),Arduino Turorial: How to use a button with Arduino Uno(https://www.youtube.com/watch?v=VPGRqML_v0w&ab_channel=educ8s.tv),Arduino Tutorial 28: Using a Pushbutton as a Toggle Switch(https://www.youtube.com/watch?v=aMato4olzi8)
// 6- Demo - Demonstration uploaded to VoiceThread.

int input1 = 4;
int input2 = 6;
int buttonState = 0;
int buttonState2 = 0;
int red = 7;


void setup() { // For setting input and output,using the related pins.
  pinMode(red,OUTPUT);
  pinMode(input1, INPUT);
  pinMode(input2, INPUT);
}

void loop() {
  buttonState = digitalRead(input1);
  buttonState2 = digitalRead(input2);

  if (buttonState == HIGH || buttonState2 == HIGH) //Check for output considering input
    digitalWrite(red, HIGH);
  else
    digitalWrite(red, LOW);
}
