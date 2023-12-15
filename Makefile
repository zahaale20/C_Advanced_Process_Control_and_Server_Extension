CC = gcc
CFLAGS = -Wall -std=c99 -pedantic
CLIENT = client
CLIENT_OBJS = client.o
SERVER = server
SERVER_OBJS = server.o net.o
MY_TIMEOUT = my_timeout
MY_TIMEOUT_OBJS = my_timeout.o
PROGS = $(CLIENT) $(SERVER) $(MY_TIMEOUT)

all : $(PROGS)

$(CLIENT) : $(CLIENT_OBJS)
	$(CC) $(CFLAGS) -o $(CLIENT) $(CLIENT_OBJS)

client.o : client.c
	$(CC) $(CFLAGS) -c client.c

$(SERVER) : $(SERVER_OBJS)
	$(CC) $(CFLAGS) -o $(SERVER) $(SERVER_OBJS)

server.o : server.c net.h
	$(CC) $(CFLAGS) -c server.c

net.o : net.c net.h
	$(CC) $(CFLAGS) -c net.c

$(MY_TIMEOUT) : $(MY_TIMEOUT_OBJS)
	$(CC) $(CFLAGS) -o $(MY_TIMEOUT) $(MY_TIMEOUT_OBJS)

mytimeout.o : mytimeout.c
	$(CC) $(CFLAGS) -c mytimeout.c


clean :
	rm *.o $(PROGS) core
