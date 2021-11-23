CPP := g++
CFLAGS := -std=c++98 -Wall -Wextra -pedantic -ggdb -Wno-unused-variable -Wno-unused-parameter -lncurses
EXE := ./build/app 
INCLUDES_FOLDER := ./emit

FILES := main.o ./emit/emit.o

all : $(EXE)

$(EXE) : $(FILES)
	$(CPP) $(CFLAGS) -o $@ $^ -I$(INCLUDES_FOLDER)

%.o : %.cpp
	clear
	$(CPP) $(CFLAGS) -o $@ -c $< -I$(INCLUDES_FOLDER)

clean : 
	rm *.o

clean_all:
	rm $(EXE)

run : $(EXE)
	valgrind ./$(EXE)