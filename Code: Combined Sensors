// This #include statement was automatically added by the Particle IDE.
//#include <Adafruit_SSD1306.h>

// This #include statement was automatically added by the Particle IDE.
//#include <Adafruit_GFX.h>

// This #include statement was automatically added by the Particle IDE.
#include <Adafruit_DHT.h>
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"

#define ADDR_6713 0x15 // default I2C slave address

#define DHTPIN 6
#define DHTTYPE DHT22 // default the DHT pins 
//#include "Adafruit_DHT/Adafruit_DHT.h"

#define OLED_DC     D3 // use hardware SPI
#define OLED_CS     D4
#define OLED_RESET  D5
//#define OLED_CLK    A3
//#define OLED_MOSI   A5
Adafruit_SSD1306 display(OLED_DC, OLED_RESET, OLED_CS);
int data [4];

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16

int CO2ppmValue;
int temperature;
int humidity;

DHT dht(DHTPIN, DHTTYPE);


void setup() 
{
    dht.begin();
    Wire.begin ();
    display.clearDisplay();
    Serial.begin(9600);
    Serial.println("Application Note AN161_ardunio_T6713_I2C");
    
}

int readC02()
{
    Wire.beginTransmission(ADDR_6713);
    Wire.write(0x04); Wire.write(0x13); Wire.write(0x8B);
    Wire.write(0x00); Wire.write(0x01);
    Wire.endTransmission();
    delay(2000);
    Wire.requestFrom(ADDR_6713, 4); 
    data[0] = Wire.read();
    data[1] = Wire.read();
    data[2] = Wire.read();
    data[3] = Wire.read();
    
    CO2ppmValue = ((data[2] * 0xFF ) + data[3]);
}


void loop() {
    int co2Value = readC02(); 
    
    //Display Settings 
    display.begin(SSD1306_SWITCHCAPVCC);
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    
    //Display temperature  
    display.setCursor(25, 10);
    display.println("Temp: " + String(temperature) + "*C" );
    
    //Display humidity 
    display.setCursor(25, 25);
    display.println("Humidity: " + String(humidity) + "%");
  
    //Display c02 
    display.setCursor(25, 40);
    display.println("CO2: " + String(co2Value) + " ppm");

    display.display();
   
    //Publish console 
    Particle.publish("gas", String(co2Value) + " ppm");
    Particle.publish ("gas",String(co2Value), PRIVATE);
    delay(2000);
    
    
    temperature = dht.getTempCelcius();
    humidity = dht.getHumidity();

  
    Particle.publish("temp", String(temperature) + " °C");
    Particle.publish("humidity", String(humidity) + "%");
    delay(2000);

} 
