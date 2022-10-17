import aiges_sdk 

class PythonClass:
    def __init__(self):
        self._x = 0

    def get_x(self):
        ccc = b"ccccccccccccdddf"
        s = len(ccc)
         
        r = aiges_sdk.ResponseData()
        r.status = 1
        r.setDataType(2)
        r.setData(memoryview(ccc))
#        r.len = s
        b = memoryview(r)
        print("shape",b.shape)
        print(r.status)
        print(r.len)
        print(r.type)
        return aiges_sdk.fibonacci(self._x)

    def set_x(self, x):
        self._x = x
