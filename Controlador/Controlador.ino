#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver ServoDriver = Adafruit_PWMServoDriver(0x40);
#define Servo0 0

//values ​​obtained after characterizing the servo
int servo_N90[] = {92, 92, 82};
int servo_90[] = {512, 512, 512};

const int MIN_SERVO[] = {-90,-90,-90};
const int MAX_SERVO[] = {90,90,90};

const int BUFFER_SIZE = 100;
char readedvalues[BUFFER_SIZE];

int ServoValues[10];
int ValuesRecieved = 0;

//#define I2C_SDA 12
//#define I2C_SCL 13

void setup() 
{
  //Wire.begin(I2C_SDA, I2C_SCL); //uncoment this line if you want to use diferent pins for I2C comunication
  Wire.setClock(400000);
  Serial.begin(115200);
  ServoDriver.begin();
  ServoDriver.setPWMFreq(50); //50 ms PWM period for MG996r

  for(int i = 0; i < sizeof(servo_N90); i++)
  {
    MoveServo(i, 0);
  }
  
}

void loop() 
{
  if(Serial.available() > 0)
  {
    memset(readedvalues, 0, BUFFER_SIZE); //reset variable with angles
    //this code accepts values in format '##,##,##,##E'
    Serial.readBytesUntil('E', readedvalues, BUFFER_SIZE);
    //Feedback();
    char* diff = strtok(readedvalues, ",");
    int count = 0;
    ValuesRecieved = 0;
    //Serial.println(readedvalues); //debug lines
    //Serial.println(diff);
    while(diff != NULL && count < 16)
    {
      ServoValues[count] = atoi(diff);
      //Serial.println(diff);
      count++;
      ValuesRecieved++;
      diff = strtok(NULL, ",");
    }
    count = 0;
    while (count < ValuesRecieved)
    {
      //Serial.println(count);
      MoveServo(count, ServoValues[count]);
      count++;
    }
  }
}

void Feedback()
{
  String RetMessage = String(readedvalues);
  RetMessage.concat("E");
  Serial.println(RetMessage);
}

void MoveServo(int num_servo, float angle)
{
  if(num_servo >= sizeof(servo_90) && num_servo >= sizeof(servo_N90))
    return;
  angle = clamp(angle, MIN_SERVO[num_servo], MAX_SERVO[num_servo]);
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
