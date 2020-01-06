all: meat

meat: meat.o menu.o getid.o
	gcc -lmysqlclient -lfcgi meat.o menu.o getid.o -o meat 

meat.o: meat.c
	gcc -lmysqlclient -lfcgi -c meat.c

menu.o: menu.c 
	gcc -lmysqlclient -lfcgi -c menu.c

getid.o: getid.c 
	gcc -lmysqlclient -lfcgi -c getid.c

clean:
	rm -rf *.o meat
