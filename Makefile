CPP := g++
CFLAGS := -std=c++98 -Wall -Wextra -pedantic -ggdb -Wno-unused-variable -Wno-unused-parameter
EXE := ./build/app 
ORIGIN := demo.o
INCLUDES_FOLDER := ./emit

FILES := ./emit/emit.o

all : $(EXE)

$(EXE) : $(ORIGIN) $(FILES)
	$(CPP) $(CFLAGS) -o $@ $^ -I$(INCLUDES_FOLDER)

%.o : %.cpp
	$(CPP) $(CFLAGS) -o $@ -c $< -I$(INCLUDES_FOLDER)

clean : 
	rm *.o

clean_all:
	rm $(EXE)

run : $(EXE)
	valgrind ./$(EXE)
