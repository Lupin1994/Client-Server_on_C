gcc -c Server.c util.c LinkedList/LinkedList.c
gcc -o Server Server.o util.o LinkedList.o
./Server