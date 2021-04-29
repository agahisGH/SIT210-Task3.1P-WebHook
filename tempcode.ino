// This #include statement was automatically added by the Particle IDE.
#include <Adafruit_DHT.h>

// Defining the pin we are connecting to.
#define DHTPIN 5
// Defining the type of sensor we are using; (AM2302).
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

int led = D7;

void setup()
{
    pinMode(led, OUTPUT);
    
    // Passes the data rate value of 9600 bits/second, or also known as the 'baud rate'.
    Serial.begin(9600);
    dht.begin();
}

void loop()
{
    digitalWrite(led, LOW);
    // Waits 25 seconds before taking the measurement
    delay(25000);
    
    digitalWrite(led, HIGH);
    
    // Reads the temperature in Celsius using the 'getTempCelcius()' function, while creating it as a float variable "checkT".
    // Reason for this is that it will be checked whether it is a valid reading, if it passes the if statement to check that below,
    // then it will be deemed valid and then converted into a string later down.
    float checkT = dht.getTempCelcius();
    
    // Checks to see if any readings have failed, if so, then it will exit and try again.
    if (isnan(checkT))
    {
        return;
    }
    
    // This assumes after the check that the reading is valid, so it then is converting "checkT" to a string variable of "t".
    String t = String(checkT);
    
    Particle.publish("temp", t, PRIVATE);
    
    // Waits another 5 seconds once the measurement has been taken, this allows for the LED light to be on for these 5 seconds, indicating to the user that the recording has taken place. 
    // It also equals to a total time of 30 seconds/reading as mentioned in TaskSheet.
    delay(5000);
}