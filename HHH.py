#!/usr/bin/python
#Filename:TestModule.py
def Hello(s):
    print ("Hello World")
    print(s)

def Add(a, b):
    print('a=', a)
    print ('b=', b)
    return a + b


def ReadBfile():
    d = "./16k16bit.mp3"
#    d = "./call.cpp"
    with open(d,"rb") as a:
        data = a.read()
        a.close()
        print(len(data))
        return data
class Test:
    def __init__(self):
        print("Init")
    def SayHello(self, name):
        print ("Hello,", name)
        return name
