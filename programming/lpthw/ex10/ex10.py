# -- coding: utf-8 --
tabby_cat = "\tI'm tabbed in."
persian_cat = "I'm split \non a line."
backslash_cat = "I'm \\ a \\ cat."

fat_cat = """
I'll do a list:
\t* Cat food
\t* Fishies
\t* Catnip\n\t* Grass
"""

print tabby_cat
print persian_cat
print backslash_cat
print fat_cat

# Extras
print "------"

new_fat_cat = '''
I'll do a list:
\t* Cat food
\t* Fishies
\t* Catnip\n\t* Grass
'''
print new_fat_cat

# 转义字符
# \(在行尾时) 续行符 
# \\ 反斜杠符号 
# \' 单引号 
# \" 双引号 
# \a 响铃 
# \b 退格(Backspace) 
# \e 转义 
# \000 空 
# \n 换行 
# \v 纵向制表符 
# \t 横向制表符 
# \r 回车 
# \f 换页 
# \oyy 八进制数yy代表的字符，例如：\o12代表换行 
# \xyy 十进制数yy代表的字符，例如：\x0a代表换行 
# \other 其它的字符以普通格式输出 

# %r 打印出来的是你写在脚本里的内容，而 %s 打印的是你应该看到的内容。