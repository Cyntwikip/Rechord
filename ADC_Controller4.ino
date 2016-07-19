/*
 * (c) Jude Teves 
 * 
 * Description: Program for controlling 3 ADC0848 Chips using Arduino Mega 2560.
 * 
 * Status: not yet tested. the version of this program that controls only 1 chip works!  
 * 
 */

 int channel = 0;

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

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // initialize mode for control pins
  pinMode(INTR, INPUT);
  pinMode(WR, OUTPUT);
  pinMode(RD, OUTPUT);
  pinMode(CS, OUTPUT);

  // initialize bit value for control pins
  digitalWrite(WR, HIGH);
  digitalWrite(CS, LOW);
  
  // initialize mode for bits 5-7
  pinMode(Abit5, INPUT); pinMode(Bbit5, INPUT); pinMode(Cbit5, INPUT);
  pinMode(Abit6, INPUT); pinMode(Bbit6, INPUT); pinMode(Cbit6, INPUT);
  pinMode(Abit7, INPUT); pinMode(Bbit7, INPUT); pinMode(Cbit7, INPUT);

  delay(500);  
}

void loop() {

  digitalWrite(CS,LOW);
  digitalWrite(RD,HIGH);
  
  // set bits 0-4 to output mode
  pinMode(Abit0, OUTPUT); pinMode(Bbit0, OUTPUT); pinMode(Cbit0, OUTPUT); 
  pinMode(Abit1, OUTPUT); pinMode(Bbit1, OUTPUT); pinMode(Cbit1, OUTPUT); 
  pinMode(Abit2, OUTPUT); pinMode(Bbit2, OUTPUT); pinMode(Cbit2, OUTPUT); 
  pinMode(Abit3, OUTPUT); pinMode(Bbit3, OUTPUT); pinMode(Cbit3, OUTPUT); 
  pinMode(Abit4, OUTPUT); pinMode(Bbit4, OUTPUT); pinMode(Cbit4, OUTPUT); 

  // Channel Selection (Multiplexer)
  selectChannel();
  
  digitalWrite(WR, LOW);
  //delay(100);  //* make pulse wide enough
  digitalWrite(WR, HIGH); // rising edge to trigger start of conversion
  digitalWrite(CS, HIGH); //* de-select

  // Conversion...
  delayMicroseconds(60);

  digitalWrite(CS,LOW);
  digitalWrite(RD,LOW); // output on data bus.

  // set bits 0-4 to input mode
  pinMode(Abit0, INPUT); pinMode(Bbit0, INPUT); pinMode(Cbit0, INPUT); 
  pinMode(Abit1, INPUT); pinMode(Bbit1, INPUT); pinMode(Cbit1, INPUT); 
  pinMode(Abit2, INPUT); pinMode(Bbit2, INPUT); pinMode(Cbit2, INPUT); 
  pinMode(Abit3, INPUT); pinMode(Bbit3, INPUT); pinMode(Cbit3, INPUT); 
  pinMode(Abit4, INPUT); pinMode(Bbit4, INPUT); pinMode(Cbit4, INPUT); 

  digitalWrite(RD, HIGH); //* read data
  digitalWrite(CS, HIGH);

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
  if(channel==0)
    Serial.print("String 1: ");
  else
    Serial.print("String 2: ");
  
  Serial.println(bit7+bit6+bit5+bit4+bit3+bit2+bit1+bit0);

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
    Serial.print("String 3: ");
  else
    Serial.print("String 4: ");
  
  Serial.println(bit7+bit6+bit5+bit4+bit3+bit2+bit1+bit0);

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
    Serial.print("String 5: ");
  else
    Serial.print("String 6: ");
  
  Serial.println(bit7+bit6+bit5+bit4+bit3+bit2+bit1+bit0);

  // switch channel
  channel = (channel+1)%2;
  
  delay(1000);
}

void selectChannel() {
  // first channel
  if(channel==0) {
    digitalWrite(Abit0, LOW); digitalWrite(Bbit0, LOW); digitalWrite(Cbit0, LOW); 
    digitalWrite(Abit1, LOW); digitalWrite(Bbit1, LOW); digitalWrite(Cbit1, LOW); 
    digitalWrite(Abit2, LOW); digitalWrite(Bbit2, LOW); digitalWrite(Cbit2, LOW); 
    digitalWrite(Abit3, HIGH); digitalWrite(Bbit3, HIGH); digitalWrite(Cbit3, HIGH);
    digitalWrite(Abit4, LOW); digitalWrite(Bbit4, LOW); digitalWrite(Cbit4, LOW);
  }
  // second channel
  else {
    digitalWrite(Abit0, HIGH); digitalWrite(Bbit0, HIGH); digitalWrite(Cbit0, HIGH); 
    digitalWrite(Abit1, LOW); digitalWrite(Bbit1, LOW); digitalWrite(Cbit1, LOW); 
    digitalWrite(Abit2, LOW); digitalWrite(Bbit2, LOW); digitalWrite(Cbit2, LOW); 
    digitalWrite(Abit3, HIGH); digitalWrite(Bbit3, HIGH); digitalWrite(Cbit3, HIGH);
    digitalWrite(Abit4, LOW); digitalWrite(Bbit4, LOW); digitalWrite(Cbit4, LOW);
  }
  return;    
}







