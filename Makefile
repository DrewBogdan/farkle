#
# Really simple Makefile for building the project
#
#	Contributors: Aaron S. Crandall <crandall@gonzaga.edu>
#	Copyright: 2023
#

SOURCE_FILE=crandallFarkle.cpp
BIN_FILE=farkle

all: build

build:
	g++ -o $(BIN_FILE) $(SOURCE_FILE)

run:
	./$(BIN_FILE)

clean:
	rm -f $(BIN_FILE)

