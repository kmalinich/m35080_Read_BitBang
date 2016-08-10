int Chip_Select = SS;
int DATAIN = MISO;
int Sclk = SCK;
int DATAOUT = MOSI;

//Instruction Set
byte WREN = 0b00000110; //Set Write Enable Latch
byte WRDI = 0b00000100; //Reset Write Enable Latch
byte RDSR = 0b00000101; //Read Status Register
byte WRSR = 0b00000001; //Write Status Register
byte READ = 0b00000011; //Read Data from Memory Array
byte WRITE = 0b00000010; //Write Data to Memory Array
byte WRINC = 0b00000111; //Write Data to Secure Array
int i = 0;
unsigned int starting_address;
int h, l;
int fourhigh;
int readings[9];
int retrieve_readings[9];
void setup() {
  Serial.println("Boot");
  pinMode(Chip_Select, OUTPUT);
  pinMode(DATAIN, INPUT);
  pinMode(Sclk, OUTPUT);
  pinMode(DATAOUT, OUTPUT);
  Serial.begin(9600);
  Serial.println();

  Serial.flush();
  Serial.println("Done setting up...");
}
void loop() {
  while (Serial.available() <= 0) {
  }

  byte aux;
  Serial.println("Reading");
  for (int index1 = 0x00; index1 <= 0x6FF; index1 = index1 + 0x20) {
    for (int index2 = index2; index2 <= index2 + 0x1F; index2 = index2 + 0x01) {
      aux = read_8(index2);
      Serial.print(aux, HEX);
      Serial.print(" ");
    }
    Serial.print("\n");
  }
  Serial.println("END");
  while (1) {

  }
}

/*****************************************************/
/*functions*/
void chip_select_low(void) {
  digitalWrite(Chip_Select, LOW);
  delay(3);
}
void chip_select_high(void) {
  digitalWrite(Chip_Select, HIGH);
  delay(3);
}
void sclk() {
  digitalWrite(Sclk, HIGH);
  digitalWrite(Sclk, LOW);
}
/************************************************/
int read_8(int address) {
  char bit;
  char inbit;
  char index;
  int value = 0;
  chip_select_low();
  send_8(READ);
  send_address(address);
  for (index = 0; index < 8; index++) {
    bit = digitalRead(DATAIN);
    inbit = bit & 0x01;
    if (inbit == 1) {
      value = value + (0x80 >> index);
      sclk();
    } else {
      sclk();
    }
  }
  chip_select_high();
  return value;
}
/***********************************************/
void send_8(char dat) {
  char bit;
  for (char index = 7; index >= 0; index--) {
    bit = ((dat >> index) & 0x01);
    if (bit == 1) {
      digitalWrite(DATAOUT, HIGH);
      sclk();
    } else {
      digitalWrite(DATAOUT, LOW);
      sclk();
    }
  }
}
/******************************************************************/
void send_address(int dat) {
  char bit;
  char index;
  for (index = 15; index >= 0; index--) {
    bit = ((dat >> index) & 0x01);
    if (bit == 1) {
      digitalWrite(DATAOUT, HIGH);
      sclk();
    } else {
      digitalWrite(DATAOUT, LOW);
      sclk();
    }
  }
}
/************************************************************/
