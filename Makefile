EXE=sequence
COMPILER=g++
SOURCE := $(wildcard *.cpp)
HEADERS := $(wildcard *.hpp)

$(EXE): $(SOURCE) $(HEADERS)
	$(COMPILER) $(SOURCE) -o $(EXE)	

all: clean $(EXE)

clean:
	rm $(EXE)
