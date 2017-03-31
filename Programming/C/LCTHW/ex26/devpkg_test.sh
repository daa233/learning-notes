#!/bin/bash
set -e

# install a piece of software from a URL.
./devpkg -I git://github.com/zedshaw/srpmin.git

# list all installed softwares
./devpkg -L

# show depends file for devpkg
./devpkg -I DEPENDS

# fetch source code to base APR 1.4.6
./devpkg -F http://archive.apache.org/dist/apr/apr-1.4.6.tar.gz

# 