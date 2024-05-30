#define sensorPin A0

int sensorValue = 0;  // int to save sensorvalue
int wetValue = 212; // int to calibrate wet state
int dryValue = 457; // int to calibrate dry state 
int humidity = 0; // int to save humidity calculations


void setup()
{ 
  Serial.begin(9600);
  delay(500);
  Serial.println("Reading sensorvalues");
  //dryValue = analogRead(sensorPin); //Kalibrate sensor in air as dry.
}


void loop()
{
  sensorValue = analogRead(sensorPin);  //Read the sensor value
  humidity = map(sensorValue, wetValue, dryValue, 100, 0);  //map de sensor value as a percentage of full wet and full dry
  Serial.print("SensorValue= ");
  Serial.print(sensorValue);  //print sensor value
  Serial.print(" | ");  //Space out the values
  Serial.print("Humidity= ");
  Serial.print(humidity); //print humidity
  Serial.println("%");
  delay(500); //Wait half a second before next reading
}