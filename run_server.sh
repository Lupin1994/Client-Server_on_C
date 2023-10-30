gcc -c Server.c util.c LinkedList/LinkedList.c HashTable_on_C/HashTable.c
gcc -o Server Server.o util.o LinkedList.o HashTable.o
./Server