#* encoding:utf-8 *#

"""
12 mal 13 Rechteck mit Puzzleteilen der Größe 3 Füllen

Ich kodiere den Zustand des Feldes binär und fange mit einer Möglichkeit für 0 (alles frei) an.
Dann gehe ich alle Zustände immer wieder durch und addiere die Anzahl Möglichkeiten für den aktuellen Zustand
zu den Anzahlen aller Zustände die ich aus diesem durch Legen eines Puzzleteils auf das Feld mit dem geringsten Index erzeugen kann.
Anschließend wird der aktuelle Zustand entfernt.
Das geschieht so lange bis der Zustand alles gefüllt auftritt. Dann wird das Ergebnis ausgegeben.

Die Puzzleteile sind ebenfalls binär kodiert um schnelles Prüfen auf Freiheit der Felder zu ermöglichen.

Beispiel:
Für ein 3*3 Feld wäre die Codierung wie folgt:
a b c
d e f    ->  0xabcdefghi  wobei 1 für ein belegtes und 0 für ein leeres Feld steht
g h i
"""

# Lösung

import time; t = time.time()	# nur zum timen wie lange es braucht

w, h = 9, 9 					# bitte w <= h wählen (aus Effizienzgründen)

states = [0]
statedict = {0:1}

def state_add(state,count):
	try:
		statedict[state] += count
	except KeyError:
		statedict[state] = count
		states.append(state)

tiles = [(1 + (1<< 1 ) + (1<< 2   ), 0, w-3),
		 (1 + (1<< w ) + (1<< 2*w ), 0, w-1),
		 (1 + (1<< w ) + (1<< w-1 ), 1, w-1),
		 (1 + (1<< w ) + (1<< w+1 ), 0, w-2),
		 (1 + (1<< 1 ) + (1<< w   ), 0, w-2),
		 (1 + (1<< 1 ) + (1<< w+1 ), 0, w-2)]

def first_empty(state):			# geht bestimmt auch irgendwie effizienter als über Stringmanipulation
	s = "0"+bin(state)[2:]
	return len(s) - s.rfind("0") - 1

fe_max = 0  					# nur zum beobachten wie weit das Programm schon ist

while True:
	state = states.pop(0)
	count = statedict.pop(state)
	fe = first_empty(state)
	if fe > fe_max:				# nur zum beobachten wie weit das Programm schon ist
		print(fe, len(states))  #
		fe_max = fe             #
	if fe > w*h-1:
		break
	for tile,xmin,xmax in tiles:
		if xmin <= (fe%w) <= xmax:
			if not (tile<<fe) & state:
				state_add((tile<<fe) | state, count)

print("\n",count if state == (1<<w*h)-1 else 0,"ways to fill","\n")




# DEBUG STUFF
import sys
if sys.version >= "3":
	raw_input = input
	xrange = range

print("stopped on place",fe)
print("time: %fs" %(time.time()-t))

def insert_every(string, char, every):
    return char.join(string[i:i+every] for i in xrange(0, len(string), every))

print(count,"\n")
print(insert_every(bin(state)[:1:-1],"\n",w))

print("keep pressing ENTER for more debug info")

for state in states:
	raw_input("")
	print(statedict[state],"\n")
	print(insert_every(bin(state)[:1:-1],"\n",w))

