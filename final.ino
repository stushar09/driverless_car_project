#include <Servo.h>
int auto_pin=11;
int sw=12;
int motor = 9;
String readString;
Servo myservo_steering;

const int r_trigPin = 2;
const int r_echoPin = 3;

const int c_trigPin = 4;
const int c_echoPin = 5;

const int L_trigPin = 6;
const int L_echoPin = 7;

long r_duration;
int r_distance;

long c_duration;
int c_distance;

long L_duration;
int L_distance;


void setup() 
{
 
 Serial.begin(57600);
 myservo_steering.attach(10);
 pinMode(auto_pin,OUTPUT);
 pinMode(motor,OUTPUT);
 pinMode(sw,INPUT);
 
 pinMode(r_trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(r_echoPin, INPUT); // Sets the echoPin as an Input

pinMode(c_trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(c_echoPin, INPUT); // Sets the echoPin as an Input

pinMode(L_trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(L_echoPin, INPUT); // Sets the echoPin as an Input

Serial.println("ok");
myservo_steering.write(110);
readString= "";
}

void loop()
{
  sw=digitalRead(12);

if(sw==HIGH)
{
  digitalWrite(auto_pin, LOW);
  while(Serial.available())
  {
     if (Serial.available()>0)
     {
       char c=Serial.read();   
       readString+= c; 
      }
      if(readString == "Turn_Left")
             {
           myservo_steering.write(0);
           delay(50);
           // Clears the trigPin
digitalWrite(r_trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(r_trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(r_trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
r_duration = pulseIn(r_echoPin, HIGH);
// Calculating the distance
r_distance= r_duration*0.034/2;
// Prints the distance on the Serial Monitor
//Serial.print("r_Distance: ");
//Serial.println(r_distance);

// Clears the trigPin
digitalWrite(c_trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(c_trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(c_trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
c_duration = pulseIn(c_echoPin, HIGH);
// Calculating the distance
c_distance= c_duration*0.034/2;
// Prints the distance on the Serial Monitor
//Serial.print("c_Distance: ");
//Serial.println(c_distance);

// Clears the trigPin
digitalWrite(L_trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(L_trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(L_trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
L_duration = pulseIn(L_echoPin, HIGH);
// Calculating the distance
L_distance=L_duration*0.034/2;
// Prints the distance on the Serial Monitor
//Serial.print("L_Distance: ");
//Serial.println(L_distance);
delay(50);
if ((L_distance>60)||(r_distance>60)||(c_distance>60))
{
  for(int i=0;i<=150;i++)
  {
  analogWrite(motor, 255); delay(10); analogWrite(motor,i);
  }
           Serial.println("ok");
         readString= "";

}
else
{
  analogWrite(motor, 0);
   Serial.println("ok");
  readString= "";
  }
  readString= "";
        }

        if(readString  == "on_Track") 
        {
           myservo_steering.write(110);
           delay(50);
           // Clears the trigPin
digitalWrite(r_trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(r_trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(r_trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
r_duration = pulseIn(r_echoPin, HIGH);
// Calculating the distance
r_distance= r_duration*0.034/2;
// Prints the distance on the Serial Monitor
//Serial.print("r_Distance: ");
//Serial.println(r_distance);

// Clears the trigPin
digitalWrite(c_trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(c_trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(c_trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
c_duration = pulseIn(c_echoPin, HIGH);
// Calculating the distance
c_distance= c_duration*0.034/2;
// Prints the distance on the Serial Monitor
//Serial.print("c_Distance: ");
//Serial.println(c_distance);

// Clears the trigPin
digitalWrite(L_trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(L_trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(L_trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
L_duration = pulseIn(L_echoPin, HIGH);
// Calculating the distance
L_distance= L_duration*0.034/2;
// Prints the distance on the Serial Monitor
//Serial.print("L_Distance: ");
//Serial.println(L_distance);
if((L_distance<100)||(r_distance<100)||(c_distance<100))
{
  analogWrite(motor,0); 
}
if ((L_distance>100)&&(r_distance>100)&&(c_distance>100))
{
  for(int i=0;i<=150;i++)
  {
  analogWrite(motor, 255); delay(10); analogWrite(motor,i);
  }
  analogWrite(motor, 255); delay(10); analogWrite(motor,150);
           //Serial.println("ok");
         readString= "";

}
else
{
  analogWrite(motor, 0);
  }
        }

        if(readString  == "Turn_Right") 
              {
           myservo_steering.write(180);
           delay(50);
           // Clears the trigPin
digitalWrite(r_trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(r_trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(r_trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
r_duration = pulseIn(r_echoPin, HIGH);
// Calculating the distance
r_distance= r_duration*0.034/2;
// Prints the distance on the Serial Monitor
//Serial.print("r_Distance: ");
//Serial.println(r_distance);

// Clears the trigPin
digitalWrite(c_trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(c_trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(c_trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
c_duration = pulseIn(c_echoPin, HIGH);
// Calculating the distance
c_distance= c_duration*0.034/2;
// Prints the distance on the Serial Monitor
//Serial.print("c_Distance: ");
//Serial.println(c_distance);

// Clears the trigPin
digitalWrite(L_trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(L_trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(L_trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
L_duration = pulseIn(L_echoPin, HIGH);
// Calculating the distance
L_distance= L_duration*0.034/2;
// Prints the distance on the Serial Monitor
//Serial.print("L_Distance: ");
//Serial.println(L_distance);
if((L_distance<100)||(r_distance<100)||(c_distance<100))
{
  analogWrite(motor,0); 
}
if ((L_distance>100)&&(r_distance>100)&&(c_distance>100))
{
  for(int i=0;i<=150;i++)
  {
  analogWrite(motor, 255); delay(10); analogWrite(motor,i);
  }
  analogWrite(motor, 255); delay(10); analogWrite(motor,150);
           //Serial.println("ok");
         readString= "";

}
else
{
  analogWrite(motor, 0);
  
  }      
              }
  if(readString  == "I_dont_see_the_line") 
        {
          analogWrite(motor,0);
                 // Serial.println("ok");
         readString= "";
        }
    }
}
else
{
  digitalWrite(auto_pin,HIGH);
  }
}
