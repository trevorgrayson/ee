import time
import serial
from argparse import ArgumentParser, REMAINDER

ATMEGA2560UART = '/dev/ttyACM0'

parser = ArgumentParser("serialsend")
parser.add_argument("msg", nargs=REMAINDER)
args = parser.parse_args()
msg = " ".join(args.msg)

ser = serial.Serial('/dev/ttyUSB0', 115200)
# time.sleep(2)   # Let Arduino settle
# ser.setDTR(False)
# ser = serial.Serial('/dev/ttyACM0', 9600, dsrdtr=False, timeout=1)
# ser.setDTR(False)
# ser.dtr = False
# time.sleep(1)          # Give board stability time
# ser.flushInput()

ser.write(msg.encode("ascii"))

ser.close()

print("OK")
