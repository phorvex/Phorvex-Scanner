# ⬡ PHORVEX SCANNER

## *Next-Gen Network Threat Detection & RF Reconnaissance System*

![Status](https://img.shields.io/badge/status-active-00ff88?style=flat-square) ![License](https://img.shields.io/badge/license-MIT-blue?style=flat-square) ![Language](https://img.shields.io/badge/Python%20%2F%20C%2B%2B-v3%20%2F%20ESP32-orange?style=flat-square)

---

## 🎯 Overview

**PHORVEX SCANNER** is a cutting-edge, portable network reconnaissance and threat detection system that simultaneously monitors WiFi and Bluetooth Low Energy (BLE) device ecosystems in real-time. Built on the powerful M5StickCPlus2 platform with a sophisticated Python backend and real-time web dashboard, this system delivers advanced threat intelligence through intelligent behavioral analysis and signal pattern recognition.

This is not just another WiFi scanner—it's a **comprehensive security monitoring solution** that transforms raw RF signals into actionable threat intelligence.

---

## ✨ Key Features

### 🛡️ **Dual-Stack Network Monitoring**
- **WiFi Network Scanning**: Captures 802.11 network beacons with real-time RSSI (Received Signal Strength Indicator) analysis
- **BLE Device Discovery**: Detects and profiles Bluetooth Low Energy peripherals with advanced signal triangulation
- **Concurrent Monitoring**: Simultaneous WiFi + BLE scanning without interference or detection lag

### 🚨 **Intelligent Threat Classification Algorithm**
- **Multi-Factor Analysis**: Combines signal strength, detection frequency, and behavioral patterns
- **Anomaly Detection**: Identifies suspicious devices through advanced heuristics:
  - Unknown/masked SSIDs with concerning signal characteristics
  - Persistent high-strength signals indicating proximity threats
  - Devices exhibiting rapid multi-beacon patterns
- **Real-Time Threat Levels**: 
  - 🔴 **THREAT**: Potential attack vectors requiring immediate investigation
  - 🟠 **WARNING**: Suspicious activity patterns warranting attention
  - 🟢 **SAFE**: Known or benign devices

### 📊 **Professional-Grade Dashboard**
- **Live Stream Analytics**: Real-time visualization of network activity
- **Comprehensive Device Profiling**: MAC address, signal strength, first/last seen timestamps
- **Alert Management**: Dedicated threat panel with timestamped incident logging
- **Dark-Themed UI**: Optimized for extended monitoring sessions with reduced eye strain
- **Responsive Design**: Full mobile support for on-the-go threat assessment

### 🔧 **Advanced Signal Processing**
- High-frequency RF scanning with configurable intervals
- RSSI trend analysis for predictive threat detection
- Persistence tracking across multiple detection cycles
- Device fingerprinting through behavioral signatures

---

## 🏗️ Architecture

```
┌─────────────────────────────────────────────────────────────┐
│                   PHORVEX SCANNER ECOSYSTEM                  │
├─────────────────────────────────────────────────────────────┤
│                                                              │
│  ┌──────────────────────┐          ┌──────────────────┐   │
│  │  M5StickCPlus2       │          │  Flask Backend   │   │
│  │  (Hardware Engine)   │ Serial ◄──► (Data Processor)│   │
│  │                      │   115200  │                  │   │
│  │ • WiFi Scanning      │  Baud   │ • Device Index   │   │
│  │ • BLE Discovery      │          │ • Threat Analysis│   │
│  │ • RF Monitoring      │          │ • API Gateway    │   │
│  └──────────────────────┘          └──────────────────┘   │
│                                             │               │
│                                             │               │
│                                    ┌────────▼────────┐    │
│                                    │  Web Dashboard   │    │
│                                    │  (Real-time UI)  │    │
│                                    │                  │    │
│                                    │ • Live Feeds     │    │
│                                    │ • Threat Alerts  │    │
│                                    │ • Analytics      │    │
│                                    └──────────────────┘    │
│                                                              │
└─────────────────────────────────────────────────────────────┘
```

---

## 📋 Hardware Requirements

- **M5StickCPlus2**: Industrial-grade ESP32-S3 based IoT device with integrated WiFi & BLE
- **USB-C Cable**: For serial communication and power delivery
- **Network Access**: WiFi connectivity for web dashboard interface (optional for headless operation)

---

## 🛠️ Installation & Setup

### Prerequisites
```bash
# Python 3.8+
python --version

# Required Python packages
pip install flask pyserial
```

### Step-by-Step Deployment

#### 1. **Flash Arduino Sketch to M5StickCPlus2**
```bash
# Use Arduino IDE or PlatformIO to upload:
# - sketch_mar28a/sketch_mar28a.ino (Primary scanner)
# - sketch_mar28b/sketch_mar28b.ino (Alternative variant)

# Configuration:
# - WiFi scan interval: 100ms
# - BLE scan interval: 100ms  
# - Serial baud rate: 115200
# - Max concurrent device tracking: 50+ devices
```

#### 2. **Deploy Flask Backend**
```bash
cd /path/to/phorvex-scanner
python scanner.py
# Server starts on http://0.0.0.0:5000
```

#### 3. **Connect Hardware**
```bash
ls /dev/ttyACM0  # Linux/macOS
# or
COM3              # Windows
```

#### 4. **Access Dashboard**
Navigate to: **http://localhost:5000**

---

## 📡 Data Flow & Protocol

### Serial Communication Format

**WiFi Device Detection:**
```
DEVICE|AA:BB:CC:DD:EE:FF|NetworkSSID|-65
```

**BLE Device Detection:**
```
BLE|AA:BB:CC:DD:EE:FF|Unknown Device|-72
```

**JSON API Response:**
```json
{
  "devices": [
    {
      "mac": "AA:BB:CC:DD:EE:FF",
      "ssid": "NetworkName",
      "rssi": -65,
      "threat": "safe|warning|threat",
      "firstSeen": 1711699200,
      "lastSeen": 1711699500,
      "count": 12
    }
  ],
  "ble_devices": [...],
  "alerts": [...]
}
```

---

## 🎓 Threat Classification Intelligence

The system employs a sophisticated multi-variable threat assessment engine:

| Factor | Threshold | Weight |
|--------|-----------|--------|
| RSSI Signal Strength | > -50 dBm | HIGH |
| Detection Frequency | ≥ 5 occurrences | HIGH |
| Device Naming | Unknown/Masked | MEDIUM |
| Persistence | Continuous observation | MEDIUM |
| Signal Pattern | Anomalous behavior | HIGH |

**BLE-Specific Heuristics:**
- Unnamed devices with strong signals = Potential surveillance risk
- Rapid beacon patterns = Possible attack vector
- Repeated high-RSSI detection = Proximity threat

---

## 🚀 Use Cases

✅ **Network Security Auditing** - Identify unauthorized devices
✅ **Rogue AP Detection** - Detect unauthorized access points
✅ **BLE Device Tracking** - Monitor and profile Bluetooth devices
✅ **Wireless Penetration Testing** - Pre-engagement reconnaissance
✅ **IoT Security Assessment** - Validate IoT ecosystem integrity
✅ **Proximity-Based Threat Detection** - Real-time venue security
✅ **RF Spectrum Analysis** - Understand wireless landscape

---

## 📊 Performance Specifications

| Metric | Value |
|--------|-------|
| WiFi Scanning Frequency | 100ms intervals |
| BLE Scanning Frequency | 100ms intervals |
| Max Tracked Devices | 50+ concurrent |
| Serial Baud Rate | 115200 bps |
| API Response Time | <100ms |
| Dashboard Refresh Rate | Real-time |
| Threat Detection Latency | <2 seconds |

---

## 🔐 Security Note

This tool is designed for **authorized network security testing only**. Ensure proper authorization before deploying in any environment.

---

## 📁 Project Structure

```
phorvex-scanner/
├── scanner.py                 # Flask backend
├── dashboard.html            # Real-time UI
├── sketch_mar28a/
│   └── sketch_mar28a.ino     # Primary firmware
├── sketch_mar28b/
│   └── sketch_mar28b.ino     # Alternative firmware
└── README.md                 # Documentation
```

---

## 🔧 Customization

### Threat Classification Tuning
Edit `classify_threat()` in `scanner.py`

### Serial Port Configuration
Default: `/dev/ttyACM0` at `115200` baud

### Dashboard Theming
Customize colors and layout in `dashboard.html`

---

## 🐛 Troubleshooting

### Serial Connection Issues
```bash
dmesg | grep ttyACM
ls -la /dev/ttyACM*
sudo usermod -a -G dialout $USER
```

### Dashboard Not Loading
- Verify Flask is running: `curl http://localhost:5000`
- Check firewall rules on port 5000
- Ensure M5StickCPlus2 is properly connected

### No Devices Detected
- Verify Arduino sketch uploaded
- Check serial monitor output
- Ensure M5StickCPlus2 is powered

---

## 🤝 Contributing

Contributions welcome! Enhancement areas:
- Advanced threat intelligence integration
- Machine learning-based anomaly detection
- Multi-device hardware support
- Cloud-based analytics
- Mobile app development

---

## 📄 License

MIT License

---

## 🙏 Acknowledgments

Built with passion for network security professionals and penetration testers.

---

**PHORVEX SCANNER** — *Threats Detected. Security Enhanced. Peace of Mind Delivered.* 🛡️

*Last Updated: March 2026*
*Maintained by [Phorvex](https://github.com/phorvex)*