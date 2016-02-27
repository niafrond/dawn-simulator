int red = 9;           
int green = 10;
int blue = 11;

int outsideBrightness = A5;


int blueSat = 0;//BlueSaturation
int redSat = 0;//RedSaturation
int greenSat = 0;//GreenSaturation

bool tokenStop=0; //Stop light change
int storedBrightness;
const int threshold = 3;
int mode = 2; //0 = eteint;1 = nightLight,2=nightLight+Lumino
int sunRiseFrequency = 360000;//3 minutes
// the setup routine runs once when you press reset:
void setup() {
  
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(green, OUTPUT);

  Serial.begin(9600);

          rgb(1,1,1);
         delay(250);
}

void loop() {
  mode=2;
  //While outside light isn(t changing,we put the night light
  while(readLuminosity()<threshold*10){
    
     
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

    rgb(0,2,1);
    delay(60000);
}
//We up only if outside if up-ing too
int upLight(int value,int factor){

 int brightness=readLuminosity();
  if(readLuminosity()<=threshold*10){
    //Night is falling or false punctual light
    storedBrightness=brightness;
    mode=1;
    return 0;
  }
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
  Serial.println(tokenStop);
  if(value>255){
    //More than 255, make it to 0
    value=255;
  }
 
  
  return value;
}

void simulatedDawn(){

  //brightness = 5;//debug
  
   greenSat=0;
  redSat=0;
  blueSat=0;
   //Simulated Dawn Warning
    rgb(0,0,1);
    delay(500);
    rgb(0,0,0);
    delay(500);
    rgb(0,0,1);
    delay(500);
  rgb(1,1,0);
  if(mode!=2){
             return;
          }
           while(greenSat<30){
                if(mode!=2){
                   return;
                }
                greenSat=upLight(greenSat,1);
    
              redSat=upLight(redSat,2);
              rgb();
              delay(sunRiseFrequency*4);//First rising will be really slow
           }
  while(greenSat<170){
          if(mode!=2){
             return;
          }

          greenSat=upLight(greenSat,1);

          redSat=upLight(redSat,2);
          rgb();
          delay(sunRiseFrequency);//No needs to be reactive, sun rising is slow
    }
        
    while(blueSat<202){
          if(mode!=2){
             return;
          }
          greenSat=upLight(greenSat,1);

         blueSat=upLight(blueSat,1);
          rgb();
       delay(sunRiseFrequency);//No needs to be reactive, sun rising is slow
    }

    while(blueSat<255){
          if(mode!=2){
             return;
          }
         blueSat=upLight(blueSat,1);
         redSat=upLight(redSat,1);
          rgb();
 delay(sunRiseFrequency);//No needs to be reactive, sun rising is slow
      
    }
    while(redSat<255){
         if(mode!=2){
            return;
          }
         redSat=upLight(redSat,1);
          rgb();
           delay(sunRiseFrequency);//No needs to be reactive, sun rising is slow
    }
    while(greenSat<255){
         if(mode!=2){
            return;
          }
         greenSat=upLight(greenSat,1);
          rgb();
           delay(sunRiseFrequency);//No needs to be reactive, sun rising is slow
      
    }
    while(mode==2){
      rgb(255,255,255);
       delay(sunRiseFrequency);//No needs to be reactive, sun rising is slow
  }

}

int readLuminosity(){

  int light=analogRead(outsideBrightness);
 
  light=light/threshold; //1024 becomes 255
  
  Serial.println(light*threshold);
  Serial.println(light);
  

  return light;
}
//yellow tip
//  rgb(238,245,37);//more orange => green to 116; lighter => blue to 220
//

