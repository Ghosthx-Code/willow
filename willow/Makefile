exec  = bin/willow.out
flags = -Wall -Wextra -g # Added common flags for debugging
src   = $(wildcard src/*.c)
obj   = $(src:src/%.c=obj/%.o)

# The 'all' target is standard
all: build

build: $(obj)
	@mkdir -p bin
	gcc $(obj) -o $(exec)

# This rule compiles each .c file into an .o file separately
obj/%.o: src/%.c
	@mkdir -p obj
	gcc -c $< -o $@

clean:
	@rm -rf bin
	@rm -rf obj
