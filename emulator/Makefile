CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic
TARGET = emulator
SRCS = main.cpp RippleCarryAdder.cpp FullAdder.cpp HalfAdder.cpp TestGenerator.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean 