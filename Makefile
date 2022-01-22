CC = g++ 

CFLAGS = -lsqlite3

all:
	$(CC) $(CFLAGS) main.cpp dbManager.cpp -o pwdManager

install:
	sudo cp pwdManager /usr/local/bin

clean:
	sudo rm -r usr/local/bin/pwdManager
