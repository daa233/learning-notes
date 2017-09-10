# Simple version of Dog
'''
class Dog:
    kind = 'canine'         # class variable shared by all instances

    def __init__(self, name):
        self.name = name    # instance variable unique to each instance
'''

# Wrong design of Dog
'''
class Dog:

    tricks = []     # mistaken use of a class variable

    def __init__(self, name):
        self.name = name

    def add_trick(self, trick):
        self.tricks.append(trick)
'''

# Correct design of Dog
class Dog:
    def __init__(self, name):
        self.name = name
        self.tricks = []    # create a new empty list for each dog

    def add_trick(self, trick):
        self.tricks.append(trick)
