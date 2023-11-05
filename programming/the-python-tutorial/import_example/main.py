from foo.bar import greet
import sys

if __name__ == "__main__":
    print("sys.path")
    for p in sys.path:
        print(p)
    greet()

