#define BAUD 9600
#define BAUD_INV 104

#define RX_PIN 13

uint8_t rx = 0x0;

void setup(){
    pinMode(RX_PIN, INPUT_PULLUP);
}

void loop(){

    //Wait until
    while(digitalRead(RX_PIN) == HIGH){
    }

    //Wait for 1.5 cycle
    delayMicroseconds(BAUD_INV * 1.5);

    for(int i=0;i<8;i++){
        rx |= digitalRead(RX_PIN) << i;
        delayMicroseconds(BAUD_INV);
    }

    //Omit stop bit
    delayMicroseconds(BAUD_INV);

    Serial.print(char(rx));

}