"""
Description: Python3 program to read from serial port
and also render a radar for OpenCV


"""

import serial, cv2

COM_PORT = '/dev/ttyUSB0'
BAUD = 9600

ser = serial.Serial(COM_PORT, BAUD)

try:
    while True:
        while ser.in_waiting:
            data_raw = ser.readline()
            data = data_raw.decode()
            print('Raw Data: ', data_raw)
            print('Decoded Data', data)
 
except KeyboardInterrupt:
    ser.close()
    print('Bye')