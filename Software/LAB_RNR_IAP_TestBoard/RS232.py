# Use Pythone 3.3
# RS232 Recv
# -*- coding: UTF-8 -*-

import sys
import serial
from PyQt4.QtGui import *
from PyQt4.QtCore import *

device = serial.Serial()
device.port = 'COM1'
device.baudrate = 9600
device.bytesize = 8
device.stopbits = 1
device.parity = 'N'
device.xonxoff = False
device.timeout = 200
device.open()

ErrTimes = 0
ReadData = 0

for i in range(1000):

    line = device.readline()
    ReadStr = line.decode()
    if len(line) != 12:
        ErrTimes += 1
        print("ErrTimes %d" % ErrTimes)
    else :
        ReadData = int(ReadStr[4:10])
        PrintStr = ReadStr[0:3] + " = " + ReadStr[4:10]
        print(PrintStr)

device.close()
