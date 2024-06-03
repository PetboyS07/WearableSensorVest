/**********************************************************
	File:   TranspiratieVerschil.cpp
	Project:   Capacitive Sensor
	
	Copyright: (c) 2024 Patrick Schuurman
	
	Auteur:    Patrick Schuurman
	Datum:     30 mei 2024
**********************************************************/

#define sensorPin A0

int sensorValue = 0;  // int to save sensorvalue
int calibrateValue = 473; // int to calibrate dry state 
int wetValue = 212; // int to calibrate wet state
int humidity = 0; // int to save humidity calculations
int calibratedSkinCapacity = 0; // variable to store calibrated skin capacity without stress


int GetAverageSensorValue(int measurmentCount)
{
  //int measurmentCount = 100;
  for(int i=0;i<measurmentCount;i++) // peforme measurment a copple of time to get average
  {
    sensorValue = analogRead(sensorPin);  //Read the sensor value
    int sumSensorValue += sensorValue; //sum all measured sensorValues
  }
  averageSensorValue = sumSensorValue / measurmentCount; // Dived the sum of sensorValues by measurements to get average
  return averageSensorValue;
}


void setup()
{ 
  Serial.begin(9600);
  delay(500);
  Serial.println("Reading sensorvalues");
  calibratedSkinCapacity = GetAverageSensorValue(100); //Perform a skin capacity calibration by getting average skin capacity over 100 measurments
}


void loop()
{
  averagesensorValue = analogRead(sensorPin);  //Read the sensor value
  humidity = map(sensorValue, wetValue, dryValue, 100, 0);  //map de sensor value as a percentage of full wet and full dry
  Serial.print("SensorValue= ");
  Serial.print(sensorValue);  //print sensor value
  Serial.print(" | ");  //Space out the values
  Serial.print("Humidity= ");
  Serial.print(humidity); //print humidity
  Serial.println("%");
  delay(500); //Wait half a second before next reading
}