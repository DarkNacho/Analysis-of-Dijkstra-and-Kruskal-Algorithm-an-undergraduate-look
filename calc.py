from sys import stdin

line = stdin.readline()
_sum = 0
while line :
    if(line != "\n"):
        nrpe = int(line.split()[1])
        nodos = int(stdin.readline().split()[1])
        densidad = float(stdin.readline().split()[1])
        tiempo = float(stdin.readline().split()[1])
        if(nodos == 2000 and densidad == 0.1):
            _sum += tiempo
            print tiempo   
    line = stdin.readline()
print "promedio: ", _sum/10.0    