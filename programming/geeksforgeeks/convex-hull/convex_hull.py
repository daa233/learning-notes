# Problem: Convex Hull
# https://practice.geeksforgeeks.org/problems/convex-hull/0/

# Convex Hull of a set of points, in 2D plane, is a convex polygon with minimum
# area such that each point lies either on the boundary of polygon or inside it.
# Now given a set of points the task is to find the convex hull of points.

# Input:
# The first line of input contains an integer T denoting the no of test cases. 
# Then T test cases follow. Each test case contains an integer N denoting the 
# no of points. Then in the next line are N*2 space separated values denoting 
# the points ie x and y.

# Output:
# For each test case in a new line print the points x and y of the convex hull 
# separated by a space in sorted order where every pair is separated from the 
# other by a ','. If no convex hull is possible print -1.

# Constraints:
# 1<=T<=100
# 1<=N<=100
# 1<=x,y<=1000

# Example:
# Input:
# 2
# 3
# 1 2 3 1 5 6
# 3
# 1 2 4 4 5 1

# Output:
# 1 2, 3 1, 5 6
# 1 2, 4 4, 5 1

import sys
import math
import enum
from typing import List


class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.cw_next = None
        self.ccw_next = None
    
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


def same_direction(v1: Vector, v2: Vector) -> bool:
    """
    Check if v1 and v2 has the same direction
    """
    return v1.dot_mul(v2) >= 0


# Gift wrapping algorithm (Jarvis's match, O(nh))
# https://algorithmtutor.com/Computational-Geometry/Convex-Hull-Algorithms-Jarvis-s-March/
class Solution1:
    def convex_hull(self, points: List[Point]) -> List[Point]:
        # find the left most point as the initial point
        init = min(points, key=lambda point: point.x)
        index = points.index(init)

        # selection sort
        p = index
        res = [init]

        while True:
            q = (p + 1) % len(points)
            for r in range(len(points)):
                if r == p or r == q:
                    continue
                # find the leftmost
                o = orientation(points[p], points[r], points[q])
                if o == Direction.clockwise:
                    # clockwise
                    q = r
                elif o == Direction.colinear:
                    # colinear, choose the far one
                    v1 = Vector(points[p], points[q])
                    v2 = Vector(points[q], points[r])
                    if same_direction(v1, v2):
                        q = r
            p = q
            if p == index:
                break
            res.append(points[p])

        if len(res) < 3:
            return -1
        else:
            return res


# Graham Scan (O(n))
# https://algorithmtutor.com/Computational-Geometry/Convex-Hull-Algorithms-Graham-Scan/
class Solution2:
    def convex_hull(self, points: List[Point]) -> List[Point]:
        # find the left most point as the initial point
        init = min(points, key=lambda point: point.x)

        def sort_key(point):
            if point == init:
                neg_cos = 2  # move the init point to last
            else:
                v1 = Vector(init, Point(init.x, init.y+1))
                v2 = Vector(init, point)
                neg_cos = - v1.dot_mul(v2) / (v1.norm() * v2.norm())
                neg_cos = round(neg_cos, 9)
                # print('neg_cos', neg_cos)
            return (neg_cos, abs(point.y-init.y))

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
                else:
                    v1 = Vector(points[p], points[q])
                    v2 = Vector(points[q], points[r])
                    if not same_direction(v1, v2):
                        # for the last point, colinear but not the same 
                        # direction --> all points are colinear
                        return -1
                r += 1
            else:
                # counter-clockwise
                res.pop()
        
        if len(res) < 3:
            return -1
        else:
            return [points[i] for i in res]


# Divide and Conquer (O(nlogn))
# https://algorithmtutor.com/Computational-Geometry/Convex-Hull-Algorithms-Divide-and-Conquer/
class Solution3:
    def convex_hull(self, points: List[Point]) -> List[Point]:
        # sort the points
        points.sort(key=lambda point: (point.x, point.y))
        res = self.convex_hull_helper(points)
        # NOTE: If all points are colinear, there will be only two points in the res.
        if len(res) < 3:
            return -1
        else:
            return res

    def convex_hull_helper(self, points: List[Point]) -> List[Point]:
        if len(points) == 1:
            points[0].cw_next = points[0]
            points[0].ccw_next = points[0]
            return points

        left_half = self.convex_hull_helper(points[0:len(points)//2])
        right_half = self.convex_hull_helper(points[len(points)//2:])
        res = self.merge(left_half, right_half)
        return res

    def merge(self, c_hull_a: List[Point], c_hull_b: List[Point]) -> List[Point]:
        p = max(c_hull_a, key=lambda point: point.x)
        q = min(c_hull_b, key=lambda point: point.x)
        cp_p = p
        cp_q = q

        # find the upper tangent
        prev_p = None
        prev_q = None
        while True:
            prev_p = p
            prev_q = q
            if q.cw_next:
                # move q clockwise as long as it makes left turn
                while orientation(p, q, q.cw_next) == Direction.counter_clockwise:
                    q = q.cw_next
            if p.ccw_next:
                # move p counter-clockwise as long as it makes right turn
                while orientation(q, p, p.ccw_next) == Direction.clockwise:
                    p = p.ccw_next
            if p == prev_p and q == prev_q:
                break
        
        # find the lower tangent
        prev_p = None
        prev_q = None
        while True:
            prev_p = cp_p
            prev_q = cp_q
            if cp_q.ccw_next:
                # move q as long as it makes right turn
                while orientation(cp_p, cp_q, cp_q.ccw_next) == Direction.clockwise:
                    cp_q = cp_q.ccw_next
            if cp_q.cw_next:
                # move p as long as it makes left turn
                while orientation(cp_q, cp_p, cp_p.cw_next) == Direction.counter_clockwise:
                    cp_p = cp_p.cw_next
            if cp_p == prev_p and cp_q == prev_q:
                break
        
        # remove all other points
        p.cw_next = q
        q.ccw_next = p
        cp_p.ccw_next = cp_q
        cp_q.cw_next = cp_p

        # final result
        res = []
        start = p
        while True:
            res.append(p)
            p = p.ccw_next

            if p == start:
                break
        
        return res


# Quick Hull
# https://algorithmtutor.com/Computational-Geometry/Convex-Hull-Algorithms-Divide-and-Conquer/
class Solution:
    def convex_hull(self, points: List[Point]) -> List[Point]:
        min_x = min(points, key=lambda point: point.x)
        max_x = max(points, key=lambda point: point.x)

        res = [min_x, max_x]
        queue = [(min_x, max_x, points), (max_x, min_x, points)]
        while queue:
            left_end, right_end, points = queue.pop(0)
            if not points:
                continue

            fp, part_points = self.find_farest_point(left_end, right_end, points)
            
            if part_points:
                res.append(fp)

            queue.append((left_end, fp, part_points))
            queue.append((fp, right_end, part_points))
        
        if len(res) < 3:
            return -1
        else:
            return res

    def find_farest_point(self, left_end, right_end, points):
        part_points = []
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

        return fp, part_points


def get_input():
    T = int(sys.stdin.readline().strip())
    coords_lists = []
    for _ in range(T):
        # NOTE: The inputs may contain extra white spaces, e.g.
        # 1
        # 3
        # 1 1
        # 1 2
        # 1 1
        N = int(sys.stdin.readline().strip())
        coords_list = []
        while N > 0:
            coords = list(map(int, sys.stdin.readline().strip().split()))
            for coord in coords:
                coords_list.append(coord)
            N -= len(coords) // 2
        coords_lists.append(coords_list)
    return coords_lists


def coords_to_points(coords_list):
    points = []
    for i in range(0, len(coords_list), 2):
        p = Point(coords_list[i], coords_list[i+1])
        if p not in points:
            points.append(p)
    return points


def process_result(convex_hull):
    if convex_hull == -1:
        return str(convex_hull)
    else:
        # sort the points
        convex_hull.sort(key=lambda p: (p.x, p.y))
        # convert points to string
        res = []
        for p in convex_hull:
            res.append(' '.join([str(p.x), str(p.y)]))
        return ', '.join(res)


def test(s: Solution):
    coords_lists = [
        [1, 2, 3, 1, 5, 6],
        [1, 2, 4, 4, 5, 1],
        [1, 1, 2, 2, 3, 3],
        [1, 1, 1, 2, 3, 4, 3, 4],
        [778, 887, 794, 916, 387, 336, 650, 493, 363, 422, 691, 28, 764, 60,
         541, 927, 173, 427, 212, 737, 568, 369, 783, 430, 863, 531, 68, 124],
    ]
    results = [
        "1 2, 3 1, 5 6",
        "1 2, 4 4, 5 1",
        "-1",
        "1 1, 1 2, 3 4",
        "68 124, 212 737, 541 927, 691 28, 764 60, 794 916, 863 531",
    ]
    for coords_list, gt in zip(coords_lists, results):
        my_res = process_result(s.convex_hull(coords_to_points(coords_list)))
        assert my_res == gt, "\ngt: {}\nmy: {}".format(gt, my_res)


if __name__ == "__main__":
    s = Solution()
    # test(s)
    # exit(0)
    coords_lists = get_input()
    for coords_list in coords_lists:
        points = coords_to_points(coords_list)
        convex_hull = s.convex_hull(points)
        print(process_result(convex_hull))
        
