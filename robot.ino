// James C
// 2024-01-25
// Description: A self driving car that takes data like the temperature as it drives around and send it using bluetooth to the laptop, which usese python to anaylize the Data


#include <Servo.h>
#include "DHT.h"

#https://www.instructables.com/Arduino-Reading-Sensor-Data-Using-Bluetooth/#discuss
#https://www.circuitbasics.com/how-to-set-up-the-dht11-humidity-sensor-on-an-arduino/
#https://tutoduino.fr/en/beginners-corner/temperature-sensor/


Servo frservo;
Servo flservo;
Servo brservo;
Servo blservo;

#define DHTPIN 2

#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);


int trig = 4;
int echo = 3;

int pos = 0;

void setup() {
  Serial.begin(9600);
  analogReference(DEFAULT);
  frservo.attach(9);
  flservo.attach(6);
  brservo.attach(10);
  blservo.attach(11);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  dht.begin();
}

void loop()
{
  int dist = get_distance();
  if(dist < 5)
  {
    while(dist < 5){
        Serial.println("turn");
    	  brservo.write(180);
      	frservo.write(180);
      	blservo.write(0);
      	flservo.write(0);
        dist = get_distance();
    }
    
  }
  else{
  	brservo.write(0);
    blservo.write(180);
    flservo.write(0);
    frservo.write(180);
  }
  
  Serial.flush();
  Serial.println("Temperature:" + String(dht.readTemperature()) );
  Serial.println("Humidite: " + String(dht.readHumidity()));

}

int get_distance()
{
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  
  long time = pulseIn(echo,HIGH);
  int distance = (time*0.034)/2;
  return distance;
  
}
