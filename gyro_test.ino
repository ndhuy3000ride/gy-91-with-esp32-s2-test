#include <MPU9250_asukiaaa.h>
#include <Wire.h>
MPU9250_asukiaaa mpu;
float aX, aY, aZ, aSqrt, gX, gY, gZ, mDirection;
uint16_t mX, mY, mZ;

#define SDA_PIN 11
#define SCL_PIN 12

#define SERIAL_PLOTTER                        //Định nghĩa sử dụng Serial Plotter
//#define SERIAL_MONITOR                      //Định nghĩa sử dụng Serial Monitor

void setup() {
  Serial.begin(9600);
  Wire.begin(SDA_PIN, SCL_PIN);
  mpu.setWire(&Wire);

  mpu.beginAccel();
  mpu.beginGyro();
  mpu.beginMag();

}

void loop() {

  if (mpu.accelUpdate() == 0) {                             //Thông số gia tốc kế
    aX = mpu.accelX();
    aY = mpu.accelY();
    aZ = mpu.accelZ();
    aSqrt = mpu.accelSqrt();

  #if defined(SERIAL_PLOTTER)
    Serial.print(String(aX));
    Serial.print("," + String(aY));
    Serial.print("," + String(aZ));
    Serial.print("," + String(aSqrt));
  #else
    Serial.print("accelX: " + String(aX));
    Serial.print("\taccelY: " + String(aY));
    Serial.print("\taccelZ: " + String(aZ));
    Serial.print("\taccelSqrt: " + String(aSqrt));
  #endif  
  }

  if (mpu.gyroUpdate() == 0) {                            //Thông số con quay hồi chuyển
    gX = mpu.gyroX();
    gY = mpu.gyroY();
    gZ = mpu.gyroZ();
  #if defined(SERIAL_PLOTTER)  
    Serial.print("," + String(gX));
    Serial.print("," + String(gY));
    Serial.print("," + String(gZ));
  #else
    Serial.print("\tgyroX: " + String(gX));
    Serial.print("\tgyroY: " + String(gY));
    Serial.print("\tgyroZ: " + String(gZ));
  #endif  
  }
  auto result = mpu.magUpdate();
  if (result == 0) {                            //Thông số từ kế
    mX = mpu.magX();
    mY = mpu.magY();
    mZ = mpu.magZ();
    mDirection = mpu.magHorizDirection();
  #if defined(SERIAL_PLOTTER)  
    Serial.print("," + String(mX));
    Serial.print("," + String(mY));
    Serial.print("," + String(mZ));
    Serial.print("," + String(mDirection));
  #else  
    Serial.print("\tmagX: " + String(mX));
    Serial.print("\tmaxY: " + String(mY));
    Serial.print("\tmagZ: " + String(mZ));
    Serial.print("\thorizontalDirection: " + String(mDirection));
  #endif  
  }
  else {
    mpu.beginMag();
    result = mpu.magUpdate();
  }
  Serial.println("");
  delay(100);
  }
