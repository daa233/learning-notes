class B:
    pass

class C(B):
    pass

class D(C):
    pass

# B C D
for c in [B, C, D]:
    try:
        raise c()
    except D:
        print "D"
    except C:
        print "C"
    except B:
        print "B"
'''
# B B B
for c in [B, C, D]:
    try:
        raise c()
    except B:
        print "B"
    except C:
        print "C"
    except D:
        print "D"
'''
