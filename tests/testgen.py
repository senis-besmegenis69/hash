
# Susigeneruokite bent 100 000 atsitiktinių simbolių eilučių ( string 'ų) porų, pvz.
# (asdfg, hijkl), apsiribojant iki 1000 simbolių ilgiu. Toje pačioje poroje esančių string'ų
# ilgiai turi sutapti, tačiau skirtingos poros gali būti skirtingo ilgio. Rekomenduojame
# susigeneruoti taip: 25 000 porų, kurių ilgis 10 simbolių, kitas 25 000 porų, kurių ilgis -
# 100, dar kitas 25 000 poras - 500, ir galiausiai likusias 25 000 poras, kurių ilgis - 1000
# simbolių.

from random import choice
from string import ascii_lowercase

def gen(file, n, l):
	for i in range(0, l):
		line1 = ''.join(choice(ascii_lowercase) for k in range(0, n)) + '\n'
		line2 = ''.join(choice(ascii_lowercase) for k in range(0, n)) + '\n'
		file.write(line1)
		file.write(line2)

with open('100000_phrases.txt', 'w') as f:
	gen(f, 10, 25000)
	gen(f, 100, 25000)
	gen(f, 500, 25000)
	gen(f, 1000, 25000)
