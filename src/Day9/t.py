l = [[int(i) for i in s.split()] for s in open('/home/jonas/AdventOfCode2023/src/Day9/Data.txt').read().split('\n') if s.strip()]

def n(l):
	if sum(i != 0 for i in l) == 0:
		return 0
	m = []
	for i in range(len(l)-1):
		m.append(l[i+1]-l[i])
	return l[-1] + n(m)

[print(n(i)) for i in l]
#print(sum(n(i) for i in l))

#print(sum(n(i[::-1]) for i in l))