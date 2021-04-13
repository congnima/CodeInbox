
def func(*args):
    print(args)

def func1(**kwargs):
    print(kwargs)

def func2(*args, **kwargs):
    print(args)
    print(kwargs)

func(1, 2, 3)
func1(a = 1, b = 2, c = 3)
# func2(a = 1, b = 2, c = 3, 1, 2, 3)
func2(1, 2, 3, a = 1, b = 2, c = 3)
