#include "Arduino.h"
#include <SPI.h>
#include <Wire.h>
//#include <Adafruit_GFX.h>
#include <SSD1306Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS D4
#define TEMPERATURE_PRECISION 12

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
//Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
SSD1306Wire display(0x3c, D2, D1);  // ADDRESS, SDA, SCL
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)

OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

// arrays to hold device addresses
DeviceAddress insideThermometer, outsideThermometer, otherThermometer;
char tempString[16];
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

// function to print a device address
uint8_t findDevices(int pin)
{
  OneWire ow(pin);

  uint8_t address[8];
  uint8_t count = 0;


  if (ow.search(address))
  {
    Serial.print("\nuint8_t pin");
    Serial.print(pin, DEC);
    Serial.println("[][8] = {");
    do {
      count++;
      Serial.println("  {");
      for (uint8_t i = 0; i < 8; i++)
      {
        Serial.print("0x");
        if (address[i] < 0x10) Serial.print("0");
        Serial.print(address[i], HEX);
        if (i < 7) Serial.print(", ");
      }
      Serial.println("  },");
    } while (ow.search(address));

    Serial.println("};");
    Serial.print("// nr devices found: ");
    Serial.println(count);
  }

  return count;
}

void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    // zero pad the address if necessary
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
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

  // Clear the buffer
  Serial.println(F("clearing the buffer\n"));

  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!
  // display.display() is NOT necessary after every single drawing command,
  // unless that's what you want...rather, you can batch up a bunch of
  // drawing operations and then update the screen all at once by calling
  // display.display(). These examples demonstrate both approaches...


  // locate devices on the bus
  Serial.printf("Found %d devices\n",findDevices(ONE_WIRE_BUS) );
  // Start up the Temp library
  sensors.begin();

  display.displayOn();
  //display.drawXbm(100, 46 ,LOGO_HEIGHT, LOGO_WIDTH, logo_bmp);
  display.setFont(ArialMT_Plain_16);

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
  
  sensors.requestTemperatures(); 

  if ((!sensors.getAddress(insideThermometer, 0)))
  {
    Serial.println("Unable to find address for Device 0");
  }
  else
  {
    Serial.print("Device 0 Address: ");
    printAddress(insideThermometer);
    Serial.println();
    sensors.setResolution(insideThermometer, TEMPERATURE_PRECISION);
    Serial.printf("Device %d Resolution: %d  Temp: %f\n",0 , sensors.getResolution(insideThermometer),  sensors.getTempCByIndex(0));
  }
  

  if ((!sensors.getAddress(outsideThermometer, 1)))
  {
    Serial.println("Unable to find address for Device 1");
  }
  else
  {
    Serial.print("Device 1 Address: ");
    printAddress(outsideThermometer);
    Serial.println();
    sensors.setResolution(outsideThermometer, TEMPERATURE_PRECISION);
    Serial.printf("Device %d Resolution: %d  Temp: %f\n",1 , sensors.getResolution(outsideThermometer),  sensors.getTempCByIndex(1));

  }
  
 

  if ((!sensors.getAddress(otherThermometer, 1)))
  {
    Serial.println("Unable to find address for Device 2");
  }
  else
  {
    Serial.print("Device 2 Address: ");
    printAddress(otherThermometer);
    Serial.println();
    sensors.setResolution(otherThermometer, TEMPERATURE_PRECISION);
    Serial.printf("Device %d Resolution: %d  Temp: %f\n",2 , sensors.getResolution(otherThermometer),  sensors.getTempCByIndex(2));

  }

  display.clear();

  for (int i = 0; i < 3; i++)
  {
    sprintf(tempString ,"T%d=%5.1f   F", i, sensors.getTempFByIndex(i) );
    display.drawString(12,16*i,tempString);
  }
  display.display();
  
  delay(500);
  // method 2: search()
  // search() looks for the next device. Returns 1 if a new address has been
  // returned. A zero might mean that the bus is shorted, there are no devices,
  // or you have already retrieved all of them. It might be a good idea to
  // check the CRC to make sure you didn't get garbage. The order is
  // deterministic. You will always get the same devices in the same order
  //
  // Must be called before search()
  //oneWire.reset_search();
  // assigns the first address found to insideThermometer
  //if (!oneWire.search(insideThermometer)) Serial.println("Unable to find address for insideThermometer");
  // assigns the seconds address found to outsideThermometer
  //if (!oneWire.search(outsideThermometer)) Serial.println("Unable to find address for outsideThermometer");

  // show the addresses we found on the bus

}

