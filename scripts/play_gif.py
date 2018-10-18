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
parser.add_argument('-d', '--delay', dest='delay', default=0.0, type=float,
                    help='''Override gif speed with your own frame time (in msec)''')
parser.add_argument('-l', '--loop', dest='loop', action='store_true', default=False,
                    help='Play the GIF in a loop until interrupted (with Ctrl+C)')
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

image = Image.open(path)

if args.delay is 0.0:
  if not 'duration' in image.info or image.info['duration'] is 0:
    log.e("This GIF doesn't have a speed. Specify one.")
  args.delay = image.info['duration']

log.l("Showing {:s} with speed {:.0f}".format(path, args.delay))

frames = np.array([np.array(frame.copy().convert('RGB').getdata(), dtype=np.uint8)
                .reshape(frame.size[1], frame.size[0], 3)
                for frame in ImageSequence.Iterator(image)])

s = scroller.scroller(args.address)

while True:
  for frame in frames:
      str = ''
      for row in frame:
          for pixel in row:
              for rgb in pixel:
                  str += format(rgb, '02x')
      s.setFrame(str)
      sleep(args.delay / 1000.0)
  if not args.loop:
    break

s.close()
