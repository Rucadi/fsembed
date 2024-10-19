# Compiler
CXX = clang++

# Compiler flags
CXXFLAGS = -std=c++23 

# Output object file
OUTPUT = fsembed.o

# Source files
SOURCES = $(wildcard *.cpp)

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Default target
all: $(OUTPUT)

# Create a single .o file from all object files
$(OUTPUT): $(OBJECTS)
	ar rcs $@ $^
	rm -f $(OBJECTS)


# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -f $(OBJECTS) $(OUTPUT)

.PHONY: all clean