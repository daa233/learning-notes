# -*- coding: utf-8 -*-
# Get the tomorrow weather of Qingdao by http://www.weather.com.cn/weather/101120201.shtml

import urllib2

count = 0
flag = False

for line in urllib2.urlopen('http://www.weather.com.cn/weather/101120201.shtml'):
    if flag:
        count = count + 1

    if '（明天）' in line:
        flag = True

    if count == 3:
        print line
