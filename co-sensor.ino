// This #include statement was automatically added by the Particle IDE.
#include <SparkFunPhant.h>

// This #include statement was automatically added by the Particle IDE.
//This library is used to push data to the data.sparkfun.com server.
#include "SparkFunPhant/SparkFunPhant.h"
#include "math.h" 

//This code was written by Jennifer Fox <jenfoxbot@gmail.com>
/*
 * ----------------------------------------------------------------------------
 * "THE Coffee-WARE LICENSE" (Revision 42):
 * <jenfoxbot@gmail.com>  wrote this file.  As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a coffee in return.
 * ----------------------------------------------------------------------------
 */

//Variables to push data to data.sparkfun.com host -- Change publicKey[] and privateKey[]
const char server[] = "data.sparkfun.com"; // Phant destination server
const char publicKey[] = "INSERT_PUBLIC_KEY_HERE"; // Phant public key
const char privateKey[] = "INSERT_PRIVATE_KEY_HERE"; // Phant private key

Phant phant(server, publicKey, privateKey); // Create a Phant object

const unsigned long postingRate = 20000; //Post rate to data.sparkfun.com (time in milliseconds)
unsigned long lastPost = millis(); //Keeps track of posting rate


//Define analog pins on Photon to use for sensors
const int CO = A2;

int CORaw;
int COppm;

//Set safety threshold levels for hazardous gas
const int COthresh = 50;


//Set variables for CO sensor (MQ7) voltage cycle
unsigned long startMillis;        
unsigned long switchTimeMillis;
const int CO_5V_Interval = 60000; //60s for 5V interval
const int CO_1_5V_Interval = 90000; //90s for 1.5V interval
bool heaterInHighPhase;

void setup() {
    Serial.begin(9600);

    //Set start time (for CO sensor heater voltage)
    startMillis = millis();
    turnHeaterHigh();
}

void loop() {
    //Cycle CO sensor (MQ7) heater voltage

    if(heaterInHighPhase){
    // 5V phase - check to switch
        if(millis() > switchTimeMillis) {
        turnHeaterLow();
        }
    }
    else {
    // 1.4V phase - check to switch
        if(millis() > switchTimeMillis) {
        turnHeaterHigh();
        }
    }


    //Read in analog value from each gas sensor -- use function defined below to measure CO sensor at end of voltage cycle
    CORaw = measureCOSensor();

    //Caclulate the PPM of each gas sensor using the funtions defined below            
    COppm = CO_ppm(CORaw);
}



//Functions to calculate PPM from Photon analog reading
//Each equation is determined by visually picking points, plotting PPM v. V_RL, then fitting a trendline to the curve (exponential)

//Calculate CO PPM
int CO_ppm(double rawValue){

    double ppm = 3.027*exp(1.0698*(rawValue*3.3/4095));
    return ppm;
}



//Functions to switch heater voltage on MQ7 (CO) sensor
void turnHeaterHigh(){
  // 5v phase
    digitalWrite(COVoltPin, LOW);
    digitalWrite(CORelayPin, HIGH);

    heaterInHighPhase = true;
    switchTimeMillis = millis() + CO_5V_Interval;
}

void turnHeaterLow(){
  // 1.4v phase
    digitalWrite(COVoltPin, HIGH);
    digitalWrite(CORelayPin, LOW);

    heaterInHighPhase = false;
    switchTimeMillis = millis() + CO_1_5V_Interval;
}

//Function to read CO sensor voltage (just before switching to 1.5V)
int measureCOSensor(){
    unsigned int gasLevel = analogRead(CO);
    unsigned int time = (millis() - startMillis) / 1000;
    delay(time);

  return gasLevel;
  
    //Publish console 
    Particle.publish("CO", String(CORaw) + " ppm");
    Particle.publish ("CO",String(CORaw), PRIVATE);
    delay(2000);
}

