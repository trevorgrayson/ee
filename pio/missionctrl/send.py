import serial  # pyserial
import time

PORT = 'COM5'
arduino = serial.Serial(port=PORT, baudrate=115200, timeout=.1)


def write_read(x):
    arduino.write(bytes(f"\0\0{x}", 'utf-8'))
    time.sleep(0.05)
    data = arduino.readline()
    return data


while True:
    s = input(">")
    value = write_read(s)
    print(value)
