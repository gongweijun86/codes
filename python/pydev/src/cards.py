from random import shuffle
values = range(1, 11) + 'Jack Queen King'.split()
suits = 'diamond clubs hearts spades'.split()
deck = ['%s of %s' % (v, s) for v in values for s in suits]
shuffle(deck)
while deck:raw_input(deck.pop())