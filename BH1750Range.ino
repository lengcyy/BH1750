#include <Wire.h>
#include <BH1750.h>

BH1750 lightMeter;

// Variables to calculate sensitivity and response time
float minLux = 10000;
float maxLux = 0;

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
  if(lux<minLux)minLux=lux;
  if(lux>maxLux)maxLux=lux;
  
  
  // Print light level, sensitivity, and minimum sensitivity for plotting
  Serial.print("Lux: ");
  Serial.print(lux); // Light level (lux)
  Serial.print(" | MinLux: ");
  Serial.print(minLux); // Light level (lux)
  Serial.print(" | MaxLux: ");
  Serial.println(maxLux); // Light level (lux)

  // Update the lastLux variable for the next loop

  delay(500); // Adjust the sampling interval if needed
}
