CC := g++
CFLAGS := -Wall -g

SRCFILES := $(wildcard ./src/*.cpp)
OBJFILES := $(SRCFILES:.cpp=.o)

LINK := -lncurses

OUTPUT := game

all : $(OUTPUT)

$(OUTPUT) : $(OBJFILES)
	$(CC) $(CFLAGS) $^ -o ./bin/$@ $(LINK)

%.o : %.cpp $.hpp
	$(CC) $(CFLAGS) -c $^ $(LINK)

run : 
	make
	./bin/$(OUTPUT)

clean : 
	rm $(OBJFILES) ./bin/$(OUTPUT)

debug :
	make
	gdb ./$(OUTPUT)
