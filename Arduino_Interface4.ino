/*
* (C) Jude Teves
* July 30, 2016
*
*
*/

#include <TimerOne.h>
#include <digitalWriteFast.h>

 int channel = 0;
 int sample = 0;

 int INTR = 46;
 int WR = 48; 
 int CS = 50;
 int RD = 52;

 int Abit0 = 40;
 int Abit1 = 38;
 int Abit2 = 36;
 int Abit3 = 34;
 int Abit4 = 32;
 int Abit5 = 30;
 int Abit6 = 28;
 int Abit7 = 26;

 int Bbit0 = 41;
 int Bbit1 = 39;
 int Bbit2 = 37;
 int Bbit3 = 35;
 int Bbit4 = 33;
 int Bbit5 = 31;
 int Bbit6 = 29;
 int Bbit7 = 27;

 int Cbit0 = 11;
 int Cbit1 = 10;
 int Cbit2 = 9;
 int Cbit3 = 8;
 int Cbit4 = 7;
 int Cbit5 = 6;
 int Cbit6 = 5;
 int Cbit7 = 4;

 int bit0;
 int bit1;
 int bit2;
 int bit3;
 int bit4;
 int bit5;
 int bit6;
 int bit7;
 
  uint8_t str1[2048];
  uint8_t str2[2048];
  uint8_t str3[2048];
  uint8_t str4[2048];
  uint8_t str5[2048];
  uint8_t str6[2048];
 

void setup() {
  // initialize mode for control pins
  pinModeFast(INTR, INPUT);
  pinModeFast(WR, OUTPUT);
  pinModeFast(RD, OUTPUT);
  pinModeFast(CS, OUTPUT);

  // initialize bit value for control pins
  digitalWriteFast(WR, HIGH);
  digitalWriteFast(CS, LOW);

  // initialize mode for bits 5-7
  pinModeFast(Abit5, INPUT); pinModeFast(Bbit5, INPUT); pinModeFast(Cbit5, INPUT);
  pinModeFast(Abit6, INPUT); pinModeFast(Bbit6, INPUT); pinModeFast(Cbit6, INPUT);
  pinModeFast(Abit7, INPUT); pinModeFast(Bbit7, INPUT); pinModeFast(Cbit7, INPUT);

  //Serial.begin(57600);
  Serial.begin(115200);
  delay(500); 

  Timer1.initialize(500);
  //Timer1.stop();
  Timer1.attachInterrupt(adc);
  Timer1.stop();
}

void adc() {
  digitalWriteFast(CS,LOW);
  digitalWriteFast(RD,HIGH);
  
  // set bits 0-4 to output mode
  pinModeFast(Abit0, OUTPUT); pinModeFast(Bbit0, OUTPUT); pinModeFast(Cbit0, OUTPUT); 
  pinModeFast(Abit1, OUTPUT); pinModeFast(Bbit1, OUTPUT); pinModeFast(Cbit1, OUTPUT); 
  pinModeFast(Abit2, OUTPUT); pinModeFast(Bbit2, OUTPUT); pinModeFast(Cbit2, OUTPUT); 
  pinModeFast(Abit3, OUTPUT); pinModeFast(Bbit3, OUTPUT); pinModeFast(Cbit3, OUTPUT); 
  pinModeFast(Abit4, OUTPUT); pinModeFast(Bbit4, OUTPUT); pinModeFast(Cbit4, OUTPUT); 

  // Channel Selection (Multiplexer)
  selectChannel();
  
  digitalWriteFast(WR, LOW);
  //delay(100);  //* make pulse wide enough
  digitalWriteFast(WR, HIGH); // rising edge to trigger start of conversion
  digitalWriteFast(CS, HIGH); //* de-select

  // Conversion...
  delayMicroseconds(60);
  
  digitalWriteFast(CS, LOW);
  digitalWriteFast(RD, LOW); // output on data bus.

  // set bits 0-4 to input mode
  pinModeFast(Abit0, INPUT); pinModeFast(Bbit0, INPUT); pinModeFast(Cbit0, INPUT); 
  pinModeFast(Abit1, INPUT); pinModeFast(Bbit1, INPUT); pinModeFast(Cbit1, INPUT); 
  pinModeFast(Abit2, INPUT); pinModeFast(Bbit2, INPUT); pinModeFast(Cbit2, INPUT); 
  pinModeFast(Abit3, INPUT); pinModeFast(Bbit3, INPUT); pinModeFast(Cbit3, INPUT); 
  pinModeFast(Abit4, INPUT); pinModeFast(Bbit4, INPUT); pinModeFast(Cbit4, INPUT); 

  //delay(100); //* recommended?
  digitalWriteFast(RD, HIGH); //* read data
  digitalWriteFast(CS, HIGH);

  //read data
  //strings 1/2
  bit0 = digitalRead(Abit0);
  bit1 = digitalRead(Abit1)<<1;
  bit2 = digitalRead(Abit2)<<2;
  bit3 = digitalRead(Abit3)<<3;
  bit4 = digitalRead(Abit4)<<4;
  bit5 = digitalRead(Abit5)<<5;
  bit6 = digitalRead(Abit6)<<6;
  bit7 = digitalRead(Abit7)<<7;
  if(channel==0) {
    str1[sample] = bit7+bit6+bit5+bit4+bit3+bit2+bit1+bit0;
  }
  else {
    str2[(sample-1)/2] = bit7+bit6+bit5+bit4+bit3+bit2+bit1+bit0;
  }

  //strings 3/4
  bit0 = digitalRead(Bbit0);
  bit1 = digitalRead(Bbit1)<<1;
  bit2 = digitalRead(Bbit2)<<2;
  bit3 = digitalRead(Bbit3)<<3;
  bit4 = digitalRead(Bbit4)<<4;
  bit5 = digitalRead(Bbit5)<<5;
  bit6 = digitalRead(Bbit6)<<6;
  bit7 = digitalRead(Bbit7)<<7;
  if(channel==0)
    str3[sample] = bit7+bit6+bit5+bit4+bit3+bit2+bit1+bit0;
  else
    str4[(sample-1)/2] = bit7+bit6+bit5+bit4+bit3+bit2+bit1+bit0;

  //strings 5/6
  bit0 = digitalRead(Cbit0);
  bit1 = digitalRead(Cbit1)<<1;
  bit2 = digitalRead(Cbit2)<<2;
  bit3 = digitalRead(Cbit3)<<3;
  bit4 = digitalRead(Cbit4)<<4;
  bit5 = digitalRead(Cbit5)<<5;
  bit6 = digitalRead(Cbit6)<<6;
  bit7 = digitalRead(Cbit7)<<7;
  if(channel==0)
    str5[sample] = bit7+bit6+bit5+bit4+bit3+bit2+bit1+bit0;
  else
    str6[(sample-1)/2] = bit7+bit6+bit5+bit4+bit3+bit2+bit1+bit0;

  

  // switch channel
  channel = (channel+1)%2;

  //if 100 samples per channel, stop conversion
  //then send the data to PC
  sample+=1;
  if(sample==4096) {
    //noInterrupts();//stop interrupts
    Timer1.stop();
    sample=0;
    sendData();
  }
}

void sendData() {
  int i=0;
  while(i<2048) {
    Serial.println((int)str1[i]);    
    i++;
  }
  i=0;
  while(i<2048) {
    Serial.println((int)str2[i]);    
    i++;
  }
  i=0;
  while(i<2048) {
    Serial.println((int)str3[i]);    
    i++;
  }
  i=0;
  while(i<2048) {
    Serial.println((int)str4[i]);    
    i++;
  }
  i=0;
  while(i<2048) {
    Serial.println((int)str5[i]);    
    i++;
  }
  i=0;
  while(i<2048) {
    Serial.println((int)str6[i]);    
    i++;
  }
}

void selectChannel() {
  // first channel
  if(channel==0) {
    digitalWriteFast(Abit0, LOW); digitalWriteFast(Bbit0, LOW); digitalWriteFast(Cbit0, LOW); 
    digitalWriteFast(Abit1, LOW); digitalWriteFast(Bbit1, LOW); digitalWriteFast(Cbit1, LOW); 
    digitalWriteFast(Abit2, LOW); digitalWriteFast(Bbit2, LOW); digitalWriteFast(Cbit2, LOW); 
    digitalWriteFast(Abit3, HIGH); digitalWriteFast(Bbit3, HIGH); digitalWriteFast(Cbit3, HIGH);
    digitalWriteFast(Abit4, LOW); digitalWriteFast(Bbit4, LOW); digitalWriteFast(Cbit4, LOW);
  }
  // second channel
  else {
    digitalWriteFast(Abit0, HIGH); digitalWriteFast(Bbit0, HIGH); digitalWriteFast(Cbit0, HIGH); 
    digitalWriteFast(Abit1, LOW); digitalWriteFast(Bbit1, LOW); digitalWriteFast(Cbit1, LOW); 
    digitalWriteFast(Abit2, LOW); digitalWriteFast(Bbit2, LOW); digitalWriteFast(Cbit2, LOW); 
    digitalWriteFast(Abit3, HIGH); digitalWriteFast(Bbit3, HIGH); digitalWriteFast(Cbit3, HIGH);
    digitalWriteFast(Abit4, LOW); digitalWriteFast(Bbit4, LOW); digitalWriteFast(Cbit4, LOW);
  }
  return;    
}

void loop() {
}

void serialEvent() {
  while(Serial.available()) {
    char c = Serial.read();
    //Serial.print(c); 
    //delay(50); 
    if(c =='c') {
      Timer1.restart();
    }
  }
}

