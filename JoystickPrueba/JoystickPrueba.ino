#define boton 8

void setup() {
  Serial.begin(9600);
  pinMode(boton,INPUT_PULLUP);
}

void loop() {
  uint16_t pote1Val = analogRead(A0);
  uint16_t pote2Val = analogRead(A1);
  delay(500);
  Serial.print("Pote Ad/At:");
  Serial.println(pote1Val);
  Serial.print("Pote Der/Iz:");
  Serial.println(pote2Val);
  //Serial.println(digitalRead(boton));
}
