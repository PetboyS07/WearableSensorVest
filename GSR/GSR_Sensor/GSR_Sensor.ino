/**********************************************************
	File:   GSR_Sensor.cpp
	Project:   Capacitive Sensor
	
	Copyright: (c) 2024 Patrick Schuurman
	
	Auteur:    Patrick Schuurman
	Datum:     30 mei 2024
**********************************************************/
const int GSR=A0;

int sensorValue=0;
float gsr_average=0;
int SerialCalibration = 0;
int HumanResistance = 0;
const int measurments = 10;
long sumcal=0;
int difference;

void setup()
{
  Serial.begin(9600);
  for(int i=0;i<500;i++)
  {
  sensorValue=analogRead(GSR);
  sumcal += sensorValue;
  delay(5);
  }
  SerialCalibration = sumcal/500;
  Serial.print("SerialCalibration =");
  Serial.println(SerialCalibration);
}

void loop()
{
  long sum=0;
  for(int i=0;i<measurments;i++) //Average the 10 measurements to remove the glitch
  {
    sensorValue = analogRead(GSR);
    //Serial.print("SV: "); 
    //Serial.println(sensorValue);
    sum += sensorValue;
    //Serial.print("SUM: "); Serial.println(sum);
    delay(5);
  }
  gsr_average = sum/10;
  difference = abs(SerialCalibration - gsr_average);
  HumanResistance = ((1024 + 2 * gsr_average) * 10000)/difference;
  Serial.print("reading: ")
  Serial.println(gsr_average);
  Serial.print("HR: ")
  Serial.println(HumanResistance);
}
