import sys
import traceback

g_list = ['a', 'b', 'c', 'd', 'e', 'f', 'g']


def f():
    g_list[5]
    return g()


def g():
    return h()


def h():
    del g_list[2]
    return i()


def i():
    g_list.append('i')
    print(g_list[7])


def print_custom_traceback():
    tb_type, tb_val, exc_tb = sys.exc_info()
    print("Custom Traceback (most recent call last):")
    for filename, linenum, funcname, source in traceback.extract_tb(exc_tb):
        print('  File "{}", line {}, in {}\n    {}'.format(
            filename, linenum, funcname, source
        ))


if __name__ == '__main__':
    try:
        f()
    except Exception as e:
        print("Sorry, out of range error")
        print(e)
        print("-"*60)
        traceback.print_exc(file=sys.stdout)
        # print_custom_traceback()
        print("-"*60)
        
