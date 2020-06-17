/* Librerias Base del Proyecto */
#include <SPI.h> //optional
#include <SD.h>
#include <TMRpcm.h>
#include <DHT.h>
#include <Wire.h>  
#include <LiquidCrystal_I2C.h>


/* Defines */
#define DHTTYPE DHT22

/* INPUTS */
const int DHT_PIN = 6;
const int PIR = 7;
const int MAGNETICO = 8;
/* OUTPUTS */
const int LUCES = 2;
const int AIRE_OFF = 3;
const int AIRE_ON = 4;
const int SPEAKER = 9;
const int CS_PIN = 10;

/* Objetos de Librerías */
LiquidCrystal_I2C lcd(0x27, 16,2);  // Set the LCD I2C address
DHT dht(DHT_PIN, DHTTYPE);
TMRpcm aud;

//Variables de Uso Global
bool ini = true;
bool start = true;
int pirState = LOW;           // de inicio no hay movimiento
int val = 0;                  // estado del pin

bool luces_state = false;
bool aire_state = false;
bool bienvenida_state = false;
int ctdPIR = 0;

void setup() {
// ------- Comunicaciones -------------
  Serial.begin(9600);
// ------- Inputs -------------
  pinMode(DHT_PIN,INPUT); // DHT22
  pinMode(PIR,INPUT); // PIR
  pinMode(MAGNETICO,INPUT); // Magnético
// ------- Outputs -------------
  pinMode(LUCES,OUTPUT); // Luces
  pinMode(AIRE_OFF,OUTPUT); // Aire Off
  pinMode(AIRE_ON,OUTPUT); // Aire On
  pinMode(SPEAKER,OUTPUT); // Speaker
  pinMode(CS_PIN,OUTPUT); // CS
// ------- Init States ---------
  digitalWrite(LUCES,OUTPUT); // Luces
  digitalWrite(AIRE_OFF,OUTPUT); // Aire Off
  digitalWrite(AIRE_ON,OUTPUT); // Aire On
// ------- DHT Init -------------
  dht.begin();
// ------- LCD Init -------------
  lcd.init();
  lcd.begin(16,2);
// ------- SD init --------------
  if(!SD.begin(CS_PIN)) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Insertar SD Card");
    lcd.setCursor(0, 1);
    lcd.print("Y Reiniciar");
    delay(3000);
    start = false;
  }
  //aud.setVolume(7);
  //bienvenida();
}

void loop() {
  if(start){
    initialize();
    readDHT22();

    if(!luces_state){
      apagarLuces();
    }

    if(!readMagnetico()){ //si puerta Abierta
        encenderLuces();
        
        if(!bienvenida_state){
          bienvenida();
          bienvenida_state = true;
        }
        
        if(!aire_state){
          encenderAire();
        }
        
    }else{
      
      //apagarLuces();
      if(luces_state){
        encenderLuces();
      }
      
      readPIR();
      //apagarLuces();
      
    }

    /*encenderAire();
    apagarAire();*/

    //readPIR();
    
    
  }
  delay(800);

}

void initialize(){
  if(ini){
    aud.volume(7);
    lcd.setCursor(0, 0);
    lcd.print("Inicializando...");
    lcd.backlight();
    delay(1000); //tiempo en que se muestra inicio
    lcd.noBacklight();
    lcd.clear();
    ini = false;
  }
}

/* ================= Funciones de Lectura de Datos ============= */
void readDHT22(){
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

bool readMagnetico(){
  if(digitalRead(MAGNETICO) == LOW){
    return false;
  }else{
    return true;
  }
}

void readPIR(){
   val = digitalRead(PIR);
   if (val == HIGH)   //si está activado
   { 
     encenderLuces();
     ctdPIR = 0;
     /*if (pirState == LOW)  //si previamente estaba apagado
     {
       Serial.println("Sensor parado");
       delay(1500);
       pirState = HIGH;
     }*/
     //Serial.println("Sensor parado");
     delay(1500);
   } 
   else   //si esta desactivado
   {
     
     ctdPIR++;
     
     if(ctdPIR > 5){
       if(luces_state){
        apagarLuces();
       }
       if(aire_state){
        apagarAire();
       }
     }
     delay(1000);
     /*if (pirState == HIGH)  //si previamente estaba encendido
     {
       Serial.println("Sensor activado");
       delay(1500);
       pirState = LOW;
     }*/
     Serial.println("Sensor parado");
     delay(1500);
   }
}

/* ============== Funciones de Acción ============== */
void encenderLuces(){
  digitalWrite(LUCES, LOW);
  delay(500);
  luces_state = true;
  //Serial.println("Luces Encendidas");
}

void apagarLuces(){
  digitalWrite(LUCES, HIGH);
  delay(500);
  luces_state = false;
  //Serial.println("Luces apagadas");
}

void encenderAire(){
  digitalWrite(AIRE_ON, HIGH);
  digitalWrite(AIRE_OFF, LOW);
  delay(1000);
  digitalWrite(AIRE_ON, LOW);
  digitalWrite(AIRE_OFF, LOW);
  delay(1000);
  aud.play("aireon.wav");
  delay(5000);
  aire_state = true;
}

void apagarAire(){
  digitalWrite(AIRE_ON, LOW);
  digitalWrite(AIRE_OFF, HIGH);
  delay(1500);
  digitalWrite(AIRE_ON, LOW);
  digitalWrite(AIRE_OFF, LOW);
  delay(1000);
  aud.play("aireoff.wav");
  delay(5000);
  aire_state = false;
}

void bienvenida(){
  aud.play("wel.wav");
  delay(3000);
}

void bienvenidoIng(){
  aud.play("weling.wav");
  delay(5000);
}

