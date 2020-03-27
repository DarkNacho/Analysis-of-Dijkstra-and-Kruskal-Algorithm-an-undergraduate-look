from sys import stdin

_time = 0
for line in stdin:
    _line = line.split()
    if(len(_line) > 1):
        if(_line[0] == "time:"):
            #_time = max(_time , int(_line[1]))
            print _line[1]