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

	if (digitalRead(3)==1 && flag==0) {
		servo.write(180);
		delay(1000);
		flag=1;
	}

	if (digitalRead(3)==0 && flag==1) {
		servo.write(3);
		delay(1000);
		flag=0;
	}

	if (flag==0) {
		for (int i=0;i<=2;i++) {
			measure();
			aver[i]=dist;
			delay(50);
		}
		dist=(aver[0]+aver[1]+aver[2])/3;
	}

	if (dist>10 && dist<30 && flag==0) {
		servo.write(180);
		delay(10000);
		servo.write(3);
		delay(1000);
	}

	if (dist>30 && dist<60 && flag==0) {
		servo.write(180);
		delay(2500);
		servo.write(3);
		delay(1000);
	}

}
