# m35080_Read_BitBang
This default Skech now reads the full memory of EEPROM chips of the m35080 family like M35080, 08ODOWQ, M35080VP and 35080V6. </br> The read begins, after any kind of serial data is transmitted to the arduino (e.g just press the space bar and hit enter).

Secure Incremental Memory rages from 0x00 till 0x1F</br>
Standard Mempory ranges from 0x20 till 0x3FF

## Arduino
I used an arduino micro, but any arduino which supports SPI is fine. Just switch the board in the arduino IDE.

## M35080 EEPROM
A datasheet is included in this repo. Connect Chipselect, Clock, In, Out, Vcc(5V) and Vss accordingly. Make sure, that max. current never exceeds 10mA.

## Write to Memory (0x20 till 0x3FF)
You can write to memory using the write_8() function. </br>
*Please backup your full memory before you make any changes.*

Example:

```int adr = 0x2F1;
char val = 0x20;
write_8(adr, val);```

or also 

```int adr = 0x2F1;
char val = 0x00;
char content[] = {0x12};
for (int i = 0; i <= sizeof(content); i++) {
  write_8(adr, content[i]);
  adr = adr + 0x1;
}```

## Write to secure (incremental) memory (0x00 till 0x1F)
You can write to memory using the write_secure() function.
Please keep in mind, that you can only count up these values, so be careful what you write.
*YOU CAN'T WRITE LOWER NUMBERS THAN WHAT IS ALREADY IN THERE*

Example:

```int adr = 0x00;
char val1 = 0x12;
char val1 = 0x26;
write_secure(adr, val1, val2);```

## Decoding BMW Cluster Information on E-Series Models

Example: </br>
If the secure memory looks like this:

| 00  | 01 | 02 | 03 | 04 | 05 | 06 | 07 |
| :--:|:--:| :--:|:--:|:--:|:--:|:--:|:--:|
| 2613 | 2613 | 2613 | 2612 | 2612 | 2612 | 2612 | 2612 |

| 08  | 09 | A | B | C | D | E | F |
| :--:|:--:| :--:|:--:|:--:|:--:|:--:|:--:|
| 2612 | 2612 | 2612 | 2612 | 2612 | 2612 | 2612 | 2612 |

The Hex-Value for the milage (km) is 26124 which equals 155.940 km in decimal.
