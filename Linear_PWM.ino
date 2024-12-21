#include <Wire.h>
#include <BH1750.h>

BH1750 lightMeter;

#define IN1 2 // Chân D2 (chọn chân hỗ trợ PWM)
#define SUPPLY_VOLTAGE 12.0 // Điện áp cấp cho LED (5V)
#define LED_RESISTANCE 220 // Điện trở bóng đèn (đơn vị: ohm)

// Biến lưu giá trị PWM
float current = 0;
int pwmValue = 0;
int step = 5;
bool increasing = true;

void setup() {
  // Cài đặt chế độ chân điều khiển
  pinMode(IN1, OUTPUT);

  Wire.begin();
  lightMeter.begin();
  Serial.begin(9600);
} 

void loop() {
  // Tạo tín hiệu PWM để thay đổi độ sáng bóng đèn
  analogWrite(IN1, pwmValue);

  // Điều chỉnh giá trị PWM tăng hoặc giảm
  if (increasing) {
    pwmValue += step; // Tăng dần
    if (pwmValue >= 255) {
      increasing = false;
    }
  } else {
    pwmValue -= step; // Giảm dần
    if (pwmValue <= 0) {
      increasing = true;
    }
  }
  
  float lux = lightMeter.readLightLevel();
  current = (SUPPLY_VOLTAGE * pwmValue) / (LED_RESISTANCE * 255);

  //Serial.print("Lux: ");
  Serial.print(lux * 2.5);
  //Serial.print(" Current: ");
  Serial.print(" ");
  Serial.println(current * 1000000);

  delay(100);
}
