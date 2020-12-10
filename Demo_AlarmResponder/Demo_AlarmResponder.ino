unsigned char _InterruptAck = 2;
volatile unsigned char Ack = 1; //1 is waiting for ack
String inString = "";
void setup() {
  Serial.begin(9600);
  inString.reserve(64);
  pinMode(_InterruptAck, INPUT);
}

void loop() {

}

void WaitForSerial() {
  if (Serial.available() > 0) {
    char buf = Serial.read();
    if (buf == '\n') {
      Packet_Parsing(inString);
      inString = "";
    }
    else {
      inString += buf;
    }
  }
}

void Packet_Parsing(String packet) {

}

void FireAlarm(){
  while(Ack){
    
  }
}
