all : huftree

huftree : huftree.o
	g++ -std=c++11 -o huftree -g huftree.o
	g++ -std=c++11 -Wall -c -g codetree.h

huftree.o : huftree.cc
	g++ -std=c++11 -Wall -c -g huftree.cc


clean :
	rm *.o
	rm huftree
