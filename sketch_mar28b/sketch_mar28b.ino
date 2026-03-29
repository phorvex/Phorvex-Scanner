#include <M5StickCPlus2.h>
#include <WiFi.h>

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

void setup() {
  auto cfg = M5.config();
  StickCP2.begin(cfg);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  StickCP2.Display.setTextSize(2);
  StickCP2.Display.println("Scanning...");
}

void loop() {
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

        // Alert if seen more than twice within 10 minutes and signal is strong
        if (devices[j].seenCount > 2 && 
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

  delay(5000);
}