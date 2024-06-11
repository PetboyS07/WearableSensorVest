//GSR Grove sensor
//Sensor sits on the skin for calabration, before starting the system.

const int GSR = A1;
const int measurments = 100;

int sensorValue = 0;
int gsr_average = 0;
int SerialCalibration = 0;
int HumanResistance = 0;

double scale = 0;
double sumcal = 0;

//int difference;
//float current_ADC = 0.0015;             //current through ADC in Ampere
//float voltage_ADC;                      // output sensor calculate back to voltage in volts //double?
//int offset = 0;                         //offset

int Sumcal(){                           //Average the x measurements to remove the glitch
  int sumcal = 0;
  for(int i = 0; i < measurments; i++)
  {
  sensorValue = analogRead(GSR);
  sumcal += sensorValue;
  delay(5);
  }
  return (sumcal / measurments);
}

void setup()
{
  Serial.begin(9600);
  
  SerialCalibration = Sumcal();         //determine once the mean value of dry skin
  //Serial.print("SerialCalibration= ");
  //Serial.println(SerialCalibration);
}

void loop()
{
  gsr_average = Sumcal();
  scale = map(gsr_average, 0, SerialCalibration, 0, 1023);          
  HumanResistance = abs((30000 * scale) / 1023);            //30 kOhm is max skin resistance
  //difference = abs(SerialCalibration - gsr_average);      //huge difference, lots of sweat

  //p 1023   pergentage
  //r 30000  HR?
  
  if(HumanResistance > 0)
  {
    Serial.print("HR = ");
    Serial.print(HumanResistance);
    Serial.println(" Ohm");
  }
  else{Serial.println("Wrong Reading");}

}

//voltage_ADC = map(gsr_average, 0, 1023, 0, ); //
  //HumanResistance = voltage_ADC / current_ADC + offset; //y = ax + b in Ohm. R = U/I + offset
  
  //HumanResistance = map(difference, 0, 1023, 0, 100);   //0 < HR < 100 procent
  //HumanResistance = (difference / SerialCalibration) * 100; //0 < HR < 100 procent
  //HumanResistance = ((1024 + 2 * gsr_average) / difference) * 10000;    //Pure nonsense!!! in ohms, but very inaccurate/unreliable
  
  
  //Serial.print("Reading= ");
  //Serial.println(gsr_average);

  //Serial.print("Difference= ");
  //Serial.println(difference);
