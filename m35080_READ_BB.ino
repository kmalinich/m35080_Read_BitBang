// Pin configuration
int Chip_Select = SS;
int DATAIN      = MISO;
int Sclk        = SCK;
int DATAOUT     = MOSI;


// Instruction set
byte WREN = 0b00000110; // Write enable latch set
byte WRDI = 0b00000100; // Write enable latch reset

byte RDSR = 0b00000101; // Status register read
byte WRSR = 0b00000001; // Status register write

byte READ = 0b00000011; // Read data from memory array

byte WRITE = 0b00000010; // Write data to memory array
byte WRINC = 0b00000111; // Write data to secure array


// Initialize global variables
unsigned int starting_address;

int i = 0;
int h;
int l;

int fourhigh;
int readings[9];
int retrieve_readings[9];




void read_full() {
	byte aux;

	Serial.println("INCREMENTAL REGISTERS:");
	Serial.print("000: ");

	for (byte index = 0x00; index < 0x10; index = index + 0x01) {
		aux = read_8(index);
		if (aux < 16) Serial.print("0");
		Serial.print(aux, HEX);
		Serial.print(" ");
	}

	Serial.print("\n");
	Serial.print("010: ");

	for (byte index = 0x10; index < 0x20; index = index + 0x01) {
		aux = read_8(index);
		if (aux < 16) Serial.print("0");
		Serial.print(aux, HEX);
		Serial.print(" ");
	}


	Serial.println("\n");
	Serial.print("NON INCREMENTAL REGISTERS:");

	int cnt = -1 ;

	for (int index = 0x20; index <= 0x3FF; index = index + 0x1) {
		cnt++;

		if (cnt % 16 == 0) {
			Serial.print("\n");
			if (index < 16)  Serial.print("0");
			if (index < 255) Serial.print("0");
			Serial.print(index, HEX);
			Serial.print(": ");
		}

		aux = read_8(index);
		if (aux < 16) Serial.print("0");
		Serial.print(aux, HEX);
		Serial.print(" ");
	}

	Serial.println("\n\nEND");
}



// functions
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
		}
		else {
			sclk();
		}
	}

	chip_select_high();
	return value;
}


void write_8(int address, char dat) {
	char bit;

	chip_select_low();
	send_8(WREN);
	chip_select_high();

	delay(10);

	chip_select_low();

	send_8(WRITE);
	send_address(address);

	// verstehe ich nicht (I do not understand)
	for (char index = 7; index >= 0; index--) {
		bit = ((dat >> index) & 0x01);

		if (bit == 1) {
			digitalWrite(DATAOUT, HIGH);
			sclk();
		}
		else {
			digitalWrite(DATAOUT, LOW);
			sclk();
		}
	}
	// verstehe ich nicht (I do not understand)

	chip_select_high();
}


void write_secure(int address, char dat1, char dat2) {
	char bit;

	chip_select_low();
	send_8(WREN);
	chip_select_high();

	delay(10);

	chip_select_low();

	send_8(WRINC);
	send_address(address);

	// verstehe ich nicht (I do not understand)
	for (char index = 7; index >= 0; index--) {
		bit = ((dat1 >> index) & 0x01);

		if (bit == 1) {
			digitalWrite(DATAOUT, HIGH);
			sclk();
		}
		else {
			digitalWrite(DATAOUT, LOW);
			sclk();
		}
	}

	for (char index = 7; index >= 0; index--) {
		bit = ((dat2 >> index) & 0x01);

		if (bit == 1) {
			digitalWrite(DATAOUT, HIGH);
			sclk();
		}
		else {
			digitalWrite(DATAOUT, LOW);
			sclk();
		}
	}
	// verstehe ich nicht (I do not understand)

	chip_select_high();
}


void send_8(char dat) {
	char bit;

	for (char index = 7; index >= 0; index--) {
		bit = ((dat >> index) & 0x01);

		if (bit == 1) {
			digitalWrite(DATAOUT, HIGH);
			sclk();
		}
		else {
			digitalWrite(DATAOUT, LOW);
			sclk();
		}
	}
}


void send_address(int dat) {
	char bit;
	char index;

	for (index = 15; index >= 0; index--) {
		bit = ((dat >> index) & 0x01);

		if (bit == 1) {
			digitalWrite(DATAOUT, HIGH);
			sclk();
		}
		else {
			digitalWrite(DATAOUT, LOW);
			sclk();
		}
	}
}


void setup() {
	Serial.begin(115200);
	Serial.println();

	Serial.println("[INIT] Pin configuration");

	pinMode(Chip_Select, OUTPUT);
	pinMode(DATAIN,      INPUT);
	pinMode(DATAOUT,     OUTPUT);
	pinMode(Sclk,        OUTPUT);

	Serial.flush();
	Serial.println("[INIT] Ready\n");
}

void loop() {
	// while (Serial.available() <= 0) { } ;

	read_full();

	while (1) { } ;
}


// vim: set filetype=cpp ts=2 sw=2 tw=0 et :
