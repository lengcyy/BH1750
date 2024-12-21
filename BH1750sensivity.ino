#include <Wire.h>
#include <BH1750.h>

BH1750 lightMeter;

// Variables to calculate sensitivity
float lastLux = 0;         // Previous light level
float sensitivity = 0;     // Sensor sensitivity
float minSensitivity = 99999; // Minimum sensitivity (initialize with a large value)

void setup() {
  Serial.begin(9600);

  // Initialize the I2C bus
  Wire.begin();

  // Initialize the BH1750 sensor
  lightMeter.begin();

  Serial.println(F("BH1750 Sensitivity Measurement Begin"));
}

void loop() {
  float lux = lightMeter.readLightLevel();

  // Calculate sensitivity (change in light level)
  sensitivity = lux - lastLux;

  // Update minimum sensitivity (if sensitivity is non-zero and smaller than current minSensitivity)
  if (abs(sensitivity) > 0 && abs(sensitivity) < minSensitivity) {
    minSensitivity = abs(sensitivity);
  }

  // Print light level, sensitivity, and minimum sensitivity
  Serial.print("Lux: ");
  Serial.print(lux); // Light level (lux)

  Serial.print(" | Sensitivity: ");
  Serial.print(abs(sensitivity)); // Sensitivity

  Serial.print(" | Min Sensitivity: ");
  Serial.println(minSensitivity); // Minimum sensitivity

  // Update the lastLux variable for the next loop
  lastLux = lux;

  delay(500); // Adjust the sampling interval if needed
}
