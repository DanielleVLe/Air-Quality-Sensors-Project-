# Air-Quality-Sensors-Project-
Detecting CO2, Temperature, Humidity, and the PM2.5 dust concentrations. This data displays graphic and numerical data on portable devices and on an OLED display. 

Code Descriptions:

COMBINED_SENSORS_DISPLAYED.ino: Obtains the CO2 levels, humidity, and temperature from the sensors and displays it on the OLED display. It publishes the data on the Particle Console and graphs it on an IoT Analytics platform called Thingspeak, as an integrated Particle Webhook.  

ARDUINO_DUST_SENSOR.ino: This is open source code written by Zuyang @HUSK. I wanted to add this to show you what I used to test the Arduino before moving on to the Particle Photon. 

PHOTON_DUST_SENSOR_PMS1003: When I applied the Arduino code into the Particle Build Platform, there weer a few modifications I made to make it work.

1. Added library for Serial Communication. 
Code: #include <ParticleSoftSerial.h> 

2. Error found in line 32: invalid conversion from 'int' to 'char*' [-fpermissive]
Solution: Changed the hexadecimal (0x42) to an ASCII Character as a string ("B") 
Code: if(PMSerial.find("B")){    

3. Error found in line 33: invalid conversion from 'unsigned char*' to 'char*' [-fpermissive]
Solution: Casted the code to force the data type to be converted into another. 
Code:  PMSerial.readBytes((char*)buf,LENG);

THE_OLED_TEST.ino: This tests the display board by displaying funky images of random patterns and the Adafruit logo. This can be found through Arduino: “Sketch” menu: Sketch→Include Library→Manage Libraries… Or you can just copy and paste this code. :) 

