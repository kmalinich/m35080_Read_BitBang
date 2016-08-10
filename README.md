# m35080_Read_BitBang
Arduino sketch for dumping data from the registers of the m35080 eeprom throught the bitbang method.


This default Skech now reads the full memory. The read begins, after any kind of serial data is transmitted to the arduino (e.g just press the space bar and hit enter).

## Write to Memory
You can write to memory using the write_8() function.
Example:

`int adr = 0x2F1;
char val = 0x20;
write_8(adr, val);`

or also 

`int adr = 0x2F1;
char val = 0x00;
char content[] = {0x12};
for (int i = 0; i <= sizeof(content); i++) {
  write_8(adr, content[i]);
  adr = adr + 0x1;
}`

## Write to secure (incremental) memory
You can write to memory using the write_secure() function.
Please keep in mind, that you can only count up these values, so be careful what you write.
YOU CAN'T WRITE LOWER NUMBERS THAN WHAT IS ALREADY IN THERE

Example:

`int adr = 0x00;
char val1 = 0x12;
char val1 = 0x26;
write_secure(adr, val1, val2);`
