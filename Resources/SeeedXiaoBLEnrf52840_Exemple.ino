#include <ArduinoBLE.h>
// Seeed Xiao BLE nrf52840 device address : B7:12:A9:C6:77:27   MAC adress of the current device
// Relative pressure is the atmospheric pressure corrected to sea-level conditions.

#define PRESSURE_SERVICE_UUID "19B10000-E8F2-537E-4F6C-D104768A1214"
#define PRESSURE_CHARACT_UUID "19B10001-E8F2-537E-4F6C-D104768A1214"

BLEService PressureService(PRESSURE_SERVICE_UUID);
BLEDoubleCharacteristic PressureData(PRESSURE_CHARACT_UUID, BLERead | BLEWrite);


double Pressure_value; // pressure measured


void setup() {  
  // initialize the serial communication
  Serial.begin(9600);
  
  // begin initialization
  if (!BLE.begin()) 
  {
    Serial.println("starting Bluetooth® Low Energy module FAILED!");
    while (1);
  }
  
  // set advertised local name and service UUID:
  BLE.setLocalName("My BLE Device");

  BLE.setAdvertisedService(PressureService);  // add the service UUID
  PressureService.addCharacteristic(PressureData); // add the pressure value characteristic
  BLE.addService(PressureService); // Add the pressure service

  // start advertising
  BLE.advertise();

  Serial.println("Seeed Xiao BLE nrf5280 STARTED !");
}


void loop() 
{
  BLEDevice central = BLE.central();
  if (central) {
    Serial.print("connected to central : ");
    Serial.println(central.address());
    
    while (central.connected()) {
        
        Pressure_value = random(10 , 30);

        PressureData.writeValue(Pressure_value);
        Serial.print("pressure: ");
        Serial.println(Pressure_value);
        
        delay(500);
    }
    
    Serial.print("Disconnected from central: ");  // If BLE between device and phone is disconnected
  }
 
}
