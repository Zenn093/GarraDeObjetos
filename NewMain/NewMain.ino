#define boton 8
#define fcEje 9
#define fcAtras 11
#define dirPinA 2
#define stepperPinA 3
#define enPinA 4
#define dirPinB 5
#define stepperPinB 6
#define enPinB 7
#define poteDerIz A1
#define poteAdAt A0
unsigned long tiempoAnterior = 0;
bool diagonal;
bool posicionado;
int pasosY;
int pasosX;  

void setup(){
  DDRD |= (1<<DDD2) | (1<<DDD3) | (1<<DDD4) | (1<<DDD5) | (1<<DDD6) | (1<<DDD7); // Pines de los steppers como salida
  DDRB &= ~((1<<DDB0) | (1<<DDB1) | (1<<DDB3)); // Pines pulsadores
  PORTB |= ((1<<DDB0) | (1<<DDB1) | (1<<DDB3));
  digitalWrite(dirPinA,HIGH); // dirPin HIGH sentido horario
  digitalWrite(enPinA, !LOW);
  digitalWrite(dirPinB,HIGH); // dirPin HIGH sentido horario
  digitalWrite(enPinB, !LOW);
  Serial.begin(9600);
}

void loop(){
  uint16_t posDerIz = analogRead(poteDerIz);
  uint16_t posAdAt = analogRead(poteAdAt);

  //  if(digitalRead(fcEje)){
  //   Serial.println("eje");
  //  }
   if(digitalRead(fcAtras)){
    Serial.println("atras");
   }

  //--------------------Prueba Joystick--------------------

  // Serial.print("Posicion Der/Iz: ");
  // Serial.println(posDerIz);
  // Serial.print("Posicion Ad/At: ");
  // Serial.println(posAdAt);
  // delay(1000);

  //Serial.println(diagonal);
  if((posDerIz < 470 || posDerIz > 580) && (posAdAt < 470 || posAdAt > 580)){ // Rango para establecer si es una diagonal o no
    diagonal = true;
  }
  else{
    diagonal = false;
  }
  //--------------------Logica Movimiento--------------------
  if(diagonal == false){
    if(posAdAt < 200){ // adelante
    girarMotor('W');
  }
  else if(posAdAt > 825){ // atras
    girarMotor('S');
  }
  else if(posDerIz > 825){ // derecha
    girarMotor('D');
  }
  else if(posDerIz < 200){ // izquierda
    girarMotor('A');
  }
  else{
    digitalWrite(enPinB, !LOW);
    digitalWrite(enPinA, !LOW);
  }
  }
  //--------------------Diagonales--------------------
  else{
      if((posDerIz > 580) && (posAdAt < 200)){ // diagonal superior derecha
    girarMotor('E');
  }
    else if((posDerIz < 470) && (posAdAt < 470)){ // diagonal superior izquierda
    girarMotor('Q');
  }
    else if((posDerIz > 580) && (posAdAt > 580)){ // diagonal inferior derecha
    girarMotor('X');
  }
    else if((posDerIz < 470) && (posAdAt > 580)){ // diagonal inferior izquierda
    girarMotor('Z');
  }
  else{
    digitalWrite(enPinB, !LOW);
    digitalWrite(enPinA, !LOW);
  }
  }
}


void posicionarse(){
  if(digitalRead(fcEje)){
    girarMotor('D');
   }
   else{
    girarMotor('W');
   }
   if(digitalRead(fcAtras)){
    posicionado = true;
    pasosX = 0;
    pasosY = 0;
   }
}

void girarMotor(char direccion){
  switch(direccion){
    case 'W':
    pasosY--;
    digitalWrite(dirPinA, LOW);
    digitalWrite(dirPinB, HIGH);
    pulsosMotor('A');
    pulsosMotor('B');
    break;
    case 'S':
    digitalWrite(dirPinA, HIGH);
    digitalWrite(dirPinB, LOW);
    pulsosMotor('A');
    pulsosMotor('B');
    pasosY++;
    break;
    case 'D':
    digitalWrite(dirPinA,LOW);
    digitalWrite(dirPinB,LOW);
    pulsosMotor('A');
    pulsosMotor('B');
    pasosX--;
    break;
    case 'A':
    digitalWrite(dirPinA,HIGH);
    digitalWrite(dirPinB,HIGH);
    pulsosMotor('A');
    pulsosMotor('B');
    pasosX++;
    break;
    case 'E':
    digitalWrite(dirPinA, LOW);
    pulsosMotor('A');
    pasosX--; pasosY--;
    break;
    case 'Q':
    digitalWrite(dirPinB,HIGH);
    pulsosMotor('B');
    pasosX--; pasosY++;
    break;
    case 'X':
    digitalWrite(dirPinB,LOW);
    pulsosMotor('B');
    pasosX--; pasosY--;
    break;
    case 'Z':
    digitalWrite(dirPinA,HIGH);
    pulsosMotor('A');
    pasosX++; pasosY--;
  }
// if (millis() - tiempoAnterior >= 200) {
//   Serial.print("pasosY: ");
//   Serial.println(pasosY);
//   Serial.print("pasosX: ");
//   Serial.println(pasosX);

//   tiempoAnterior = millis();
// }
}


void pulsosMotor(char setMotor){
  delay(1);
  // if(!diagonal){
  //   delay(1);
  // }
  // else{
  //   delay(0.5);
  // }
  uint8_t setEnPin;
  uint8_t setstepperPin;
  if(setMotor == 'A'){
    setstepperPin = stepperPinA;
    setEnPin = enPinA;
  }
  else if(setMotor == 'B'){
    setstepperPin = stepperPinB;
    setEnPin = enPinB;
  }
  digitalWrite(setEnPin, LOW);
  //Generar pulso step
  digitalWrite(setstepperPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(setstepperPin, LOW);
}
