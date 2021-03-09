all: myAppStore

myAppStore: main.o
	g++ main.o -o myAppStore

main.o:
	g++ -c main.cpp

heap.o:
	g++ -c heap.cc

bst.o: 
	g++ -c bst.cc

utils.o:
	g++ -c utils.cc

clear:
	rm myAppStore main.o heap.o bst.o utils.o
