#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <Servo.h>

// Erstellen einer Instanz des Motorschields
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *motor1 = AFMS.getMotor(1);
Adafruit_DCMotor *motor2 = AFMS.getMotor(2);
Adafruit_DCMotor *motor3 = AFMS.getMotor(3);
Adafruit_DCMotor *motor4 = AFMS.getMotor(4);  

// Servo Objekte 
Servo servo1;
Servo servo2;
Servo servo3;

void setup() {
  // Initialisieren des Motorschields
  AFMS.begin();

  // Anfangsgeschwindigkeit setzen (von 0 bis 255)
  motor1->setSpeed(100);
  motor2->setSpeed(100);
  motor3->setSpeed(100);
  motor4->setSpeed(100);

  // Anfangsrichtung setzen
  motor1->run(FORWARD);  
  motor2->run(FORWARD);
  motor3->run(FORWARD);
  motor4->run(FORWARD);
  
  // Servo Pins definieren
  servo1.attach(10);
  servo2.attach(9);
  servo3.attach(3);

  // Servo auf 0 Grad setzen
  servo1.write(0);    
  servo2.write(0);
  servo3.write(0);
}

void loop() {
  servo1.write(180);  // Servo auf 180 Grad setzen
  servo2.write(180);
  servo3.write(180);
  delay(5000);        // 5 Sekunden warten
  
  servo1.write(0);    // Servo zurück auf 0 Grad setzen
  servo2.write(0);
  servo3.write(0);
  delay(5000);        // 5 Sekunden warten
  
  // Die DC-Motoren drehen durchgehend
}
