# Air-Quality-Sensors-Project-
Detecting CO2, Temperature, Humidity, and the PM2.5 dust concentrations. This data displays graphic and numerical data on portable devices and on an OLED display. 

Code Descriptions:

COMBINED_SENSORS_DISPLAYED.ino: Obtains the CO2 levels, humidity, and temperature from the sensors and displays it on the OLED display. It publishes the data on the Particle Console and graphs it on an IoT Analytics platform called Thingspeak, as an integrated Particle Webhook.  

ARDUINO_DUST_SENSOR.ino: This is open source code written by Zuyang @HUSK. I wanted to add this to show you what I used to test the Arduino before moving on to the Particle Photon. 

THE_OLED_TEST.ino: This tests the display board by displaying funky images of random patterns and the Adafruit logo. This can be found through Arduino: “Sketch” menu: Sketch→Include Library→Manage Libraries… Or you can just copy and paste this code. :) 

