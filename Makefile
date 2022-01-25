CC = g++ 

CFLAGS = -lsqlite3

all:
	$(CC) main.cpp dbManager.cpp -o pwdManager $(CFLAGS)

install:
	sudo cp pwdManager /usr/local/bin

clean:
	sudo rm -r usr/local/bin/pwdManager
