/* DPEA Arduino Style Guide - Written by Kyle Stewart - Updated 04/06/17 */
/* Begin each sketch with a one-line file name, date, and author like this */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                    Golden Rule: If your code looks like junk, it is                                //
//                                                                                                                    //
//                                      if (codeAppearance == junk) code = junk;                                      //
//                                                                                                                    //
//                               Note the use of the comparison vs assignment operators :)                            //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Headers (in the comment blocks) can make your code easier to read quickly                                         //
//  Keep your lines no longer than the headers for split screen usage                                                 //
//  Good formatting and organization makes good code :)                                                               //
//                                                                                                                    //
//  Note the vertical spacing to group related statements (paragraphing)                                              //
//  Readability, structure, and organization are paramount to good code                                               //
//  Use descriptive variable names and clear logic for best readability                                               //
//                                                                                                                    //
//  Comment anything complicated, potentially confusing, or unclear                                                   //
//  Considering rethinking your approach if you have to comment excessively                                           //
//  Your code should read like English, so it should mostly self-comment                                              //
//                                                                                                                    //
//  The Serial Monitor is a great commenting and debugging tool                                                       //
//  I give two different example uses, one of which uses Strings                                                      //
//  If your code isn't working correctly due to logic errors, Monitor it!                                             //
//                                                                                                                    //
//  Global variables should only be used for pins and where strictly needed                                           //
//  Use constant byte variable type for pin numbers or where logical                                                  //
//  WARNING: Keep in mind a byte can only be between 0 and 255.                                                       //
//                                                                                                                    //
//  Related variables may be declared on one line (see below)                                                         //
//  Begin example below                                                                                               //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                                    //
//                                            Global Variable Declarations                                            //
//                                                                                                                    //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const byte knobPin = A5; // bytes are integers between 0 and 255, const means we can't change these.  use for pins!
const int minKnobValue = 256, maxKnobValue = 1023; // these values are bigger than 255 so we use ints

const byte piArray[] = {3, 14, 15, 9, 2, 6, 5, 3}; // mmmmm... pi
const byte piecesOfPi = sizeof(piArray); // sizeof gives array size in bytes

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                                    //
//                                                   Main Functions                                                   //
//                                                                                                                    //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  Serial.begin(9600); // have the Arduino dial up the computer

  for (byte pin = 2; pin < 16; pin++) {
    pinMode(pin, OUTPUT);
  }
}

void loop() {
  blinkPiUsingKnob();
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                                    //
//                                                    Pi Functions                                                    //
//                                                                                                                    //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void blinkPiUsingKnob() {
  //
  // typically, index is a better variable name than distanceFromStartOfArray, but they mean the same thing ;)
  //
  for (byte distanceFromStartOfArray = 0; distanceFromStartOfArray < piecesOfPi; distanceFromStartOfArray++) {

    const byte thisPin = piArray[distanceFromStartOfArray];

    printSliceOfPi(thisPin);

    digitalWrite(thisPin, HIGH);
    delayUsingKnob();
    digitalWrite(thisPin, LOW);
    delayUsingKnob();
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                                    //
//                                                   Knob Functions                                                   //
//                                                                                                                    //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// delay for a time in milliseconds according to the knob position (between minKnobValue and maxKnobValue)
// delay length can change mid-delay because we use millis() and a while loop
//
void delayUsingKnob() {
  int knobValue = getStartingKnobVoltage(knobPin);

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

int getStartingKnobVoltage(const byte pin) {
  int startingKnobValue = analogRead(pin); // read the knob voltage (0 to 1023)

  printStartingKnobValue(startingKnobValue);

  if (startingKnobValue < minKnobValue) startingKnobValue = minKnobValue;
  if (startingKnobValue == maxKnobValue) printEasterEgg();

  return startingKnobValue;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                                    //
//                                               Serial Print Functions                                               //
//                                                                                                                    //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void printSliceOfPi(const byte thisPin) {
  //\n skips a line, \t inserts a tab, Strings are sets of characters
  String piPrintString = String("\n") + String("This slice of pi: \t") + thisPin;
  Serial.println(piPrintString);
}

void printStartingKnobValue(const int startingKnobValue) {
  Serial.print("Starting knob value:");
  Serial.print("\t Decimal: ");
  Serial.print(startingKnobValue);
  Serial.print(",\t Binary: ");
  printBinary(startingKnobValue);
  Serial.print(",\t Hexadecimal: ");
  Serial.println(startingKnobValue, HEX);
}

void printBinary(const int value) {
    for (int bitPosition = 9; bitPosition >= 0; bitPosition--) Serial.print(bitRead(value, bitPosition));
}

void printEasterEgg() {
  Serial.println("Turn it up to 1111111111!");
}
