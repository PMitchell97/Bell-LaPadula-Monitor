all: Subjects Objects blpsecure
	g++ -o blpsecure Subjects.o Objects.o blpsecure.o


Subjects: Subjects.cpp
	g++ -c -g -std=c++11 -c -o Subjects.o Subjects.cpp
Objects: Objects.cpp
	g++ -c -g -std=c++11 -c -o Objects.o Objects.cpp
blpsecure: blpsecure.cpp
	g++ -c -g -std=c++11 blpsecure.cpp

.PHONY:
	clean
clean:
	rm *.o blpsecure





