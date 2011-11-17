girls=['alice','bernice','clarice']
boys=['chris','arnold','bob']
print [b+'+'+g for b in boys for g in girls if b[0]==g[0]]
