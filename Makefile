CXX = g++
CFLAGS = -c -g -std=c++17
LFLAGS = -g
SRC = $(wildcard src/*.cpp) $(wildcard src/**/*.cpp)
HEADER = $(wildcard src/*.h) $(wildcard src/**/*.h)
OBJ = ${SRC:.cpp=.o}
TARGET = qq

all: ${SRC} ${OBJ} ${TARGET}

${TARGET}: ${OBJ}
	${CXX} ${LFLAGS} $^ -o $@

%.o: %.cpp ${HEADER}
	${CXX} ${CFLAGS} $< -o $@

clean:
	rm src/*.o ${TARGET}