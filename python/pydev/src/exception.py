#try:
#    x = input("input the first number: ")
#    y = input("input the second number: ")
#    print x/y
#except (ZeroDivisionError,TypeError), e:
## print "the second number can't be zero!"
#    print e
#-------------------------------------
#try:
#    print "A simple test..."
#except:
#    print "What? Something went wrong?"
#else:
#    print "Ah...It went as planned"
#-------------------------------------
#while True:
#    try:
#        x = input("Enter the first number: ")
#        y = input("Enter the second number: ")
#        value = x / y
#        print 'x/y is', value
#    except Exception,e:
##        print 'Invalid input: Please try again.'
#        print e
#    else:
#        break
try:
    x = 1 / 0
except NameError:
    print 'Unknown variable...'
else:
    print 'That went well!'
finally:
    print 'cleaning up...'
    
def describePerson(person):
    print 'Description of',person['name']
    print 'Age:',person['age']
    try:
        #attention: print 'Occupation: ',person['occupation']
        print 'Occupation: ' + person['occupation']
    except:
        pass


























