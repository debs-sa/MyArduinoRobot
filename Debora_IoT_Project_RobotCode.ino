 
#include <AFMotor.h>  
#include <NewPing.h>
#include <Servo.h>
#include <LiquidCrystal.h> 
 
#define TRIG_PIN A0 
#define ECHO_PIN A1
#define MAX_DISTANCE 100 
#define MAX_SPEED 150 // sets speed of DC  motors
#define MAX_SPEED_OFFSET 20
 
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 

AF_DCMotor motor3(3, MOTOR34_64KHZ);
AF_DCMotor motor4(4, MOTOR34_64KHZ);
Servo myservo;   
 
boolean goesForward=false;
int distance = 100;
int speedSet = 0;

//ldc pins
int RS = 8;
int E = 9;
int D4 = 10;
int D5 = 3;
int D6 = 12;
int D7 = 13;

LiquidCrystal lcd(RS, E, D4, D5, D6, D7);

//redled and buzzer
int LEDBuzzerPin = 1;

//rgb led pins
int redPin= 7;
int bluePin = 6;
int greenPin = 5;

 
void setup() {
 
  myservo.attach(10);  
  myservo.write(115); 
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);

  lcd.begin(16, 2);
  
}
 
void loop() {
 int distanceR = 0;
 int distanceL = 0;
 delay(40);
 
 if(distance<=25)
 {
  moveStop();
  delay(100);
  moveBackward();
  delay(200);
  moveStop();
  delay(200);
  distanceR = lookRight();
  delay(200);
  distanceL = lookLeft();
  delay(200);
 
  if(distanceR>=distanceL)
  {
    turnRight();
    moveStop();
  } 
 
  else
 
  {
    turnLeft();
    moveStop();
  }
 } 
 
 else
 {
  moveForward();
 }
 distance = readPing();

//lcd
lcd.setCursor(3, 0);
lcd.print("DEBORA'S");
lcd.setCursor(0, 1);
lcd.print("ARDUINO PORJECT");

//redled and buzzer
digitalWrite(LEDBuzzerPin,HIGH);
delay(300);
digitalWrite(LEDBuzzerPin,LOW);
delay(4000);

//rgb led
setColor(255, 0, 0); // Red Color
delay(2000);
setColor(0, 255, 0); // Green Color
delay(2000);
setColor(0, 0, 255); // Blue Color
delay(2000);
setColor(255, 255, 255); // White Color
delay(2000);
setColor(170, 0, 255); // Purple Color
delay(2000);
}

void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}

//robot movements
int lookRight()
{
    myservo.write(50); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(115); 
    return distance;
}
 
int lookLeft()
{
    myservo.write(170); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(115); 
    return distance;
    delay(100);
}
 
int readPing() { 
  delay(100);
  int cm = sonar.ping_cm();
  if(cm==0)
  {
    cm = 250;
  }
  return cm;
}
 
void moveStop() {
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  } 
 
void moveForward() {
 
 if(!goesForward)
  {
    goesForward=true;
    motor3.run(FORWARD); 
    motor4.run(FORWARD);     
   for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) // slowly bring the speed up to avoid loading down the batteries too quickly
   {
    motor3.setSpeed(speedSet);
    motor4.setSpeed(speedSet);
    delay(5);
   }
  }
}
 
void moveBackward() {
    goesForward=false;
    motor3.run(BACKWARD);
    motor4.run(BACKWARD);  
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) // slowly bring the speed up to avoid loading down the batteries too quickly
  {;
    motor3.setSpeed(speedSet);
    motor4.setSpeed(speedSet);
    delay(5);
  }
}  
 
void turnRight() {
  motor3.run(FORWARD);   
  motor4.run(BACKWARD);
  delay(500);
  motor3.run(FORWARD);
  motor4.run(FORWARD);      
} 
 
void turnLeft() { 
  motor3.run(BACKWARD); 
  motor4.run(FORWARD); 
  delay(500);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}
