TARGET=a.out
OBJS=occitest.o

LIB_PATH=-L/home/orion/Software/occi/instantclient_10_2

LIBS=-lnsl -lclntsh -locci

CC=g++
%.o:%.cpp
	$(CC) -c -g $< -o $@ ${INCLUDE_PATH}
$(TARGET):$(OBJS)
	$(CC) -g $(OBJS) -o $(TARGET) ${LIB_PATH} -lpthread ${LIBS} 
