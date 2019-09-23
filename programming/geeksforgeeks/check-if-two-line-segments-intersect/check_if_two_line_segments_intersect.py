# Problem: Check If two Line segments Intersect
# https://practice.geeksforgeeks.org/problems/check-if-two-line-segments-intersect/0

# Given the coordinates of the end points of two line segments and you have to 
# check if they intersect or not.
 
# Input:
# The first line of input contains a single integer T denoting the number of test
# cases.
# Then T test cases follow. Each test case consists of 2 lines.
# The first line consists of 4 integers: x1, y1, x2, y2 where (x1,y1) and (x2,y2)
# are the end points of the first line segment.
# The second line consists of 4 integers: x3, y3, x4, y4 where (x3,y3) and
# (x4,y4) are the end points of the second line segment.
 
# Output:
# Corresponding to each test case, in a new line, print 1 if the line segments 
# intersect, otherwise print 0.
 
# Constraints:
# 1 ≤ T ≤ 300
# -1000000 ≤ xi,yi ≤ 1000000    1<=i<= 4
 
# Example:

# Input
# 2
# 1 1 10 1
# 1 2 10 2
# 10 0 0 10
# 0 0 10 10

# Output
# 0
# 1

import sys

# Using the orientation
# refers to https://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/
class Solution:
    def line_intersect(self, line1, line2):
        x1, y1, x2, y2 = line1
        x3, y3, x4, y4 = line2
        p1 = (x1, y1)
        p2 = (x2, y2)
        q1 = (x3, y3)
        q2 = (x4, y4)

        o1 = self.orientation(p1, p2, q1)
        o2 = self.orientation(p1, p2, q2)
        if o1 == 0 and o2 == 0:
            # (p1, p2, q1) and (p1, p2, q2) are both collinear
            # check intersection
            if self.x_in_range(q1[0], p1[0], p2[0]) or \
               self.x_in_range(q2[0], p1[0], p2[0]) or \
               self.x_in_range(p1[0], q1[0], q2[0]) or \
               self.x_in_range(p2[0], q1[0], q2[0]):
                return 1
            else:
                return 0
        elif o1 * o2 > 0:
            # (p1, p2, q1) and (p1, p2, q2) have the same orientation
            return 0
        else:
            # (p1, p2, q1) and (p1, p2, q2) have different orientations
            # check (q1, q2, p1) and (q1, q2, p2)
            o3 = self.orientation(q1, q2, p1)
            o4 = self.orientation(q1, q2, p2)
            if o3 * o4 > 0:
                # (q1, q2, p1) and (q1, q2, p2) have the same orientation
                return 0
            else:
                # (q1, q2, p1) and (q1, q2, p2) have different orientations
                return 1

    def orientation(self, p1, p2, q):
        """
        Compute the orientation of (p1, p2, q).
        The orientation can be computed by the cross product of vectors p1p2 and p2q.
        Refers to https://en.wikipedia.org/wiki/Cross_product.
        Defined orientation:
        - 'clockwise': p1p2 x p2q > 0
        - 'counterclockwise': p1p2 x p2q < 0
        - 'collinear': p1p2 x p2q = 0
        """
        v1 = (p2[0]-p1[0], p2[1]-p1[1])
        v2 = (q[0]-p2[0], q[1]-p2[1])
        return v1[0]*v2[1] - v1[1]*v2[0]

    def x_in_range(self, x, c1, c2):
        if x >= min(c1, c2) and x <= max(c1, c2):
            return True
        else:
            return False


# Compute the intersect point of two straight lines and check the range
class Solution1:
    def line_intersect(self, line1, line2):
        if not self.is_line(line1) or not self.is_line(line2):
            return 0

        x1, y1, x2, y2 = line1
        x3, y3, x4, y4 = line2

        if x2 - x1 == 0 and x4 - x3 == 0:
            # both no slope
            if x1 != x3:
                return 0
            else:
                if self.x_in_range(y1, y3, y4) or self.x_in_range(y2, y3, y4) \
                    or self.x_in_range(y3, y1, y2) or self.x_in_range(y4, y1, y2):
                    return 1
                else:
                    return 0
        elif x2 - x1 == 0 and x4 - x3 != 0:
            # line1 no slope
            k2 = (y4 - y3) / (x4 - x3)
            b2 = y3 - k2 * x3
            inter_y = k2 * x1 + b2
            if self.x_in_range(inter_y, y1, y2):
                return 1
            else:
                return 0
        elif x2 - x1 != 0 and x4 - x3 == 0:
            # line2 no slope
            k1 = (y2 - y1) / (x2 - x1)
            b1 = y1 - k1 * x1
            inter_y = k1 * x3 + b1
            if self.x_in_range(inter_y, y3, y4):
                return 1
            else:
                return 0
        else:
            # both have slope
            k1 = (y2 - y1) / (x2 - x1)
            b1 = y1 - k1 * x1
            k2 = (y4 - y3) / (x4 - x3)
            b2 = y3 - k2 * x3

            if k1 == k2:
                if b1 == b2:
                    if self.x_in_range(y1, y3, y4) or self.x_in_range(y2, y3, y4) \
                        or self.x_in_range(y3, y1, y2) or self.x_in_range(y4, y1, y2):
                        return 1
                    else:
                        return 0
                else:
                    return 0
            else:
                inter_x = (b2 - b1) / (k1 - k2)
                if self.x_in_range(inter_x, x1, x2) and self.x_in_range(inter_x, x3, x4):
                    return 1
                else:
                    return 0
    
    def x_in_range(self, x, c1, c2):
        x = round(x, 9) # avoid float precision error
        # float precision error refers to https://www.jianshu.com/p/c2ffd2fcb49e

        if x >= min(c1, c2) and x <= max(c1, c2):
            return True
        else:
            return False
    
    def is_line(self, line):
        x1, y1, x2, y2 = line
        if x1 == x2 and y1 == y2:
            return False
        else:
            return True


def test(s):
    assert s.line_intersect([0, 0, 1, 1], [0, 1, 1, 0]) is 1
    assert s.line_intersect([0, 0, 0, 1], [1, 0, 1, 1]) is 0
    assert s.line_intersect([0, 0, 2, 0], [1, 0, 1, 1]) is 1
    assert s.line_intersect([939, 432229, 939, 432229], [-656, -301471, -824, -378751]) is 0
    assert s.line_intersect([-654, 336456, -77, 39301], [-493, 253541, 873, 729]) is 1


if __name__ == "__main__":
    s = Solution()
    # test(s)
    T = int(sys.stdin.readline().strip())
    for i in range(T):
        line1 = list(map(int, sys.stdin.readline().strip().split()))
        line2 = list(map(int, sys.stdin.readline().strip().split()))
        res = s.line_intersect(line1, line2)
        print(res)

