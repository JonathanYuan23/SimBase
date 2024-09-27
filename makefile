CXX=clang++
CXXFLAGS=-I./src -std=c++17 -g -MMD -Wall
EXEC=SimBase
CCFILES=$(wildcard src/*.cpp) $(wildcard src/cpu/*.cpp) $(wildcard src/gpu/*.cpp)
OBJECTS=${CCFILES:.cpp=.o}
DEPENDS=${CCFILES:.cpp=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean format

clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}

format:
	find src -name '*.cpp' -o -name '*.hpp' -o -name '*.c' -o -name '*.h' | xargs clang-format -i