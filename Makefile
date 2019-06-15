CXX := g++

FLAGS := -std=c++17 -g  -lasound
OUT := bin/SynthBox
INCLUDE_DIR := include
SOURCE_DIR := source
all: $(OUT)

clean:
	$(RM) $(OUT)

run: all
	./$(OUT)

$(OUT): $(SOURCE_DIR)/*
	$(CXX) $(FLAGS) -I$(INCLUDE_DIR) $^ -o $@ $(LIBRARIES)