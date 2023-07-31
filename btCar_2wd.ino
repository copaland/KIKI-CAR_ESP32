#include <BluetoothSerial.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

#define IN1 32
#define IN2 33
#define IN3 34
#define IN4 35
#define ASLEEP 25
#define BSLEEP 26

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
  pinMode(IN4, OUTPUT);
  pinMode(ASLEEP, OUTPUT);
  pinMode(BSLEEP, OUTPUT);

  Serial.println("Motor pins enabled.");

  delay(1000);
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
}

void stop()
{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
}

void forward()
{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);

    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}

void reverse()
{
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
}

void left()
{
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}

void right()
{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);

    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
}
