/* 
Peron Peroff Useless Machine
Based on Bruno Munari
Roni Bandini, Buenos Aires, Argentina
Updated on December, 2023 
Parts: Servo motor, 3d printed arm, switch, dfplayer pro, speaker and wooden box
*/

#include "SoftwareSerial.h"
#include <Servo.h>
#include <DFRobot_DF1201S.h>

SoftwareSerial DF1201SSerial(2, 3); 
DFRobot_DF1201S DF1201S;

Servo servoMotor;
int switchPin=7;
int servoPin=6;

int myVolume=25;
int isPlaying=0;

int howManySeconds=6;

void setup(){
                
        delay(2000);
        Serial.begin(115200); 
        Serial.println("Peron Peroff started");    
        Serial.println("");    
        Serial.println("There is something unspeakably sinister about a machine that does nothing–absolutely nothing–except switch itself off. —Arthur C. Clarke")
        Serial.println("");   
          
        servoMotor.attach(servoPin);
        pinMode(switchPin, INPUT_PULLUP);         

        Serial.println("Init servo adjusting");
        servoMotor.write(10);
        
        #if (defined ESP32)
          DF1201SSerial.begin(115200, SERIAL_8N1, /*rx =*/D3, /*tx =*/D2);
        #else
          DF1201SSerial.begin(115200);
        #endif
      
        while (!DF1201S.begin(DF1201SSerial)) {
          Serial.println("DfPlayer init failed, check wire connection");
          delay(1000);         
          }
      
        DF1201S.enableAMP();        
        DF1201S.setPlayMode(DF1201S.SINGLE);
        DF1201S.setVol(myVolume);      
  
        delay(2000);                                                       
}


void loop(){ 

   
int butValue = digitalRead(switchPin);

  if (butValue==0){  
        
        Serial.println("Switch on");                                           

        Serial.println("Play peronist march");
        DF1201S.setVol(myVolume);
        DF1201S.playFileNum(1);
        DF1201S.start();       
                    
        // Wait x seconds
        delay(howManySeconds*1000);   
        howManySeconds=howManySeconds-2;

        if (howManySeconds==2){howManySeconds=1;}
        if (howManySeconds<1){howManySeconds=6;}
      
        Serial.println("Turn off");
        servoMotor.write(180);
        delay(1000);
        
        Serial.println("Return to the box");
        servoMotor.write(10);
        
        DF1201S.setVol(0);
        DF1201S.pause();

        delay(2000);
        
  }           
            

  delay(250);               
  
}
