
import GPUtil
import psutil
import wmi
import math
import serial
import time


arduino = serial.Serial(port='COM8', baudrate=115200, timeout=.1)

def write_read(x):
    arduino.write(bytes(x,'utf-8'))
    time.sleep(0.05)
    data = arduino.readline()
    return data


while 1:
      w = wmi.WMI(namespace="root\OpenHardwareMonitor")
      temperature_infos = w.Sensor()
      valor=0
      contador=0

      for sensor in temperature_infos:
          if sensor.SensorType==u'Temperature' and sensor.Parent==u'/lpc/nct6798d' and sensor.Name==u'Temperature #1':
              valor=sensor.Value
    
      gpu = GPUtil.getGPUs()[0]
      
      A = str(round(valor,2))
      B = str(round(psutil.cpu_percent(),2))
      C = str(round(gpu.temperature,2))
      D = str(round(gpu.load*100,2))
      finalString = A + "," + B + "," + C + "," + D + "\n"
      #print(finalString)
      value = write_read(finalString)
