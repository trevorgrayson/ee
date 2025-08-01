import os
import time
import tty
import termios
# from argparse import ArgumentParser

# parser = ArgumentParser
# parser.add_argument("m", help="text to be sent to device")
# parser.add_argument("--port", default='/dev/ttyUSB0')
# parser.add_argument("--baud", default=9600)
# args = parser.parse_args()
SERIAL_PORT = '/dev/ttyUSB0'  # args.port
BAUD_RATE = termios.B9600

message = "OK"

"""
def configure_serial(fd, baudrate):
# set ispeed
# set ospeed
# setraw (kill echo, buffering
# apply
"""


def send(path, message, delay=1.0):
    try:
        fd = os.open(path, os.O_RDWR|os.NOCTTY | os.O_SYNC)
        # configure_serial(fd, BAUD_RATE)
        with os.fdopen(fd, 'w', buffering=1) as ser:
            time.sleep(2)
            ser.write(message)
            ser.flush()
            time.sleep(delay)
        # read?
    except Exception as ex:
        print(ex)

send(SERIAL_PORT, message)
print("OK")
