/* SudoWiz bathroom unlocker

Created by ...
at Startup Weekend, Castlemont High, 2015
*/ 

#include <Servo.h> 
#include "sha1.h"
#include "pitches.h"
 
int melody[] = {
  NOTE_C4, NOTE_G3
};

int noteDurations[] = {
  4, 2,
};

Servo myservo;  // create servo object to control a servo 

//initialize Sha1
uint8_t *hash;
//Sha1.init();

int codes[] = {1999, 7649, 7680, 2085, 1103,
6305, 5324, 9947, 9517, 3595, 7475, 3432, 8251,
5144, 1571, 6224, 4018, 4539, 9829, 5426};
int codesSize = 20;
int i=0;

//led pins
int redPin = 4;
int greenPin = 5;
int bluePin = 6;

#define COMMON_ANODE

void setup() 
{ 
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
  Serial.begin(9600); 
  myservo.write(0);
  
  //led setup
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT); 
  
  setColor(255, 0, 0);  // red
}

 
void loop() 
{     
  if (Serial.available() > 0) {
     int code = Serial.parseInt();
     
     Serial.println("Current entered code: ");
     Serial.println(code);
    
    //search the list of codes for the code entered
    for (int i = 0; i < codesSize; i++) {
      if (code == codes[i]) {
        //Serial.print(i);
        
        //TURN THE LOCK
        myservo.write(90);
        
        //set the light to green
        setColor(0,255,0);
        
        //PLAY A TONE
        tone(8,NOTE_C4,1000);
       
        //lock the door after unlocking
        delay(5000);
        myservo.write(0);
        setColor(255, 0, 0);  // red
        
        codes[i] = codes[codesSize-1];
        codesSize--;
        return;
      }
    }  
    
    Serial.println("got here");
    myservo.write(0);
    tone(8,NOTE_G3,500);

    setColor(255, 0, 0);  // red
    delay(500);
    setColor(0,0,0);
    delay(500);
    setColor(255, 0, 0); 
  }
}

void setColor(int red, int green, int blue)
{
  #ifdef COMMON_ANODE
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  #endif
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);  
}

void createCodes ()
{
  //Sha1.print("stuff");
}


