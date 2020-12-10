#define	DATA_COMMAND	0X40
#define	DISP_COMMAND	0x80
#define	ADDR_COMMAND	0XC0
int DIO = 27;
int CLK = 29;
int STB = 25;
//Common Cathode, Segment Active HIGH
unsigned char tab[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07,
                       0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71
                      };
unsigned char num[8];//Value of digit
void setup ()
{
  pinMode(STB, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(DIO, OUTPUT); //Put three pin to output mode
}
void loop()
{
  unsigned char i;
  init_TM1638();//Initialize TM1638
  for (i = 0; i < 8; i++) Write_DATA(i << 1, tab[0]);//Initialize latch
  while (1) {
    i = Read_key();
    if (i < 8) {
      num[i]++;
      while (i == Read_key());
      if (num[i] > 15) num[i] = 0;
      Write_DATA(i * 2, tab[num[i]]); //i is address
      Write_allLED(1 << i);
    }
  }
}

void TM1638_Write(unsigned char	DATA) { //Write Data
  unsigned char i;
  pinMode(DIO, OUTPUT);
  for (i = 0; i < 8; i++) {
    digitalWrite(CLK, LOW);
    if (DATA & 0X01) digitalWrite(DIO, HIGH);
    else digitalWrite(DIO, LOW);
    DATA >>= 1;
    digitalWrite(CLK, HIGH);
  }
}
unsigned char TM1638_Read(void) { //Read data
  unsigned char i;
  unsigned char temp = 0;
  pinMode(DIO, INPUT);
  for (i = 0; i < 8; i++) {
    temp >>= 1;
    digitalWrite(CLK, LOW);
    if (digitalRead(DIO) == HIGH) temp |= 0x80;
    digitalWrite(CLK, HIGH);
  }
  return temp;
}
void Write_COM(unsigned char cmd) { //Send command word
  digitalWrite(STB, LOW);
  TM1638_Write(cmd);
  digitalWrite(STB, HIGH);
}

unsigned char Read_key(void) {
  unsigned char c[4], i, key_value = 0;
  digitalWrite(STB, LOW);
  TM1638_Write(0x42); //Read Button
  for (i = 0; i < 4; i++) {
    c[i] = TM1638_Read();
  }
  digitalWrite(STB, HIGH);//Combine 4 byte to a word
  for (i = 0; i < 4; i++) key_value |= c[i] << i;
  for (i = 0; i < 8; i++) {
    if ((0x01 << i) == key_value)
      break;
  }
  return i;
}
void Write_DATA(unsigned char add, unsigned char DATA) { //Write data to address
  Write_COM(0x44);
  digitalWrite(STB, LOW);
  TM1638_Write(0xc0 | add);
  TM1638_Write(DATA);
  digitalWrite(STB, HIGH);
}

void Write_allLED(unsigned char LED_flag)
{ //Control LED
  unsigned char i;
  for (i = 0; i < 8; i++) {
    if (LED_flag & (1 << i))Write_DATA(2 * i + 1, 1);
    else Write_DATA(2 * i + 1, 0);
  }
}

void init_TM1638(void) {
  unsigned char i;
  Write_COM(0x8b);//0x88-0x8f 8-Level Brightness
  Write_COM(0x40);//Auto Increment Addr by 1
  digitalWrite(STB, LOW);
  TM1638_Write(0xc0);//Set Initial Addr
  for (i = 0; i < 16; i++)TM1638_Write(0x00);//Send 16 bytes of data
  digitalWrite(STB, HIGH);
}

