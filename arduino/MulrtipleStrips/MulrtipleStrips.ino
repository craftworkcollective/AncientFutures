#include <Adafruit_NeoPixel.h>

#define NUM_STRIPS 5
#define NUM_LEDS 60  // Number of LEDs per strip

// Define pins for each strip
const int LED_PINS[NUM_STRIPS] = { 6, 7, 8, 9, 10 };

// Create an array of NeoPixel objects for each strip
Adafruit_NeoPixel strips[NUM_STRIPS] = {
  Adafruit_NeoPixel(NUM_LEDS, LED_PINS[0], NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUM_LEDS, LED_PINS[1], NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUM_LEDS, LED_PINS[2], NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUM_LEDS, LED_PINS[3], NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUM_LEDS, LED_PINS[4], NEO_GRB + NEO_KHZ800)
};

// Define color pairs for each strip
uint32_t colorStart[NUM_STRIPS] = {
  Adafruit_NeoPixel::Color(255, 192, 203),  // Pink
  Adafruit_NeoPixel::Color(124, 252, 0),    // Green
  Adafruit_NeoPixel::Color(0, 0, 255),      // Blue
  Adafruit_NeoPixel::Color(255, 255, 0),    // Yellow
  Adafruit_NeoPixel::Color(255, 255, 255)   // White
};

uint32_t colorEnd[NUM_STRIPS] = {
  Adafruit_NeoPixel::Color(30, 144, 255),   // Blue
  Adafruit_NeoPixel::Color(255, 0, 0),      // Red
  Adafruit_NeoPixel::Color(144, 238, 144),  // Green
  Adafruit_NeoPixel::Color(0, 255, 255),    // Cyan
  Adafruit_NeoPixel::Color(255, 165, 0)     // Orange
};

const float gamma = 2.2;  // Gamma correction factor

void setup() {
  for (int i = 0; i < NUM_STRIPS; i++) {
    strips[i].begin();
    strips[i].show();  // Initialize all pixels to 'off'
  }
}

void loop() {

  // --- GRADIENTS --- // 
  for (int step = 0; step <= 255; step++) {  // Forward transition
    for (int i = 0; i < NUM_STRIPS; i++) {
      uint32_t blendedColor = interpolateColors(colorStart[i], colorEnd[i], step / 255.0);
      for (int j = 0; j < NUM_LEDS; j++) {
        strips[i].setPixelColor(j, blendedColor);
      }
      strips[i].show();
    }
    delay(10);  // Adjust speed of animation
  }

  for (int step = 255; step >= 0; step--) {  // Reverse transition
    for (int i = 0; i < NUM_STRIPS; i++) {
      uint32_t blendedColor = interpolateColors(colorStart[i], colorEnd[i], step / 255.0);
      for (int j = 0; j < NUM_LEDS; j++) {
        strips[i].setPixelColor(j, blendedColor);
      }
      strips[i].show();
    }
    delay(10);  // Adjust speed of animation
  }

   // --- RAINBOW --- // 
  rainbowAllStrips(DELAY_TIME);
}



// Rainbow cycle for all strips
void rainbowAllStrips(int wait) {
  for (long firstPixelHue = 0; firstPixelHue < 5 * 65536; firstPixelHue += 256) {
    for (int i = 0; i < NUM_STRIPS; i++) {
      strips[i].rainbow(firstPixelHue + (i * 5000));  // Offset hue per strip
      strips[i].show();
    }
    delay(wait);
  }
}

// Function to blend between two colors with gamma correction
uint32_t interpolateColors(uint32_t color1, uint32_t color2, float t) {
  // Extract RGB components
  float r1 = pow(((color1 >> 16) & 0xFF) / 255.0, gamma);
  float g1 = pow(((color1 >> 8) & 0xFF) / 255.0, gamma);
  float b1 = pow((color1 & 0xFF) / 255.0, gamma);

  float r2 = pow(((color2 >> 16) & 0xFF) / 255.0, gamma);
  float g2 = pow(((color2 >> 8) & 0xFF) / 255.0, gamma);
  float b2 = pow((color2 & 0xFF) / 255.0, gamma);

  // Interpolate in gamma-corrected space
  float r = pow((1 - t) * r1 + t * r2, 1 / gamma);
  float g = pow((1 - t) * g1 + t * g2, 1 / gamma);
  float b = pow((1 - t) * b1 + t * b2, 1 / gamma);

  return Adafruit_NeoPixel::Color(r * 255, g * 255, b * 255);
}
