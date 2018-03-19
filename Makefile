sources          := $(shell find src/ -iname "*.cpp" -not -iname "*xboy.cpp")
createExecutable := g++ -lsfml-graphics -lsfml-window -lsfml-system
tests            := $(shell find tests/ -iname "*.cpp")

compiledTests   := $(patsubst %.cpp, obj/%.o, $(tests))
compiledSources := $(patsubst %.cpp, obj/%.o, $(sources))

.PHONY: clean test run

all: bin/xboy bin/test-xboy

obj/%.o: %.cpp
	@mkdir -p `dirname $@`
	g++ $< -o $@ -c -Wall -Wextra -std=c++1z

bin/xboy: $(compiledSources) src/xboy.cpp
	@mkdir -p bin
	$(createExecutable) -o bin/xboy ${compiledSources} src/xboy.cpp

bin/test-xboy: $(compiledTests) src/test-xboy.cpp
	@mkdir -p bin
	$(createExecutable) -o bin/test-xboy ${compiledSources} $(compiledTests) src/test-xboy.cpp

run: bin/xboy
	bin/xboy

test: bin/test-xboy
	bin/test-xboy

clean:
	rm -rf bin obj
