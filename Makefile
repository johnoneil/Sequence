EXE=sequence
COMPILER=g++
SOURCE=sequence.cpp

$(EXE): $(SOURCE)
	$(COMPILER) $(SOURCE) -o $(EXE)	

all: clean $(EXE)

clean:
	rm $(EXE)
