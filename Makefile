CXX := g++

STD := -std=c++23

APP_WARNINGS := -Wall -Wextra -Wshadow -Wconversion -Wpedantic -Werror
TEST_WARNINGS := -Wall -Wextra -Wshadow -Wconversion -Wpedantic

COMMON_INCLUDES := -I. -IstrukturosFailai

APP_SOURCES := programaVektoriai.cpp pagalbinesFunkcijos/*.cpp Studentas.cpp

TEST_SOURCES := pagalbinesFunkcijos/*.cpp Studentas.cpp
VECTOR_TEST_SOURCES := VectorTest.cpp

GTEST_REPO := https://github.com/google/googletest.git
GTEST_ROOT := googletest
GTEST_DIR := $(GTEST_ROOT)/googletest
GTEST_INC := -I$(GTEST_DIR)/include -I$(GTEST_DIR)
GTEST_SRC := $(GTEST_DIR)/src/gtest-all.cc
GTEST_MAIN_SRC := $(GTEST_DIR)/src/gtest_main.cc

TEST_TARGET := tests_runner

.PHONY: O3fast O3 O2 O1 runO1 runO2 runO3 runO3fast googletest tests test clean clean-tests clean-all

O3fast:
	$(CXX) $(STD) -O3 -ffast-math -march=native -flto $(APP_WARNINGS) $(COMMON_INCLUDES) $(APP_SOURCES) -o O3fast

O3:
	$(CXX) $(STD) -O3 -march=native -flto $(APP_WARNINGS) $(COMMON_INCLUDES) $(APP_SOURCES) -o O3

O2:
	$(CXX) $(STD) -O2 -march=native -flto $(APP_WARNINGS) $(COMMON_INCLUDES) $(APP_SOURCES) -o O2

O1:
	$(CXX) $(STD) -O1 -march=native -flto $(APP_WARNINGS) $(COMMON_INCLUDES) $(APP_SOURCES) -o O1

runO1: O1
	./O1

runO2: O2
	./O2

runO3: O3
	./O3

runO3fast: O3fast
	./O3fast

googletest:
	@if [ ! -d "$(GTEST_ROOT)" ]; then \
		echo "Cloning GoogleTest from $(GTEST_REPO)"; \
		git clone --depth 1 $(GTEST_REPO) $(GTEST_ROOT); \
	else \
		echo "GoogleTest already exists in $(GTEST_ROOT)"; \
	fi

tests: googletest
	$(CXX) $(STD) -O0 -g $(TEST_WARNINGS) $(COMMON_INCLUDES) $(GTEST_INC) \
		$(TEST_SOURCES) \
		$(GTEST_SRC) \
		$(GTEST_MAIN_SRC) \
		-pthread \
		-o $(TEST_TARGET)

test: tests
	./$(TEST_TARGET)

testVector: googletest
	$(CXX) $(STD) -O0 -g $(TEST_WARNINGS) $(COMMON_INCLUDES) $(GTEST_INC) \
		$(VECTOR_TEST_SOURCES) \
		$(GTEST_SRC) \
		$(GTEST_MAIN_SRC) \
		-pthread \
		-o $(TEST_TARGET)
	./tests_runner

clean-tests:
	rm -f $(TEST_TARGET)

clean:
	rm -f O1 O2 O3 O3fast $(TEST_TARGET)

clean-all: clean
	rm -rf $(GTEST_ROOT)