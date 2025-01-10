#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver ServoDriver = Adafruit_PWMServoDriver(0x40);
#define num_servo 2
#define ServoPWMFreq 50

//#define I2C_SDA 12
//#define I2C_SCL 13

void setup() 
{
  //Wire.begin(I2C_SDA, I2C_SCL); //uncoment this line if you want to use diferent pins for I2C comunication
  Wire.setClock(400000);
  Serial.begin(115200);
  ServoDriver.begin();
  ServoDriver.setPWMFreq(ServoPWMFreq); //50 ms PWM period for MG996r
}

void loop() 
{
  Get0();
  Get180();
}

void Get0()
{
  for(int i = 70; i < 120; i+=4)
  {
    ServoDriver.setPWM(num_servo, 0, i);
    Serial.println(i);
    delay(1000);
  }
}

void Get180()
{
  for(int i = 490; i < 530; i+=4)
  {
    ServoDriver.setPWM(num_servo, 0, i);
    Serial.println(i);
    delay(1000);
  }
}
