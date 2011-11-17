__metaclass__ = type
class Person:
    def setName(self,name):
        self.name = name
    def getName(self):
        return self.name
    def greet(self):
        print "hello world! I'm %s." % self.name
class Class:
    def method(self):
        print "I have a self"
def function():
    print "I don't hava a self"
class Bird:
    song = "Squaawk"
    def sing(self):
        print self.song
class Secretive:
    def __inaccessible(self):
        print "this is inaccessible."
    def accessible(self):
        print "this is accessible."
        self.__inaccessible()
class MemberCounter2:
    members = 0
    def init(self):
        MemberCounter2.members += 1
class Filter:
    def init(self):
        self.blocked = []
    def filter(self,sequence):
        return [x for x in sequence if x not in self.blocked]
class SPAMFilter(Filter):
    def init(self): # rewrite init() in Filter
        self.blocked = ["SPAM"]
class Calculator:
    def calculate(self,expression):
        self.value = eval(expression)
class Talker:
    def talk(self):
        print 'Hi,my value is',self.value
class TalkingCalculator(Calculator, Talker):
    pass
try:
    x = input("input the first number: ")
    y = input("input the second number: ")
    print x/y
except (ZeroDivisionError,TypeError), e:
# print "the second number can't be zero!"
    print e
class MuffledCalculator:
    muffled = True
    def calculate(self,expression):
        try:
            return eval(expression)
        except ZeroDivisionError:
            if self.muffled:
                print 'Division by zero is illegal'
            else:
                raise
        





















        
        
        
        
        
        
        
        
        
        
        
        
        