#!/usr/bin/env python3

from scroller import scroller, log

import argparse
import signal

from time import sleep
import random
#import binascii


WIDTH = 15
HEIGHT = 8

BALLS = 3


parser = argparse.ArgumentParser(description='Show bouncing balls on the Arduino text scroller.')

parser.add_argument('-a', '--address', dest='address', required=True,
                    help='IP address/hostname of the scroller')
parser.add_argument('-d', '--delay', dest='delay', default=25.0, type=float,
                    help='''Animation frame time (in msec)''')
parser.add_argument('-l', '--lines', dest='lines', action='store_true', default=False,
                    help='Connect the balls with lines')

args = parser.parse_args()

if args.delay < 0.0 or args.delay > 1000.0:
    log.e("The delay must be in the 0-1000ms range")

s = scroller.scroller(args.address)
def signalHandler(sig, frame):
        s.close()
        exit(0)

signal.signal(signal.SIGINT, signalHandler)


LED_MAP = []

class Ball():
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.vx = 0
        self.vy = 0
        self.color = [255,255,255]
        LED_MAP[int(self.y)][int(self.x)] = self.color

    def set_color(self, r, g, b):
        self.color = [int(r),int(g),int(b)]

    def set_velocity(self, vx, vy):
        self.vx = vx
        self.vy = vy

    def move(self):
        LED_MAP[int(self.y)][int(self.x)] = [0,0,0]

        self.x += self.vx
        self.y += self.vy

        if self.x >= WIDTH or self.x <= 0:
            self.vx *= -1
        if self.y >= HEIGHT or self.y <= 0:
            self.vy *= -1

        if (self.x > WIDTH - 1):
            self.x = WIDTH - 1
        if (self.y > HEIGHT - 1):
            self.y = HEIGHT - 1
        if (self.x < 0):
            self.x = 0
        if (self.y < 0):
            self.y = 0

        LED_MAP[int(self.y)][int(self.x)] = self.color


def setup():
    for j in range(HEIGHT):
        LED_MAP.append([])
        for i in range(WIDTH):
            LED_MAP[j].append([0,0,0])

def reset_map():
    for j in range(HEIGHT):
        for i in range(WIDTH):
            LED_MAP[j][i] = [0,0,0]

def get_map_hex():
    str = ""
    for j in range(HEIGHT):
        for i in range(WIDTH):
            for led in LED_MAP[j][i]:
                str += format(led, '02x')
    return str

def get_line(start, end):
    """Bresenham's Line Algorithm
    Produces a list of tuples from start and end
    >>> points1 = get_line((0, 0), (3, 4))
    >>> points2 = get_line((3, 4), (0, 0))
    >>> assert(set(points1) == set(points2))
    >>> print points1
    [(0, 0), (1, 1), (1, 2), (2, 3), (3, 4)]
    >>> print points2
    [(3, 4), (2, 3), (1, 2), (1, 1), (0, 0)]
    """
    # Setup initial conditions
    x1, y1 = start
    x2, y2 = end
    dx = x2 - x1
    dy = y2 - y1

    # Determine how steep the line is
    is_steep = abs(dy) > abs(dx)

    # Rotate line
    if is_steep:
        x1, y1 = y1, x1
        x2, y2 = y2, x2

    # Swap start and end points if necessary and store swap state
    swapped = False
    if x1 > x2:
        x1, x2 = x2, x1
        y1, y2 = y2, y1
        swapped = True

    # Recalculate differentials
    dx = x2 - x1
    dy = y2 - y1

    # Calculate error
    error = int(dx / 2.0)
    ystep = 1 if y1 < y2 else -1

    # Iterate over bounding box generating points between start and end
    y = y1
    points = []
    for x in range(x1, x2 + 1):
        coord = (y, x) if is_steep else (x, y)
        points.append(coord)
        error -= abs(dy)
        if error < 0:
            y += ystep
            error += dx

    # Reverse the list if the coordinates were swapped
    if swapped:
        points.reverse()
    return points

def draw_line(b1,b2, b):
    line = get_line([b1.x, b1.y], [b2.x, b2.y])
    for point in line:
        LED_MAP[point[1]][point[0]] = [255 - b * 64, 1 * b * 32, b * 32]

def main():
    setup()
    balls = []

    for i in range(BALLS):
        ball = Ball(int(random.random() * (WIDTH-1)), int(random.random() * (HEIGHT-1)))
        ball.set_velocity(int(random.random() * 2.0 + 1),int(random.random() * 2.0 + 1))
        ball.set_color(random.random() *255.0, random.random() *255.0, random.random() *255.0)
        balls.append(ball)

    while True:
        reset_map()
        for ball in balls:
            ball.move()

        if args.lines:
            for b in range(len(balls)):
                draw_line(balls[b], balls[(b + 1) % BALLS], b)

        s.setFrame(get_map_hex())
        sleep(args.delay / 1000.0)

main()
