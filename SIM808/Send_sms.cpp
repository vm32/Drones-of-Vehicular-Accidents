#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX
String comdata = "";
void Send_Message(void);
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
  Send_Message();
   mySerial.listen();
   while(1)
  {  
    while(mySerial.available()>0)  
        Serial.write(mySerial.read());
   while(Serial.available())
    mySerial.write(Serial.read());  //Arduino send the sim808 feedback to computer     
  } 
}

void Send_Message(void)//sned message 
{
   mySerial.println("AT");   
  delay(500);
  //Send message
  mySerial.println("AT+CMGF=1");
  delay(500);
  mySerial.println("AT+CMGS=\"13424403025\"");//Change the receiver phone number
  delay(500);
  mySerial.println("438801554_A+ ");//the message you want to send
  delay(100);
  mySerial.write(26); 
}
