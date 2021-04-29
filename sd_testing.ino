#include <SPI.h>
#include <SD.h>
#include "HX711.h"

#define calibration_factor -211100.0 //This value is obtained using the SparkFun_HX711_Calibration sketch

#define LOADCELL_DOUT_PIN  3
#define LOADCELL_SCK_PIN  2

HX711 scale;

int CS = 10;
File myFile;
String test_str = "testing"; //need a way to automatically generate a file name
int buttonPin = 8; //wire according to arduino website (pretty sure button press opens 5v)
int ledGreen = 5;
int ledRed = 6;
int x = 0;
String buttonState = "";

void setup() {
  Serial.begin(9600);
  if (Serial.available())
  {
  Serial.println("Serial initialized");
  }
  pinMode(buttonPin, INPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledRed, OUTPUT);
  SD.begin(CS);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0
  myFile = SD.open(test_str, FILE_WRITE);
  
  for (x = 0; x < 4; x++) { //blink the red led 4 times once the SD file is opened
    digitalWrite(ledRed, HIGH);
    delay(50);
    digitalWrite(ledRed, LOW);
    delay(50);
  }
  Serial.println("File successfully opened");
 
}

void loop() {
  buttonState = digitalRead(buttonPin);
  
  while (buttonState == LOW) //while the button is not pressed
  {
    myFile.println(scale.get_units(), 10); //print the scale output to the SD file
  }

  myFile.close(); //close the file once the button is pressed
    Serial.println("File closed");
    
  for (x = 0; x < 4; x++) { //blink the green LED 4 times
    digitalWrite(ledGreen, HIGH);
    delay(50);
    digitalWrite(ledGreen, LOW);
    delay(50);
  }
  delay(30000);
}
