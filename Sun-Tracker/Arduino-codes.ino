#include <Servo.h>

Servo myServo;
int ldrLeft = A0;
int ldrRight = A1;
int angle = 90;  // Başlangıç açısı

void setup() {
  Serial.begin(9600);
  myServo.attach(9);  // Servo motor pin
  myServo.write(angle);
}

void loop() {
  int left = analogRead(ldrLeft);
  int right = analogRead(ldrRight);

  // Verileri ROS 2'ye gönder
  Serial.print(left);
  Serial.print(",");
  Serial.println(right);
  
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    if (command.startsWith("S:")) {
      int newAngle = command.substring(2).toInt();
      newAngle = constrain(newAngle, 0, 180);
      myServo.write(newAngle);
    }
  }

  delay(200);
}
