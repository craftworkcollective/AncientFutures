// A basic everyday NeoPixel strip test program.

// NEOPIXEL BEST PRACTICES for most reliable operation:
// - Add 1000 uF CAPACITOR between NeoPixel strip's + and - connections.
// - MINIMIZE WIRING LENGTH between microcontroller board and first pixel.
// - NeoPixel strip's DATA-IN should pass through a 300-500 OHM RESISTOR.
// - AVOID connecting NeoPixels on a LIVE CIRCUIT. If you must, ALWAYS
//   connect GROUND (-) first, then +, then data.
// - When using a 3.3V microcontroller with a 5V-powered NeoPixel strip,
//   a LOGIC-LEVEL CONVERTER on the data line is STRONGLY RECOMMENDED.
// (Skipping these may work OK on your workbench but can fail in the field)

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN    10

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 300

#define BRIGHTNESS 50

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)


// setup() function -- runs once at startup --------------------------------

void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(BRIGHTNESS); // Set BRIGHTNESS to about 1/5 (max = 255)
}


// loop() function -- runs repeatedly as long as board is on ---------------

void loop() {
  // Fill along the length of the strip in various colors...
  //colorWipe(strip.Color(255,192,203), BRIGHTNESS); // Red
  //colorWipe(strip.Color(  0, 255,   0), BRIGHTNESS); // Green
  //colorWipe(strip.Color(  0,   0, 255), BRIGHTNESS); // Blue

  // Do a theater marquee effect in various colors...
  //theaterChase(strip.Color(127, 127, 127), BRIGHTNESS); // White, half brightness
  //theaterChase(strip.Color(127,   0,   0), BRIGHTNESS); // Red, half brightness
  //theaterChase(strip.Color(  0,   0, 127), BRIGHTNESS); // Blue, half brightness

 // rainbow(10);             // Flowing rainbow cycle along the whole strip
  //theaterChaseRainbow(50); // Rainbow-enhanced theaterChase variant

 //   twoColorGradient(strip.Color(100, 0, 0), strip.Color(255,192,203), 10); // Red to Blue

//twoColorGradientHSV(0, 16000, 10); // Red (0) to Blue (16000)
//twoColorGradientHSV(0, 43690, 10); // Red to Blue

 //twoColorGradientRGB(strip.Color(255, 0, 0), strip.Color(255,192,203), 20); // Red to Blue

 twoColorGradientRGB(strip.Color(255, 0, 0), strip.Color(0,0,255), 20); // Red to Blue

}

void twoColorGradientRGB(uint32_t color1, uint32_t color2, int wait) {
  const float gamma = 2.2;  // Gamma correction factor

  for (int i = 0; i <= 255; i++) {  // Forward transition
    float t = i / 255.0;  // Normalize transition step

    // Extract and gamma-correct RGB values
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

    uint32_t blendedColor = strip.Color(r * 255, g * 255, b * 255);

    for (int j = 0; j < strip.numPixels(); j++) {
      strip.setPixelColor(j, blendedColor);
    }
    strip.show();
    delay(wait);
  }

  for (int i = 255; i >= 0; i--) {  // Reverse transition
    float t = i / 255.0;

    float r1 = pow(((color1 >> 16) & 0xFF) / 255.0, gamma);
    float g1 = pow(((color1 >> 8) & 0xFF) / 255.0, gamma);
    float b1 = pow((color1 & 0xFF) / 255.0, gamma);

    float r2 = pow(((color2 >> 16) & 0xFF) / 255.0, gamma);
    float g2 = pow(((color2 >> 8) & 0xFF) / 255.0, gamma);
    float b2 = pow((color2 & 0xFF) / 255.0, gamma);

    float r = pow((1 - t) * r1 + t * r2, 1 / gamma);
    float g = pow((1 - t) * g1 + t * g2, 1 / gamma);
    float b = pow((1 - t) * b1 + t * b2, 1 / gamma);

    uint32_t blendedColor = strip.Color(r * 255, g * 255, b * 255);

    for (int j = 0; j < strip.numPixels(); j++) {
      strip.setPixelColor(j, blendedColor);
    }
    strip.show();
    delay(wait);
  }
}


void twoColorGradientHSV(uint16_t hue1, uint16_t hue2, int wait) {
  for (int i = 0; i <= 255; i++) {  // Transition forward
    uint16_t hue = map(i, 0, 255, hue1, hue2);
    for (int j = 0; j < strip.numPixels(); j++) {
      strip.setPixelColor(j, strip.ColorHSV(hue, 255, 255)); // Full saturation and brightness
    }
    strip.show();
    delay(wait);
  }

  for (int i = 255; i >= 0; i--) {  // Transition backward
    uint16_t hue = map(i, 0, 255, hue1, hue2);
    for (int j = 0; j < strip.numPixels(); j++) {
      strip.setPixelColor(j, strip.ColorHSV(hue, 255, 255));
    }
    strip.show();
    delay(wait);
  }
}


void twoColorGradient(uint32_t color1, uint32_t color2, int wait) {
  for (int i = 0; i < 256; i++) { // 256 steps of blending
    for (int j = 0; j < strip.numPixels(); j++) {
      // Interpolate between the two colors
      uint8_t r = map(i, 0, 255, (color1 >> 16) & 0xFF, (color2 >> 16) & 0xFF);
      uint8_t g = map(i, 0, 255, (color1 >> 8) & 0xFF, (color2 >> 8) & 0xFF);
      uint8_t b = map(i, 0, 255, color1 & 0xFF, color2 & 0xFF);

      strip.setPixelColor(j, strip.Color(r, g, b));
    }
    strip.show();
    delay(wait);
  }
  // Reverse animation back to color1
  for (int i = 255; i >= 0; i--) {
    for (int j = 0; j < strip.numPixels(); j++) {
      uint8_t r = map(i, 0, 255, (color1 >> 16) & 0xFF, (color2 >> 16) & 0xFF);
      uint8_t g = map(i, 0, 255, (color1 >> 8) & 0xFF, (color2 >> 8) & 0xFF);
      uint8_t b = map(i, 0, 255, color1 & 0xFF, color2 & 0xFF);

      strip.setPixelColor(j, strip.Color(r, g, b));
    }
    strip.show();
    delay(wait);
  }
}



// Some functions of our own for creating animated effects -----------------

// Fill strip pixels one after another with a color. Strip is NOT cleared
// first; anything there will be covered pixel by pixel. Pass in color
// (as a single 'packed' 32-bit value, which you can get by calling
// strip.Color(red, green, blue) as shown in the loop() function above),
// and a delay time (in milliseconds) between pixels.
void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

// Theater-marquee-style chasing lights. Pass in a color (32-bit value,
// a la strip.Color(r,g,b) as mentioned above), and a delay time (in ms)
// between frames.
void theaterChase(uint32_t color, int wait) {
  for(int a=0; a<10; a++) {  // Repeat 10 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show(); // Update strip with new contents
      delay(wait);  // Pause for a moment
    }
  }
}

// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void rainbow(int wait) {
  // Hue of first pixel runs 5 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
  // means we'll make 5*65536/256 = 1280 passes through this loop:
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    // strip.rainbow() can take a single argument (first pixel hue) or
    // optionally a few extras: number of rainbow repetitions (default 1),
    // saturation and value (brightness) (both 0-255, similar to the
    // ColorHSV() function, default 255), and a true/false flag for whether
    // to apply gamma correction to provide 'truer' colors (default true).
    strip.rainbow(firstPixelHue);
    // Above line is equivalent to:
    // strip.rainbow(firstPixelHue, 1, 255, 255, true);
    strip.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}

// Rainbow-enhanced theater marquee. Pass delay time (in ms) between frames.
void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;     // First pixel starts at red (hue 0)
  for(int a=0; a<30; a++) {  // Repeat 30 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in increments of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        // hue of pixel 'c' is offset by an amount to make one full
        // revolution of the color wheel (range 65536) along the length
        // of the strip (strip.numPixels() steps):
        int      hue   = firstPixelHue + c * 65536L / strip.numPixels();
        uint32_t color = strip.gamma32(strip.ColorHSV(hue)); // hue -> RGB
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show();                // Update strip with new contents
      delay(wait);                 // Pause for a moment
      firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
    }
  }
}
