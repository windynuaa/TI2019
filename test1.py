import serial
import tkinter as tk
from tkinter import scrolledtext
port = "COM7"
buadrate = 115200
ser = serial.Serial(port,buadrate,timeout = 0.2)
while 1:
    s = ser.readline()
    print(s)
ser.close()
