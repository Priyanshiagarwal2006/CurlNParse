CXX = g++
CXXFLAGS = -lcurl
TARGET = cnp
OBJ = cnp.o
SRCS = main.cpp cnp.cpp

all: $(TARGET)

$(OBJ): cnp.cpp
	$(CXX) -c $< $(CXXFLAGS)

$(TARGET): main.cpp $(OBJ)
	$(CXX) $^ $(CXXFLAGS) -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean run
