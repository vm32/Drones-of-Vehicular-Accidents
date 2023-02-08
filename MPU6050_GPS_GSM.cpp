#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#include<SoftwareSerial.h> 
#include <DFRobot_SIM808.h>
#define rxPin 7
#define txPin 8
SoftwareSerial mySerial(txPin, rxPin);
 DFRobot_SIM808 sim808(&mySerial);
 char wlat[12];
 char wlon[12];
 char wwspeed[12];

Adafruit_MPU6050 mpu;
void setup(void) {
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
	pinMode(2, OUTPUT);
	pinMode(4, OUTPUT);
	pinMode(LED_BUILTIN, OUTPUT);
	Serial.begin(115200);
	// Try to initialize!
	if (!mpu.begin()) {
		Serial.println("Failed to find MPU6050 chip");
		while (1) {
			delay(10);

		}
	}
	Serial.println("MPU6050 Found!");
	// set accelerometer range to +-8G
	mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
	// set gyro range to +- 500 deg/s
	mpu.setGyroRange(MPU6050_RANGE_500_DEG);
	// set filter bandwidth to 21 Hz
	mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
	delay(100);
}
void loop() {
  if (sim808.getGPS()) 
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
    

	/* Get new sensor events with the readings */
	sensors_event_t a, g, temp;
	mpu.getEvent(&a, &g, &temp);
	/* Print out the values */
	Serial.print("Acceleration X: ");
	Serial.print(a.acceleration.x);
	Serial.print(", Y: ");
	Serial.print(a.acceleration.y);
	Serial.print(", Z: ");
	Serial.print(a.acceleration.z);
	Serial.println(" m/s^2");
	Serial.print("Rotation X: ");
	Serial.print(g.gyro.x);
	Serial.print(", Y: ");
	Serial.print(g.gyro.y);
	Serial.print(", Z: ");
	Serial.print(g.gyro.z);
	Serial.println(" rad/s");
	Serial.print("Temperature: ");
	Serial.print(temp.temperature);
	Serial.println(" C");
	Serial.println("");
	digitalWrite(2, HIGH);
	digitalWrite(2, LOW);
	delay(150);
	digitalWrite(2, LOW);
	digitalWrite(2, HIGH);
	delay(100);
	delay(500);

	if (g.gyro.x > 0.45 or g.gyro.x < -0.45) {
		digitalWrite(4, HIGH);
		digitalWrite(2, LOW);
		delay(100);
		Serial.print("Accident detect on gyro : ");
		Serial.print(g.gyro.y);
		digitalWrite(4, LOW);
		digitalWrite(2, LOW);
		delay(100);
	};
	if (g.gyro.y > 0.45 or g.gyro.y < -0.45) {
		digitalWrite(4, HIGH);
		digitalWrite(2, LOW);
		delay(100);
		Serial.print("Accident detect on gyro : ");
		Serial.print(g.gyro.y);
		digitalWrite(4, LOW);
		digitalWrite(2, LOW);
		delay(100);
	};
	if (a.acceleration.x > 0.06) {
		digitalWrite(4, HIGH);
		digitalWrite(2, LOW);
		delay(100);
		Serial.print("Accident detect on acceleration : ");
		Serial.print(a.acceleration.x);
		digitalWrite(4, LOW);
		digitalWrite(2, LOW);
		delay(100);
	};

	if (temp.temperature > 45) {
		digitalWrite(4, HIGH);
		digitalWrite(2, LOW);
		delay(100);
		Serial.print("temprature is HIGH : ");
		Serial.print(temp.temperature);
		digitalWrite(4, LOW);
		digitalWrite(2, LOW);
		delay(100);
	};
  }
  
 void SubmitHttpRequest(float la,float lo, float ws)
 {
  
  dtostrf( la,6, 6, wlat); 
  dtostrf( lo,6, 6, wlon); 
  dtostrf( ws,6, 6, wwspeed); 

 mySerial.println("AT");
delay(100);
ShowSerialData();

mySerial.println("AT+CREG?");
 delay(100);
 ShowSerialData();

mySerial.println("AT+CSQ");
delay(100);
ShowSerialData();

mySerial.println("AT+CGATT?");
delay(100);
ShowSerialData();

 mySerial.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");
 delay(1000);
 ShowSerialData();

 mySerial.println("AT+SAPBR=3,1,\"APN\",\"Mobinil\"");
 delay(4000);
 ShowSerialData();

 mySerial.println("AT+SAPBR=1,1");
 delay(2000);
ShowSerialData();

mySerial.println("AT+SAPBR=3,1");
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

mySerial.print("AT+HTTPPARA=\"URL\",\"gpstest.edafait.com/Default2?");
mySerial.print("&lat=");  // This is the value name
mySerial.print(wlat); // value of...
mySerial.print("&longs=");  // This is the value name
mySerial.print(wlon); // value of...
mySerial.print("&actions=");  // This is the value name
mySerial.print(wwspeed); // value of...
mySerial.print("&dates=");  // This is the value name

mySerial.print("AT+CGSN");
mySerial.print("&time=");  // This is the value name

 mySerial.print("AT+CGMM");

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

