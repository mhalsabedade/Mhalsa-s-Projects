#include <RF24.h> 
#include <Wire.h> 
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

RF24 radio(9, 10);  // Define CE, CSN pins for NRF24L01 module

float elapsedTime, currentTime, previousTime; 

// Max size of this struct is 32 bytes – NRF24L01 buffer limit 
struct Data_Package  
{ 
    char msg; 
};
Data_Package data;  // Create struct instance

Adafruit_MPU6050 mpu;  // MPU6050 sensor instance

void setup()  
{ 
    Serial.begin(9600);
    
    // Initialize radio communication 
    if (!radio.begin()) {
        Serial.println("NRF24L01 Initialization Failed!");
        while (1);
    }

    radio.openWritingPipe(0xF0F0F0F0E1LL);  // Set address
    radio.setPALevel(RF24_PA_LOW);
    radio.stopListening(); // Set as transmitter

    // Initialize MPU6050
    if (!mpu.begin()) {
        Serial.println("MPU6050 Initialization Failed!");
        while (1);
    }

    Serial.println("MPU6050 Ready.");
}

void loop()  
{ 
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp); // Get sensor readings

    // Checking acceleration values and assigning messages
    if (a.acceleration.x >= 2) { 
        data.msg = 1; 
    } 
    else if (a.acceleration.x <= -2) { 
        data.msg = 2; 
    } 
    else if (a.acceleration.y >= 2) { 
        data.msg = 3; 
    } 
    else if (a.acceleration.y <= -2) { 
        data.msg = 4; 
    } 
    else { 
        data.msg = 0; 
    }

    // Send data over NRF24L01
    radio.write(&data, sizeof(Data_Package));

    // Print for debugging
    Serial.print("Sent Message: ");
    Serial.println(data.msg);

    delay(100); // Small delay to prevent flooding the transmission
}
