/**********************************************************
	File:   Testonderzoek.cpp
	Project:   Capacitive + gsr + lcd
	
	Copyright: (c) 2024 Patrick Schuurman
	
	Auteur:    Patrick Schuurman
	Datum:     18 mei 2024
**********************************************************/

// Bibliotheek voor communicatie met I2C / TWI apparaten
#include <Wire.h> 
#include <LiquidCrystal_I2C.h> 
LiquidCrystal_I2C lcd(0x27, 20, 4);
#define sensorPin A5

long calibratedSkinCapacity = 0; // variable to store calibrated skin capacity without stress
long currentSkinCapacity = 0;
char array1[] = "Test1";  // CHANGE THIS AS PER YOUR NEED 
char array2[] = "Test2";     // CHANGE THIS AS PER YOUR NEED 
char array3[] = "Test3";   // CHANGE THIS AS PER YOUR NEED
char array4[] = "Test4";     // CHANGE THIS AS PER YOUR NEED

// get a average reading from sensordata over x amount op measurments
int GetAverageSensorValue(int measurmentCount)
{
  int sensorValue = 0;  // int to save sensorvalue
  long sumSensorValue = 0; // reset sum everytime function gets called
  
  for(int i=0;i<measurmentCount;i++) // peforme measurment a copple of time to get average
  {
    sensorValue = analogRead(sensorPin);  //Read the sensor value
    sumSensorValue += sensorValue; //sum all measured sensorValues
  }
  long averageSensorValue = sumSensorValue / measurmentCount; // Dived the sum of sensorValues by measurements to get average
  return averageSensorValue;
}


void CalibrateSkinCapacity()
{
  delay(1000);
  Serial.println("Calibrating skin capacity...");
  calibratedSkinCapacity = GetAverageSensorValue(100); //Perform a skin capacity calibration by getting average skin capacity over 100 measurments
  Serial.print("Skin capacity calibrated at: ");
  Serial.println(calibratedSkinCapacity);
  delay(500);
}


void setup() 
{
  lcd.init();                  // initialiseer het LCD scherm
  lcd.backlight();             // zet de backlight aan
  Serial.begin(9600);
  delay(500);
  CalibrateSkinCapacity();
}


void loop() 
{
  currentSkinCapacity = GetAverageSensorValue(50);  // get de a average of the current sensorvalue
  int difference = calibratedSkinCapacity - currentSkinCapacity;  // calculate the difference between clabratedValue and current to detect transpiration
  int diffPerc = map(difference,0,calibratedSkinCapacity,0,100); // Transfere diff into percantage
  //lcd.clear();
  // when sensor doesnt make good contact with skin give ERROR otherwise continue
  if(difference < 0)
  {
    screenError(); //print Error op lcd.
  }
  else
  {
    //Serial.print("Skin Capacity= ");
    //Serial.println(currentSkinCapacity);  //print sensor value
    //Serial.print(",");
    //Serial.print("Diff= ");
    //Serial.print(difference); // print differnece between calc en current value
    //Serial.print(",");
    //Serial.print("diffPerc= ");
    //Serial.print(diffPerc);
    //Serial.println("%");
    screenCapa();
  }
}

void screenCapa()
{
  lcd.setCursor(0,0);
  lcd.print("Skin Capacity:      ");                // BY DEFAULT CURSOR IS SET AT 0,0 ie, 0th ROW AND 0th COLUMN
  lcd.setCursor(0,1);
  lcd.print(currentSkinCapacity);
}


void screenGSR() 
{               
  lcd.setCursor(3, 1);         // zet de cursor op positie 1, regel 2
  lcd.write(1);                // teken symbool uit geheugen positie 1
  lcd.setCursor(9, 1);         // zet de cursor op positie 1, regel 2
  lcd.write(1);                // teken symbool uit geheugen positie 2
  lcd.setCursor(15, 1);         // zet de cursor op positie 1, regel 2
  lcd.write(1);                // teken symbool uit geheugen positie 3
  lcd.setCursor(1, 3);         // zet de cursor op positie 2, regel 3
}

void screenError() 
{               
  lcd.setCursor(0,4);
  lcd.print("        ERROR                               ");
}

void screen4() 
{               
  lcd.setCursor(6,1);
  lcd.print("Scherm 4");
}

void screen5() 
{               
  lcd.setCursor(6,2);
  lcd.print("Scherm 5");
}

void screen6() 
{               
  lcd.setCursor(6,3);
  lcd.print("Scherm 6");
}

void screen7() 
{               
  lcd.setCursor(0,0);
  lcd.print("");
}
