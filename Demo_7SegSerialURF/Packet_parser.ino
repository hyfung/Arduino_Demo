//const unsigned char PWM_PIN[] = {3, 5, 6, 9, 10, 11}; //For 328P
//const unsigned char PWM_PIN[] = {2,3,4,5,6,7,8,9,10,11,12,13}; //For Mega2560
const char valid_opcode[] = "HLIOPARSXT?D";
const unsigned char PWM_PIN[] = {3, 5, 6, 9, 10, 11}; //For 328P

void WaitForPacket() {
  //while (Serial.available() == 0) nop(); //This is a blocking statement
  while (Serial.available() > 0) {
    char buf = Serial.read();
    if (buf == '\r') continue; //Remove carriage return
    //else if (buf == '?') print_help();
    else if (buf == 'X') {
      Serial.println("Device Reset Ack");
      delay(500);
      asm volatile("jmp 0");
    }
    else if (buf == '\n') {
      packet_parser(inPacket);
      Serial.println("Packet Parser: Job's done.");
      /*
        Optional for redirection
      */
      inPacket = "";
      break;
    }
    else {
      inPacket += buf;
    }
  }
  //while (Serial.available() > 0) Serial.read(); //Garbage collection, this line doesnt work yet
}

void packet_parser(String packet) {
  //Try clear input buffer//
  int arg = -255;
  unsigned char PIN = 0;
  //----Checking Integrity--------------------
  Serial.println("Instruction Received: " + packet);
  bool valid = false;
  valid =  (packet.length() == 3) || (packet.length() == 6);
  if (!valid) {
    Serial.println("Error: Invalid Packet Length");
    return;
  }
  valid = false;
  //---------Now we get the arguments----------------
  if (packet.length() == 6) {
    arg = packet.substring(3, 6).toInt();
  }
  PIN = packet.substring(0, 2).toInt();
  char opcode = packet[2];
  for (int i = 0; i < strlen(valid_opcode); i++) {
    if ( opcode == valid_opcode[i] ) valid = true;
  }
  if (!valid) {
    Serial.println("Error: Invalid Opcode");
    return;
  }
  //----------Now we check pin number----------------------
  if ( (PIN < 2) || ( PIN > 20) ) {
    //D is special case for delay
    if (opcode != 'D') {
      Serial.println("Error: Invalid Pin");
      return;
    }
  }
  //--------Decode Instruction-------
  switch (opcode) {
    case 'L':
      digitalWrite(PIN, LOW);
      //Serial.println("Pin setted to LOW: " + PIN);
      break;
    case 'H':
      digitalWrite(PIN, HIGH);
      //Serial.println("Pin setted to HIGH: " + PIN);
      break;
    case 'I':
      pinMode(PIN, INPUT);
      //Serial.println("Pin setted to INPUT: " + PIN);
      break;
    case 'O':
      pinMode(PIN, OUTPUT);
      //Serial.println("O: Pin setted to OUTPUT: " + PIN);
      break;
    case 'P':
      valid = false;
      for (int i = 0; i < sizeof(PWM_PIN); i ++) {
        if (PIN == PWM_PIN[i]) valid = true;
      }
      if (valid == false) {
        Serial.println("This pin does not support PWM");
        break;
      }
      if (arg == -255) {
        Serial.println("Warning: Argument Empty");
        break;
      }
      x = arg;
      analogWrite(PIN, arg);
      //Serial.println("Analog Write Pin: " + PIN);
      //Serial.println("PWM: " + arg);
      break;
    case 'T':
      digitalWrite(PIN, !digitalRead(PIN));
      //Serial.println("Pin Toggled: " + PIN);
      //Serial.println("State: " + digitalRead(PIN));
      break;
    case 'A':
      if ( PIN > 13 && PIN < 21) {
        //Serial.print("Analog Read: ");
        Serial.println(analogRead(PIN));
      }
      else Serial.println("A: This is not ADC Pin!");
      break;
    case 'R':
      //Serial.println("Digital Read of Pin: " + PIN);
      //Serial.println("State: " + digitalRead(PIN));
      Serial.println( digitalRead(PIN) ? 1 : 0 );
      break;
    case 'S':
      for (int i = 2; i < 21; i++) {
        Serial.print("Pin " + i + ':');
        Serial.println( digitalRead(i) ? 1 : 0 );
      }
      break;
    case 'D':
      Serial.print("Delay for: ");
      Serial.println(PIN * 1000  + arg);
      delay(PIN * 1000  + arg);
      break;
    default:
      Serial.println("Invalid Instruction.");
  }
  inPacket = "";
}
