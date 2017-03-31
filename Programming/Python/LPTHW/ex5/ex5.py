# --coding: utf-8 --
my_name = 'Zed A. Shaw'
my_age = 35 # not a lie
my_height = 74 # inches
my_weight = 180 # lbs
my_eyes = 'Blue'
my_teeth = 'White'
my_hair = 'Brown'


print "Let's talk about %s. " % my_name
print "He's %d inches tall. " % my_height
print "He's %r cms tall. " % (2.54 * my_height)
print "He's %d pounds heavy. " % my_weight
print "He's %r kgs heavy. " % (0.45359 * my_weight)
print "Actually that's not too heavy. "
print "He's got %s eyes and %s hair. " % (my_eyes, my_hair)
print "His teeth are usually %s depending on the coffee. " % my_teeth

# this line is tricky, try to get it exactly right
print "If I add %d, %d, and %d I get %d. " % (my_age, my_height, my_weight,
    my_age + my_height + my_weight)

temp = "daskfjsalkd"
print "The temp is %r" % temp

'''
格式化符号   说明
%c  转换成字符（ASCII 码值，或者长度为一的字符串）
%r  优先用repr()函数进行字符串转换（Python2.0新增）
%s  优先用str()函数进行字符串转换
%d / %i      转成有符号十进制数
%u  转成无符号十进制数
%o  转成无符号八进制数
%x / %X     (Unsigned)转成无符号十六进制数（x / X 代表转换后的十六进制字符的大
小写）
%e / %E     转成科学计数法（e / E控制输出e / E）
%f / %F     转成浮点数（小数部分自然截断）
%g / %G     %e和%f / %E和%F 的简写
%%  输出%
'''