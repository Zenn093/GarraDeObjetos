#define stepperPin 7
#define dirPin 6
#define enPin 5
unsigned long tac;

void setup() {
  DDRD |= (1<<stepperPin) | (1<<dirPin) | (1<<enPin);
  digitalWrite(dirPin,HIGH);
  digitalWrite(enPin, LOW);
}

void loop() {
  for(int i = 0; i<1000; i++){
    digitalWrite(stepperPin,HIGH);
    delay(1);
    digitalWrite(stepperPin,LOW);
    delay(1);
    }
  digitalWrite(enPin, HIGH);
  delay(5000);
  digitalWrite(dirPin,!digitalRead(dirPin));
  digitalWrite(enPin, LOW);
}

bool esperar(uint16_t t){
  if (millis() > tac + t){
    return true;
  }
  else{
    return false;
    }
}
