CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g
#CFLAGS = --std=c++17 -Wall -Werror -pedantic -g -I./boost/include
TEST_LIBS = -lboost_unit_test_framework
#TEST_LIBS = -L./boost/lib -lboost_unit_test_framework
DEPS = RandWriter.hpp
OBJECTS = RandWriter.o 
PROGRAM = TextWriter
STATIC_LIB = TextWriter.a
TEST = test

.PHONY: all clean lint

all: $(PROGRAM) $(STATIC_LIB) $(TEST)

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

$(PROGRAM): TextWriter.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

$(TEST): test.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(TEST_LIBS)

$(STATIC_LIB): $(OBJECTS)
	ar rcs $(STATIC_LIB) $(OBJECTS)

clean:
	rm *.o $(PROGRAM) $(STATIC_LIB) $(TEST)

lint:
	cpplint *.cpp *.hpp