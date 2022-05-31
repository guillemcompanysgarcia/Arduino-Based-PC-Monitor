#main Python script

import GPUtil
import psutil
import wmi
import math
import serial
import time


arduino = serial.Serial(port='COM8', baudrate=115200, timeout=.1) #open serial port

def write_read(x): #function to send data to the arduino board
    arduino.write(bytes(x,'utf-8'))


while 1:
      w = wmi.WMI(namespace="root\OpenHardwareMonitor") #open Hardware Monitor
      temperature_infos = w.Sensor()
      value=0

      for sensor in temperature_infos: #Search for the CPU temperature. Due to lack of OpenHardwareMonitor limitation with 11th Intel Family I only get the core 0 temp.
        #It is posible to do the mean of all your processor temps. 
          if sensor.SensorType==u'Temperature' and sensor.Parent==u'/lpc/nct6798d' and sensor.Name==u'Temperature #1':
              value=sensor.Value
    
      gpu = GPUtil.getGPUs()[0]
      
      A = str(round(value,2))
      B = str(round(psutil.cpu_percent(),2))
      C = str(round(gpu.temperature,2))
      D = str(round(gpu.load*100,2))
      finalString = A + "," + B + "," + C + "," + D + "\n" #Create the String to send to arduino
      write_read(finalString) #calling the send function
