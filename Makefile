libs := -lfas -lpthread
cflags := -std=c++11 -static -Wall
CC = g++

fas_base := ./fas/base
fas_libs := ./lib

objects := $(patsubst %.cpp, %.o, $(wildcard *.cpp))

mdm:$(objects)
	$(CC) $^  -I${fas_base} -I./ -L${fas_libs} $(cflags) -o $@  $(libs)
%.o:%.cpp
	$(CC) -c $^  -I${fas_base} -I./ -L${fas_libs} $(cflags) -o $@  $(libs)

.PHONY : clean
clean:
	rm *.o   -rf 
