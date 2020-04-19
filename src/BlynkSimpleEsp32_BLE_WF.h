/****************************************************************************************************************************
   BlynkSimpleEsp32_BLE_WF.h
   For ESP32 using BLE along with WiFi

   BlynkESP32_BT_WF is a library for inclusion of both ESP32 Blynk BT/BLE and WiFi libraries. Then select either one or both at runtime.
   Forked from Blynk library v0.6.1 https://github.com/blynkkk/blynk-library/releases
   Built by Khoi Hoang https://github.com/khoih-prog/BlynkGSM_ESPManager
   Licensed under MIT license
   Version: 1.0.5

   Original Blynk Library author:
   @file       BlynkSimpleESP32.h
   @author     Volodymyr Shymanskyy
   @license    This project is released under the MIT License (MIT)
   @copyright  Copyright (c) 2015 Volodymyr Shymanskyy
   @date       Oct 2016
   @brief

   Version Modified By   Date      Comments
   ------- -----------  ---------- -----------
    1.0.0   K Hoang      25/01/2020 Initial coding
    1.0.1   K Hoang      27/01/2020 Enable simultaneously running BT/BLE and WiFi
    1.0.2   K Hoang      04/02/2020 Add Blynk WiFiManager support similar to Blynk_WM library
    1.0.3   K Hoang      24/02/2020 Add checksum, clearConfigData()
    1.0.4   K Hoang      14/03/2020 Enhance GUI. Reduce code size.
    1.0.5   K Hoang      18/04/2020 MultiWiFi/Blynk. Dynamic custom parameters. SSID password maxlen is 63 now. 
                                    Permit special chars # and % in input data.
 *****************************************************************************************************************************/

#ifndef BlynkSimpleEsp32_BLE_WF_h
#define BlynkSimpleEsp32_BLE_WF_h

#ifndef ESP32
#error This code is intended to run on the ESP32 platform! Please check your Tools->Board setting.
#endif

#ifndef BLYNK_INFO_CONNECTION
#define BLYNK_INFO_CONNECTION "Esp32_BLE"
#endif

#define BLYNK_SEND_ATOMIC
#define BLYNK_SEND_CHUNK 20
//#define BLYNK_SEND_THROTTLE 20

// KH
#define BLYNK_TIMEOUT_MS     30000UL

#include <BlynkApiArduino.h>
#include <Blynk/BlynkProtocol.h>
#include <utility/BlynkFifo.h>

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#define SERVICE_UUID           "713D0000-503E-4C75-BA94-3148F18D941E"
#define CHARACTERISTIC_UUID_RX "713D0003-503E-4C75-BA94-3148F18D941E"
#define CHARACTERISTIC_UUID_TX "713D0002-503E-4C75-BA94-3148F18D941E"

class BlynkTransportEsp32_BLE :
  public BLEServerCallbacks,
  public BLECharacteristicCallbacks
{

  public:
    BlynkTransportEsp32_BLE()
      : mConn (false)
      , mName ("Blynk")
    {}

    void setDeviceName(const char* name) {
      mName = name;
    }

    // IP redirect not available
    void begin(char BLYNK_UNUSED *h, uint16_t BLYNK_UNUSED p) {}

    void begin() {
      // Create the BLE Device
      BLEDevice::init(mName);

      // Create the BLE Server
      pServer = BLEDevice::createServer();
      pServer->setCallbacks(this);

      // Create the BLE Service
      pService = pServer->createService(SERVICE_UUID);

      // Create a BLE Characteristic
      pCharacteristicTX = pService->createCharacteristic(
                            CHARACTERISTIC_UUID_TX,
                            BLECharacteristic::PROPERTY_NOTIFY
                          );

      pCharacteristicTX->addDescriptor(new BLE2902());

      pCharacteristicRX = pService->createCharacteristic(
                            CHARACTERISTIC_UUID_RX,
                            BLECharacteristic::PROPERTY_WRITE
                          );

      pCharacteristicRX->setCallbacks(this);

      // Start the service
      pService->start();

      // Start advertising
      pServer->getAdvertising()->addServiceUUID(pService->getUUID());
      pServer->getAdvertising()->start();
    }

    bool connect() {
      mBuffRX.clear();
      return mConn = true;
    }

    void disconnect() {
      mConn = false;
    }

    bool connected() {
      return mConn;
    }

    size_t read(void* buf, size_t len) {
      millis_time_t start = BlynkMillis();
      while (BlynkMillis() - start < BLYNK_TIMEOUT_MS) {
        if (available() < len) {
          delay(1);
        } else {
          break;
        }
      }
      size_t res = mBuffRX.get((uint8_t*)buf, len);
      return res;
    }

    size_t write(const void* buf, size_t len) {
      pCharacteristicTX->setValue((uint8_t*)buf, len);
      pCharacteristicTX->notify();
      return len;
    }

    size_t available() {
      size_t rxSize = mBuffRX.size();
      return rxSize;
    }

  private:

    void onConnect(BLEServer* pServer);
    void onDisconnect(BLEServer* pServer);

    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string rxValue = pCharacteristic->getValue();

      if (rxValue.length() > 0) {
        uint8_t* data = (uint8_t*)rxValue.data();
        size_t len = rxValue.length();

        BLYNK_DBG_DUMP(">> ", data, len);
        mBuffRX.put(data, len);
      }
    }

  private:
    bool mConn;
    const char* mName;

    BLEServer *pServer;
    BLEService *pService;
    BLECharacteristic *pCharacteristicTX;
    BLECharacteristic *pCharacteristicRX;

    BlynkFifo<uint8_t, BLYNK_MAX_READBYTES * 2> mBuffRX;
};

class BlynkEsp32_BLE
  : public BlynkProtocol<BlynkTransportEsp32_BLE>
{
    typedef BlynkProtocol<BlynkTransportEsp32_BLE> Base;
  public:
    BlynkEsp32_BLE(BlynkTransportEsp32_BLE& transp)
      : Base(transp)

    {}

    void begin(const char* auth)
    {
      Base::begin(auth);
      state = DISCONNECTED;
      conn.begin();
    }

    void setDeviceName(const char* name) {
      conn.setDeviceName(name);
    }

};


static BlynkTransportEsp32_BLE _blynkTransportBLE;

// KH
BlynkEsp32_BLE Blynk_BLE(_blynkTransportBLE);

#define Blynk Blynk_BLE

inline
void BlynkTransportEsp32_BLE::onConnect(BLEServer* pServer) {
  BLYNK_LOG1(BLYNK_F("BLECon"));
  connect();
  Blynk_BLE.startSession();
};

inline
void BlynkTransportEsp32_BLE::onDisconnect(BLEServer* pServer) {
  BLYNK_LOG1(BLYNK_F("BLEDisCon"));
  Blynk_BLE.disconnect();
  disconnect();
}
//


#include <BlynkWidgets.h>

#endif
