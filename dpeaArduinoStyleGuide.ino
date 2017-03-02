/* DPEA Arduino Style Guide - Created 022617 by Kyle Stewart */
/* Begin each sketch with a one-line file name, date, and author like this */

////////////////////////////////////////////////////////////////////////////////
//                Golden Rule: If your code looks like junk, it is            //
//                                                                            //
//                  if (codeAppearance == junk) code = junk;                  //
//                                                                            //
//           Note the use of the comparison vs assignment operators :)        //
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//  Global variables should only be used for pins and where strictly needed   //
//  Use constant byte variable type for pin numbers or where logical          //
//  WARNING: Keep in mind a byte can only be between 0 and 255.               //
////////////////////////////////////////////////////////////////////////////////
const byte ledArray[] = {3, 14, 15, 9, 2, 6, 5, 3}; // mmmmm... pi
const byte numberOfLeds = sizeof(ledArray); // sizeof gives array size in bytes

////////////////////////////////////////////////////////////////////////////////
//  Related variables may be declared on one line (here, knob variables)      //
////////////////////////////////////////////////////////////////////////////////
const byte minKnobValue = 100, knobPin = A5;

void setup() {
  Serial.begin(9600); // have the Arduino dial up the computer

  for (byte pin = 2; pin < 16; pin++) {
    pinMode(pin, OUTPUT);
  }
}

////////////////////////////////////////////////////////////////////////////////
//  Keep line width reasonable to allow split screen usage                    //
//  For reference, these text boxes are 80 characters wide (an old standard)  //
//  for statements can be split as demonstrated below if necessary            //
//                                                                            //
//  Note the vertical spacing to group related statements (paragraphing)      //
//  Readability, structure, and organization are paramount to good code       //
//  Use descriptive variable names and clear logic for best readability       //
//                                                                            //
//  Comment anything complicated, potentially confusing, or unclear           //
//  Considering rethinking your approach if you have to comment excessively   //
//  Your code should read like English, so it should mostly self-comment      //
//                                                                            //
//  The Serial Monitor is a great commenting and debugging tool               //
//  I give two different example uses, one of which uses Strings              //
//  If your code isn't working correctly due to logic errors, Monitor it!     //
////////////////////////////////////////////////////////////////////////////////

void loop() {
  //
  // blink each LED in the array in order using the knob for delay times
  //
  for (byte distanceFromStartOfArray = 0;
       distanceFromStartOfArray < numberOfLeds;
       distanceFromStartOfArray++) {

    byte thisPin = ledArray[distanceFromStartOfArray];

    Serial.print("Blinking LED: ");
    Serial.println(thisPin);

    digitalWrite(thisPin, HIGH);
    delayUsingKnob();
    digitalWrite(thisPin, LOW);
    delayUsingKnob();
  }
}

//
// delay for a time in milliseconds according to the knob position
// delay length can change mid-delay because we use millis() and a while loop
// the min delay is set by minKnobValue and the max is 1023 = 0b1111111111
//
void delayUsingKnob() {
  int knobValue = analogRead(knobPin); // read the knob voltage (0 to 1023)

  String knobPrintString = String("Starting knob Value: ") + knobValue;
  Serial.println(knobPrintString);

  if (knobValue < minKnobValue) knobValue = minKnobValue; // single-line if

  //
  // run the timer while checking the knob for updates
  //
  unsigned long delayStartTime = millis(); // get the Arduino clock time
  while (millis() - delayStartTime < knobValue) {
    int newKnobValue = analogRead(knobPin); // update the knob value

    if (newKnobValue < minKnobValue) {
      knobValue = minKnobValue;
    } else {
      knobValue = newKnobValue;
    }
  }
}

