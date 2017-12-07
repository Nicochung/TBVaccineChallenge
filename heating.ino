#include <math.h> 

const int Thermistor = P1_3;
const int Transistor = P1_4;
float rawADC, rawVoltage, rawPD;
float Temp, neededenergy, tempgoal, tempdiff, timing;


void setup() {
  Serial.begin(9600);
  pinMode(Thermistor, INPUT);
  pinMode(Transistor, OUTPUT);
//  analogReference(INTERNAL1V5);
  tempgoal = 30.0;
}

double gettemp(){

  rawADC = analogRead(Thermistor);
  Serial.println(rawADC);
 long Resistance;  double Temp; 
 Resistance=4700.0*((1024.0/rawADC) - 1);  
 Temp = logf(Resistance); 
 Temp = 1 / (0.00124372 + (0.000222748 * Temp) + (0.0000000760979 * Temp * Temp * Temp)); 
 return Temp;
}
void loop() {

  Temp = gettemp();
  Temp = Temp - 273.15;  // Convert Kelvin to Celsius
  Serial.println(Temp);
  
  if (Temp < tempgoal){
    
    while (Temp <(tempgoal-1)){
      
    digitalWrite(Transistor, HIGH);
    Serial.println(digitalRead(Transistor));
    delay(10000);
    Serial.println("I am working!!!");
    digitalWrite(Transistor, LOW);
    Serial.println(digitalRead(Transistor));
    Temp = gettemp();
    Serial.println(Temp);
    
    } 
  }
  else if (Temp >= tempgoal){
    digitalWrite(Transistor, LOW);
    Serial.println("Suitable Temp");
    delay(1000); 
  }
    
}

