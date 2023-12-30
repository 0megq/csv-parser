# Default target entry
all:
	gcc -o target/CSVParser tests/tests.c src/csv.c -Wall -Wextra -std=c99 -Wno-missing-braces -g -O0

# Clean everything
clean:
	del *.o target/CSVParser.exe /s

