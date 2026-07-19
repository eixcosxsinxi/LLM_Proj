CC := gcc

# General compiler flags
CFLAGS := -g -Wall -Wextra

# Different visibility rules
SRC_CFLAGS := $(CFLAGS) -Iinclude
TEST_CFLAGS := $(CFLAGS) -Iinclude -Itest/include

# Directories
PROD := models/prod
TEST := models/test
BUILD := models/build

# Source files
SRC := $(wildcard src/*.c) # space seperated list of all files in src/ directory
TEST_SRC := $(wildcard test/*.c) # space seperated list of all files in test/ directory

# Object files
SRC_OBJ := $(patsubst src/%.c,$(BUILD)/%.o,$(SRC)) # space seperated list of all files in $(SRC) but src/ replaced with build/ and .c replaced with .o
TEST_OBJ := $(patsubst test/%.c,$(BUILD)/%.o,$(TEST_SRC)) # space seperated list of all files in $(TEST) but test/ replaced with build/ and .c replaced with .o
LIB_OBJ := $(filter-out $(BUILD)/main.o,$(SRC_OBJ)) # filters out the main.o which contains a int main() from otherwise reusable library objects so that there aren't two main entry points

.PHONY: all test run clean

# Build everything
all: LLM test_file
	echo "all done!"

# Production executable
LLM: $(SRC_OBJ)
	$(CC) $^ -o $(PROD)/$@

# Test executable
test_file: $(TEST_OBJ) $(LIB_OBJ)
	$(CC) $^ -o $(TEST)/$@

# Compile production source files into object files
$(BUILD)/%.o: src/%.c
	$(CC) $(SRC_CFLAGS) -c $< -o $@

# Compile test source files into object files
$(BUILD)/%_test.o: test/%_test.c
	$(CC) $(TEST_CFLAGS) -c $< -o $@

# Run tests
test: test_file
	./$(TEST)/test_file

# Run LLM
run: LLM
	./$(PROD)/LLM

# Remove generated files
clean:
	rm -f $(BUILD)/*.o
	rm -f $(PROD)/LLM
	rm -f $(TEST)/test_file