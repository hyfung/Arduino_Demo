import serial

ser = serial.Serial(port="/dev/ttyACM0", baudrate=115200)
buf = ""

while True:
    x = ser.read().decode()
    buf = buf + x
    if x == '\n':
        buf = buf[:-2]
        print(buf)
        buf = ""