compiler        = g++
files       = game.cpp main.cpp

all: compile

compile: $(files)
	$(compiler) $(files) 

clean:
	rm -f a.out

exe:
	./a.out

