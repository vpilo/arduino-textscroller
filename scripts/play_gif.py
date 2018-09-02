#!/usr/bin/env python3

from scroller import scroller, log

import argparse
from os import path
import signal
import sys
from time import sleep
import numpy as np
from PIL import Image, ImageSequence


WIDTH = 15
HEIGHT = 8

parser = argparse.ArgumentParser(description='Show a GIF on the Arduino text scroller.')

parser.add_argument('-a', '--address', dest='address', required=True,
                    help='IP address/hostname of the scroller')
parser.add_argument('-d', '--delay', dest='delay', default=300.0, type=float,
                    help='''Delay between frames in msec''')
parser.add_argument('file', help='File to display', type=argparse.FileType('r'))

args = parser.parse_args()

if args.delay < 0.0 or args.delay > 1000.0:
    log.e("The delay must be in the 0-1000ms range")

if args.file is sys.stdin:
    log.e("You must specify an actual file")

def signalHandler(sig, frame):
        s.close()
        exit(0)

signal.signal(signal.SIGINT, signalHandler)

path = args.file.name
args.file.close()

log.v("Showing {:s}".format(path))

image = Image.open(path)
frames = np.array([np.array(frame.copy().convert('RGB').getdata(), dtype=np.uint8)
                .reshape(frame.size[1], frame.size[0], 3)
                for frame in ImageSequence.Iterator(image)])

s = scroller.scroller(args.address)

for frame in frames:
    str = ''
    for row in frame:
        for pixel in row:
            for rgb in pixel:
                str += format(rgb, '02x')
    s.setFrame(str)
    sleep(args.delay / 1000.0)

s.close()
