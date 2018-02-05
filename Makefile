sources         := $(shell find src/ -iname "*.cpp")
tests           := $(shell find tests/ -iname "*.cpp")
compiledTests   := $(patsubst %.cpp, obj/%.o, $(tests))
compiledSources := $(patsubst %.cpp, obj/%.o, $(sources))

.PHONY: clean test

test: bin/xboy
	bin/xboy

obj/%.o: %.cpp
	@mkdir -p `dirname $@`
	g++ $< -o $@ -c -Wall -Wextra -std=c++1z

bin/xboy: $(compiledSources) $(compiledTests)
	@mkdir -p bin
	g++ -o bin/xboy ${compiledTests} ${compiledSources}

all: bin/xboy

clean:
	rm -rf bin obj
