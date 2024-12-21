#include <Wire.h>
#include <BH1750.h>

BH1750 lightMeter;

void setup() {
  Serial.begin(9600);         // Bật giao tiếp Serial
  Wire.begin();               // Khởi tạo giao tiếp I2C
  lightMeter.begin();         // Khởi động cảm biến BH1750
}

void loop() {
  // Chuyển sang chế độ đo One-Time High Resolution Mode
  //lightMeter.setMTreg(31);
  lightMeter.configure(BH1750::ONE_TIME_HIGH_RES_MODE);

  unsigned long startTime = millis();  // Ghi lại thời gian bắt đầu phép đo
  
  // Chờ cảm biến hoàn thành phép đo (theo thời gian mặc định là 120ms)
  while (!lightMeter.measurementReady()) {
    delay(1);
  }

  unsigned long endTime = millis();    // Ghi lại thời gian khi nhận được kết quả

  // Đọc giá trị ánh sáng từ cảm biến
  float lux = lightMeter.readLightLevel();

  // Tính toán thời gian đo
  unsigned long measurementTime = endTime - startTime;

  // In kết quả ra Serial Monitor
  Serial.print("Lux: ");
  Serial.print(lux);
  Serial.print(" | Measurement Time: ");
  Serial.print(measurementTime);
  Serial.println(" ms");

  delay(500);
}
