#include<SoftwareSerial.h> 
#include <DFRobot_SIM808.h>
#include <MPU6050_tockn.h>
#include <Wire.h>
MPU6050 mpu6050(Wire);

#define rxPin 11       //Tx
#define txPin 10       //Rx 

 SoftwareSerial mySerial(txPin, rxPin);
 DFRobot_SIM808 sim808(&mySerial);
 char wlat[12];
 char wlon[12];
 char wwspeed[12];
 
void setup(){
  pinMode(2,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
mySerial.begin(9600);
Serial.begin(115200); 
Serial.println("Starting...");
 while(!sim808.init()) {
      delay(1000);
      Serial.print("Sim808 init error\r\n");
  }
  //************* Turn on the GPS power************
if( sim808.attachGPS())
{
  Serial.println("Open the GPS power success");
}
else 
{
    Serial.println("Open the GPS power failure");
}
}
 void loop(){
  mpu6050.update();
  Serial.print("angleX : ");
  Serial.print(mpu6050.getAngleX());
  Serial.print("\tangleY : ");
  Serial.print(mpu6050.getAngleY());
  Serial.print("\tangleZ : ");
  Serial.println(mpu6050.getAngleZ());
   if (mpu6050.getAngleY() >= 30) { 
  digitalWrite(4, HIGH); 
  digitalWrite(2,LOW);
  delay(100);                     
  digitalWrite(4, LOW);
  digitalWrite(2,LOW);  
  delay(100);
  };
  if (mpu6050.getAngleY() < -30 ) { 
  digitalWrite(4, HIGH); 
  digitalWrite(2,LOW);
  delay(100);                     
  digitalWrite(4, LOW);
  digitalWrite(2,LOW);  
  delay(100);
  };
  if (mpu6050.getAngleX() <= -6.00 ) { 
  digitalWrite(2, HIGH); 
  digitalWrite(4,LOW);
  delay(100);                      
  digitalWrite(2, LOW);
  digitalWrite(4,LOW);  
  delay(100);
  };
  if (mpu6050.getAngleX() > 6.00 ) { 
  digitalWrite(2, HIGH); 
  digitalWrite(4,LOW);
  delay(100);                      
  digitalWrite(2, LOW);
  digitalWrite(4,LOW);  
  delay(100);
  };
if (sim808.getGPS()) {
   Serial.print(sim808.GPSdata.year);
   Serial.print("/");
   Serial.print(sim808.GPSdata.month);
   Serial.print("/");
   Serial.print(sim808.GPSdata.day);
  Serial.print(" ");
   Serial.print(sim808.GPSdata.hour);
   Serial.print(":");
  Serial.print(sim808.GPSdata.minute);
  Serial.print(":");
  Serial.print(sim808.GPSdata.second);
  Serial.print(":");
  Serial.println(sim808.GPSdata.centisecond);

   Serial.print("latitude :");
   Serial.println(sim808.GPSdata.lat,6);

  sim808.latitudeConverToDMS();
  Serial.print("latitude :");
  Serial.print(sim808.latDMS.degrees);
  Serial.print("\^");
  Serial.print(sim808.latDMS.minutes);
  Serial.print("\'");
  Serial.print(sim808.latDMS.seconeds,6);
  Serial.println("\"");
  Serial.print("longitude :");
  Serial.println(sim808.GPSdata.lon,6);
  sim808.LongitudeConverToDMS();
 Serial.print("longitude :");
 Serial.print(sim808.longDMS.degrees);
 Serial.print("\^");
 Serial.print(sim808.longDMS.minutes);
 Serial.print("\'");
 Serial.print(sim808.longDMS.seconeds,6);
Serial.println("\"");

 Serial.print("speed_kph :");
 Serial.println(sim808.GPSdata.speed_kph);
Serial.print("heading :");
 Serial.println(sim808.GPSdata.heading);
 
 
    float la = sim808.GPSdata.lat;
     float lo = sim808.GPSdata.lon;
    float ws = sim808.GPSdata.speed_kph;


     delay(1000);
     SubmitHttpRequest(la,lo,ws);
       }


  };
 

 void SubmitHttpRequest(float la,float lo, float ws)
 {
  
  dtostrf( la,6, 6, wlat); 
  dtostrf( lo,6, 6, wlon); 
  dtostrf( ws,6, 6, wwspeed); 

 mySerial.println("AT");
delay(100);
ShowSerialData();

mySerial.println("AT+CREG?"); //Network Registration Report
 delay(100);
 ShowSerialData();

mySerial.println("AT+CSQ");      //signal quality command
delay(100);
ShowSerialData();

mySerial.println("AT+CGATT?");   //Attach Or Detach
delay(100);
ShowSerialData();

 mySerial.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\""); //used to configure and to activate the PDP context (data traffic).
 delay(1000);
 ShowSerialData();

 mySerial.println("AT+SAPBR=3,1,\"APN\",\"Mobinil\"");
 delay(4000);
 ShowSerialData();

 mySerial.println("AT+SAPBR=1,1"); //used to configure and to activate the PDP context (data traffic).
 delay(2000);
ShowSerialData();

mySerial.println("AT+SAPBR=3,1");  //used to configure and to activate the PDP context (data traffic).
delay(2000);
ShowSerialData();

mySerial.println("AT+SAPBR=2,1");
delay(2000);
ShowSerialData();

mySerial.println("AT+HTTPINIT"); 
delay(2000); 
ShowSerialData();

mySerial.println("AT+HTTPPARA=\"CID\",1");
delay(2000); 
ShowSerialData();

mySerial.println("AT+HTTPSSL=0");    
ShowSerialData();
delay(1000);

mySerial.println("AT+HTTPSSL=1");
delay(2000); 
ShowSerialData();

mySerial.print("AT+HTTPPARA=\"URL\",\"https://vm32.github.io/back.html?");
mySerial.print("&lat=");  // This is the value lat
mySerial.print(wlat); // value of...
mySerial.print("&longs=");  // This is the value longs
mySerial.print(wlon); // value of...
mySerial.print("&actions=");  // This is the value actions
mySerial.print(wwspeed); // value of...
mySerial.print("&dates=");  // This is the value dates

mySerial.print("AT+CGSN");
mySerial.print("&time=");  // This is the value time

 mySerial.print("AT+CGMM"); //Model Identification

 mySerial.println("\"");
 delay(2000);
 ShowSerialData();



 mySerial.println("AT+HTTPACTION=2");//submit the request 
delay(1000);
ShowSerialData();

mySerial.println("AT+HTTPACTION=1");//submit the request 
delay(10000);
ShowSerialData();

 mySerial.println("AT+HTTPACTION=0");//submit the request 
 delay(1000);
 ShowSerialData();

 mySerial.println("AT+HTTPACTION=0");//submit the request 
delay(1000);;
ShowSerialData();

mySerial.println("AT+HTTPREAD");// read the data from the website you access
delay(300);
ShowSerialData();


mySerial.println("");
delay(100);

 };

 void ShowSerialData()
 {
   while(mySerial.available()!=0)
     {
       Serial.write(mySerial.read());
     }

 } 
