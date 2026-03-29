#include <M5StickCPlus2.h>
#include <WiFi.h>
#include <BLEDevice.h>
#include <BLEScan.h>

struct Device {
  String mac;
  int rssi;
  unsigned long firstSeen;
  unsigned long lastSeen;
  int seenCount;
  String ssid;
};

Device devices[50];
int deviceCount = 0;

BLEScan* pBLEScan;

void setup() {
  auto cfg = M5.config();
  StickCP2.begin(cfg);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  BLEDevice::init("");
  pBLEScan = BLEDevice::getScan();
  pBLEScan->setActiveScan(true);
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);
  StickCP2.Display.setTextSize(2);
  StickCP2.Display.println("Scanning...");
}

void scanWiFi() {
  int n = WiFi.scanNetworks();
  unsigned long now = millis();

  for (int i = 0; i < n; i++) {
    String mac = WiFi.BSSIDstr(i);
    int rssi = WiFi.RSSI(i);
    String ssid = WiFi.SSID(i);
    bool found = false;

    for (int j = 0; j < deviceCount; j++) {
      if (devices[j].mac == mac) {
        devices[j].lastSeen = now;
        devices[j].rssi = rssi;
        devices[j].seenCount++;
        found = true;
        if (devices[j].seenCount > 1 &&
            (now - devices[j].firstSeen) < 600000 &&
            rssi > -70) {
          Serial.println("ALERT|" + mac + "|" + ssid + "|" + rssi);
        }
        break;
      }
    }

    if (!found && deviceCount < 50) {
      devices[deviceCount++] = {mac, rssi, now, now, 1, ssid};
    }

    Serial.println("DEVICE|" + mac + "|" + ssid + "|" + String(rssi));
  }
}

void scanBLE() {
  BLEScanResults* foundDevices = pBLEScan->start(3, false);
  for (int i = 0; i < foundDevices->getCount(); i++) {
    BLEAdvertisedDevice d = foundDevices->getDevice(i);
    String mac = d.getAddress().toString().c_str();
    int rssi = d.getRSSI();
    String name = d.haveName() ? d.getName().c_str() : "(unknown)";
    Serial.println("BLE|" + mac + "|" + name + "|" + String(rssi));
  }
  pBLEScan->clearResults();
}

void loop() {
  scanWiFi();
  scanBLE();
  delay(3000);
}