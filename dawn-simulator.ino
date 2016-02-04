int red = 9;           
int green = 10;
int blue = 11;

int outsideBrightness = A5;
int lampSwitch = 2;

int blueSat = 0;//BlueSaturation
int redSat = 0;//RedSaturation
int greenSat = 0;//GreenSaturation

bool tokenStop=0; //Stop light change
int storedBrightness;
int mode = 2; //0 = eteint;1 = nightLight,2=nightLight+Lumino //Disabled : push button electro magnetic sensible make it unexploitable
// the setup routine runs once when you press reset:
void setup() {
  
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(offLed,OUTPUT);
  Serial.begin(9600);
           
         //test Rouge
        rgb(2,0,0);
          delay(250);
         //test green
          rgb(0,2,0);
         delay(250);
        //test blue
         rgb(0,0,2);
         delay(250);
         rgb(0,0,0);
          rgb(1,1,1);
         delay(250);
}

void loop() {

  //While outside light isn(t changing,we put the night light
  while(readLuminosity()<10){
     
      nightLight();
      
  }
  simulatedDawn();
  

}



void rgb(int r,int g,int b){
    
    analogWrite(red, r);
    analogWrite(green, g);
    analogWrite(blue, b);

}
void rgb(){
    
    analogWrite(red, redSat);
    analogWrite(green, greenSat);
    analogWrite(blue, blueSat);

}
void nightLight(){

    rgb(0,3,1);
    delay(100);
}
//We up only if outside if up-ing too
int upLight(int value,int factor){

 int brightness=readLuminosity();

  if(storedBrightness<=brightness){
    //If outside brightness is growing, light inside up
    storedBrightness=brightness;
    tokenStop=0;
  }
  if(value<(brightness * factor) && !tokenStop){
    //If outside brightness is growing, light inside up
    value=value+factor;
  }else{
    tokenStop=1;//No more light up
  }
  if(value>255){
    //More than 255, make it to 0
    value=255;
  }
  delay(170);//Eye perception
  return value;
}

int simulatedDawn(){

  //brightness = 5;//debug
  
   greenSat=0;
  redSat=0;
  blueSat=0;
   //Simulated Dawn Warning
    rgb(0,0,2);
    delay(1000);
    rgb(0,0,0);
    delay(1000);
    rgb(0,0,2);
    delay(1000);
  rgb(1,1,0);
  while(greenSat<170){


          greenSat=upLight(greenSat,1);

          redSat=upLight(redSat,2);
          rgb();
         // delay(100);
    }
        
    while(blueSat<202){
          if(mode!=2){
             return 0;
          }
          greenSat=upLight(greenSat,1);

         blueSat=upLight(blueSat,1);
          rgb();
      
    }

    while(blueSat<255){
          if(mode!=2){
             return 0;
          }
         blueSat=upLight(blueSat,1);
         redSat=upLight(redSat,1);
          rgb();

      
    }
    while(redSat<255){
         if(mode!=2){
            return 0;
          }
         redSat=upLight(redSat,1);
          rgb();
    }
    while(greenSat<255){
         if(mode!=2){
            return 0;
          }
         greenSat=upLight(greenSat,1);
          rgb();
      
    }
    while(mode==2){
      rgb(255,255,255);
  }

}

int readLuminosity(){

  int light=analogRead(outsideBrightness);
 
  light=light/3; //1024 becomes 255
  
  Serial.println(light*3);
  Serial.println(light);
  

  return light;
}
//yellow tip
//  rgb(238,245,37);//more orange => green to 116; lighter => blue to 220
//
