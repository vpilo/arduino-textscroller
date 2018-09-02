from . import log

import socket

class scroller:

    __sock = None

    __CONNECTION_PORT = 10666
    __MAX_ROW_BYTES = 256

    def setSpeed(self, speed):
        self.__command('SPEED', str(speed))

    def setColor(self, red, green, blue):
        self.__command('COLOR', str(red), str(green), str(blue))

    def setRainbow(self):
        self.__command('RAINBOW')

    def setText(self, message):
        self.__command('TEXT', message)

    def setFrame(self, pixels):
        self.__command('PIXELS', pixels)

    def close(self):
        self.__check()
        self.__sock.close()

    def __init__(self, ip):
        try:
            log.v("Connecting to %s..." % ip)
            self.__sock = socket.create_connection((ip, self.__CONNECTION_PORT), 5)
        except socket.error:
            log.e("There's no scroller at that address.")
        except socket.timeout:
            log.e("Unable to connect with the scroller at that address.")
        log.v("Connected")

    def __command(self, cmd, *args):
        self.__check()

        for arg in args:
            cmd += ' ' + arg

        sendCmd = cmd.encode('utf8', errors='surrogateescape')
        try:
            log.v("Sending command: {:s}".format(' '.join('{:02x}'.format(x) for x in sendCmd)))
            self.__sock.sendall(sendCmd + b'\n')
        except socket.error:
            log.e("Cannot send command: {:s}".format(sendCmd))

        buffer = bytearray()
        try:
            bytes_received = 0
            while bytes_received < self.__MAX_ROW_BYTES:
                chunk = self.__sock.recv(self.__MAX_ROW_BYTES - bytes_received)
                buffer += chunk
                bytes_received = bytes_received + len(chunk)
                log.v("Got {:d} bytes".format(len(chunk)))
                if len(chunk) == 0 or buffer.find(b'\n') >= 0:
                    break
        except socket.error:
            print("Connection broken")
            exit(2)
        response = buffer.decode('utf8', errors='surrogateescape')
        log.v("Answer: {:s}".format(response.strip()))
        if not response.startswith("OK\n"):
            log.e("Error: {}".format(buffer))

    def __check(self):
        if self.__sock is None:
          log.e('Not connected')