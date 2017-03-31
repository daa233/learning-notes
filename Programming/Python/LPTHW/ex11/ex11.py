print "How old are you?",
age = raw_input()
print "How tall are you?",
height = raw_input()
print "How much do you weigh?",
weight = raw_input()

print "So, you're %r old, %r tall and %r heavy." % (age, height, weight)

# Extras 有关raw_input
'''
raw_input() 直接读取控制台的输入（任何类型的输入它都可以接收）。而对于 input() ，它希望能够读取一个合法的 python 表达式，
即你输入字符串的时候必须使用引号将它括起来，否则它会引发一个 SyntaxError 。

例子 2 可以看到：raw_input() 将所有输入作为字符串看待，返回字符串类型。而 input() 在对待纯数字输入时具有自己的特性，
它返回所输入的数字的类型（ int, float ）；同时在例子 1 知道，input() 可接受合法的 python 表达式，
举例：input( 1 + 3 ) 会返回 int 型的 4 。

查看 Built-in Functions ，得知：

input([prompt])

    Equivalent to eval(raw_input(prompt)) 

input() 本质上还是使用 raw_input() 来实现的，只是调用完 raw_input() 之后再调用 eval() 函数，
所以，你甚至可以将表达式作为 input() 的参数，并且它会计算表达式的值并返回它。

不过在 Built-in Functions 里有一句话是这样写的：Consider using the raw_input() function for general input from users.

除非对 input() 有特别需要，否则一般情况下我们都是推荐使用 raw_input() 来与用户交互。
'''