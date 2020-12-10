#define R 15
#define Y 13
#define G 12
#define W 14
#define A 2
#define B 0

volatile bool R_stat = 0;
volatile bool Y_stat = 0;
volatile bool G_stat = 0;
volatile unsigned int count = 0;

void setup() {
  Serial.begin(115200);

  unsigned char OUT[] = {R, Y, G, W};
  unsigned char IN[] = {A, B};

  for (uint8_t i = 0; i < 4; i++) pinMode(OUT[i], OUTPUT);
  for (uint8_t i = 0; i < 2; i++) pinMode(IN[i], INPUT);

  //  attachInterrupt(digitalPinToInterrupt(A), A_handler, FALLING);
  //  attachInterrupt(digitalPinToInterrupt(B), B_handler, FALLING);
}

unsigned int last = 0;
unsigned int threshold = 500;
int flagA = 0;
int flagB = 0;
unsigned int button_scan_rate = 0;
bool A_stat = false;
bool B_stat = false;

void loop() {
  if ((millis() - last) > threshold ) {
    last = millis();
    digitalWrite(R, R_stat ? HIGH : LOW);
    R_stat = !R_stat;
    Serial.println(count);
  }

  if (!Y_stat && !G_stat) {
    digitalWrite(W, LOW);
  } else {
    digitalWrite(W, HIGH);
  }

  if ((millis() - button_scan_rate) > 100) {
    Serial.println("Polled");
    button_scan_rate = millis();
    flagA += digitalRead(A) ? -1 : 1;
    flagB += digitalRead(B) ? -1 : 1;
    if (flagA < 0) flagA = 0;
    if (flagB < 0) flagB = 0;
    Serial.println(flagA);
    Serial.println(flagB);
  }

  if (flagA > 10) {
    flagA = 0;
    A_stat = !A_stat;
  }

  if (flagB > 10) {
    flagB = 0;
    B_stat != B_stat;
  }

  digitalWrite(Y, A_stat ? HIGH : LOW);
  digitalWrite(G, B_stat ? HIGH : LOW);



}


//
//ICACHE_RAM_ATTR void A_handler() {
//  digitalWrite(Y, Y_stat ? HIGH : LOW);
//  Y_stat = !Y_stat;
//  count++;
//}
//
//ICACHE_RAM_ATTR void B_handler() {
//  digitalWrite(G, G_stat ? HIGH : LOW);
//  G_stat = !G_stat;
//  count++;
//}
