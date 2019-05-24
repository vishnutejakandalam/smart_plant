#include "ESP8266WiFi.h"
#include <BlynkSimpleEsp8266.h>
#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel p(10,12);
const int trigPin = 0;
const int echoPin = 5;
long duration;
int i=0;
int distance;
BlynkTimer timer;
void setup()
{
pinMode(trigPin, OUTPUT); 
pinMode(echoPin, INPUT);
 Blynk.begin("4069a24a2e2a4a4a87ff34170d790fed","UTStarcom","9491802862");p.begin();
Serial.begin(115200);
pinMode(A0,INPUT);
timer.setInterval(12,hello);
}
void loop()
{
 Blynk.run();
timer.run();
}

void hello()
{
 p.setPixelColor(3,p.Color(50,50,50));
 p.setPixelColor(5,p.Color(50,50,50));
 int val=map(analogRead(A0),978,638,0,100);
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance= duration*0.034/2;
Serial.print("Distance: ");
Serial.println(distance);
if(distance >= 70)
{
 if(i==0)
{
 Blynk.notify("I MISS YOU");
 i=1;
} 
Serial.println("face on");
   for(uint16_t i=0;i<255;i=i+5)
  {
     p.setPixelColor(0,p.Color(i,i,i));
    p.setPixelColor(1,p.Color(i,i,i));
    p.setPixelColor(9,p.Color(i,i,i));
    p.setPixelColor(8,p.Color(i,i,i));
    p.setPixelColor(7,p.Color(i,i,i));
    p.show();
}
}
else 
{
 Serial.println("face off");
 for(uint16_t i=255;i>=0;i=i-15)
  {
    p.setPixelColor(0,p.Color(i,i,i));
    p.setPixelColor(1,p.Color(i,i,i));
    p.setPixelColor(9,p.Color(i,i,i));
    p.setPixelColor(8,p.Color(i,i,i));
    p.setPixelColor(7,p.Color(i,i,i));
    p.show();
}
 i=0;
 }
 if(val<=20)
{
 Blynk.notify("moisture too low");
}

}

