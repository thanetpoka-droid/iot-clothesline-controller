#include <Servo.h>

int rainPin = A0;   // Rain Sensor (Analog)
int lightPin = D1;  // LDR Sensor (Analog)

int rainValue = 0;
int lightValue = 0;

Servo myServo;

void setup() {
  Serial.begin(115200);
  myServo.attach(D3);
  myServo.write(0); // เริ่มต้น Servo = 0°
  Serial.println("=== ระบบตรวจสอบฝน + แสง เริ่มทำงาน ===");
}

void loop() {
  // อ่านค่าจากเซ็นเซอร์
  rainValue = analogRead(rainPin);         
  lightValue = 1023 - analogRead(lightPin); 

  Serial.print("Rain Sensor: ");
  Serial.print(rainValue);
  Serial.print(" | Light Sensor: ");
  Serial.println(lightValue);

  // -------------------------------
  // เงื่อนไขการทำงาน
  // -------------------------------
  if (lightValue < 300) {
    // 🌙 กลางคืน → Servo ต้องไปที่ 180° เสมอ
    myServo.write(0);
    Serial.println("🌙 กลางคืน -> Servo = 0°");
  } 
  else {
    // ☀️ สว่าง → เช็คฝน
    if (rainValue <= 950) {
      // ฝนตก
      myServo.write(0);
      Serial.println("🌧️ ฝนตก + สว่าง -> Servo = 0°");
    } 
    else {
      // ฝนหยุด
      myServo.write(180);
      Serial.println("☀️ ฝนหยุด + สว่าง -> Servo = 180°");
    }
  }

  delay(3000); // ดีเลย์ 2 วินาที
}
