CXX = g++
CXXFLAGS = -MMD -Wall -fcompare-debug-second -lportaudio
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
