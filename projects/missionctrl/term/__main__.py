from argparse import ArgumentParser
from serial import Serial

parser = ArgumentParser("term writer")
parser.add_argument("text", help="text to write")
parser.add_argument("-p", "--port", help="serial port to use", default="COM5")

arg = parser.parse_args()

link = Serial(arg.port, 9600)

link.write(arg.text.encode())
link.write(b'\n')
