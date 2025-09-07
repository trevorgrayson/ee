#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

float calculateDistance(int rssi, int txPower = -59, float pathLoss = 2.0)
{
    return pow(10.0, ((float)(txPower - rssi)) / (10.0 * pathLoss));
}

class MyServerCallbacks : public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
        //
    }

    void onDisconnect(BLEServer* pServer) {
        //
    }
};

// Event handling:
// ESP_GAP_BLE_SCAN_RESULT_EVT


void setup()
{
    Serial.begin();
    BLEDevice::init("Phone Finder");
    BLEServer *pServer = BLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks());

    BLEService *pService = pServer->createService(BLEUUID((uint16_t)0x180F));
    BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                                BLEUUID((uint16_t)0x2A19),
                                                BLECharacteristic::PROPERTY_READ
                                            );
    pCharacteristic->setValue("hello");
    pService->start();

    pServer->getAdvertising()->start();
    // waiting
}

void loop()
{
    BLEScan *scan = BLEDevice::getScan();
    scan->setActiveScan(true);
    scan->setInterval(1000);
    scan->setWindow(999);

    // pick client
    BLEScanResults results = scan->start(5, false);
    // scan->getResults();

    for (int i = 0; i < results.getCount(); i++)
    {
        BLEAdvertisedDevice device = results.getDevice(i);

        String name = device.getName().c_str();
        if (name.length() == 0) {
            name = "[No Name]";
        }
        int rssi = device.getRSSI();
        float distance = calculateDistance(rssi);
        Serial.printf("%s: %d dBm, %d\n", name.c_str(), rssi, distance);
    }
    delay(2000);
}