# compiler: g++
CXX = g++

# compiler flags
CXXFLAGS = -I../Matrix/include -I../Matrix/src

# default target
all: $(TARGET)

# use the name of the source file as the name of the target
TARGET = $(basename $(SRC))

# compile .cpp file to .o file
$(TARGET).o: $(SRC)
	$(CXX) $(CXXFLAGS) -c $(SRC) -o $(TARGET).o

# link .o file to executable file
$(TARGET): $(TARGET).o
	$(CXX) $(TARGET).o -o $(TARGET)

# clean up
clean:
	rm -f $(TARGET).o $(TARGET)

