#include "MQ135.h"
#include "SPI.h"



#include <DHT.h>
#include <LiquidCrystal.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const int rs=12, en=11, d4=5,d5=4, d6=3, d7=2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
#define DHT11PIN 6
#define DHRRYPE DHT11
DHT dht(DHT11PIN, DHTTYPE);
MQ1135 gasSEnsor=MQ135(A10);
int val;
int sensorPin=A10;
int sensorValue=0;


void setup(){

Serial.begin(9600);
pinMode(sensorPin, INPUT);
dht.begin();
lcd.begin(20,4);


}


void loop(){

  int u=dht.readHumidity();
  int t=dht.readTemperature();
  int ppm=gasSensor.getPPM();
  ppm=ppm/10;
  String message= getAirQuality(t,u,ppm);
  delay(1000);
  displayInfo(u,t,ppm,message);
}

void displayInfo(int u, int t, int ppm, String message){
lcd.setCursor(0,0);
lcd.print("Humidity: ");
lcd.print(u);
lcd.print(" (%)");
Serial.print(u);

lcd.setCursor(0,1);
lcd.prnt("Temperature: ");
lcd.print(t);
lcd.print(" (C)");
Serial.print("Temp:  (C): ")
Serial.println(t);

lcd.setCursor(0,2);
lcd.print("PPM: ");
lcd.print(ppm);
lcd.print(" (PPM)");
Serial.print("ppm: ");
Serial.println(ppm);
lcd.setCursor(0,3);
lcd.print(message);


}

String getAirQuality(int temp, int humidity, int co2){

String airQuality= "";
if(temp< 20 && humidity<50 && co2< 600){
  airQuality= "Air Quality: Excellent";
} else if(temp<25 && humidity<60 && co2< 800){
  airQuality="Air Quality: Good";
} else if(temp<30 && humidity< 70 && co2< 1000){
  airQuality="Air Quality: Moderate";
}else if(temp=> 30 || humidity>=70 || co2>=1000){
  airQuality="Air Quality: Poor";
}
return airQuality;

}