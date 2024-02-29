CXX = g++
CXXFLAGS = -std=c++11 -D__LINUX_ALSA__ -D__LITTLE_ENDIAN__ -MMD -Wall -lstk -I/usr/local/include/stk -fcompare-debug-second
EXEC = $(shell basename $(CURDIR)).out
OBJECTS = main.o
DEPENDS = ${OBJECTS:.o=.d}
${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} ${CXXFLAGS} -o ${EXEC}
.PHONY: build
build: ${OBJECTS}
	${CXX} ${OBJECTS} ${CXXFLAGS} -o ${EXEC}
-include ${DEPENDS}
.PHONY: clean
clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}
