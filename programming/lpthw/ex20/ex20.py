# -- coding: utf-8 --
from sys import argv

script, input_file = argv

def print_all(f):
	print f.read()
# Move to the start position of the file
def rewind(f):
	f.seek(0)

def print_a_line(line_count, f):
	print line_count, f.readline()

current_file = open(input_file)

print "First let's print the whole file:\n"

print_all(current_file)

print "Now let's rewind, kind of like a tape."
rewind(current_file)

print "Let's print three lines:"

current_line = 1
print_a_line(current_line, current_file)

current_line = current_line + 1
print_a_line(current_line, current_file)

current_line = current_line + 1
print_a_line(current_line, current_file)

'''
# Extras
# 看来file对象内部有个变量会记录当前读取的行的位置，
# 每次使用readline()后，该变量增加一行
def print_a_new_line(f):
	print f.readline()
rewind(current_file)
print_a_new_line(current_file)
print_a_new_line(current_file)
print_a_new_line(current_file)
'''