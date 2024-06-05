//GSR Grove sensor
//Sensor zit op de huid voor de kalabratie, voordat het systeem wordt gestart.
const int GSR = A1;

int sensorValue = 0;
float gsr_average = 0;
int SerialCalibration = 0;
int HumanResistance = 0;
const int measurments = 100;
int difference;
int sumcal = 0;

int Sumcal(){      //Average the x measurements to remove the glitch
  int sumcal = 0;
  for(int i = 0; i < measurments; i++)
  {
  sensorValue = analogRead(GSR);
  sumcal += sensorValue;
  delay(5);
  }
  return abs(sumcal / measurments);
}

void setup()
{
  Serial.begin(9600);
  
  SerialCalibration = Sumcal();             //bepaal waarde van de droge huid
  //Serial.print("SerialCalibration= ");
  //Serial.println(SerialCalibration);
}

void loop()
{
  gsr_average = Sumcal();
  difference = abs(SerialCalibration - gsr_average);    //groot verschil;, veel zweet
  HumanResistance = map(difference, 0, SerialCalibration, 0, 100); //0 < HR < 100 procent

  //HumanResistance = (difference / SerialCalibration) * 100; //0 < HR < 100 procent
  //HumanResistance = ((1024 + 2 * gsr_average) * 10000) / difference; //in ohm, maar zeer onnauwkeurig
  
  //Serial.print("Reading= ");
  //Serial.println(sensorValue);
  //sensorValue = analogRead(GSR);

  //Serial.print("Difference= ");
  //Serial.println(difference);

  Serial.print("HR= ");
  Serial.println(HumanResistance);

}