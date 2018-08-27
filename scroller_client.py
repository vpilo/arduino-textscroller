#!/usr/bin/env python
import socket
import sys
import argparse
from time import sleep

VERBOSE = True
MAX_ROW_BYTES = 256
PORT = 10666

epilog = '''
The scroller reserves the right to crop your message as it pleases.
'''

parser = argparse.ArgumentParser(description='Show a message on the Arduino text scroller.', epilog=epilog)

parser.add_argument('-a', '--address', dest='address', required=True,
                    help='IP address/hostname of the scroller')
parser.add_argument('-s', '--speed', dest='speed', type=int,
                    help='Speed of scrolling, 1 (fastest) to 10 (slowest)')
parser.add_argument('-c', '--color', dest='color', nargs=3, type=int,
                    help='Text color, three 0-255 values for each of the R, G, B channels')
parser.add_argument('-r', '--rainbow', dest='rainbow', action='store_true', default=False,
                    help='Rainbow colors mode, overrides --color')
parser.add_argument(dest='message', nargs='+',
                    help='Message to display. It can have no quotes.')

args = parser.parse_args()

if args.speed != None and (args.speed < 1 or args.speed > 10):
    print("Speed must be in the 1-10 range")
    exit(1)

if args.color != None:
    for channel in args.color:
        if channel < 0 or channel > 255:
            print("Colors must be in the 0-255 range")
            exit(1)

def command(sock, cmd):
    try:
        if VERBOSE: print("Sending command: '%s'" % cmd)

        cmd += "\n"
        sock.sendall(cmd)
    except socket.error:
        print("Cannot send command: {:s}".format(cmd))
        exit(2)

    buffer = bytearray()
    try:
        chunks = []
        bytes_received = 0
        while bytes_received < MAX_ROW_BYTES:
            chunk = sock.recv(MAX_ROW_BYTES - bytes_received)
            buffer += chunk
            bytes_received = bytes_received + len(chunk)
            if VERBOSE: print("Got {:d} bytes: '{}'".format(len(chunk), ":".join("{:02x}".format(ord(c)) for c in chunk)))
            if len(chunk) == 0 or buffer.find('\n') >= 0:
                break
    except socket.error:
        print("Connection broken")
        exit(2)
    response = buffer.decode()
    if not response.startswith("OK\n"):
        print("Error: {}".format(buffer))
        exit(2)

s = None
try:
    if VERBOSE: print("Connecting to %s..." % args.address)
    s = socket.create_connection((args.address, PORT), 5)
except socket.error:
    print("There's no scroller at that address.")
    exit(1)
except socket.timeout:
    print("Unable to connect with the scroller at that address.")
    exit(1)

if VERBOSE: print("Connected")


if args.speed != None:
    command(s, "SPEED " + args.speed)

if args.color != None:
    command(s, "COLOR {:d} {:d} {:d}".format(args.color[0], args.color[1], args.color[2]))

command(s, "TEXT " + ' '.join(args.message))

s.close()
