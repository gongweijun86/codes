
OBJS = letsgo.o structure.o

letsgo : $(OBJS)
	gcc letsgo.o structure.o -o letsgo

letsgo.o : letsgo.c structure.h
	gcc -c letsgo.c -o letsgo.o

structure.o : structure.c structure.h
	gcc -c structure.c -o structure.o

clean : 
	rm *.o
cleanall :
	rm *.o
	rm letsgo 
