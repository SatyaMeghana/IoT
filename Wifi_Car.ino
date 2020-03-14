#include <Blynk.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define RightMotorSpeed 5
#define RightMotorDir   0 
#define LeftMotorSpeed  4
#define LeftMotorDir    2

const int trigPin = 14;  //sets D5 pin of ESP as Trigger
const int echoPin = 12;  //sets D6 pin of EsP as echo
const int buzzPin = 15;  //sets the D8 pin of ESP for the buzzer

// defines variables

char auth[] = "*********************"; //blynk token
char ssid[] = "*******"; //your ssid
char pass[] = "*******"; //your password

int minRange = 0;
int maxRange = 1023;

int minSpeed = 450;
int maxSpeed = 2500;
int noSpeed = 0;

long duration;
int distance;


void moveControl(int x, int y)
{

  if(y >= maxRange && x >= minRange && x <= maxRange) 
  {
    digitalWrite(RightMotorDir,HIGH); 
    digitalWrite(LeftMotorDir,HIGH);
    analogWrite(RightMotorSpeed,maxSpeed);
    analogWrite(LeftMotorSpeed,maxSpeed);
  }
 
  // move forward right
  else if(x >= maxRange && y >= maxRange)  
  {
    digitalWrite(RightMotorDir,HIGH);
    digitalWrite(LeftMotorDir,HIGH);
   analogWrite(RightMotorSpeed,minSpeed);
    analogWrite(LeftMotorSpeed,maxSpeed);
  }

  // move forward left
  else if(x <= minRange && y >= maxRange)
  {
    digitalWrite(RightMotorDir,HIGH);
    digitalWrite(LeftMotorDir,HIGH);
    analogWrite(RightMotorSpeed,maxSpeed);
    analogWrite(LeftMotorSpeed,minSpeed);
  }

  // neutral zone
  else if(y < maxRange && y > minRange && x < maxRange && x > minRange)
  {
    analogWrite(RightMotorSpeed,noSpeed);
    analogWrite(LeftMotorSpeed,noSpeed);
  }

 // move back
  else if(y <= minRange && x >= minRange && x <= maxRange)
  {
    digitalWrite(RightMotorDir,LOW);
    digitalWrite(LeftMotorDir,LOW);
   analogWrite(RightMotorSpeed,maxSpeed);
    analogWrite(LeftMotorSpeed,maxSpeed);
  }

  // move back and right
 else if(y <= minRange && x <= minRange)
  {
   digitalWrite(RightMotorDir,LOW);
    digitalWrite(LeftMotorDir,LOW);
    analogWrite(RightMotorSpeed,minSpeed);
    analogWrite(LeftMotorSpeed,maxSpeed); 
  }

  // move back and left
  else if(y <= minRange && x >= maxRange)
  {
    digitalWrite(RightMotorDir,LOW);
    digitalWrite(LeftMotorDir,LOW);
    analogWrite(RightMotorSpeed,maxSpeed);
    analogWrite(LeftMotorSpeed,minSpeed);
  }
}



void setup()
{
  Serial.begin(9600);
   Serial.print("Connected to 9600");
  Blynk.begin(auth, ssid, pass);
  Serial.print("Connected to blynk");
  
 // initial settings for motors off and direction forward
  pinMode(RightMotorSpeed, OUTPUT);
  pinMode(LeftMotorSpeed, OUTPUT);
  pinMode(RightMotorDir, OUTPUT);
  pinMode(LeftMotorDir, OUTPUT);
  Serial.print("Pinmode");
  digitalWrite(RightMotorSpeed, LOW);
  digitalWrite(LeftMotorSpeed, LOW);
  digitalWrite(RightMotorDir, HIGH);
  digitalWrite(LeftMotorDir,HIGH);

  Serial.print("Setting default");
  
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(buzzPin, OUTPUT);// Sets the buzzPin as an Output
  digitalWrite(buzzPin,LOW);
  Serial.begin(9600); // 
 }


void loop()
{

  Blynk.run();
  //Serial.print("Running");
   Serial.print("Connected to blynk");
   // Clears the trigPin
   digitalWrite(trigPin, LOW);
   //digitalWrite(buzzPin, LOW);
   delayMicroseconds(2);

   // Sets the trigPin on HIGH state for 10 micro seconds
   digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculating the distance
  distance= duration*0.034/2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(2000);
   //buzzer
  if (distance <= 50 && distance >= 0) {
      // Buzz
      digitalWrite(buzzPin, HIGH);
        if (distance <= 300 ){
     analogWrite(RightMotorSpeed,noSpeed);
    analogWrite(LeftMotorSpeed,noSpeed);
  }
    } else {
      // Don't buzz
      digitalWrite(buzzPin, LOW);
    }
 
}



BLYNK_WRITE(V1)
{
  int x = param[0].asInt();
  int y = param[1].asInt();
 /*
  Serial.print("x value is: ");
  Serial.println(x);
  Serial.print("y value is: ");
  Serial.println(y);
 */
  moveControl(x,y);
 
}
