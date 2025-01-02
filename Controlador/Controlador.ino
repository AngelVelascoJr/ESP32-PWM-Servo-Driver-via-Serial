#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver ServoDriver = Adafruit_PWMServoDriver(0x40);
#define Servo0 0

//values ​​obtained after characterizing the servo
int servo_0[] = {92};
int servo_180[] = {512};

const int BUFFER_SIZE = 100;
char readedvalues[BUFFER_SIZE];

int ServoValues[10];
int ValuesRecieved = 0;

//#define I2C_SDA 12
//#define I2C_SCL 13

void setup() 
{
  //Wire.begin(I2C_SDA, I2C_SCL); //uncoment this line if you want to use diferent pins for I2C comunication
  Serial.begin(9600);
  ServoDriver.begin();
  ServoDriver.setPWMFreq(50); //50 ms PWM period for MG996r
}

void loop() 
{
  if(Serial.available() > 0)
  {
    //this code accepts values in format '##,##,##,##\n'
    Serial.readBytesUntil('\n', readedvalues, BUFFER_SIZE);
    char* found = strtok(readedvalues,",");
    char* diff = strtok(readedvalues, ",");
    int count = 0;
    ValuesRecieved = 0;
    while(diff != NULL && count < 16)
    {
      ServoValues[count] = atoi(diff);
      count++;
      ValuesRecieved++;
      diff = strtok(NULL, ",");
    }
    count = 0;
    while (count < ValuesRecieved)
    {
      MoveServo(count, ServoValues[count]);
      count++;
    }
  }
}

void MoveServo(int num_servo, float angle)
{
  int low = ((servo_180[num_servo]-servo_0[num_servo])/180.0)*angle + servo_0[num_servo];
  ServoDriver.setPWM(num_servo, 0, low);
}

int clamp(int val, int min_val, int max_val) {
    if (val < min_val) {
        return min_val;
    } else if (val > max_val) {
        return max_val;
    } else {
        return val;
    }
}
