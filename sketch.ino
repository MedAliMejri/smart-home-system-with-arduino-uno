//configuration de capteur tem/numidité 
#define light A0
#include <DHT.h>
DHT dht(3, DHT22 );
//configuration de servau moteur 
#include <Servo.h>
Servo servwindow;
Servo servdoor;
//
#define echo 4
#define trig 5




void setup() {
  pinMode(echo, INPUT);
  pinMode(trig,OUTPUT);
  Serial.begin(9600);
  dht.begin();//activation de capteur dht
  servwindow.attach(9);//affectation servau au pwmpin exp:9
  servdoor.attach(6);//affectation servau au pwmpin exp:6
 


}

void loop() {
  
  float l=(1023-analogRead(light))*0.0977;//0.0977=100/1023
  float temp= dht.readTemperature();//readtemperature fonction predifinie dans bibleo pour capter la temp
  digitalWrite(trig, LOW);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  int t=pulseIn(echo,HIGH);//pulse in pour calculer le temps de l'echo em mode high(5v) en microseconde
  //c'est le temps de l'onde ultrasonique aller/retour de Transemetter à Receiver
  int distance=(t/2)*0.0343;//la vitesse de son est 343m/s convertit en 0.0343cm/µ
  
  //window is open :
  if((temp>30) && (l>30)){//si la temp>30 c° and la lumination >30%
    servwindow.write(180);//angle de rotation 180°
  }
  else{
    servwindow.write(0);//angle de rotation 0°
  }

  //door is open:
  if ((temp>30) && (distance<50)){
    servdoor.write(180);
    delay(5000);
    servdoor.write(0);
  }
  else{
    servdoor.write(0);
  } 
  Serial.print("la temperature est:");
  Serial.print(temp);
  Serial.print(" C°");
  delay(400);
  
  Serial.print("     la lumination est:");
  Serial.print(l);
  Serial.print("%");
  delay(400);

  Serial.print("   la distance: ");
  Serial.print( distance);
  Serial.println("cm");
  delay(400);



}
