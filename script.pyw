import GPUtil
import psutil
import wmi
import math
import serial
import time

import serial.tools.list_ports

# Get a list of all available serial ports
ports = list(serial.tools.list_ports.comports())

# Iterate over all the available ports and find the one with 'Arduino' in the description
for p in ports:
    if 'CH340' in p.description:
        arduino_port = p.device
        break

# Print the Arduino port
print('Detected Arduino port:', arduino_port)

arduino = serial.Serial(port=arduino_port, baudrate=115200, timeout=.1)
w = wmi.WMI(namespace="root\OpenHardwareMonitor")

def write_read(x):
    arduino.write(bytes(x,'utf-8'))
    time.sleep(0.05)
    data = arduino.readline()
    return data

while 1:

	temperature_infos = w.Sensor()
	valor=0
	contador=0
	
	for sensor in temperature_infos:
		if sensor.SensorType==u'Temperature' and sensor.Name==u'Temperature #1' :
			valor=sensor.Value
	
	gpu = GPUtil.getGPUs()[0]
      
	A = str(round(valor,2))
	B = str(round(psutil.cpu_percent(),2))
	C = str(round(gpu.temperature,2))
	D = str(round(gpu.load*100,2))
	finalString = A + "," + B + "," + C + "," + D + "\n"
	print(finalString)
	value = write_read(finalString)
