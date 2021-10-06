//joystick side
//1.sending part
#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>

//int ledPin = 13;   // select the pin for the LED
byte xval;
byte yval;
byte val = 0;

//byte time;
int xpin = A0;
int ypin = A1;
int kick = 3;

void setup(){
 // pinMode(ledPin,OUTPUT);    // declare the LED's pin as output
  Serial.begin(9600);  
    Mirf.csnPin = 9;
    Mirf.cePin = 10;
 
  
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setRADDR((byte *)"clie1");
  Mirf.payload = sizeof(unsigned long);
  Mirf.config();
 pinMode(xpin , INPUT);
 pinMode(ypin , INPUT);
 pinMode(kick , INPUT);
 pinMode(kick , LOW);

 
}
void loop(){
 /*
  if (Serial.available()){
    val = Serial.read();

  }*/
  xval = analogRead(xpin)/8.25; //data[0]
 delay(10); 
  yval = analogRead(ypin)/8.25 + 125; //data[1]
delay(10);
 // delay(300);

  Serial.println(xval);
  Serial.println();
  Serial.println(yval);
  
  //delay(300);
   // byte time;
 //   time = val;

    Mirf.setTADDR((byte *)"serv1");
    Mirf.send((byte *)&xval);  
    while(Mirf.isSending()){
    }

    Mirf.setTADDR((byte *)"serv1");
    Mirf.send((byte *)&yval);  
    while(Mirf.isSending()){
    }
    
    if(digitalRead(kick) == HIGH)
    {
      val = 255;  
    Mirf.setTADDR((byte *)"serv1");
    Mirf.send((byte *)&val);  
    while(Mirf.isSending()){
    }        
    }
    else
    {
    val = 0;
    }
  
}
