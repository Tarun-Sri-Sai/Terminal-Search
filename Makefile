CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic -Werror

all: bin/search.exe

bin/%.exe: src/%.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	del /F /Q bin\*.exe