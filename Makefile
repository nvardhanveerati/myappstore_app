all: myAppStore

myAppStore: main.o heap.o bst.o utils.o hash.o prime.o
	g++ main.o heap.o bst.o utils.o prime.o hash.o -o myAppStore

main.o:
	g++ -c main.cpp

hash.o:
	g++ -c hash.cc

heap.o:
	g++ -c heap.cc

bst.o: 
	g++ -c bst.cc

utils.o:
	g++ -c utils.cc

prime.o:
	g++ -c prime.cc

clear:
	rm myAppStore main.o heap.o bst.o utils.o prime.o hash.o
