const int MAGNETICO = 8;
const int LED = 7;

void setup() {
  pinMode(MAGNETICO, INPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if(digitalRead(MAGNETICO) == LOW){
      digitalWrite(LED, HIGH);
      Serial.println("puerta abierta");
  }else{
      Serial.println("puerta cerrada");
      digitalWrite(LED, LOW);
  }
  delay(1000);
}
