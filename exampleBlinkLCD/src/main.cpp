#include "Arduino.h"
#include <SPI.h>
#include <Wire.h>
//#include <Adafruit_GFX.h>
#include <SSD1306Wire.h>


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
//Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
SSD1306Wire display(0x3c, D2, D1);  // ADDRESS, SDA, SCL

#define NUMFLAKES     10 // Number of snowflakes in the animation example

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
static const unsigned char PROGMEM logo_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

void testDrawLine(){

  //display.displayOff();

  display.drawLine(0,0,64,64);
  //display.displayOn();
  display.display();
  delay(2000);


}

void setup()
{
  // initialize LED digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(9600);
  Serial.println(F("SSD1306 begin program"));

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.init()){ // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;) {
          Serial.println(F("SSD1306 allocation failed, looping"));
          delay(1000);
    }} // Don't proceed, loop forever
  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  Serial.println(F("display init went ok"));

  display.displayOn();
  Serial.println(F("initial display returned.\n"));

  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  Serial.println(F("clearing the buffer\n"));

  display.displayOff();

  // Draw a single pixel in white
  display.setPixel(10, 10);

  display.displayOn();

  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!
  display.display();
  delay(2000);
  // display.display() is NOT necessary after every single drawing command,
  // unless that's what you want...rather, you can batch up a bunch of
  // drawing operations and then update the screen all at once by calling
  // display.display(). These examples demonstrate both approaches...
  Serial.println(F("TestDrawLine\n"));

  testDrawLine();      // Draw many lines

//  testdrawrect();      // Draw rectangles (outlines)

//  testfillrect();      // Draw rectangles (filled)

//  testdrawcircle();    // Draw circles (outlines)

//  testfillcircle();    // Draw circles (filled)

//  testdrawroundrect(); // Draw rounded rectangles (outlines)

//  testfillroundrect(); // Draw rounded rectangles (filled)

//  testdrawtriangle();  // Draw triangles (outlines)
//
  //testfilltriangle();  // Draw triangles (filled)

//  testdrawchar();      // Draw characters of the default font

//  testdrawstyles();    // Draw 'stylized' characters

//  testscrolltext();    // Draw scrolling text

//  testdrawbitmap();    // Draw a small bitmap image

  // Invert and restore display, pausing in-between
//  display.invertDisplay(true);
//  delay(1000);
//  display.invertDisplay(false);
//  delay(1000);

//  testanimate(logo_bmp, LOGO_WIDTH, LOGO_HEIGHT); // Animate bitmaps

  
}



void loop()
{
  // turn the LED on (HIGH is the voltage level)
  digitalWrite(LED_BUILTIN, HIGH);
  // wait for a second
  delay(200);
  // turn the LED off by making the voltage LOW
  digitalWrite(LED_BUILTIN, LOW);
   // wait for a second
  delay(100);
  Serial.println(F("Got into loop, drawing rectangles"));
  delay(1000);
  display.fillRect(32,16,64,32);      // Draw rectangles (outlines)
  display.display();
  delay(2000);
  display.clear();

  display.drawCircle(60,30,15);
  display.fillCircle(99,30,10);
  display.display();
  delay(2000);
  display.clear();

}

