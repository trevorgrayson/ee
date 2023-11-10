import serial

ser = serial.Serial("COM11", 9600)
ser.write(b'hello')
ser.close()
