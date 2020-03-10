# 编写高质量代码：改善 Python 程序的91个建议

## 第1章 引论

### 建议1. 理解 Pythonic 概念

```shell
$ python -c "import this"
The Zen of Python, by Tim Peters

Beautiful is better than ugly.
Explicit is better than implicit.
Simple is better than complex.
Complex is better than complicated.
Flat is better than nested.
Sparse is better than dense.
Readability counts.
Special cases aren't special enough to break the rules.
Although practicality beats purity.
Errors should never pass silently.
Unless explicitly silenced.
In the face of ambiguity, refuse the temptation to guess.
There should be one-- and preferably only one --obvious way to do it.
Although that way may not be obvious at first unless you're Dutch.
Now is better than never.
Although never is often better than *right* now.
If the implementation is hard to explain, it's a bad idea.
If the implementation is easy to explain, it may be a good idea.
Namespaces are one honking great idea -- let's do more of those!
```

（1）Pythonic 的定义

充分体现 Python 自身特色，看起来像是伪代码。

（2）代码风格

充分利用 Python 语法，但不应当过分地使用奇技淫巧。

（3）标准库

写Pythonic程序需要对标准库有充分的理解，特别是内置函数和内置数据类型。

（4）Pythonic的库或框架

程序员利用Pythonic的库或框架能更加容易、更加自然地完成任务。如果用Python编写的库或框架迫使程序员编写累赘的或不推荐的代码，那么可以说它并不Pythonic。现在业内通常认为Flask这个框架是比较Pythonic的。

### 建议2：编写 Pythonic 代码

（1）要避免劣化代码

与优化代码对应，劣化代码就是一开始写出来就是不合理的代码，比如不合适的变量命名等。

​	1）避免只用大小写来区分不同的对象。

​	2）避免使用容易引起混淆的名称。

​	3）不要害怕过长的变量名。

（2）深入认识Python有助于编写Pythonic代码

	- 全面掌握Python提供给我们的所有特性，包括语言特性和库特性。其中最好的学习方式应该是通读官方手册中的Language Reference和Library Reference。
	- 学习每个Python新版本提供的新特性，以及掌握它的变化趋势。
	- 深入学习业界公认的比较Pythonic的代码，比如Flask、gevent和requests等。
	- 尝试利用工具达到事半功倍的效果。如使用 `pep8` 检查代码是否符合PEP8规范：`pep8 --first demo.py`。

### 建议3：理解Python与C语言的不同之处

（1）“缩进”与“{}”

与C、C++、Java等语言使用花括号{}来分隔代码段不同，Python中使用严格的代码缩进方式分隔代码块。统一缩进风格，不要混用 Tab 和空格。

（2）`'`与`"`

C语言中单引号（'）与双引号（"）有严格的区别，单引号代表一个字符，它实际对应于编译器所采用的字符集中的一个整数值。但在Python中，单引号与双引号没有明显区别，仅仅在输入字符串内容不同时，在使用上存在微小差异。

（3）三元操作符“?:”

三元操作符是if...else的简写方法，语法形式为C ? X: Y，它表示当条件C为True的时候取值X，C为False的时候取值为Y。

```python
In [7]: x = 1

In [8]: y = 2

In [9]: print(x if x < y else y)
1
```

（4）switch...case

在 Python 中优先用 if...elif...else 实现。下面的跳转表也可以实现：

```python
# 跳转表
In [3]: def f(x):
   ...:     return {
   ...:         0: "hello",
   ...:         1: "world"
   ...:     }.get(x, "not 0 or 1")
   ...:

In [4]: f(2)
Out[4]: 'not 0 or 1'

In [5]: f(1)
Out[5]: 'world'

In [6]: f(0)
Out[6]: 'hello'
```

### 建议4：在代码中适当添加注释

Python中有3种形式的代码注释：块注释、行注释以及文档注释（docstring）。

1）使用块或者行注释的时候仅仅注释那些复杂的操作、算法，还有可能别人难以理解的技巧或者不够一目了然的代码。

2）注释和代码隔开一定的距离，同时在块注释之后最好多留几行空白再写代码。

3）给外部可访问的函数和方法（无论是否简单）添加文档注释。注释要清楚地描述方法的功能，并对参数、返回值以及可能发生的异常进行说明，使得外部调用它的人员仅仅看docstring就能正确使用。

4）推荐在文件头中包含copyright申明、模块描述等，如有必要，可以考虑加入作者信息以及变更记录。

没有注释的代码通常会给他人的阅读和理解带来一定困难，即使是自己写的代码，过一段时间再回头阅读可能也需要一定时间才能理解当初的思路。

注释应该是用来解释代码的功能、原因以及想法的，而不是对代码本身的解释。

对于不再需要的代码，应该将其删除，而不是将其注释掉。即使你担心以后还会用到，版本控制工具也可以让你轻松找回被删除的代码。

### 建议5：通过适当添加空行使代码布局更为优雅、合理

布局清晰、整洁、优雅的代码能够给阅读它的人带来愉悦感，而且它能帮助开发者之间进行良好的沟通。在一个团队中，保持良好的代码格式需要团队成员在选取一套合适的代码格式规则的基础上遵从和应用。

1）在一组代码表达完一个完整的思路之后，应该用空白行进行间隔。如每个函数之间，导入声明、变量赋值等。

2）尽量保持上下文语义的易理解性。

3）避免过长的代码行，每行最好不要超过80个字符。

4）不要为了保持水平对齐而使用多余的空格，其实使阅读者尽可能容易地理解代码所要表达的意义更重要。

5）空格的使用要能够在需要强调的时候警示读者，在疏松关系的实体间起到分隔作用，而在具有紧密关系的时候不要使用空格。

### 建议6：编写函数的4个原则

函数能够带来最大化的代码重用和最小化的代码冗余。精心设计的函数不仅可以提高程序的健壮性，还可以增强可读性、减少维护成本。

原则1 函数设计要尽量短小，嵌套层次不宜过深。

原则2 函数申明应该做到合理、简单、易于使用。除了函数名能够正确反映其大体功能外，参数的设计也应该简洁明了，参数个数不宜太多。参数太多带来的弊端是：调用者需要花费更多的时间去理解每个参数的意思，测试人员需要花费更多的精力来设计测试用例，以确保参数的组合能够有合理的输出，这使覆盖测试的难度大大增加。

原则3　函数参数设计应该考虑向下兼容。实际工作中我们可能面临这样的情况：随着需求的变更和版本的升级，在前一个版本中设计的函数可能需要进行一定的修改才能满足这个版本的要求。因此在设计过程中除了着眼当前的需求还得考虑向下兼容。

原则4 一个函数只做一件事，尽量保证函数语句粒度的一致性。

Python中函数设计的好习惯还包括：不要在函数中定义可变对象作为默认值，使用异常替换返回错误，保证通过单元测试等。

### 建议7：将常量集中到一个文件

实际上Python的内建命名空间是支持一小部分常量的，如我们熟悉的True、False、None等，只是Python没有提供定义常量的直接方式而已。

```python
# Put in const.py...
# from http://code.activestate.com/recipes/65207-constants-in-python
class _const:
    class ConstError(TypeError): pass  # Base exception class.
    class ConstCaseError(ConstError): pass

    def __setattr__(self, name, value):
        if name in self.__dict__:
            raise self.ConstError("Can't change const.%s" % name)
        if not name.isupper():
            raise self.ConstCaseError('const name %r is not all uppercase' % name)
        self.__dict__[name] = value

# Replace module entry in sys.modules[__name__] with instance of _const
# (and create additional reference to it to prevent its deletion -- see
#  https://stackoverflow.com/questions/5365562/why-is-the-value-of-name-changing-after-assignment-to-sys-modules-name)
import sys
_ref, sys.modules[__name__] = sys.modules[__name__], _const()

import const

const.X = 1
const.Y = 2
const.Z = 3


# NOTE: To use const in other modules
# import const
# print(const.X, const.Y, const.Z)


if __name__ == '__main__':
    import __main__  as const  # Test this module...

    try:
        const.Answer = 42  # Not OK to create mixed-case attribute name.
    except const.ConstCaseError as exc:
        print(exc)
    else:  # Test failed - no ConstCaseError exception generated.
        raise RuntimeError("Mixed-case const names should't be allowed!")

    try:
        const.ANSWER = 42  # Should be OK, all uppercase.
    except Exception as exc:
        raise RuntimeError("Defining a valid const attribute should be allowed!")
    else:  # Test succeeded - no exception generated.
        print('const.ANSWER set to %d raised no exception' % const.ANSWER)

    try:
        const.ANSWER = 17  # Not OK, attempt to change defined constant.
    except const.ConstError as exc:
        print(exc)
    else:  # Test failed - no ConstError exception generated.
        raise RuntimeError("Shouldn't be able to change const attribute!")
```

这里涉及到了 Python 导包的问题，如何导入下划线开头的类或函数？

另一种做法，参考：https://www.programiz.com/python-programming/variables-constants-literals

## 第2章 编程惯用法

### 建议8 利用 assert 语句来发现问题

断言（assert）在很多语言中都存在，它主要为调试程序服务，能够快速方便地检查程序的异常或者发现不恰当的输入等，可防止意想不到的情况出现。

```python
assert expression ["," expression2]
```

加上-O的参数：`python -O asserttest.py` 便可以禁用断言。

断言实际是被设计用来捕获用户所定义的约束的，而不是用来捕获程序本身错误的。

1）不要滥用，这是使用断言最基本的原则。

2）如果Python本身的异常能够处理就不要再使用断言。

3）不要使用断言来检查用户的输入。

4）在函数调用后，当需要确认返回值是否合理时可以使用断言。

5）当条件是业务逻辑继续下去的先决条件时可以使用断言。

### 建议9：数据交换值的时候不推荐使用中间变量

```python
x, y = y, x
```

这种方式更加简洁、高效。

### 建议10：充分利用Lazy evaluation的特性

Lazy evaluation常被译为“延迟计算”或“惰性计算”，指的是仅仅在真正需要执行的时候才计算表达式的值。

1）避免不必要的计算，带来性能上的提升。

如果对于or条件表达式应该将值为真可能性较高的变量写在or的前面，而and则应该推后。

2）节省空间，使得无限循环的数据结构成为可能。Python中最典型的使用延迟计算的例子就是生成器表达式了，它仅在每次需要计算的时候才通过 `yield` 产生所需要的元素。斐波那契数列在Python中实现起来就显得相当简单，而while True也不会导致其他语言中所遇到的无限循环的问题。

```python
def fib():
    a, b = 0, 1
    while True:
        yield a
        a, b = b, a+b
        
In [16]: from itertools import islice

In [17]: print(list(islice(fib(), 5)))
[0, 1, 1, 2, 3]
```

生成器的知识点可以参考：https://www.liaoxuefeng.com/wiki/1016959663602400/1017318207388128

### 建议11：理解枚举替代实现的缺陷

关于枚举最经典的例子大概非季节和星期莫属了，它能够以更接近自然语言的方式来表达数据，使得程序的可读性和可维护性大大提高。

推荐使用 Python3 的内置 `enum` 模块：

```python
>>> from enum import Enum
>>> class Color(Enum):
...     RED = 1
...     GREEN = 2
...     BLUE = 3
...
```

默认是不同枚举名称可以赋值一样，可以加 `@unique` 来避免。

更多用法参考：https://docs.python.org/3/library/enum.html

### 建议12：不推荐使用type来进行类型检查

推荐使用 `isinstance` 来做类型检查，不推荐 `type`，因为“基于内建类型扩展的用户自定义类型，type函数并不能准确返回结果。”

```python
In [23]: class UserInt(int):
    ...:     pass
    ...:

In [24]: a = UserInt()

In [25]: a
Out[25]: 0

In [26]: type(a)
Out[26]: __main__.UserInt

In [27]: isinstance(a, int)
Out[27]: True

In [28]: b = 1

In [29]: type(a) == type(b)
Out[29]: False

In [30]: isinstance(a, UserInt)
Out[30]: True
```

### 建议13：尽量转换为浮点类型后再做除法

随着Python语言的发展，对整数除法问题也做了一定的修正，在Python3中这个问题已经不存在了。Python3之前的版本可以通过 `from future importdivision`机制使整数除法不再截断，这样即使不进行浮点类型转换，输出结果也是正确的（请读者自行试验）。

```python
$ python2 -c "from __future__ import division; print 5 / 2"
2.5
$ python2 -c "print 5 / 2"
2
```

在计算机的世界里，浮点数的存储规则决定了不是所有的浮点数都能准确表示，有些是不准确的，只是无限接近。如0.1转换为二进制表示形式则为0.000110011001……后面1001无限循环。

对于在while中使用i!=1.5这种条件表达式更是要避免的，浮点数的比较同样最好能够指明精度。

```python
In [38]: i = 1

In [39]: while i != 1.5:
    ...:     i = i + 0.1
    ...:     print(i)
    ...:     if i > 1.6:
    ...:         break
    ...:
1.1
1.2000000000000002
1.3000000000000003
1.4000000000000004
1.5000000000000004
1.6000000000000005
```

