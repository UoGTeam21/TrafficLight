# TrafficLight
#include<iostream>
using namespace std;
int main()
  {
  int redEW=18; // pin 12
  int redSN=23; // pin 16
  int greenEW=25; // pin 22
  int greenSN=12; // pin 32
  int yellowEW=2; // pin 3
  int yellowSN=3; // pin 5
  int sider=5; // pin 29
  int sideg=6; // pin 31
  
  import RPi.GPIO as GPIO
  import time  
GPIO.setmode(GPIO.BCM)
GPIO.setup(18,GPIO.OUT)

  GPIO.output(18, GPIO.LOW); //initialize
  GPIO.output(23, GPIO.LOW);
  GPIO.output(25, GPIO.LOW);
  GPIO.output(12, GPIO.LOW);
  GPIO.output(2, GPIO.LOW);
  GPIO.output(3, GPIO.LOW);
  
  while (1)
  {
  int tr,tg,ty; //timing
  for (tr=5,tr>0,tr--)
  {
  GPIO.output(18, GPIO.HIGH);
  GPIO.output(23, GPIO.HIGH);
  GPIO.output(5, GPIO.HIGH); // all red
  }
  
  for(tgEW=10,tgEW>0,tgEW--)
  {
   GPIO.output(25, GPIO.HIGH);
  GPIO.output(23, GPIO.HIGH);
  GPIO.output(5, GPIO.HIGH); //EW green, else red
}
for(tyEW=3,tyEW>0,tyEW--)
 {
  GPIO.output(2, GPIO.HIGH);
  GPIO.output(23, GPIO.HIGH);
  GPIO.output(5, GPIO.HIGH); //EW yellow, else red
  }
    for(tgSN=10,tgSN>0,tgSN--)
  {
   GPIO.output(18, GPIO.HIGH);
  GPIO.output(12, GPIO.HIGH);
  GPIO.output(5, GPIO.HIGH); //SN green, else red
}
for(tySN=3,tySN>0,tySN--)
 {
  GPIO.output(18, GPIO.HIGH);
  GPIO.output(3, GPIO.HIGH);
  GPIO.output(5, GPIO.HIGH); //SN yellow, else red
  }
    for(tgside=10,tgEW>0,tgEW--)
  {
   GPIO.output(18, GPIO.HIGH);
  GPIO.output(23, GPIO.HIGH);
  GPIO.output(6, GPIO.HIGH); //side green, else red
}
}

while True:

GPIO.output(18, GPIO.HIGH)
sleep(1)
GPIO.output(18, GPIO.LOW)
sleep(1)
