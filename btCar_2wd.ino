#include <BluetoothSerial.h>

//#define USE_PIN
#ifdef USE_PIN
const char *pin = "1234"; //BT pin
#endif
String device_name = "KiKi-Car"; //BT name check

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

#define IN1 32    //a1 M1
#define IN2 33    //a2 M1
#define ASLEEP 25 //a3 M1

#define IN3 13    //b1 M2
#define IN4 15    //b2 M2
#define BSLEEP 26 //b3 M2

#define LED_LEFT 4 //
#define LED_RIGHT 12 //

int speed = 2048; //4096/100*80
bool ledState = false;//for test

unsigned long timeOn = 500;
unsigned long changeTime = 0;

void setup() 
{
  Serial.begin(115200);
  SerialBT.begin(device_name); //BT name
  
  #ifdef USE_PIN
    SerialBT.setPin(pin);
    Serial.println("Using PIN");
  #endif
  
  Serial.print("Bluetooth enabled:");
  Serial.println(device_name);
  
  //use drv8837
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  pinMode(ASLEEP, OUTPUT);
  pinMode(BSLEEP, OUTPUT);
  pinMode(LED_LEFT, OUTPUT);
  pinMode(LED_RIGHT, OUTPUT);

  Serial.println("Motor pins enabled.");

  delay(1000);
  //forward();
}

void loop() 
{  

  if (millis() >= changeTime)  {
    ledState = (ledState == LOW) ? HIGH : LOW;
    digitalWrite(LED_LEFT,ledState);
    digitalWrite(LED_RIGHT,!ledState);
    changeTime = millis() + timeOn;
  }

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
        case 'U':
          sleft();
          break;
        case 'V':
          sright();
          break;          
        case 'S':
          stop();
          break;
        default:
          stop();
          break;
      }
  }
  delay(10);
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

void sleft()
{
    digitalWrite(IN1, LOW); //M2 FOWARD
    analogWrite(IN2, speed);
    digitalWrite(ASLEEP, HIGH); //high on

    analogWrite(IN3, speed);
    digitalWrite(IN4, LOW);
    digitalWrite(BSLEEP, HIGH); //high on
}

void sright()
{
    analogWrite(IN1, speed);
    digitalWrite(IN2, LOW);
    digitalWrite(ASLEEP, HIGH); //high on

    digitalWrite(IN3, LOW);
    analogWrite(IN4, speed);
    digitalWrite(BSLEEP, HIGH); //high on
}
