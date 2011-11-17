girls=['alice','bernice','clarice']
boys=['chris','arnold','bob']
lettersGirls = {}
for girl in girls:
	lettersGirls.setdefault(girl[0],[]).append(girl)
	print lettersGirls
print [b+'+'+g for b in boys for g in lettersGirls[b[0]]]
