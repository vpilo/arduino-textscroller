#!/usr/bin/env python3

from scroller import scroller, log

import argparse
from time import sleep
import sys
import signal

description = '''
Displays raw pixel data via input pipe on the Arduino text scroller.
Pipe RGB hex-encoded bytes (e.g. 'FF00FF' for purple) for each pixel. A color for each pixel must be given.
'''

parser = argparse.ArgumentParser(description=description)

parser.add_argument('-a', '--address', dest='address', required=True,
                    help='IP address/hostname of the scroller')
parser.add_argument('-d', '--delay', dest='delay', default=300.0, type=float,
                    help='''Delay between frames in msec''')

args = parser.parse_args()

if args.delay < 0.0 or args.delay > 1000.0:
    log.e("The delay must be in the 0-1000ms range")


def signalHandler(sig, frame):
        s.close()
        exit(0)

signal.signal(signal.SIGINT, signalHandler)


s = scroller.scroller(args.address)

for line in sys.stdin:
    s.setFrame(line.strip())
    sleep(args.delay / 1000.0)

s.close()
