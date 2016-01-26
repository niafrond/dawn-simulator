int red = 9;           
int green = 10;
int blue = 11;
int blueSat = 0;
int redSat = 0;
int greenSat = 0;
int potentInput = A5;
int potentVoltage = 2;
bool tokenStop=0;
int storedBrightness;
int brightness = 250;    // how bright outside is
int fadeAmount = 5;    // how many points to fade the LED by

// the setup routine runs once when you press reset:
void setup() {
  // declare pin 9 to be an output:
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(green, OUTPUT);
  Serial.begin(9600);
            rgb(255,255,255);
         delay(500);
         //test Rouge
        rgb(255,0,0);
          delay(500);
         //test green
          rgb(0,255,0);
         delay(500);
        //test blue
         rgb(0,0,255);
         delay(500);
         rgb(0,0,0);
}

void loop() {

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

int upLight(int value,int factor){
  
  brightness=analogRead(potentInput);
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
  delay(100);
  return value;
}

void simulatedDawn(){
  greenSat=0;
  redSat=0;
  blueSat=0;
  while(greenSat<128){


          greenSat=upLight(greenSat,1);

          redSat=upLight(redSat,2);
          rgb();
         // delay(100);
    }
        
    while(blueSat<202){
          greenSat=upLight(greenSat,1);

         blueSat=upLight(blueSat,1);
          rgb();
      
    }

    while(blueSat<255){
      
         blueSat=upLight(blueSat,1);
         redSat=upLight(redSat,1);
          rgb();

      
    }
    while(redSat<255){
         
         redSat=upLight(redSat,1);
          rgb();
    }
    while(greenSat<255){
         greenSat=upLight(greenSat,1);
          rgb();
      
    }

}
//void jaune(){
//  rgb(238,245,37);//plus orange => green a 116; plus clair => bleu => 220
//}
