/*
   1- Author: Muhammad Hakim - UIN: 667621373
   2- Lab: Lab 4 - Multiple Inputs and Outputs 
   3- Description:
      The code is a solution that requires the implementation of two independent systems that function concurrently.
      The first system uses a joystick to control 4 LEDs in a diamond formation, where each LED corresponds to a direction of the joystick.
      The second system uses a photoresistor to control the speed of the output of a piezo speaker, which plays a melody from a given link.
      As the light intensity changes on the photoresistor, the speed of the melody changes.
   4-Lab Questions:
      What does the map() function do? 
        The map() function is used  to map the input from the photoresistor to the output speed of the melody.
      How did you change the speed of the melody in your code?
        The speed of the melody can be changed by using the input from the photoresistor to alter the noteDuration variable using the map() function.
        The map() function is used to convert the input range from the photoresistor to the desired output range for the noteDuration variable.
        This way, when the light intensity on the photoresistor changes, the noteDuration variable changes accordingly, resulting in a change in the speed of the melody.
      What was the hardest part of the lab to implement? 
        Figuring out what Piezo Speaker looks like.
   5- References: 
      https://lastminuteengineers.com/joystick-interfacing-arduino-processing/
      https://www.arduino.cc/reference/en/language/functions/math/map/
      https://www.circuitbasics.com/how-to-use-photoresistors-to-detect-light-on-an-arduino/
      https://github.com/robsoncouto/arduino-songs
   6- Demo:Demonstration uploaded to VoiceThread 
*/

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0

// Define the pins for the joystick and LEDs
int joyXPin = A0;
int joyYPin = A1;
int ledUpPin = 8;
int ledDownPin = 9;
int ledLeftPin = 10;
int ledRightPin = 11;
// Define variables to store the joystick values
int joyXVal = 0;
int joyYVal = 0;
// change this to whichever pin you want to use
int buzzer = 7;
const int photoresistor_pin = A2;


// change this to make the song slower or faster
int tempo = 132;

// notes of the moledy followed by the duration.
// a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
// !!negative numbers are used to represent dotted notes,
// so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
int melody[] = {

  // Baby Elephant Walk
  // Score available at https://musescore.com/user/7965776/scores/1862611


  NOTE_C4,-8, NOTE_E4,16, NOTE_G4,8, NOTE_C5,8, NOTE_E5,8, NOTE_D5,8, NOTE_C5,8, NOTE_A4,8,
  NOTE_FS4,8, NOTE_G4,8, REST,4, REST,2,
  NOTE_C4,-8, NOTE_E4,16, NOTE_G4,8, NOTE_C5,8, NOTE_E5,8, NOTE_D5,8, NOTE_C5,8, NOTE_A4,8,
  NOTE_G4,-2, NOTE_A4,8, NOTE_DS4,1,

  NOTE_A4,8,
  NOTE_E4,8, NOTE_C4,8, REST,4, REST,2,
  NOTE_C4,-8, NOTE_E4,16, NOTE_G4,8, NOTE_C5,8, NOTE_E5,8, NOTE_D5,8, NOTE_C5,8, NOTE_A4,8,
  NOTE_FS4,8, NOTE_G4,8, REST,4, REST,4, REST,8, NOTE_G4,8,
  NOTE_D5,4, NOTE_D5,4, NOTE_B4,8, NOTE_G4,8, REST,8, NOTE_G4,8,

  NOTE_C5,4, NOTE_C5,4, NOTE_AS4,16, NOTE_C5,16, NOTE_AS4,16, NOTE_G4,16, NOTE_F4,8, NOTE_DS4,8,
  NOTE_FS4,4, NOTE_FS4,4, NOTE_F4,16, NOTE_G4,16, NOTE_F4,16, NOTE_DS4,16, NOTE_C4,8, NOTE_G4,8,
  NOTE_AS4,8, NOTE_C5,8, REST,4, REST,2,
};

// sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
// there are two values per note (pitch and duration), so for each note there are four bytes
int notes = sizeof(melody) / sizeof(melody[0]) / 2;

// this calculates the duration of a whole note in ms
int wholenote = (60000 * 4) / tempo;

int divider = 0, noteDuration = 0;
int threshold = 25;

void setup() {
  // Set the LED pins to output mode
  pinMode(ledUpPin, OUTPUT);
  pinMode(ledDownPin, OUTPUT);
  pinMode(ledLeftPin, OUTPUT);
  pinMode(ledRightPin, OUTPUT);  
  
  // initialize the pins for the photoresistor and piezo speaker
  pinMode(photoresistor_pin, INPUT);
  pinMode(buzzer, OUTPUT);
  
  // Start the serial communication
  Serial.begin(9600);
}

void loop() {

  // iterate over the notes of the melody.
  // Remember, the array is twice the number of notes (notes + durations)
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
    // read the value of the photoresistor:
    int photoresistorValue = analogRead(photoresistor_pin);
    int light = map(photoresistorValue, 0, 1023, 1, 10);
    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(buzzer, melody[thisNote], noteDuration * 0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration/(0.1*light));

    // stop the waveform generation before the next note.
    noTone(buzzer);

  // Read the joystick values
  joyXVal = analogRead(joyXPin);
  joyYVal = analogRead(joyYPin);

  // Map the joystick values to LED states
  if (joyXVal < 450) {
    digitalWrite(ledLeftPin, HIGH);
    digitalWrite(ledRightPin, LOW);
  } else if (joyXVal > 550) {
    digitalWrite(ledLeftPin, LOW);
    digitalWrite(ledRightPin, HIGH);
  } else {
    digitalWrite(ledLeftPin, LOW);
    digitalWrite(ledRightPin, LOW);
  }
  
  if (joyYVal < 450) {
    digitalWrite(ledUpPin, HIGH);
    digitalWrite(ledDownPin, LOW);
  } else if (joyYVal > 550) {
    digitalWrite(ledUpPin, LOW);
    digitalWrite(ledDownPin, HIGH);
  } else {
    digitalWrite(ledUpPin, LOW);
    digitalWrite(ledDownPin, LOW);
  }
  
  // Print the joystick values to the Serial Monitor
  Serial.print("X: ");
  Serial.print(joyXVal);
  Serial.print(", Y: ");
  Serial.println(joyYVal);

  }
}
