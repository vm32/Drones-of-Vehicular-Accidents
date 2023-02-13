#include <MPU6050_tockn.h>
#include <Wire.h>
MPU6050 mpu6050(Wire);
void setup() {
  pinMode(2,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
}

void loop() {
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
}
