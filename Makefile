libraries := -lsfml-graphics -lsfml-window -lsfml-system
flags     := -Wall -Wextra -std=c++17 -g
compiler  := clang++-6.0

sources := $(shell find src/ -iname "*.cpp" -not -iname "*xboy.cpp")
tests   := $(shell find tests/ -iname "*.cpp")

compiledTests   := $(patsubst %.cpp, obj/%.o, $(tests))
compiledSources := $(patsubst %.cpp, obj/%.o, $(sources))

.PHONY: all clean test run

all: bin/xboy bin/test-xboy

obj/%.o: %.cpp
	@mkdir -p `dirname $@`
	$(compiler) $< -o $@ -c ${flags}

bin/xboy: $(compiledSources) src/xboy.cpp
	@mkdir -p bin
	$(compiler) -o bin/xboy ${compiledSources} src/xboy.cpp ${libraries} ${flags}

bin/test-xboy: $(compiledSources) $(compiledTests) src/test-xboy.cpp
	@mkdir -p bin
	$(compiler) -o bin/test-xboy ${compiledSources} ${compiledTests} src/test-xboy.cpp ${libraries} ${flags}

run: bin/xboy
	bin/xboy

test: bin/test-xboy
	bin/test-xboy

clean:
	rm -rf bin obj
