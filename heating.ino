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
 //    Temperature in Kelvin = 1 / {A + B[ln(R)] + C[ln(R)]^3}
 //    where A = 0.00124372, B = 0.000222748 and C = 760979e-8
 long Resistance;  double Temp;  // Dual-Purpose variable to save space.
 Resistance=4700.0*((1024.0/rawADC) - 1);  // Assuming a 10k Thermistor.  Calculation is actually: Resistance = (1024 /ADC -1) * BalanceResistor
// For a GND-Thermistor-PullUp--Varef circuit it would be Rtherm=Rpullup/(1024.0/ADC-1)
 Temp = logf(Resistance); // Saving the Log(resistance) so not to calculate it 4 times later. // "Temp" means "Temporary" on this line.
 Temp = 1 / (0.00124372 + (0.000222748 * Temp) + (0.0000000760979 * Temp * Temp * Temp));   // Now it means both "Temporary" and "Temperature"
// Serial.println(Temp);
 return Temp;
}
void loop() {

  Temp = gettemp();
  Temp = Temp - 273.15;  // Convert Kelvin to Celsius // Now it only means "Temperature"
  Serial.println(Temp);
  
  if (Temp < tempgoal){
    
    while (Temp <(tempgoal-1)){
    
   // tempdiff = tempgoal - Temp;
    
  //  timing = neededenergy/30*1000;
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

