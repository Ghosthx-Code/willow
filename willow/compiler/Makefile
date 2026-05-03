exec    = ../compiler/willow.out
flags   = -Wall -Wextra -g
src     = $(shell find . -name '*.c' -type f)
obj     = $(src:./%.c=o/%.o)

all: build

build: $(obj)
	gcc $(obj) -o $(exec)

o/%.o: ./%.c
	@mkdir -p $(dir $@)
	gcc -c $(flags) $< -o $@

clean:
	@rm -rf o
	@rm -f ../compiler/willow.out

.PHONY: all build clean
