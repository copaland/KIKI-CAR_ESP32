#include <BluetoothSerial.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

#define IN1 33    //a1 M1
#define IN2 25    //a2 M1
#define ASLEEP 32 //a3 M1

#define IN3 27    //b1 M2
#define IN4 14    //b2 M2
#define BSLEEP 26 //b3 M2

int speed = 2500; //4096/100*80
void setup() 
{
  Serial.begin(115200);
  SerialBT.begin("BluetoothCar");
  Serial.println("Bluetooth enabled.");

  delay(1000);
  
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(ASLEEP, OUTPUT);
  pinMode(BSLEEP, OUTPUT);

  Serial.println("Motor pins enabled.");

  delay(1000);
  //forward();
}

void loop() 
{  
  while (SerialBT.available()) {
      Serial.print("Received: ");
      char command = SerialBT.read();
      Serial.println(command);

      switch(command)
      {
        case 'F':
          forward();
          break;
        case 'B':
          reverse();
          break;
        case 'L':
          left();
          break;
        case 'R':
          right();
          break;
        case 'S':
          stop();
          break;
        default:
          stop();
          break;
      }
  }
  asm("nop");
}

void stop()
{
    
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(ASLEEP, LOW); //high on

    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    digitalWrite(BSLEEP, LOW);  
}

void forward()
{
    digitalWrite(IN1, LOW); //M2 FOWARD
    analogWrite(IN2, speed);
    digitalWrite(ASLEEP, HIGH); //high on

    digitalWrite(IN3, LOW); //M1
    analogWrite(IN4, speed);
    digitalWrite(BSLEEP, HIGH); //high on
}

void reverse()
{
    digitalWrite(IN1, speed); //M2 BACK
    analogWrite(IN2, LOW);
    digitalWrite(ASLEEP, HIGH); //high on
    
    digitalWrite(IN3, speed); //M1 BACK
    analogWrite(IN4, LOW);
    digitalWrite(BSLEEP, HIGH); //high on
}

void left()
{
    digitalWrite(IN1, LOW); //M2 FOWARD
    analogWrite(IN2, speed);
    digitalWrite(ASLEEP, HIGH); //high on

    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    digitalWrite(BSLEEP, LOW); //high on
}

void right()
{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(ASLEEP, LOW); //high on

    digitalWrite(IN3, LOW);
    analogWrite(IN4, speed);
    digitalWrite(BSLEEP, HIGH); //high on
}
