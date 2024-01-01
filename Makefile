TARGETDIR="target"
TARGET="${TARGETDIR}/CSVParser.exe"

all:
	mkdir -p ${TARGETDIR}
	gcc -o ${TARGET} tests/tests.c src/csv.c -Wall -Wextra -std=c99 -Wno-missing-braces -g -O0

clean:
	rm -rf ${TARGETDIR}

