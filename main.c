#include <Servo.h>
Servo servo;
int trigPin = 6;
int echoPin = 7;
long duration, dist, average;
int flag=0; //button flag
long aver[3];

void setup() {
	servo.attach(5);
	pinMode(3,INPUT);
	pinMode(trigPin, OUTPUT);
	pinMode(echoPin, INPUT);
	servo.write(180);
}

void measure() {
	digitalWrite(trigPin, LOW);
	delayMicroseconds(5);
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(15);
	digitalWrite(trigPin, LOW);
	pinMode(echoPin, INPUT);
	duration = pulseIn(echoPin, HIGH);
	dist = (duration/2) / 29.1;
}

void loop() {

}
