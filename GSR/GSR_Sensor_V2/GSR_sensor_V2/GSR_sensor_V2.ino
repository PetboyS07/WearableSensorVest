//GSR Grove sensor
const int GSR = A1;

int sensorValue = 0;
float gsr_average = 0;
int SerialCalibration = 0;
int HumanResistance = 0;
const int measurments = 100;
int difference;

int Sumcal(){      //Average the x measurements to remove the glitch
  int sumcal = 0;
  for(int i = 0; i < measurments; i++)
  {
  sensorValue = analogRead(GSR);
  sumcal += sensorValue;
  delay(5);
  }
  return sumcal / measurments;
}

void setup()
{
  Serial.begin(9600);
  
  SerialCalibration = Sumcal();
  //Serial.print("SerialCalibration= ");
  //Serial.println(SerialCalibration);
}

void loop()
{
  gsr_average = Sumcal();
  difference = abs(SerialCalibration - gsr_average);
  //HumanResistance = ((1024 + 2 * gsr_average) * 10000) / difference;
  //1024 is 2^10, want tien byte output
  //2 maal gemiddelde output, ?
  // * 10000, want de geleiding op droge huid is heel groot
  // delen door het verschil met calibratie, 1/conductance is resistance
  
  //Serial.print("reading= ");
  //Serial.println(gsr_average);

  Serial.print("difference= ");
  Serial.println(difference);

  //Serial.print("HR= ");
  //Serial.println(HumanResistance);

}