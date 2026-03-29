from flask import Flask, jsonify, render_template_string
import serial
import threading
import time

app = Flask(__name__)

devices = {}
ble_devices = {}

def classify_threat(device, is_ble=False):
    count = device['count']
    rssi = device['rssi']
    name = device.get('name', '') or device.get('ssid', '')

    if rssi > -50 and count >= 5 and is_ble and (not name or name.startswith('❓')):
        return 'threat'
    if rssi > -55 and count >= 4:
        return 'warning'
    return 'safe'

def read_serial():
    try:
        ser = serial.Serial('/dev/ttyACM0', 115200, timeout=1)
        while True:
            line = ser.readline().decode('utf-8', errors='ignore').strip()
            if line.startswith('DEVICE|'):
                parts = line.split('|')
                if len(parts) == 4:
                    _, mac, ssid, rssi = parts
                    now = time.time()
                    if mac not in devices:
                        devices[mac] = {'mac': mac, 'ssid': ssid, 'rssi': int(rssi), 'firstSeen': now, 'lastSeen': now, 'count': 1}
                    else:
                        devices[mac]['lastSeen'] = now
                        devices[mac]['rssi'] = int(rssi)
                        devices[mac]['count'] += 1
            elif line.startswith('BLE|'):
                parts = line.split('|')
                if len(parts) == 4:
                    _, mac, name, rssi = parts
                    now = time.time()
                    if mac not in ble_devices:
                        ble_devices[mac] = {'mac': mac, 'name': name, 'rssi': int(rssi), 'firstSeen': now, 'lastSeen': now, 'count': 1}
                    else:
                        ble_devices[mac]['lastSeen'] = now
                        ble_devices[mac]['rssi'] = int(rssi)
                        ble_devices[mac]['count'] += 1
    except Exception as e:
        print(f"Serial error: {e}")

threading.Thread(target=read_serial, daemon=True).start()

@app.route('/api/devices')
def get_devices():
    wifi = []
    for d in devices.values():
        d['threat'] = classify_threat(d, is_ble=False)
        wifi.append(d)

    ble = []
    for d in ble_devices.values():
        d['threat'] = classify_threat(d, is_ble=True)
        ble.append(d)

    alerts = [
        {'mac': d['mac'], 'ssid': d.get('ssid') or d.get('name', 'Unknown'), 'rssi': d['rssi'], 'time': time.strftime('%H:%M:%S')}
        for d in wifi + ble if d['threat'] == 'threat'
    ]

    return jsonify({'devices': wifi, 'ble_devices': ble, 'alerts': alerts})

@app.route('/')
def index():
    return render_template_string(open('/home/pageery/Desktop/scanner/dashboard.html').read())

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=False)
