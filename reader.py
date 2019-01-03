import numpy as np
import matplotlib.pyplot as plt
import serial

ser = serial.Serial('/dev/ttyACM0',38400)

ls1=[]
counter=0
plt.ion()
while(True):
	ser.read(1)
	if(ser.read(1)==b'\r'):
		ls1.append(int(ser.read(8),16))
		counter+=1
		a=len(ls1)
		if(a%5==0):
			plt.clf()
			plt.title("ADC Voltage vs. Time")
			plt.xlabel("t")
			plt.ylabel("V")
			plt.scatter(np.arange(a),ls1)
			plt.pause(0.00001)
