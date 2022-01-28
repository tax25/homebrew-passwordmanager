CC = g++ 

CFLAGS = -lsqlite3

all:
	$(CC) main.cpp dbManager/dbManager.cpp -o pwdManager $(CFLAGS)

install:
	sudo cp pwdManager /usr/local/bin
	rm pwdManager

clean:
	sudo rm usr/local/bin/pwdManager
