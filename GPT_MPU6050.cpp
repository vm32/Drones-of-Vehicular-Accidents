#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

const int threshold = 20; // threshold value for detecting an accident

void setup() {
  Serial.begin(9600);

  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G); // set accelerometer range to +-8G
  mpu.setGyroRange(MPU6050_RANGE_500_DEG); // set gyro range to +- 500 deg/s
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ); // set filter bandwidth to 21 Hz
}

void loop() {
  int16_t ax, ay, az;
  int16_t gx, gy, gz;

  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz); // read accelerometer and gyroscope values

  if (abs(ax) > threshold || abs(ay) > threshold || abs(az) > threshold) {
    // check if any of the values exceed the threshold
    Serial.println("Accident detected!");
    delay(1000);
  }
}
