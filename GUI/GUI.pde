import controlP5.*;

ControlP5 cp5;

int PH = 100;
int temp = 100;
int rpm = 30;
float minPH = 0.0;
float maxPH = 12.0; 
int mintemp = 25;
int maxtemp = 80;
int minrpm = 0;
int maxrpm = 3700;
Slider abc;

void setup() {
  size(700,450);
  noStroke();
  textSize(32);
  cp5 = new ControlP5(this);
  
  cp5.addSlider("PH")
     .setPosition(100,50)
     .setSize(400,60)
     .setRange(minPH,maxPH)
     ;
  
  cp5.addSlider("temp")
     .setPosition(100,180)
     .setSize(400,60)
     .setRange(mintemp,maxtemp)
     ;
     
     
  cp5.addSlider("rpm")
     .setPosition(100,310)
     .setSize(400,60)
     .setRange(minrpm,maxrpm)
     ;
}

void draw() {
  background(0);
  
  if ( PH < 2)
  {
    fill(#c0392b);
  }
  else if ( PH < 5)
  {
    fill(#e67e22);
  }
  else if ( PH < 6)
  {
    fill(#f1c40f);
  }
  else if ( PH < 8)
  {
    fill(#2ecc71);
  }
  else if ( PH < 10)
  {
    fill(#3498db);
  }
  else if ( PH < 12)
  {
    fill(#9b59b6); 
  }
  else
  {
    fill(#8e44ad);
  }
  rect(0,0,width,150);
  fill(0);
  text("Current PH: "+ PH, 100, 140);

  
  
  fill(255,255-temp,0);
  rect(0,150,width,150);
  fill(0);
  //text("",x,y)
  text("Current Temp: "+ temp + "°", 100, 280);
  
  fill(0,255,255-rpm);
  rect(0,300,width,150);
  fill(0);
  text("Current RPM: "+ rpm , 100, 420);

}