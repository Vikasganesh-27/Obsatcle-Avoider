#include <Servo.h>

int trigPin1 = 2;
int echoPin1 = 3;
int trigPin2 = 4;
int echoPin2 = 5;
int trigPin3 = 6;
int echoPin3 = 7;

int motPos1 = 8;
int motNeg1 = 9;
int motPos2 = 10;
int motNeg2 = 11;

int servoPin  = A0;

Servo myServo;

int min_dist = 70;

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  myServo.attach(servoPin);
  myServo.write(90);
  delay(50);
}

void loop() 
{
  Serial.print("Distance 1 : ");
  int d1 = usSensor(trigPin1,echoPin1);
  Serial.println(d1);
  Serial.print("Distance 2 : ");
  int d2 = usSensor(trigPin2,echoPin2); 
  Serial.println(d2);
  Serial.print("Distance 3 : ");
  int d3 = usSensor(trigPin3,echoPin3);
  Serial.println(d3);

  if(d1>min_dist & d2<min_dist & d3<min_dist) //forward
  {
    forward();
    delay(20);
  }
  
  
  if(d1<min_dist & d2>min_dist & d3<min_dist) //left
  { 
    stop();
    delay(20);
   	left();
    delay(20);
  }
  
   
  if(d1<min_dist & d2<min_dist & d3>min_dist) //right
  {
    stop();
    delay(20);
   	right();
    delay(20);
  }
  
  if(d1>min_dist & d2>min_dist & d3<min_dist)//forward priority
  {
   	forward();
    delay(20);
  }
  
  if(d1>min_dist & d2<min_dist & d3>min_dist)//forward priority
  {
   	forward();
    delay(20);
  }
  
  if(d1<min_dist & d2>min_dist & d3>min_dist)//left priority
  {
    stop();
    delay(20);
   	left();
    delay(20);
  }
  
  if(d1<min_dist & d2<min_dist & d3<min_dist)//backward
  {
    stop();
    delay(20);
   	backward();
    delay(20);
  }
  
  if(d1>min_dist & d2>min_dist & d3>min_dist)//forward priority
  {
    stop();
    delay(20);
   	forward();
    delay(20);
  }
  delay(2000);
}

int usSensor(int trigPin, int echoPin)
{
  digitalWrite(trigPin,LOW);
  digitalWrite(trigPin,HIGH);
  digitalWrite(trigPin,LOW);

  long duration = pulseIn(echoPin, HIGH);

  int distance = duration*0.034/2;
}

void forward()
{
  myServo.write(90);
  digitalWrite(motPos1, HIGH);
  digitalWrite(motNeg1, LOW);
  digitalWrite(motPos2, HIGH);
  digitalWrite(motNeg2, LOW);
  delay(20);
}

void backward()
{
  
  digitalWrite(motPos1, LOW);
  digitalWrite(motNeg1, HIGH);
  digitalWrite(motPos2, LOW);
  digitalWrite(motNeg2, HIGH);
  delay(20);
}

void left()
{
  myServo.write(0);
  digitalWrite(motPos1, HIGH);
  digitalWrite(motNeg1, LOW);
  digitalWrite(motPos2, LOW);
  digitalWrite(motNeg2, HIGH);
  delay(20);
}

void right()
{
  myServo.write(180);
  digitalWrite(motPos1, LOW);
  digitalWrite(motNeg1, HIGH);
  digitalWrite(motPos2, HIGH);
  digitalWrite(motNeg2, LOW);
  delay(20);
}

void stop()
{
  myServo.write(90);
  digitalWrite(motPos1, LOW);
  digitalWrite(motNeg1, LOW);
  digitalWrite(motPos2, LOW);
  digitalWrite(motNeg2, LOW);
  delay(20);
}

