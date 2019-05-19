import serial
import tkinter as tk
from tkinter import scrolledtext
from threading import Thread
import time
port = "COM7"
buadrate = 115200
ser = serial.Serial(port,buadrate,timeout = 0.2)
GUI = tk.Tk()
GUI.title("钢琴&手风琴")
GUI.geometry("800x600")
information = tk.LabelFrame(GUI, text = "琴键记录", padx= 10, pady = 10)
information.place(x = 20, y = 20)
information_window = scrolledtext.ScrolledText(information, width = 88, height = 10, padx = 10, pady = 10, font = ("宋体",12), selectforeground = "blue",wrap = tk.WORD)
information_window.grid()
canvas = tk.Canvas(GUI,width = 800, height = 300)
canvas.place(x = 20,y = 300)
def rectangle(x1,y1,x2,y2,colour):
    canvas.create_rectangle(x1,y1,x2,y2, fill = colour)
    time.sleep(0.5)
    canvas.create_rectangle(x1,y1,x2,y2, fill = "white")
def qinjian_record(qinjian):
    if qinjian =='':
        information_window.insert("end",'*')
        information_window.see("end") 
    else:
        information_window.insert("end",''+str(qinjian)+'')
        information_window.see("end")
def main():
    while 1:
        s = ser.readline()
        s = str(s,encoding = 'utf-8')
        qinjian_record(s)
        s_list = list(s)
        s_list_len = len(s_list)
        i = 0
        while i<s_list_len :
            if s_list[i] == '1':
                q1 = Thread(target=rectangle, args=(0,5,90,320,"lightsteelblue",))
                q1.start()
            if s_list[i] == '2':
                q2 = Thread(target=rectangle, args=(100,5,190,320,"pink",))
                q2.start()
            if s_list[i] == '3':
                q3 = Thread(target=rectangle, args=(200,5,290,320,"lightsteelblue",))
                q3.start()
            if s_list[i] == '4':
                q4 = Thread(target=rectangle, args=(300,5,390,320,"pink",))
                q4.start()
            if s_list[i] == '5':
                q5 = Thread(target=rectangle, args=(400,5,490,320,"lightsteelblue",))
                q5.start()
            if s_list[i] == '6':
                q6 = Thread(target=rectangle, args=(500,5,590,320,"pink",))
                q6.start()
            if s_list[i] == '7':
                q7 = Thread(target=rectangle, args=(600,5,690,320,"lightsteelblue",))
                q7.start()
            if s_list[i] == '8':
                q8 = Thread(target=rectangle, args=(700,5,790,320,"pink",))
                q8.start()
            i = i+1
ma = Thread(target = main)
ma.start()
GUI.mainloop()
ser.close()
