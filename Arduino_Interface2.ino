/*
* (C) Jude Teves
* June 29, 2016
*
*
* Possible causes of error:
* execution time of queue, pinMode, and digitalRead/Write are too long.
*
*/

#include <TimerOne.h>
#include <TimerThree.h>
#include <QueueArray.h>
#include <digitalWriteFast.h>

 int channel = 0;
 int samples = 0;

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

 QueueArray <int> str1;
 QueueArray <int> str2;
 QueueArray <int> str3;
 QueueArray <int> str4;
 QueueArray <int> str5;
 QueueArray <int> str6;
 

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

  Serial.begin(9600);
  delay(500); 

  Timer1.initialize(150);
  Timer1.attachInterrupt(adc);
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
  digitalWriteFast(CS,HIGH); //* de-select

  // Conversion...
  delayMicroseconds(60);
  
  digitalWriteFast(CS,LOW);
  digitalWriteFast(RD,LOW); // output on data bus.

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
  int bit0 = digitalReadFast(Abit0);
  int bit1 = digitalReadFast(Abit1)<<1;
  int bit2 = digitalReadFast(Abit2)<<2;
  int bit3 = digitalReadFast(Abit3)<<3;
  int bit4 = digitalReadFast(Abit4)<<4;
  int bit5 = digitalReadFast(Abit5)<<5;
  int bit6 = digitalReadFast(Abit6)<<6;
  int bit7 = digitalReadFast(Abit7)<<7;
  if(channel==0)
    str1.enqueue(bit7+bit6+bit5+bit4+bit3+bit2+bit1+bit0);
  else
    str2.enqueue(bit7+bit6+bit5+bit4+bit3+bit2+bit1+bit0);

  //strings 3/4
  int bit0 = digitalReadFast(Bbit0);
  int bit1 = digitalReadFast(Bbit1)<<1;
  int bit2 = digitalReadFast(Bbit2)<<2;
  int bit3 = digitalReadFast(Bbit3)<<3;
  int bit4 = digitalReadFast(Bbit4)<<4;
  int bit5 = digitalReadFast(Bbit5)<<5;
  int bit6 = digitalReadFast(Bbit6)<<6;
  int bit7 = digitalReadFast(Bbit7)<<7;
  if(channel==0)
    str3.enqueue(bit7+bit6+bit5+bit4+bit3+bit2+bit1+bit0);
  else
    str4.enqueue(bit7+bit6+bit5+bit4+bit3+bit2+bit1+bit0);

  //strings 5/6
  int bit0 = digitalReadFast(Cbit0);
  int bit1 = digitalReadFast(Cbit1)<<1;
  int bit2 = digitalReadFast(Cbit2)<<2;
  int bit3 = digitalReadFast(Cbit3)<<3;
  int bit4 = digitalReadFast(Cbit4)<<4;
  int bit5 = digitalReadFast(Cbit5)<<5;
  int bit6 = digitalReadFast(Cbit6)<<6;
  int bit7 = digitalReadFast(Cbit7)<<7;
  if(channel==0)
    str5.enqueue(bit7+bit6+bit5+bit4+bit3+bit2+bit1+bit0);
  else
    str6.enqueue(bit7+bit6+bit5+bit4+bit3+bit2+bit1+bit0);

  // switch channel
  channel = (channel+1)%2;

  //if 100 samples per channel, stop conversion
  //then send the data to PC
  sample+=1;
  if(sample==200) {
    noInterrupts();//stop interrupts
    sample=0;
    sendData();
  }
}

void sendData() {
  Serial.println("String 1:");
  while(!str1.isEmpty())
    Serial.print(str1.dequeue());
  Serial.println();
  
  Serial.println("String 2:");
  while(!str2.isEmpty())
    Serial.print(str2.dequeue());
  Serial.println();
  
  Serial.println("String 3:");
  while(!str3.isEmpty())
    Serial.print(str3.dequeue());
  Serial.println();
  
  Serial.println("String 4:");
  while(!str4.isEmpty())
    Serial.print(str4.dequeue());
  Serial.println();
  
  Serial.println("String 5:");
  while(!str5.isEmpty())
    Serial.print(str5.dequeue());
  Serial.println();
  
  Serial.println("String 6:");
  while(!str6.isEmpty())
    Serial.print(str6.dequeue());
    
  interrupts();
}

void loop() {
  // put your main code here, to run repeatedly:

}
