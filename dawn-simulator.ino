int red = 9;           
int green = 10;
int blue = 11;
int outsideBrightness = A5;
int lampSwitch = 2;
int offLed = 7;

int blueSat = 0;
int redSat = 0;
int greenSat = 0;

bool tokenStop=0;
int storedBrightness;
int mode = 1; //0 = eteint;1 = Veilleuse,lumino
// the setup routine runs once when you press reset:
void setup() {
  // declare pin 9 to be an output:
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(lampSwitch,INPUT);
  pinMode(offLed,OUTPUT);
  Serial.begin(9600);
           
         //test Rouge
        rgb(30,0,0);
          delay(250);
         //test green
          rgb(0,30,0);
         delay(250);
        //test blue
         rgb(0,0,30);
         delay(250);
         rgb(0,0,0);
          rgb(30,30,30);
         delay(250);
  attachInterrupt(digitalPinToInterrupt(lampSwitch), switchMode, CHANGE);
}

void loop() {

  simulatedDawn();
  while(mode!=0){
    rgb(255,255,255);
  }
  off();

}

void switchMode(){
  mode++;
  if(mode==2){
      mode=0;
  }
  Serial.println("mode");
  Serial.println(mode);
  delay(500);
  

}

void off(){
  while(mode==0){
    digitalWrite(offLed,HIGH);
    rgb(0,0,0);
  }
  digitalWrite(offLed,LOW);  
  
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
void veilleuse(){
    rgb(40,20,40);
}

int upLight(int value,int factor){

  
  if(mode==0){
     return 0;
  }
 int brightness=analogRead(outsideBrightness);
  if(storedBrightness<=brightness){
    storedBrightness=brightness;
    tokenStop=0;
  }
  Serial.println(brightness);
  if(value<(brightness * factor) && !tokenStop){
    value=value+factor;
  }else{
    tokenStop=1;//Plus aucune valeur n'augmente
  }
  if(value>255){

    value=255;
  }
  delay(170);
  return value;
}

int simulatedDawn(){
  greenSat=0;
  redSat=0;
  blueSat=0;
  int brightness = analogRead(outsideBrightness);
  //brightness = 5;//debug
  while(brightness<10){
      if(mode==0){
          return 0;
      }
      veilleuse();
  }
  while(greenSat<170){

          if(mode==0){
            return 0;
          }
          greenSat=upLight(greenSat,1);

          redSat=upLight(redSat,2);
          rgb();
         // delay(100);
    }
        
    while(blueSat<202){
          if(mode==0){
            return 0;
          }
          greenSat=upLight(greenSat,1);

         blueSat=upLight(blueSat,1);
          rgb();
      
    }

    while(blueSat<255){
          if(mode==0){
            return 0;
          }
         blueSat=upLight(blueSat,1);
         redSat=upLight(redSat,1);
          rgb();

      
    }
    while(redSat<255){
         if(mode==0){
            return 0;
          }
         redSat=upLight(redSat,1);
          rgb();
    }
    while(greenSat<255){
         if(mode==0){
            return 0;
          }
         greenSat=upLight(greenSat,1);
          rgb();
      
    }

}
//void jaune(){
//  rgb(238,245,37);//plus orange => green a 116; plus clair => bleu => 220
//}

