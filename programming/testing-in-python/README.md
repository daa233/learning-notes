# Testing in Python

参考 [Getting Started With Testing in Python](https://realpython.com/python-testing/) 和 Facebook Research 的 [fvcore](https://github.com/facebookresearch/fvcore/) 学习写 Python 的测试代码。



## 测试你的代码

### 自动测试 vs. 手动测试

你可能已经做过测试了，只是你没意识到而已。例如，我们写了一个程序，然后通过运行验证是否实现了期望的功能，这其实就是一种手动测试（manual testing）的方法，称为探索性测试（exploratory testing）。在做探索性测试的时候，我们没有一个完整的计划，纯粹就是探索。

如果想要进行完成的手动测试，我们就要将程序所有的功能列下来，然后给出它所有可能的输入类型，以及对应的期望结果。这样，如果每次更改代码了，都要把这个过程过一遍，过程十分繁琐。

自动化测试（automated testing）就是为了解决上面的问题而出现的，意思就是用脚本来代替人，按照给定的计划进行测试。

> Automated testing is the execution of your test plan (the parts of your application you want to test, the order in which you want to test them, and the expected responses) by a script instead of a human.

### 单元测试 vs. 集成测试

测试中有很多术语。

假如我们要测试一辆车的灯光，我们可能会在车内打开车灯（这是 testing step），然后自己去车外或者叫朋友去车外看看车灯是否亮了（这是 test assertion）。如果我们测试的是很多个组件，就叫集成测试（integration testing）。对应到我们写的程序中，这些组件就是类、函数、模块等。

集成测试存在一个挑战，就是一旦测试结果对不上，我们很难诊断到底是哪个部分出了问题。单元测试（unit testing）可以解决这个问题。单元测试用来测试一些小的单一组件是否正常工作。

在 Python 中，集成测试和单元测试都可以写。

例如，对 `sum()` 进行简单的单元测试：

```python
>>> assert sum([1, 2, 3]) == 6, "Should be 6"
```

因为值正确，所以在交互式解释器上（REPL）不会有任何输出。

反之，如果值不正确，就会报错并输出后面的提示语句：

```python
>>> assert sum([1, 1, 1]) == 6, "Should be 6"
---------------------------------------------------------------------------
AssertionError                            Traceback (most recent call last)
<ipython-input-154-fa10351dd942> in <module>
----> 1 assert sum([1, 1, 1]) == 6, "Should be 6"

AssertionError: Should be 6
```

除了在 REPL 上运行，我们也可以写成文件 `test_sum.py` 然后执行：

```python
def test_sum():
    assert sum([1, 2, 3]) == 6, "Should be 6"

if __name__ == '__main__':
    test_sum()
    print("Everything passed")
```

这样我们就写好了一个测试样例（test case），一个 test assertion，我们还有一个 entry point（指的是加上了 `if __name__ == '__main__'`语句，可以通过命令运行，即 entry point 就是命令行）：

```shell
$ python test_sum.py
Everything passed
```

在 Python 中，`sum()` 可以接受任何 iteratle 的对象作为第一个参数。刚刚写的是 list 类型，也可以写 tuple 类型。创建 `test_sum_2.py` 文件，写入以下代码：

```python
def test_sum():
    assert sum([1, 2, 3]) == 6, "Should be 6"

def test_sum_tuple():
    assert sum((1, 2, 2)) == 6, "Should be 6"

if __name__ == '__main__':
    test_sum()
    test_sum_tuple()
    print("Everything passed")
```

这里在第二个断言语句中，故意将 `(1, 2, 2)` 的和与 `6` 比较，以获得报错信息。在终端运行时，会有以下结果：

```shell
$ python test_sum_2.py
Traceback (most recent call last):
  File "test_sum_2.py", line 12, in <module>
    test_sum_tuple()
  File "test_sum_2.py", line 7, in test_sum_tuple
    assert sum((1, 2, 2)) == 6, "Should be 6"
AssertionError: Should be 6
```

上面的报错信息给出了错误发生的位置和期望的结果是什么。

像上面这种方式测试，做简单的验证还是可以的，但是如果进行复杂的测试，程序中可能很多错误的时候，就需要用 test runner 了。

> The test runner is a special application designed for running tests, checking the output, and giving you tools for debugging and diagnosing tests and applications.

### Test Runner 的选择

Python 中有很多 test runner，Python 标准库中内置的是 `unittest`。常见的 test runner 有：

- `unittest`
- `nose` or `nose2`
- `pytest`

#### `unittest`

`unittest` 中既包含一个 testing framework，又包含一个 test runner。

在写和执行测试代码时，`unittest`有一些重要的要求：

- 把测试代码写成类的方法
- 要使用 `unittest.TestCase` 中定义的特殊断言方法，而不能使用 Python 内置的 `assert` 语句

将前面的例子改写以使用 `unittest`，需要做以下工作：

1. 导入 `unittest` 标准库

2. 创建一个 `TestSum` 类，并且继承自 `TestCase` 类

3. 将测试函数改写成 `TestSum` 类中的方法

4. 将  `assert` 改成 `TestCase` 类中的 `self.assertEqual()`

5. 将命令行 entry point 改成调用 `unittest.main()`

下面是 `test_sum_unittest.py` 样例：

```python
import unittest


class TestSum(unittest.TestCase):

    def test_sum(self):
        self.assertEqual(sum([1, 2, 3]), 6, "Should be 6")

    def test_sum_tuple(self):
        self.assertEqual(sum((1, 2, 2)), 6, "Should be 6")


if __name__ == '__main__':
    unittest.main()
```

在终端运行结果如下：

```shell
$ python test_sum_unittest.py
.F
======================================================================
FAIL: test_sum_tuple (__main__.TestSum)
----------------------------------------------------------------------
Traceback (most recent call last):
  File "test_sum_unittest.py", line 10, in test_sum_tuple
    self.assertEqual(sum((1, 2, 2)), 6, "Should be 6")
AssertionError: 5 != 6 : Should be 6

----------------------------------------------------------------------
Ran 2 tests in 0.001s

FAILED (failures=1)
```

这样就用 `unittest` 运行了两个测试，失败了一个。

关于 `unittest` 的更多信息参考 [unittest Documentation](https://docs.python.org/3/library/unittest.html)。

#### `nose`

你可能会发现，随着时间流逝，当我们为应用程序编写了成百上千个测试的时候，使用 `unittest` 的输出越来越难以理解和使用。

`nose` 支持 `unittest` framework 的所有测试代码，而且是 `unittest` test runner 的直接替代品。`nose2` 是基于 `nose` 的一个分支，推荐使用 `nose2`，可以通过 PyPI 安装：`pip install nose2`。

> nose2’s purpose is to extend `unittest` to make testing nicer and easier to understand.

`nose2` 会自动发现所有以 `test*` 开头命名的测试脚本以及从 `unittest` 继承给过来的测试样例。例如上面的例子，可以在当前文件夹执行：

```shell
$ nose2		# now only test_sum_unittest.py in the current directory
.F
======================================================================
FAIL: test_sum_tuple (test_sum_unittest.TestSum)
----------------------------------------------------------------------
Traceback (most recent call last):
  File "/Users/duang/Documents/projects/learning-notes-2/programming/testing-in-python/test_sum_unittest.py", line 10, in test_sum_tuple
    self.assertEqual(sum((1, 2, 2)), 6, "Should be 6")
AssertionError: 5 != 6 : Should be 6

----------------------------------------------------------------------
Ran 2 tests in 0.000s

FAILED (failures=1)
```

`nose2` 提供了很多命令行参数，可以用来过滤要执行的测试。如果想要了解更多信息，参考 [nose 2 documentation](https://nose2.readthedocs.io/)。

 #### `pytest`

`pytest` 也支持执行 `unittest` 的测试样例。`pytest` 的优势是写 `pytest` 版的测试样例，`pytest` 版的测试样例是 Python 脚本文件中一系列以 `test_` 开头的函数。

`pytest` 还有以下特色：

- 支持 Python 内置的 `assert` 语句
- 支持过滤测试样例
- 能够从失败的测试返回
- 有一个良好的生态，数百插件供扩展功能

> The `pytest` framework makes it easy to write small tests, yet scales to support complex functional testing for applications and libraries.

```python
# content of test_sample.py
def func(x):
    return x + 1


def test_answer():
    assert func(3) == 5
```

在命令行运行 `pytest`，输出结果：

```shell
$ pytest	# now only test_sample.py in the current directory
============================= test session starts ==============================
platform darwin -- Python 3.7.3, pytest-5.3.1, py-1.8.0, pluggy-0.13.1
rootdir: /Users/duang/Documents/projects/learning-notes/programming/testing-in-python/pytest_sample
collected 1 item

test_sample.py F                                                         [100%]

=================================== FAILURES ===================================
_________________________________ test_answer __________________________________

    def test_answer():
>       assert func(3) == 5
E       assert 4 == 5
E        +  where 4 = func(3)

test_sample.py:8: AssertionError
============================== 1 failed in 0.13s ===============================
```

**注意：**MacOS 可能自带了 Python2 版本的旧的 `pytest`，路径为 `/usr/local/bin/pytest`，如果干扰了其他版本 `pytest` 的路径，可以通过 `pip2 uninstall pytest` 卸载旧版的。

有关 `pytest` 的更多信息参考 [Pytest Documentation Website](https://docs.pytest.org/en/latest/)。

---

经过简单的不完全测试，`nose2` 和 `pytest` 都支持 `unittest` 的测试代码，但是二者识别的文件头不一样，`nose2` 识别的是 `test*`，`pytest` 识别的是 `test_*`；`nose2` 是基于 `unittest` 的，再次基础上支持了更多特性；`nose2` 和 `pytest` 都支持各自的写法，而且都可以不继承 `unittest.TestCase`，不用写 `main` 函数；`pytest` 的输出看上去更美观、更现代一些，`nose2` 文档里推荐 Python 初学者使用 `pytest`。



## 写第一份测试

创建一个项目 `project`，使用 `tree -F project/` 显示目录结构如下：

```text
project/
└── my_sum/
    └── __init__.py
```

下面是 `__init__.py` 的内容：

```python
def sum(arg):
    total = 0
    for val in arg:
        total += val
    return total
```

代码中的 `total` 会将 `arg` 中的所有值加在一起，然后返回最终的结果。

### 将测试代码写在哪里

现在是刚开始写，我们可以直接在项目根目录里创建一个 `test.py`：

```text
project/
├── my_sum/
│   └── __init__.py
└── test.py
```

但是当我们写的测试越来越多，这个 `test.py` 会变得越来越混乱和臃肿，难以维护。这时我们可以创建一个 `tests/` 文件夹，然后在里面写很多个测试文件。按照惯例，测试文件需要以 `test_` 开头，这样才能被 test runner 识别和执行（注意：上面的 `test.py` 不能被 `pytest` 识别）。一些更大的项目可能会在测试文件夹中分更多的子文件夹。

### 怎样组织测试代码

写测试之前，需要考虑几件事：

1. 想要测试什么？
2. 是写单元测试还是写集成测试？

然后工作流大致如下：

1. 创建输入
2. 执行要测试的代码，得到输出
3. 将输出和期待结果进行对比

在这个项目中，我们要测试自定义的 `sum()` 函数。这里有很多情形需要测试，例如：

- 它能对一个整数 list 求和吗？
- 它能对一个 tuple 或者 set 求和吗？
- 它能对一个浮点数 list 求和吗？
- 如果碰到不好的输入怎么办？例如一个整数和一个字符串
- 如果输入的一个值是负的怎么办？

最简单的情况就是对一个整数 list 求和，可以在 `test.py` 中加入以下代码：

```python
from my_sum import sum


class TestSum(unittest.TestCase):
    def test_list_int(self):
        """
        Test that it can sum a list of integers
        """
        data = [1, 2, 3]
        result = sum(data)
        self.assertEqual(result, 6)


if __name__ == '__main__':
    unittest.main()
```

### 怎样写断言

我们用断言（assertion）来验证程序输出是否符合期望。这里有一些写断言的最佳实践：

- 确保测试是可复现的，多次运行结果一致
- 要让断言的结果和输入数据相关联，例如判断 `sum()` 函数的输出是不是各个值的和（这里有点啰嗦，应该是提醒的作用）

`unittest` 中提供了与值、类型、变量的存在性等相关的各种断言方法，下面是一些常用的：

| Method                    | Equivalent to      |
| ------------------------- | ------------------ |
| `.assertEqual(a, b)`      | `a == b`           |
| `.assertTrue(x)`          | `bool(x) is True`  |
| `.assertFalse(x)`         | `bool(x) is False` |
| `.assertIs(a, b)`         | `a is b`           |
| `.assertIsNone(x)`        | `x is None`        |
| `.assertIn(a, b)`         | `a in b`           |
| `.assertIsInstance(a, b)` | `isinstance(a, b)` |

`.assertIs()`、`.assertIsNone()`、`.assertIn()` 和 `.assertIsInstance()` 都有对应的取反方法，例如 `.assertIsNot()`。

### 副作用

在写测试的时候，经常不是看看一个函数的返回值是多少那么简单。很多时候，执行一段代码会改变环境里的其他的东西，例如类的属性、文件系统里的文件或者数据库里的值，这就是副作用（side effects）。副作用是测试中很重要的一部分。在将一个东西加入断言列表前，先判断是否测试了它的副作用。

如果一个单元测试代码有很多副作用，我们可能已经违反了“单一职责原则”（[Single Responsibility Principle](https://en.wikipedia.org/wiki/Single_responsibility_principle)）。违反了单一职责原则意味着我们的代码做了太多事，最好重构一下。遵循“单一职责原则”是一种设计代码的好方法，该代码很容易为最终的可靠应用编写可重复且简单的单元测试。



## 执行第一份测试

### 执行 Test Runner

Python 程序中执行我们的测试代码、检查断言并且告知我们测试结果的东西叫 **test runner**。

> The Python application that executes your test code, checks the assertions, and gives you test results in your console is called the **test runner**.

```python
if __name__ == '__main__':
  unittest.main()
```

这是一个命令行 entry point，可以通过 `python test.py` 或者 `python -m unittest test` 来执行。第二种方式还可以在执行时添加参数，例如：

```shell
$ python -m unittest -v test
test_list_int (test.TestSum) ... ok

----------------------------------------------------------------------
Ran 1 test in 0.000s

OK
```

上面 `python -m unittest test` 中的 `test`  是 module name，还可以换成 `discover`，之后会自己寻找 `test*` 开头的文件并尝试测试：`python -m unittest discover`。

如果我们在 `tests` 文件夹下有多个测试文件 `test*.py`，可以使用 `-s` 参数指定测试的文件夹：

```shell
$ python -m unittest discover -s tests
```

这样 `unittest` 会将所有的测试都在一个 test plan 中运行，并且给出最终结果。

如果源代码不在项目根目录下，例如在 `src/` 子目录下，可以加 `-t` 参数：

```shell
$ python -m unittest discover -s tests -t src
```

这样 `unittest` 会切换到 `src/` 目录下，扫描所有的 `test*.py` 文件，然后测试它们。

### 理解测试输出

`sum()` 应该也能支持其他类型的 list，比如分数（`fractions.Fraction`）。修改 `test.py`来测试 `sum()` 对分数的支持：

```python
import unittest
from fractions import Fraction

from my_sum import sum


class TestSum(unittest.TestCase):

    def test_list_int(self):
        """
        Test that it can sum a list of integers
        """
        data = [1, 2, 3]
        result = sum(data)
        self.assertEqual(result, 6)

    def test_list_fraction(self):
        """
        Test that is can sum a list of fractions
        """
        data = [Fraction(1, 4), Fraction(1, 4), Fraction(2, 5)]
        result = sum(data)
        self.assertEqual(result, 1)


if __name__ == '__main__':
    unittest.main()
```

再次执行 `python -m unittest test`，会有以下结果：

```shell
$ python -m unittest test
F.
======================================================================
FAIL: test_list_fraction (test.TestSum)
----------------------------------------------------------------------
Traceback (most recent call last):
  File "test.py", line 23, in test_list_fraction
    self.assertEqual(result, 1)
AssertionError: Fraction(9, 10) != 1

----------------------------------------------------------------------
Ran 2 tests in 0.001s

FAILED (failures=1)
```

在输出中，可以看到以下信息：

1. 第一行是所有测试的执行结果，包括失败的（`F`）和通过的（`.`）。
2. `FAIL` 处给出了失败的更详细信息，包括方法名字、具体的 test case、断言语句等等。

可以加上 `-v` 参数来获得更详细的输出信息。

### 在 PyCharm 和 Visual Studio Code 中运行测试

（略）



## 对网络框架 Django 和 Flask 进行测试

（略）



## 更高级的测试场景

在对应用创建测试之前，牢记三个基本步骤：

1. 创建输入
2. 执行代码，获得输出
3. 比较输出和预期结果

但是有时候应用的输入不是简单的几个数或者字符串，有可能需要一个类或者 context，这时应该怎么办呢？

我们创建的输入数据被称为 **fixture**。

如果我们运行同样的测试，每次传入不同的值并且预期得到的同样的结果，这被称为 **parameterization**。

### 处理预期中的失败

如果某个错误是我们预期得到的，比如给 `sum()` 传入 bad value 应该报错，这时我们可以使用 `.assertRaises()` 这个 context-manager：

```python
import unittest
from fractions import Fraction

from my_sum import sum


class TestSum(unittest.TestCase):

    def test_list_int(self):
        """
        Test that it can sum a list of integers
        """
        data = [1, 2, 3]
        result = sum(data)
        self.assertEqual(result, 6)

    def test_list_fraction(self):
        """
        Test that is can sum a list of fractions
        """
        data = [Fraction(1, 4), Fraction(1, 4), Fraction(2, 5)]
        result = sum(data)
        self.assertEqual(result, 1)

    def test_bad_type(self):
        data = "banana"
        with self.assertRaises(TypeError):
            result = sum(data)


if __name__ == '__main__':
    unittest.main()
```

### 隔离应用中的行为

前面提到了副作用，它会让单元测试更加困难，每次运行测试，可能得到不同的结果；甚至有更糟的情况，某个测试结果可能影响应用的状态，从而导致其他测试失败。

如果应用的某一部分出现了很多副作用，可以使用下面这些技巧来解决：

- 遵循单一职责原则重构代码
- 使用 Mocking
- 对这一部分使用集成测试而不是单元测试

如果你不熟悉 mocking，参考 [Python CLI Testing](https://realpython.com/python-cli-testing/#mocks) 或/和 [Python之Mock的入门](https://www.cnblogs.com/Zzbj/p/10594633.html)。

### 写集成测试

单元测试是构建可预期的、稳定的程序的好方法，但是最后我们还需要写集成测试。

集成测试是为了同时测试应用中的各个组件，来检查它们是否能同时工作。集成测试可能会需要像应用的用户一样的操作：

- 调用 HTTP REST API
- 调用 Python API
- 调用网络服务
- 运行命令行程序

写集成测试和写单元测试没有太大区别。只是写集成测试需要同时测试多个组件，需要更多的 fixtures，如数据库、network socket、配置文件等，也会面临更多的副作用。

这也就是为什么我们最好把单元测试和集成测试分开。集成测试的 fixture 比较庞大，执行起来也更加费时，所以我们一般不会在每次提交更新代码后都运行集成测试，而是只是在上线前运行。

一种简单的隔离单元测试和集成测试的方法就是把它们放在不同的文件夹下：

```text
project/
│
├── my_app/
│   └── __init__.py
│
└── tests/
    |
    ├── unit/
    |   ├── __init__.py
    |   └── test_sum.py
    |
    └── integration/
        ├── __init__.py
        └── test_integration.py
```

执行集成测试：

```shell
$ python -m unittest discover -s tests/integration
```

### 测试数据驱动的应用程序

很多集成测试需要提供一些后端数据，如数据库。举个例子，假如我们想测试某个应用程序能否正常显示数据库中100名顾客的信息，甚至有些顾客的名字是汉语的。

这种类型的集成测试需要不同的 test fixtures，以确保程序是可重复的、可预测的。

一种比较好的方法是把测试数据存储在测试文件夹下的 `fixtures` 文件夹下，然后每次测试的时候导入这些数据。下面是一个示例的目录结构，包含一些 JSON 格式的测试数据：

```text
project/
│
├── my_app/
│   └── __init__.py
│
└── tests/
    |
    └── unit/
    |   ├── __init__.py
    |   └── test_sum.py
    |
    └── integration/
        |
        ├── fixtures/
        |   ├── test_basic.json
        |   └── test_complex.json
        |
        ├── __init__.py
        └── test_integration.py
```

在测试代码中，可以使用 `.setUp()` 方法来从某个 fixture 文件导入测试数据，然后依据这份数据执行多个测试。

```python
import unittest


class TestBasic(unittest.TestCase):
    def setUp(self):
        # Load test data
        self.app = App(database='fixtures/test_basic.json')

    def test_customer_count(self):
        self.assertEqual(len(self.app.customers), 100)

    def test_existence_of_customer(self):
        customer = self.app.get_customer(id=10)
        self.assertEqual(customer.name, "Org XYZ")
        self.assertEqual(customer.address, "10 Red Road, Reading")


class TestComplexData(unittest.TestCase):
    def setUp(self):
        # load test data
        self.app = App(database='fixtures/test_complex.json')

    def test_customer_count(self):
        self.assertEqual(len(self.app.customers), 10000)

    def test_existence_of_customer(self):
        customer = self.app.get_customer(id=9999)
        self.assertEqual(customer.name, u"张三")
        self.assertEqual(customer.address, "238 Songling Road, Qingdao")

if __name__ == '__main__':
    unittest.main()
```



## 在多个不同的环境中测试

如果我们需要测试应用程序在不同版本的 Python 或者不同版本的其他包上的运行情况，可以使用 Tox。

> Tox is an application that automates testing in multiple environments.

具体参考 [Tox Documentation Website](https://tox.readthedocs.io/en/latest/)。



## 自动执行测试

之前我们都是通过运行一个命令来执行测试，有一些工具可以在我们对代码进行更新后自动执行测试。自动测试工具通常被称为 CI/CD 工具，意思是“持续集成/部署”（Continuous Integration/Continuous Deployment）。它们可以运行测试、编译、发布应用，甚至将它们部署到生产中。

[Travis CI](https://travis-ci.com/) 是一个比较常用的 CI 服务，对 Python 适配也很好。GitHub、GitLab 上的所有的开源项目都可以免费使用 Travis CI。

将项目托管到 GitHub/GitLab，然后创建一个 `.travis.yml` 文件：

```yaml
language: python
python:
  - "2.7"
  - "3.7"
install:
  - pip install -r requirements.txt
script:
  - python -m unittest discover
```

在配置完成后，之后我们每次上传代码更新远程 Git 仓库，Travis CI 都会执行测试命令，并且可以在它们的网站上查看测试结果。



## 测试机器学习模型

参考博客 [How to unit test machine learning code](https://medium.com/@keeper6928/how-to-unit-test-machine-learning-code-57cf6fd81765) 和 Facebook Research GitHub Repo [fvcore](https://github.com/facebookresearch/fvcore)。



## 接下来呢？

### 引入 Linter

> A linter will look at your code and comment on it. It could give you tips about mistakes you’ve made, correct trailing spaces, and even predict bugs you may have introduced.

在上面的介绍中，我们只让 Tox 和 Travis CI 执行了测试命令，其实也可以执行其他命令，例如 linter 的相关命

令。

有关 linter 的相关信息，参考 [Python Code Quality tutorial](https://realpython.com/python-code-quality/)。

#### 使用 `flake8` 进行 Passive Linting

> A popular linter that comments on the style of your code in relation to the [PEP 8](https://www.youtube.com/watch?v=Hwckt4J96dI) specification is `flake8`.

可以使用 `pip` 安装 `flake8`，运行 `flake8` 时可以指定文件、文件夹或者不指定：

```shell
$ pip install flake8
$ flake8
./test.py:28:13: F841 local variable 'result' is assigned to but never used
```

输出包含了 `flake8` 检测到的错误和警告，每条都对应一个规则代号，例如上面的是 `F841`。

`flake8` 可以通过配置文件或者命令行参数来进行配置。`flake8` 会寻找项目目录下的 `.flake8` 文件或者 `setup.cfg` 文件。如果使用 Tox，也可以把在 `tox.ini` 中配置 `flake8`。

下面是 `flake8` 的一个示例配置文件：

```yacas
[flake8]
ignore = E305
exclude = .git,__pycache__
max-line-length = 90
```

>  It is common to set the line length for tests to up to 120 characters.

详细参数参考 [Flake8 Documentation Website](http://flake8.pycqa.org/en/latest/user/options.html)。

也可以将 `flake8` 加入到 CI 的配置中，例如 Travis CI：

```yaml
matrix:
  include:
    - python: "3.7"
      script: "flake8"
```

Travis 会读取项目中的 `.flake8` 配置文件，并且如果项目中有任何 linting 错误就会构建失败。

#### 使用 Code Formatter 进行 Aggressive Linting

> `flake8` is a passive linter: it recommends changes, but you have to go and change the code. A more aggressive approach is a code formatter. Code formatters will change your code automatically to meet a collection of style and layout practices.

`black` 是一个很严格的格式化程序，可通过 `pip` 安装，仅支持 Python 3.6+。它没有任何配置选项而且有一个特定的代码风格，所以非常适合用于测试。

```shell
$ black test.py
reformatted test.py
All done! ✨ 🍰 ✨
1 file reformatted.
```

更多信息参考 [GitHub Website](https://github.com/psf/black)。

#### *使用 `isort` 自动排序导包信息

> isort is a Python utility / library to sort imports alphabetically, and automatically separated into sections. It provides a command line utility, Python library and [plugins for various editors](https://github.com/timothycrosley/isort/wiki/isort-Plugins) to quickly sort all your imports. It requires Python 3.6+ to run but supports formatting Python 2 code too.

在命令行中运行：

```shell
isort -y -sp .
```

在 `setup.cfg` 中配置：

```yacas
[isort]
line_length=80
multi_line_output=3
include_trailing_comma=True
known_standard_library=numpy,setuptools
known_myself=fvcore
known_third_party=cv2,torch,PIL,yacs,tqdm,yaml,termcolor,shapely,portalocker
no_lines_before=STDLIB,THIRDPARTY
sections=FUTURE,STDLIB,THIRDPARTY,myself,FIRSTPARTY,LOCALFOLDER
default_section=FIRSTPARTY
```

更多信息参考 [GitHub Website](https://github.com/timothycrosley/isort)。

### 保持测试代码整洁

在写测试时，复制和粘贴代码的次数要比写常规程序用得多得多。测试有时会非常重复，但是这不是让代码草率和难以维护的原因。

写测试时需要遵循 DRY 原则：**D**on't **R**epeat **Y**ourself。

Test fixtures 是写好测试代码、维护测试代码的好方法。可读性很重要，可以考虑使用 `flake8` 这样的 linting 工具来维护测试代码：

```shell
$ flake8 --max-line-length=120 tests/
```

### 测试变更之间的性能下降

在 Python 中，有很多方法进行基准测试。标准库中提供了 `timeit` 模块，它能够多次执行函数记录运行时间，并且给出最后的分布结果：

```python
def test():
    # ... your code

if __name__ == '__main__':
    import timeit
    print(timeit.timeit("test()", setup="from __main__ import test", number=100))
```

如果使用 `pytest` 作为 test runner，还可以使用 `pytest-benchmark` 插件，可以通过 `pip` 安装。它提供了一个 `benchmark` 作为 fixture，可以将任何可以调用的接口传递给 `benchmark()`，然后它记录这个调用接口的时间：

```python
def test_my_function(benchmark):
    result = benchmark(test)
```

更多信息参考 [pytest-benchmark Documentation Website](https://pytest-benchmark.readthedocs.io/en/latest/)

### 测试应用中的安全隐患

> Bandit is a tool designed to find common security issues in Python code.

可以使用 `bandit` 来检查应用中的安全问题：

```shell
$ bandit -r my_sum
[main]	INFO	profile include tests: None
[main]	INFO	profile exclude tests: None
[main]	INFO	cli include tests: None
[main]	INFO	cli exclude tests: None
[main]	INFO	running on Python 3.7.3
Run started:2019-12-16 07:27:48.973719

Test results:
	No issues identified.

Code scanned:
	Total lines of code: 5
	Total lines skipped (#nosec): 0

Run metrics:
	Total issues (by severity):
		Undefined: 0.0
		Low: 0.0
		Medium: 0.0
		High: 0.0
	Total issues (by confidence):
		Undefined: 0.0
		Low: 0.0
		Medium: 0.0
		High: 0.0
Files skipped (0):
```

和 `flake8` 类似，`bandit` 也是可以配置的，可以在 `setup.cfg` 中进行配置：

```yacas
[bandit]
exclude: /test
tests: B101, B102, B301
```

更多信息参考 [GitHub Website](https://github.com/PyCQA/bandit)。



## 总结

在 Python 中开始写测试不需要很复杂：就从 `unittest` 开始，写一些小的、可维护的方法来验证程序正确就行了。当我们学习了更多东西之后，可以考虑切换到 `pytest` 这样的其他测试框架，使用更多的功能。