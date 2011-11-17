__metaclass__ = type
class Bird:
    def __init__(self):
        self.hungry = True
    def eat(self):
        if self.hungry:
            print 'Ahhhhaaaa'
            self.hungry = False
        else:
            print 'No,thanks!'
class SongBird(Bird):
    def __init__(self):
#        Bird.__init__(self)
        super(SongBird,self).__init__()
        self.sound = 'Squawk'
    def sing(self):
        print self.sound

def checkIndex(key):
    """
        所给的键是能够接受的索引么？
    """
    if not isinstance(key, (int, long)): raise TypeError
    if key < 0: raise IndexError
class ArithmeticSequence:
    def __init__(self,start = 0, step = 1):
        """
            初始化序列
            起始值，步长，改变
        """
        self.start = start;
        self.step = step;
        self.changed = {}
    def __getitem__(self, key):
        """
        Get an item from the arithmetic sequence
        """
        checkIndex(key)
        try:
            return self.changed[key]
        except KeyError:
            return self.start + self.step * key
    def __setitem__(self, key, value):
        """
        Set an item of the sequence
        """
        checkIndex(key)
        self.changed[key] = value

class CounterList(list):
    def __init__(self,*args):
        super(CounterList, self).__init__(*args)
        self.counter = 0
    def __getitem__(self, index):
        self.counter += 1
        return super(CounterList, self).__getitem__(index)
__metaclass__ = type              
class Rectangle:
    def __init__(self):
        self.width = 0
        self.height = 0
    def setSize(self, size):
        self.width, self.height = size
    def getSize(self):
        return self.width, self.height
    size = property(getSize, setSize)
__metaclass__ = type
class MyClass:
    @staticmethod
    def smeth():
        print 'this is a static method'
#    smeth = staticmethod(smeth)
    @classmethod
    def cmeth(cls):
        print 'this is a class method of', cls
#    cmeth = classmethod(cmeth)
class Fibs:
    def __init__(self):
        self.a = 0
        self.b = 1
    def next(self):
        self.a, self.b = self.b, self.a + self.b
        return self.a
    def __iter__(self):
        return self

























        
        
        
        