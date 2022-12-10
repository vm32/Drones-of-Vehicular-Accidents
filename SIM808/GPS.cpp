#include <SoftwareSerial.h>

//#define SERIAL_TX_BUFFER_SIZE 256
//#define SERIAL_RX_BUFFER_SIZE 256
SoftwareSerial mySerial(2, 3); // RX, TX
String comdata = "";
void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);

 while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  delay(200);
}

void loop() // run over and over
{
  delay(2000);
   mySerial.println("AT");   
  delay(200);
  //Send message
  mySerial.println("AT+CGNSPWR=1");
  delay(200);
  //reset GPS in autonomy mode
  mySerial.println("AT+CGNSTST=1");
  delay(200);
   mySerial.listen();
   while(1)
  {  
    while(mySerial.available()>0)  
        Serial.write(mySerial.read());
   while(Serial.available())
    mySerial.write(Serial.read());  //Arduino send the sim808 feedback to computer     
  } 
}

