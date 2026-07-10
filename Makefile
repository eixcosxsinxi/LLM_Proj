# variables
PROD = models/prod
TEST = models/test
BUILD = models/build

# make all
LLM_and_TEST: LLM test_file
	echo "all done!"

# make LLM
LLM: main.o matrix.o
	gcc -g $(addprefix $(BUILD)/,$^) -o $(PROD)/$@

# make test_file
test_file: matrix_test.o matrix.o
	gcc -g $(addprefix $(BUILD)/,$^) -o $(TEST)/$@

# dependencies of LLM
main.o: src/main.c
	gcc -c -Iinclude $< -o $(BUILD)/$@

# dependencies of test_file
matrix_test.o: test/matrix_test.c
	gcc -c -Iinclude $< -o $(BUILD)/$@

# dependencies of both
matrix.o: src/matrix.c# include/matrix.h
	gcc -c -Iinclude $< -o $(BUILD)/$@

.PHONY: test
test: test_file
	./$(TEST)/test_file

.PHONY: clean
clean:
	rm -f $(BUILD)/*.o
	rm -f $(PROD)/LLM
	rm -f $(TEST)/test_file

.PHONY: run
run: LLM
	./$(PROD)/LLM