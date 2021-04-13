import sys

class Test(object):
    def __init__(self):
        1/0

def factory():
    return Test()

try:
    test = factory()
except:
    print('Unexpected error:', sys.exc_info()[0])
