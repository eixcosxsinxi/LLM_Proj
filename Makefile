# variables
PROD = models/prod
TEST = models/test
BUILD = models/build

# make all
LLM_and_TEST: LLM test_file
	echo "all done!"

# make LLM
LLM: main.o matrix.o linear_layer.o
	gcc -g $(addprefix $(BUILD)/,$^) -o $(PROD)/$@

# make test_file
test_file: main_test.o matrix_test.o linear_layer_test.o matrix.o linear_layer.o
	gcc -g $(addprefix $(BUILD)/,$^) -o $(TEST)/$@

# dependencies of LLM
main.o: src/main.c
	gcc -g -c -Iinclude $< -o $(BUILD)/$@

# dependencies of test_file
main_test.o: test/main_test.c
	gcc -g -c -Iinclude $< -o $(BUILD)/$@

matrix_test.o: test/matrix_test.c
	gcc -g -c -Iinclude $< -o $(BUILD)/$@

linear_layer_test.o: test/linear_layer_test.c
	gcc -g -c -Iinclude $< -o $(BUILD)/$@

# dependencies of both
matrix.o: src/matrix.c
	gcc -g -c -Iinclude $< -o $(BUILD)/$@

linear_layer.o: src/linear_layer.c
	gcc -g -c -Iinclude $< -o $(BUILD)/$@

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