def init(data):
    data['first'] = {}
    data['middle'] = {}
    data['last'] = {}
def lookup(data,label,name):
    return data[label].get(name)
def store(data,full_name):
    names = full_name.split()
    if len(names) == 2: names.insert(1, '')
    labels = 'first', 'middle', 'last'
    for label, name in zip(labels, names):
        people = lookup(data, label, name)
        if people:
            people.append(full_name)
        else:
            data[label][name] = [full_name]
def store2(data,*full_names):
    for full_name in full_names:
        names = full_name.split()
        if len(names) == 2: names.insert(1, '')
        labels = 'first', 'middle', 'last'
        for label, name in zip(labels, names):
            people = lookup(data, label, name)
            if people:
                people.append(full_name)
            else:
                data[label][name] = [full_name]
def story(**kwds):
    return 'Once upon a time, there was a ' \
            '%(job)s called %(name)s.' % kwds
def power(x,y,*others):
    if others:
        print 'received redundant parameters:',others
    return pow(x, y)
def multiplier(factor):
    def multiplyByFactor(number):
        return number*factor
    return multiplyByFactor
def factorial(n):
    result = n
    for i in range(1, n):
        result *= i
    return result
def factorial1(n):
    if n == 1:
        return n
    else:
        return n * factorial1(n - 1)
def search(sequence,number,lower,upper):
    if lower == upper:
        assert number == sequence[upper]
        return upper
    else:
        middle = (lower + upper) / 2
        if number > sequence[middle]:
            return search(sequence, number, middle + 1, upper)
        else:
            return search(sequence, number, lower, middle)
       









