#include <Wire.h>
#include <BH1750.h>

BH1750 lightMeter;

// Variables to calculate sensitivity and response time
float lastLux = 0;         // Previous light level
float sensitivity = 0;     // Sensor sensitivity
float minSensitivity = 99999; // Minimum sensitivity (initialize with a large value)
unsigned long startTime = 0;  // Start time of light level change
bool isResponding = false;    // Flag to track response measurement
const float THRESHOLD = 10;   // Change threshold to detect response (lux)

// Variables for frequency response
unsigned long frequencyStartTime = 0; // Start time for frequency calculation
int responseCount = 0;                // Count of significant light changes

void setup() {
  Serial.begin(9600);

  // Initialize the I2C bus
  Wire.begin();

  // Initialize the BH1750 sensor
  lightMeter.begin();

  Serial.println(F("BH1750 Test begin"));

  // Inform the user how to use the Serial Plotter
  Serial.println("Open Serial Plotter (Tools > Serial Plotter) to view the graph.");
}

void loop() {
  float lux = lightMeter.readLightLevel();

  // Calculate sensitivity (change in light level)
  sensitivity = lux - lastLux;

  // Update minimum sensitivity (if sensitivity is non-zero and smaller than current minSensitivity)
  if (abs(sensitivity) > 0 && abs(sensitivity) < minSensitivity) {
    minSensitivity = abs(sensitivity);
  }

  // Check if the light level changes significantly
  if (abs(sensitivity) > THRESHOLD) {
    if (!isResponding) {
      // Start measuring response time
      startTime = millis();
      isResponding = true;
      Serial.println("Significant light change detected. Measuring response time...");
    }
    // Increment response count for frequency calculation
    responseCount++;
  }

  // Check if the light level has stabilized
  
  // Print light level, sensitivity, and minimum sensitivity for plotting
  Serial.print("Lux: ");
  Serial.print(lux); // Light level (lux)

  Serial.print(" | Difference: ");
  Serial.print(abs(sensitivity)); // Sensitivity

  Serial.print(" | Sensitivity: ");
  Serial.println(minSensitivity); // Minimum sensitivity

  // Update the lastLux variable for the next loop
  lastLux = lux;

  delay(500); // Adjust the sampling interval if needed
}
