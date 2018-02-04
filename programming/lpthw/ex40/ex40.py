# -- coding: utf-8 --
cities = {'CA': 'San Francisco', 'MI': 'Detroit', 'FL': 'Jacksonville'}


cities['NY'] = 'New York'
cities['OR'] = 'Portland'

# Python中已经有map函数了，所以这里用themap作为变量名
def find_city(themap, state):
    if state in themap:
        return themap[state]
    else:
        return "Not found."

# ok pay attention! 可以将函数名作为字典中的元素，和函数一样调用
cities['_find'] = find_city

while True:
    print "State? (ENTER to quit)",
    state = raw_input("> ")

    if not state: break

    # this line is the most important ever! study!
    city_found = cities['_find'](cities, state)
    print city_found
