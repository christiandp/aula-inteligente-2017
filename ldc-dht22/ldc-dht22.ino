#include <LiquidCrystal.h>
#include <DHT.h>

#define DHTTYPE DHT22


const int DHTPin = 7;     // what digital pin we're connected to

//Variables de Uso
bool ini = true;

DHT dht(DHTPin, DHTTYPE);
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  //Serial.begin(9600);
  lcd.begin(16, 2);
  dht.begin();
}

void loop() {

   if(ini){
    lcd.setCursor(1, 0);
    lcd.print("Bienvenidos al");   
    lcd.setCursor(0, 1);
    lcd.print("Aula Inteligente");
    delay(3000);
    lcd.clear();
    ini = false;
   }
  
   // Wait a few seconds between measurements.  
   //delay(2000);
   
   // Reading temperature or humidity takes about 250 milliseconds!
   float h = dht.readHumidity();
   float t = dht.readTemperature();
   
  //Print Temp
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print(" C");
  //Print Humedad
  lcd.setCursor(0,1);
  lcd.print("Humedad: ");
  lcd.print(h);
  lcd.print(" %");

  
   
}
