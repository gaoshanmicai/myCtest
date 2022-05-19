#/bin/sh
CC=mipsel-openwrt-linux-gcc
PROG= mytestlist sqlitInsert slectDB updatedb deletedb msgrecv msgsend signaltest
INCLUDE= -I/opt/openwrt/build_dir/target-mipsel_24kc_musl/sqlite-autoconf-337000/compiler/include
INCLUDE +=-I ./

LINK = -L/opt/openwrt/build_dir/target-mipsel_24kc_musl/sqlite-autoconf-337000/compiler/lib
FLAGS= -g -std=c11
all:${PROG}

mytestlist:mytestlist.o
	$(CC) $(FLAGS) -o mytestlist   $(LINK)  $(INCLUDE) -static mytestlist.c  -lsqlite3
sqlitInsert:sqlitInsert.o
	$(CC) $(FLAGS) -o sqlitInsert   $(LINK)  $(INCLUDE) -static sqlitInsert.c  -lsqlite3
slectDB:slectDB.o
	$(CC) $(FLAGS) -o selectDB   $(LINK)  $(INCLUDE) -static slectDB.c  -lsqlite3
updatedb:updatedb.o
	$(CC) $(FLAGS) -o updatedb   $(LINK)  $(INCLUDE) -static updatedb.c  -lsqlite3

deletedb:deletedb.o
	$(CC) $(FLAGS) -o deletedb   $(LINK)  $(INCLUDE) -static deletedb.c  -lsqlite3


msgsend:msgsend.o
	$(CC) $(FLAGS) -o msgsend   $(LINK)  $(INCLUDE) msgsend.c
msgrecv:mserecv.o
	$(CC) $(FLAGS) -o msgrecv   $(LINK)  $(INCLUDE) mserecv.c

signaltest:signaltest.o
	$(CC) $(FLAGS) -o signaltest   $(LINK)  $(INCLUDE) signaltest.c -lpthread

clean:
	rm *.o $(PROG)