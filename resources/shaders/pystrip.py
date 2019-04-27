import sys



with open(sys.argv[1]) as f:
    lines = f.readlines()


#print(lines)

def rep(a,b):
	ll=a.replace(" "+b,b)
	ll=ll.replace(b+" ", b)
	return ll

replist = ["+","-","*","/", ",", "(",")","[","]", "{","}","*=","=","&&","||"]

f = open(sys.argv[2], 'w')
for l in lines:	
	l = l.replace("else","else ")
	if (not l.startswith('#')):
		l = l.replace("\n","")
	if (l.startswith('#')):
		l  = "\n"+l

	#print(l)
	for i in replist:
		l = rep(l,i)

	f.write(l)

f.close()
#lines = [line.rstrip('\n') for line in open('filename')]