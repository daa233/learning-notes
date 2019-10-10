# @problem: 587. Erect the Fence
# @file: erect_the_fence.py
# @url: https://leetcode-cn.com/problems/erect-the-fence
# @description: 
# 
# There are some trees, where each tree is represented by (x,y)
# coordinate in a two-dimensional garden. Your job is to fence the
# entire garden using the minimum length of rope as it is expensive. The
# garden is well fenced only if all the trees are enclosed. Your task is
# to help find the coordinates of trees which are exactly located on the
# fence perimeter.
# Example 1:
# Input: [[1,1],[2,2],[2,0],[2,4],[3,3],[4,2]]
# Output: [[1,1],[2,0],[4,2],[3,3],[2,4]]
# Explanation:
# 
# Example 2:
# Input: [[1,2],[2,2],[4,2]]
# Output: [[1,2],[2,2],[4,2]]
# Explanation:
# Even you only have trees in a line, you need to use rope to enclose
# them.
# 
# Note:
# 
# All trees should be enclosed together. You cannot cut the rope to
# enclose trees that will separate them in more than one group.
# All input integers will range from 0 to 100.
# The garden has at least one tree.
# All coordinates are distinct.
# Input points have NO order. No order required for output.
# input types have been changed on April 15, 2019. Please reset to
# default code definition to get new method signature.
# 
# @author: Du Ang
# @date: Oct 10, 2019

import math
import enum
from typing import List


class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y
    
    def __eq__(self, p):
        return self.x == p.x and self.y == p.y

    def __str__(self):
        return "({}, {})".format(self.x, self.y)


class Vector:
    def __init__(self, p1: Point, p2: Point):
        self.x = p2.x - p1.x
        self.y = p2.y - p1.y
    
    def cross_mul(self, v: Point):
        cross_prod = self.x * v.y - v.x * self.y
        return cross_prod

    def dot_mul(self, v: Point):
        dot_prod = self.x * v.x + self.y * v.y
        return dot_prod

    def norm(self):
        return math.sqrt(self.x**2 + self.y**2)

    def __eq__(self, p):
        return self.x == p.x and self.y == p.y

    def __str__(self):
        return "({}, {})".format(self.x, self.y)


class Direction(enum.Enum):
    colinear = 0
    counter_clockwise = 1
    clockwise = -1


def orientation(p: Point, q: Point, r: Point) -> int:
    """
    colinear: 0
    counter-clockwise: 1
    clockwise: -1
    """
    v1 = Vector(p, q)
    v2 = Vector(q, r)
    cross_prod = v1.cross_mul(v2)
    if cross_prod == 0:
        return Direction.colinear
    elif cross_prod > 0:
        return Direction.counter_clockwise
    else:
        return Direction.clockwise


# Graham Scan (O(n))
# https://algorithmtutor.com/Computational-Geometry/Convex-Hull-Algorithms-Graham-Scan/
class Solution1:
    def outerTrees(self, points: List[List[int]]) -> List[List[int]]:
        if len(points) <= 2:
            return points

        points = [Point(item[0], item[1]) for item in points]

        # find the left most point as the initial point
        init = min(points, key=lambda point: (point.x, point.y))

        def sort_key(point):
            if point == init:
                neg_cos = 2  # move the init point to last
            else:
                v1 = Vector(init, Point(init.x, init.y+1))
                v2 = Vector(init, point)
                neg_cos = - v1.dot_mul(v2) / (v1.norm() * v2.norm())
                neg_cos = round(neg_cos, 9)
                # print('neg_cos', neg_cos)
            return (neg_cos, point.y-init.y, init.x-point.x)

        # sort the points according to the angle
        points.sort(key=sort_key)

        res = [len(points)-1, 0]
        r = 1
        while r < len(points):
            p = res[-2]
            q = res[-1]
            o = orientation(points[p], points[q], points[r])
            if o == Direction.clockwise:
                # clockwise
                if r != len(points) - 1:
                    res.append(r)
                r += 1
            elif o == Direction.colinear:
                # colinear
                if r != len(points) - 1:
                    res.append(r)
                r += 1
            else:
                # counter-clockwise
                res.pop()
        
        return [[points[i].x, points[i].y] for i in res]


# Quick Hull
class Solution2:
    def outerTrees(self, points: List[List[int]]) -> List[List[int]]:
        if len(points) <= 2:
            return points

        points = [Point(item[0], item[1]) for item in points]

        min_x = min(points, key=lambda point: point.x)
        max_x = max(points, key=lambda point: point.x)

        res = [min_x, max_x]
        queue = [(min_x, max_x, points), (max_x, min_x, points)]
        while queue:
            left_end, right_end, points = queue.pop(0)
            if not points:
                continue

            fp, part_points, colinear_points = self.find_farest_point(
                left_end, right_end, points)
            
            if part_points:
                res.append(fp)
            else:
                for p in colinear_points:
                    if p not in res:
                        res.append(p)

            queue.append((left_end, fp, part_points))
            queue.append((fp, right_end, part_points))
        
        return [[p.x, p.y] for p in res]

    def find_farest_point(self, left_end, right_end, points):
        part_points = []
        colinear_points = []
        fp = None
        if not points:
            return fp, part_points
        
        max_area = 0
        v1 = Vector(left_end, right_end)
        for p in points:
            v2 = Vector(right_end, p)
            area = v1.cross_mul(v2)
            if p == left_end or p == right_end:
                continue
            elif area > 0:
                part_points.append(p)
                if area > max_area:
                    max_area = area
                    fp = p
            elif area == 0:
                colinear_points.append(p)

        return fp, part_points, colinear_points


Solution = Solution2



