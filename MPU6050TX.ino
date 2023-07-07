#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile
#include "Wire.h"       
#include "I2Cdev.h"     
#include "MPU6050.h" 

RH_ASK driver;
MPU6050 mpu;
int16_t ax, ay, az;
int16_t gx, gy, gz;

struct MyData {
  byte X;
  byte Y;
};

MyData data;

void setup()
{
    Serial.begin(9600);    // Debugging only
   
    if (!driver.init())
         Serial.println("init failed");
          Wire.begin();
  mpu.initialize();
         
}

void loop()
{
    const char *msg1 = "Turn LED ON!";
    const char *msg2 = "Turn LED OFF";
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  data.X = map(ax, -17000, 17000, 0, 255 ); // X axis data
  data.Y = map(ay, -17000, 17000, 0, 255);  // Y axis data
   
  if (data.Y < 80) { //gesture : down 
    Serial.print("gesture 1");
    driver.send((uint8_t *)msg1, strlen(msg1));
    }
 if (data.Y > 145) {//gesture : up
  driver.send((uint8_t *)msg2, strlen(msg2));
  Serial.print("gesture 2");
    }
 if (data.X > 155) {//gesture : left
  Serial.print("gesture 3");
    }
 if (data.X < 80) {//gesture : right
  Serial.print("gesture 4");
    }
 if (data.X > 100 && data.X < 170 && data.Y > 80 && data.Y < 130) { //gesture : little bit down
    Serial.print("gesture 5");
    }
    driver.waitPacketSent();
    delay(100);
}
