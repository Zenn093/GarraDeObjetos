#define boton 4
#define dirPinA 5
#define stepperPinA 6
#define enPinA 7
#define dirPinB 8
#define stepperPinB 10
#define enPinB 11
#define poteDerIz A1
#define poteAdAt A0   
uint32_t tiempo[2];
bool tLed = 0;
bool diagonal = false;

void setup() {
  Serial.begin(9600);
  DDRD |= (1<<stepperPinA) | (1<<dirPinA) | (1<<enPinA);
  DDRD &= ~(1<<boton);
  DDRB |= (1<<PB1) | (1<<PB0) | (1<<PB2);
  digitalWrite(dirPinA,HIGH); // dirPin HIGH sentido horario
  digitalWrite(enPinA, LOW);
  digitalWrite(dirPinB,HIGH); // dirPin HIGH sentido horario
  digitalWrite(enPinB, LOW);
}

void loop() {
  uint16_t posDerIz = analogRead(poteDerIz);
  uint16_t posAdAt = analogRead(poteAdAt);
  // delay(100);
  // Serial.print("posAdAt: ");
  // Serial.println(posAdAt);
  // delay(100);
  // Serial.print("posDerIz: ");
  // Serial.println(posDerIz);
  if((posDerIz>400)&&(diagonal == false)){ // Derecha
    digitalWrite(dirPinA,HIGH);
    digitalWrite(dirPinB,HIGH);
    girarMotor('D');
  }
   else if((posDerIz<100)&&(diagonal == false)){ // Izquierda
      digitalWrite(dirPinA,LOW);
      digitalWrite(dirPinB,LOW);
      girarMotor('A');
  }
  else{
    digitalWrite(enPinA, !LOW);
  }
//AD/AT
    if((posAdAt>600)&&(diagonal == false)){ // Atras
      girarMotor('S');
  }
   else if((posAdAt<250)&&(diagonal == false)){ // Adelante
    girarMotor('W');
  }
  else{
    digitalWrite(enPinB,!LOW);
  }
  //Diagonales
      if((posAdAt<190)&&(posDerIz<100)){ // Diagonal superior izquierda
      //Serial.println("digSupIz");
      girarMotor('Q');
      diagonal = true;
  }
   else if((posAdAt<150)&&(posDerIz>620)){ // Diagonal superior derecha
    //Serial.println("digSupDe");
    girarMotor('E');
    diagonal = true;
  }
     else if((posAdAt>500)&&(posDerIz<100)){ // Diagonal inferior izquierda
    girarMotor('Z');
    diagonal = true;
  }
       else if((posAdAt>600)&&(posDerIz>600)){ // Diagonal inferior derecha
    girarMotor('X');
    diagonal = true;
  }
  else{
    diagonal = false;
    digitalWrite(enPinB,!LOW);
    digitalWrite(enPinA,!LOW);
  }

  // if(digitalRead(boton)){
  //   digitalWrite(13,HIGH);
  //   tLed = true;
  // }
  //   if(intervalo(tiempo[0],5000) && (tLed)){
  //   tLed = false;
  //   digitalWrite(13,LOW);
  //   tiempo[0] = millis();
  // }

}


// void girarMotor(char motor){
//     uint8_t setEnPin;
//     uint8_t setstepperPin;
//   if (motor == 'A'){
//     setEnPin = enPinA;
//     setstepperPin = stepperPinA;
//   }
//       else if(motor == 'B'){
//       setEnPin = enPinB;
//       setstepperPin = stepperPinB;
//     }

//       digitalWrite(setEnPin, !HIGH);
//   digitalWrite(setEnPin, !HIGH);
//     delay(1);
//     digitalWrite(setstepperPin,HIGH);
//     digitalWrite(setstepperPin,HIGH);
//     delay(1);
//     digitalWrite(setstepperPin,LOW);
//     digitalWrite(setstepperPin,LOW);
// }

void girarMotor(char direccion){
    uint8_t setEnPin;
    uint8_t setstepperPin;
    //Serial.println(direccion);
    // if (direccion == 'W'){
    //   digitalWrite(dirPinA,HIGH);
    //   digitalWrite(dirPinB,LOW);
    //   pulsosMotor('A');
    //  // pulsosMotor('B');
    // }
    switch(direccion){
      case 'W':
      //Serial.println("adelante");
      digitalWrite(dirPinA,HIGH);
      digitalWrite(dirPinB,!LOW);
      pulsosMotor('A');
      pulsosMotor('B');
      break;
      case 'S':
      //Serial.println("abajo");
      digitalWrite(dirPinB,!HIGH);
      digitalWrite(dirPinA,LOW);
      pulsosMotor('A');
      pulsosMotor('B');
      break;
      case 'D':
      //Serial.println("derecha");
      digitalWrite(dirPinB,!HIGH);
      digitalWrite(dirPinA,HIGH);
      pulsosMotor('A');
      pulsosMotor('B');
      break;
      case 'A':
      //Serial.println("izquierda");
      digitalWrite(dirPinB,!LOW);
      digitalWrite(dirPinA,LOW);
      pulsosMotor('A');
      pulsosMotor('B');
      break;
      case 'E':
      //Serial.println("DiagSupDe");
      digitalWrite(dirPinA,!LOW);
      pulsosMotor('A');
      break;
      case 'Q':
      //Serial.println("DiagSupIz");
      digitalWrite(dirPinB,!LOW);
      pulsosMotor('B');
      break;
      case 'X':
      //Serial.println("DiagInfDer");
      digitalWrite(dirPinA,LOW);
      pulsosMotor('A');
      break;
      case 'Z':
      //Serial.println("DiagInfIz");
      digitalWrite(dirPinB,!LOW);
      pulsosMotor('B');
      break;
    }
}

void pulsosMotor(char setMotor){
    uint8_t setEnPin;
    uint8_t setstepperPin;
      if (setMotor == 'A'){
    setstepperPin = stepperPinA;
    setEnPin = enPinA;
  }
      else if(setMotor == 'B'){
      setEnPin = enPinB;
      setstepperPin = stepperPinB;
    }
    digitalWrite(setEnPin, !HIGH);
    delayMicroseconds(500);
    digitalWrite(setstepperPin,HIGH);
    delayMicroseconds(500);
    digitalWrite(setstepperPin,LOW);
}


bool intervalo(uint32_t &t, uint16_t tMax){
  if ((millis()) > (t + tMax)){
    t = millis();
    return true;
  }
  else{
    return false;
    }
}
