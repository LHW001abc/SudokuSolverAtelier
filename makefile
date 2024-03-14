PROJECT_NAME = SudokuSolver

# Directories
SRC_DIR = src
RES_DIR = res
BIN_DIR = bin

# Files
EXEC = $(BIN_DIR)/$(PROJECT_NAME)
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BIN_DIR)/%.o)

# Automatic prerequisites
REQS = $(SRCS:$(SRC_DIR)/%.cpp=$(BIN_DIR)/%.d)
REQFLAGS = -MMD

# SFML library (edit paths as necessary)
SFML_DIR = C:/SFML-2.5.1
SFML_BIN_DIR = $(SFML_DIR)/bin
SFML_INC_DIR = $(SFML_DIR)/include
SFML_LIB_DIR = $(SFML_DIR)/lib
SFML_LIBS = sfml-graphics sfml-window sfml-system
SFML_FLAGS = -I$(SFML_INC_DIR) -L$(SFML_LIB_DIR) $(SFML_LIBS:%=-l%)

# Compiler
CXX = g++
CXXFLAGS = -Wpedantic -Wall -Wextra -Werror -std=c++17

#####################
# Do not edit below #
#####################

.DEFAULT_GOAL = build

setup_bin:
	$(info Setting up bin directory...)
	@mkdir -p $(BIN_DIR)
	@cp $(SFML_BIN_DIR)/sfml-graphics-2.dll $(BIN_DIR)/
	@cp $(SFML_BIN_DIR)/sfml-window-2.dll $(BIN_DIR)/
	@cp $(SFML_BIN_DIR)/sfml-system-2.dll $(BIN_DIR)/
	@cp -r $(RES_DIR)/ $(BIN_DIR)/
	$(info Done.)

build: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJS) $(SFML_FLAGS)

run:
	./$(EXEC)

clean:
	rm -r $(BIN_DIR)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp | setup_bin
	$(CXX) -c $(CXXFLAGS) $(REQFLAGS) -o $@ $< $(SFML_FLAGS)

.PHONY: setup_bin build run clean

-include $(REQS)