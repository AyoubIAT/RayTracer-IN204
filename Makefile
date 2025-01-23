# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++20 -Wall -I./include

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# List of source files
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)

# Object files
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Output executable
EXEC = output

# Default target
all: $(EXEC)

# Create object directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Create binary directory if it doesn't exist
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Linking step: Create the executable from object files
$(EXEC): $(OBJECTS) | $(BIN_DIR)
	$(CXX) $(OBJECTS) -o $(EXEC)

# Compilation step: Compile each source file into an object file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up object files and executable
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Phony targets
.PHONY: all clean
