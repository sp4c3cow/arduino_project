#include <Servo.h> // використовуємо бібліотеку для роботи з сервоприводом
Servo servo; // оголошуємо змінну servo типу Servo
int trigPin = 6; // Триггер
int echoPin = 7; // Ехо
long duration, dist, average; // змінні
int flag=0; // button flag
long aver[3]; // Масив для розрахунку середнього арифметичного

void setup() {
	servo.attach(5); // серво на 5 порту
	pinMode(3,INPUT); // кнопка
	pinMode(trigPin, OUTPUT); // пін тригера в режимі виходу
	pinMode(echoPin, INPUT); // пін відлуння в режимі входу
	servo.write(180); // при підключенні харчування поставити кришку відкритою
}

void measure() { // блок, що вимірює відстань
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
		servo.write(180); // відкрити кришку
		delay(1000); // почекати 3.5 секунди
		flag=1; // ставимо прапорець, що кнопка натиснута
	}

	if (digitalRead(3)==0 && flag==1) {
		servo.write(3); // закрити кришку
		delay(1000); // почекати
		flag=0; // знімаємо прапорець 
	}

	if (flag==0) { // заповнюємо масив трьома вимірами
		for (int i=0;i<=2;i++) { 
			measure(); // вимірюємо відстань, отримуємо dist
			aver[i]=dist; // присвоюємо значення dist елементу масиву з номером i
			delay(50); // рекомендована затримка між вимірами
		}
		dist=(aver[0]+aver[1]+aver[2])/3; // розрахунок середнього арифметичного з 3-х вимірів 
	}

	if (dist>10 && dist<30 && flag==0) { // якщо рука від 10 до 30 см, то кнопка не була натиснута
		servo.write(180);  // відкрити кришку
		delay(10000); // почекати 10 секунд
		servo.write(3); // закрити кришку
		delay(1000); // почекати секунду
	}

	if (dist>30 && dist<60 && flag==0) { // якщо рука від 30 до 60 см, то кнопка не була натиснута
		servo.write(180); // відкрити кришку
		delay(2500); // почекати 2,5 секунд
		servo.write(3); // закрити кришку
		delay(1000); // почекати секунду
	}

}
