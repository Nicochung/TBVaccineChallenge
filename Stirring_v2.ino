
//motor related variables:
const int maxRPM = 3700; // motor document says 3700 is max for 4:1 gear ratio
int errorToleranceRPM = 80;
int desiredRPM = 800;
int motorPin = 10; //analogwrite pin
int motorPower = 0;   

//photodiode related variables:
int revolutionPhase = 0; //1 = first flash, 2 = first dim, 3 = second flash, 4 = second dim -> third flash = 1 rev and new cycle
int seconds = 5; // counter for keeping track of when a second elapses to reset rpm measurement
int inputPin = 6; // can do analogread and digitalread
int numberOfRevs = 0;
int measuredRPM = 0;

void setup()  { 
  Serial.begin(9600);
  pinMode(motorPin, OUTPUT);
  pinMode(inputPin, INPUT);
  motorPower = (desiredRPM / maxRPM) * 255; //initial estimate for speed - we assume desired RPM <= 3700
} 

int isBright(int pinID){ 
  int diodeInput = analogRead(pinID);

  if (diodeInput > 500){
    return 1;
  }
  else{
    return 0;
  }

  
}

void loop()  { 

  analogWrite(motorPin,motorPower); //always drive motor each loop iteration with PMW

  //After initial 5 seconds of getting motor to some speed using rough estimates:
  
  if (millis() >= 5000) {
    //determine RPM over the last second and make small change to motor power 
    //accordingly if RPM is not at the level we want


    //evaluate rpm from recent data and make decisions
      if (millis() > ((seconds+1)*1000)){ 
      
        measuredRPM = numberOfRevs * 60 * 1.975;
        Serial.println(measuredRPM);
        
        seconds++;
        numberOfRevs = 0; // reset
    
        int rpmDifference = desiredRPM - measuredRPM;
    
        //check if 
        if (rpmDifference > 0 && rpmDifference > errorToleranceRPM){
          //increase speed slightly
          if (motorPower < 255){
            motorPower++;
          }
        }
        else if (rpmDifference < 0 && abs(rpmDifference) > errorToleranceRPM){
          if (motorPower > 0){
            //decrease speed
            motorPower--;
          }
        }
        
        
      }
      //collect data
      else{
          if (revolutionPhase == 0 && isBright(inputPin) == 1){
            revolutionPhase++;
          }
          else if (revolutionPhase == 1 && isBright(inputPin) == 0){
            revolutionPhase++;
          }
          else if (revolutionPhase == 2 && isBright(inputPin) == 1){
            revolutionPhase++;
          }
          else if (revolutionPhase == 3 && isBright(inputPin) == 0){
            revolutionPhase++;
          }
          else if (revolutionPhase == 4 && isBright(inputPin) == 1){
            numberOfRevs++;
            revolutionPhase = 1;
          }
      }
    }
}


