# -- coding: utf-8 --


def final_room():
    "尼玛紫禁之巅"
    print "你来到了“尼玛紫禁之巅”，这里是王尼玛的老窝。"
    print "一个头很大的怪物蹲在地上玩手机……没错，你确定那就是你的邻居——王尼玛。"
    print "可是，你并没有发现你的女神。"
    print "你大声质问王尼玛：“王尼玛！你把我的女神弄哪去了？！”"
    print "王尼玛：“什么女神，我只拿了你的WIFE...”"
    print "“少说废话，快把女神还给我！”"
    print "一个无线路由器飞过来砸晕了你！"
    print "--------------------"
    print "一切都是个误会，你收到了一条短信：“您的信用卡新消费500,000.00元，余额-233.33元。”"
    dead("你上了暴走大事件。")

def sword_room():
    """尼玛论贱堂"""
    print "这里迷雾漫漫，墙上好像挂着两幅画，你还没有看清，突然屎壳郎倒下了，把你摔倒在地……好在它已经完成了它的使命……"
    print "你爬将起来，站在屎壳郎的遗体上，终于看清了墙上的画像，分别是“半壁江山”，“雾里滔滔”。"
    print "咦，这两幅画的画面一直在变化！原来这是两个动态表情包！"
    print "你即将被魔性的表情包吞噬！千钧一发之际，你要？"
    print " 1. 闭上眼睛  2. 通灵“天线宝宝”  3. 狗带"
    while True:
        command = raw_input("> ")
        # 输入选项是数字
        if judge_input(command):
            if command == '1':
                print "雾里滔滔的魔性表情充斥了你的整片脑海……"
                dead("你痛苦至极，深陷其中却无法睁开双眼。")
            elif command == '2':
                print "“天线宝宝”发出大招，放出日光屏蔽了所有表情，带你冲出了迷雾！"
                final_room()
            elif command == '3':
                print "“雾里滔滔”没有轻易地让你狗带，而“半壁江山”想让你死在春天里。"
                dead("谢天谢地，你的屎壳郎突然醒来，将你喷死。")
            else:
                print "想什么呢，你没有这个选项。"
        else:
            print "想什么呢，你得输入数字选项才行。"

def book_room():
    """尼玛藏书阁"""
    print "你来到了“尼玛藏书阁”。"
    print "你看了看四周，发现全是《暴走日报》。"
    print "所以，你的选择是？"
    print " 1. 全烧了  2. 熟背所有的《暴走日报》  3. 拉屎"
    while True:
        command = raw_input("> ")
        # 输入选项是数字
        if judge_input(command):
            if command == '1':
                print "顿时火光四起，尼玛藏书阁化为灰烬……"
                dead("你被烧死了。")
            elif command == '2':
                print "恭喜你升级为王尼玛的助手！你离女神又近了一步！"
                dead("王尼玛让你陪他儿子做游戏，你被他儿子用头顶死。")
            elif command == '3':
                print "突然，一个巨大的屎壳郎从地底爬出！"
                print "恭喜你获得坐骑——屎壳郎！"
                print "屎壳郎驮着你冲入了“尼玛论贱堂”！"
                sword_room()
            else:
                print "想什么呢，你没有这个选项。"
        else:
            print "想什么呢，你得输入数字选项才行。"

def dead(why):
    """Print why you died and exit the game."""
    print why, "Good job!"
    exit(0)

def start():
    """游戏开始"""
    print "在一个黑暗的屋子里醒来，发现你的女神不见了……"
    print "你爬将起来，突然发现地上有张纸条，上书："
    print "“我是隔壁的王尼玛，你的WIFE被我带走了。”"
    print "所以……你的选择是？"
    print " 1. 向前走  2. 回家睡觉  3. 回家看《暴走大事件》"
    while True:
        command = raw_input("> ")
        # 输入选项是数字
        if judge_input(command):
            if command == '1':
                book_room()
            elif command == '2':
                print "恭喜你获得“胎迷”称号！"
                dead("王尼玛给你送来了绿帽子祝贺。Good job!")
            elif command == '3':
                dead("你获得“活该被虐”谥号，汪汪。")
            else:
                print "想什么呢，你没有这个选项。"
        else:
            print "想什么呢，你得输入数字选项才行。"
    

# Judge if the input is all numbers
def judge_input(string):
    """Judge if the input string is all numbers."""
    for i in range(0, len(string)):
        # if the every word in string's ASCII represent the numbers 
        if not (ord(string[i]) in range(49, 51)):
            return False
    return True

start()

# Extras
''' 

If 语句的规则 
1. 每一个“if 语句”必须包含一个 else. 
2. 如果这个 else 永远都不应该被执行到，因为它本身没有任何意义，那你必须在 else 语句后面使用一个叫做 die 的函数，让它打印出错误信息并且
    死给你看，这和上一节的习题类似，这样你可以找到很多的错误。 
3. “if 语句”的嵌套不要超过 2 层，最好尽量保持只有 1 层。 这意味着如果你在 if 里边又有了一个 if，那你就需要把第二个 if 移到另一个函数
    里面。 
4. 将“if 语句”当做段落来对待，其中的每一个 if, elif, else 组合就跟一个段落的句子组合一样。在这种组合的最前面和最后面留一个空行作区分。
5. 你的布尔测试应该很简单，如果它们很复杂的话，你需要将它们的运算事先放到一个 变量里，并且为变量取一个好名字。

循环的规则 
1. 只有在循环永不停止时使用“while 循环”，这意味着你可能永远都用不到。这条只有 Python 中成立，其他的语言另当别论。 
2. 其他类型的循环都使用“for 循环”，尤其是在循环的对象数量固定或者有限的情况下。

调试(debug)的小技巧 
1. 不要使用 “debugger”。 Debugger 所作的相当于对病人的全身扫描。你并不会得到某方面的有用信息，而且你会发现它输出的信息态度，而且大部
    分没有用，或者只会让你更困惑。 
2. 最好的调试程序的方法是使用 print 在各个你想要检查的关键环节将关键变量打印出来，从而检查哪里是否有错。 
3. 让程序一部分一部分地运行起来。不要等一个很长的脚本写完后才去运行它。写一点，运行一点，再修改一点。

'''
