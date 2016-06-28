/*
 * (c) Jude Teves 
 * 
 * Description: Program for controlling the ADC0848 Chip using Arduino Mega 2560.
 * 
 * Status: tested. 
 * 
 * Details: capable of changing channels. Receives the 'correct' data from the
 * specified channel.
 * 
 * Limitations/Constraints: Input voltage was 0V, 3V, and 5.5V. 
 * Tested using 5V charger as power supply.
 * 
 * Problems: When 3V was fed into any of the channels, the output data of both
 * channels become the same. If 0 is fed, 00h is the output for the specified
 * channel. If 5V, then FFh.
 * 
 * Possible causes of error: power supply used or Vref input.
 * 
 * 
 * UPDATE!!
 * THIS IS NOW WORKING!
 * 
 */

 int channel = 0;

 int INTR = 46;
 int WR = 48; 
 int CS = 50;
 int RD = 52;

 int bit0 = 40;
 int bit1 = 38;
 int bit2 = 36;
 int bit3 = 34;
 int bit4 = 32;
 int bit5 = 30;
 int bit6 = 28;
 int bit7 = 26;

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
  pinMode(bit5, INPUT);
  pinMode(bit6, INPUT);
  pinMode(bit7, INPUT);

  delay(500);  
}

void loop() {

  digitalWrite(CS,LOW);
  digitalWrite(RD,HIGH);
  //digitalWrite(WR, HIGH);
  
  // set bits 0-4 to output mode
  pinMode(bit0, OUTPUT);
  pinMode(bit1, OUTPUT);
  pinMode(bit2, OUTPUT);
  pinMode(bit3, OUTPUT);
  pinMode(bit4, OUTPUT);

  // Channel Selection (Multiplexer)
  selectChannel();
  
  digitalWrite(WR, LOW);
  delay(100);  //* make pulse wide enough
  digitalWrite(WR, HIGH); // rising edge to trigger start of conversion
  digitalWrite(CS,HIGH); //* de-select

  // Conversion...
  while(digitalRead(INTR)){
    delay(100);
    //Serial.println("INTR=HIGH -> data not ready yet");
  }; // conversion is complete when INTR is LOW.

  digitalWrite(CS,LOW);
  //digitalWrite(WR,HIGH);
  digitalWrite(RD,LOW); // output on data bus.

// set bits 0-4 to input mode
  pinMode(bit0, INPUT);
  pinMode(bit1, INPUT);
  pinMode(bit2, INPUT);
  pinMode(bit3, INPUT);
  pinMode(bit4, INPUT);

  delay(100); //* recommended?
  digitalWrite(RD, HIGH); //* read data

  digitalWrite(CS, HIGH);

  displayData();

  // switch channel
  channel = (channel+1)%2;
  
  delay(1000);
}

void selectChannel() {
  // first channel
  if(channel==0) {
    digitalWrite(bit0, LOW);
    digitalWrite(bit1, LOW);
    digitalWrite(bit2, LOW);
    digitalWrite(bit3, HIGH);
    digitalWrite(bit4, LOW);
  }
  // second channel
  else {
    digitalWrite(bit0, HIGH);
    digitalWrite(bit1, LOW);
    digitalWrite(bit2, LOW);
    digitalWrite(bit3, HIGH);
    digitalWrite(bit4, LOW);
  }
  return;    
}

void displayData() {
  if(channel==0)
    Serial.print("Channel 1: ");
  else
    Serial.print("Channel 2: ");

  Serial.print(digitalRead(bit7));
  Serial.print(digitalRead(bit6));
  Serial.print(digitalRead(bit5));
  Serial.print(digitalRead(bit4));
  Serial.print(digitalRead(bit3));
  Serial.print(digitalRead(bit2));
  Serial.print(digitalRead(bit1));
  Serial.println(digitalRead(bit0));

  return;
}






