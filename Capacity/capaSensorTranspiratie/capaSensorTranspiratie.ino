/**********************************************************
	File:   TranspiratieVerschil.cpp
	Project:   Capacitive Sensor
	
	Copyright: (c) 2024 Patrick Schuurman
	
	Auteur:    Patrick Schuurman
	Datum:     30 mei 2024
**********************************************************/

#define sensorPin A5

long calibratedSkinCapacity = 0; // variable to store calibrated skin capacity without stress

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
  Serial.begin(9600);
  delay(500);
  CalibrateSkinCapacity();
}


void loop()
{
  int currentSkinCapacity = GetAverageSensorValue(50);  // get de a average of the current sensorvalue
  int difference = calibratedSkinCapacity - currentSkinCapacity;  // calculate the difference between clabratedValue and current to detect transpiration
  int diffPerc = map(difference,0,calibratedSkinCapacity,0,100); // Transfere diff into percantage

  // when sensor doesnt make good contact with skin give ERROR otherwise continue
  if(difference < 0)
  {
    //Serial.println("Sensor ERROR, Please be sure sensor makes contact"); // sensor doesnt make good contact
  }
  else
  {
    Serial.print("Skin Capacity= ");
    Serial.println(currentSkinCapacity);  //print sensor value
    //Serial.print(",");
    //Serial.print("Diff= ");
    //Serial.print(difference); // print differnece between calc en current value
    //Serial.print(",");
    //Serial.print("diffPerc= ");
    //Serial.print(diffPerc);
    //Serial.println("%");
  }

  delay(500); //Wait half a second before next reading
}