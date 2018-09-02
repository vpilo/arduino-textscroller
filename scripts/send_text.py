#!/usr/bin/env python3

from scroller import scroller, log

import argparse

epilog = '''
Not specifying a color keeps the previous one.
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
parser.add_argument('message', nargs='+', help='Message to display')

args = parser.parse_args()

if args.speed != None and (args.speed < 1 or args.speed > 10):
    log.e("Speed must be in the 1-10 range")

if args.color != None:
    for channel in args.color:
        if channel < 0 or channel > 255:
            log.e("All channels must be in the 0-255 range")


s = scroller.scroller(args.address)

if args.rainbow == True:
    s.setRainbow()
elif args.color != None:
    s.setColor(args.color[0], args.color[1], args.color[2])

if args.speed != None:
    s.setSpeed(args.speed)

if args.message != None:
    s.setText(' '.join(args.message))

s.close()
