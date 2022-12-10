#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX
String comdata = "";
void Call_Phone(void);
void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);

 while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // set the data rate for the SoftwareSerial port
  mySerial.begin(4800);
  delay(200);
}

void loop() // run over and over
{
  delay(2000);
  Call_Phone();
   mySerial.listen();
   while(1)
  {  
    while(mySerial.available()>0)  
        Serial.write(mySerial.read());
   while(Serial.available())
    mySerial.write(Serial.read());  //Arduino send the sim808 feedback to computer     
  } 
}

void Call_Phone(void)//sned message 
{
   mySerial.println("AT");//Send AT command     
   delay(500);  
  //Make a phone call
   mySerial.println("ATD10086;");//Change the receiver phone number   
   delay(200);
}
