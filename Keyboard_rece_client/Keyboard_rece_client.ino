//robot side
//2.receiving part
#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>

int motorpinb1 = 4;
int motorpinb2 = 5;
int motorpinf1 = 2;
int motorpinf2 = 3;
int solenoidpin = 9;
int kickpin = 6;
void setup(){
   pinMode(motorpinb1,OUTPUT);
   pinMode(motorpinb2,OUTPUT);
   pinMode(motorpinf1,OUTPUT);
   pinMode(motorpinf2,OUTPUT);
   pinMode(kickpin,OUTPUT);
   
   digitalWrite(motorpinb1,LOW);
   digitalWrite(motorpinb2,LOW);
   digitalWrite(motorpinf1,LOW);
   digitalWrite(motorpinf2,LOW);
   digitalWrite(kickpin,LOW);
   
   pinMode(solenoidpin ,OUTPUT);
   analogWrite(solenoidpin , 125);
  Serial.begin(9600);
 
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setRADDR((byte *)"serv1"); 
  Mirf.payload = sizeof(unsigned long); 
  Mirf.config();
}

void loop(){
  byte data[Mirf.payload];   
  if(!Mirf.isSending() && Mirf.dataReady()){
    Serial.println("Got packet");
    Mirf.getData(data);
   // char a = Mirf.getData(data);
   Serial.print("First value:");
    Serial.println(byte (data[0]));
  }
  
  if(data[0] <= 58)
  {
  move_right();
  Serial.println("MOVE RIGHT");
  }
  if(data[0] >= 78)
  {
    if(data[0] <= 124){
      move_left();
  Serial.println("MOVE LEFT");
    }
  }

  
 //delay(300);   

  
  //  byte data[Mirf.payload];   

  if(data[0] >= 182)
  {
    if(data[0] <= 254)
    {
    move_forward();
  Serial.println("MOVE FORWARD");
    }
  }
  if(data[0] <= 168)
  {
    if(data[0] >= 140)
    {
      move_back();
  Serial.println("MOVE BACK");
    }
  }
  if(data[0] > 168)
  {
    if(data[0] < 182)
    {
    //stop forward back but move right
    
   Serial.println("stop F & B");
   
    }
  }
// STOP THE CAR


  
   // delay(300);
  

    if(data[0] == 255)
    {
     kick_ball();
    Serial.println("KICK THE BALL");
    digitalWrite(kickpin , HIGH);
    delay(100);
    }
    else
    {
     digitalWrite(kickpin , LOW);
    }
  //  delay(300);

  delay(50);
}
void kick_ball()
{

}
void move_left()
{
   digitalWrite(motorpinb1,LOW);
   digitalWrite(motorpinb2,LOW);
   digitalWrite(motorpinf1,HIGH);
   digitalWrite(motorpinf2,LOW);
}
void move_right()
{
   digitalWrite(motorpinb1,HIGH);
   digitalWrite(motorpinb2,LOW);
   digitalWrite(motorpinf1,LOW);
   digitalWrite(motorpinf2,LOW);
}

void move_forward()
{
   digitalWrite(motorpinb1, HIGH);
   digitalWrite(motorpinb2,LOW);
   digitalWrite(motorpinf1,HIGH);
   digitalWrite(motorpinf2,LOW);
}
void move_back()
{
   digitalWrite(motorpinb1,LOW);
   digitalWrite(motorpinb2,HIGH);
   digitalWrite(motorpinf1,LOW);
   digitalWrite(motorpinf2,HIGH);
}

