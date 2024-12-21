#include <Wire.h>
#include <BH1750.h>

BH1750 lightMeter;

// Thông số cho bộ lọc trung bình động
#define WINDOW_SIZE 5           // Kích thước cửa sổ lọc
float luxBuffer[WINDOW_SIZE];   // Mảng lưu trữ các giá trị lux
int bufferIndex = 0;            // Vị trí hiện tại trong bộ đệm
bool bufferFilled = false;      // Kiểm tra xem bộ đệm đã đầy hay chưa

void setup() {
  Wire.begin();
  lightMeter.begin();
  Serial.begin(9600);

  // Khởi tạo bộ đệm
  for (int i = 0; i < WINDOW_SIZE; i++) {
    luxBuffer[i] = 0.0;
  }
}

void loop() {
  // Đọc giá trị ánh sáng từ cảm biến BH1750
  float rawLux = lightMeter.readLightLevel();

  // Cập nhật bộ đệm với giá trị mới
  luxBuffer[bufferIndex] = rawLux;
  bufferIndex = (bufferIndex + 1) % WINDOW_SIZE;
  if (bufferIndex == 0) {
    bufferFilled = true;
  }

  // Tính giá trị trung bình
  float filteredLux = 0.0;
  int count = bufferFilled ? WINDOW_SIZE : bufferIndex;
  for (int i = 0; i < count; i++) {
    filteredLux += luxBuffer[i];
  }
  filteredLux /= count;

  // Hiển thị giá trị
  //Serial.print("Raw Lux: ");
  Serial.print(rawLux);
  //Serial.print(" | Filtered Lux: ");
  Serial.print(" ");
  Serial.println(filteredLux);

  delay(100); // Chờ 100ms trước khi lấy giá trị tiếp theo
}
