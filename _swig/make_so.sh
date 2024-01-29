#sudo apt-get update
#sudo apt-get install swig
#sudo apt-get install python3-dev

#make *.i file:
#%module mojbiblioteka
#%{
##include "twoj_kod.h"
#%}
#
#%include "twoj_kod.h"

swig -python sarakitdevices.i
g++ -shared -o _sarakitdevices.so devices.cpp sarakitdevices_wrap.c -I/usr/include/python3.9 -fPIC
#python test.py
