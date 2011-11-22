TARGET=all
OBJS=occitest.o

INCLUDE_PATH=\
	-I /opt/rdbms/demo\
	-I /opt/rdbms/public\
	-I /opt/plsql/public\
	-I /opt/precomp/public\
	-I .   

LIB_PATH=-L/opt/lib\
	-L/opt/rdbms/lib\ 

LIBS=-lnsl -lclntsh -locci  

CC=g++
%.o:%.cpp
	$(CC) -c -g $< -o $@ ${INCLUDE_PATH}
$(TARGET):$(OBJS)
	$(CC) -g $(OBJS) -o $(TARGET) -lpthread -luuid ${INCLUDE_PATH} ${LIB_PATH} ${LIBS}
