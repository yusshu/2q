CXX = g++
CFLAGS = -c -g
LFLAGS = -g
SRC = ${wildcard src/*.cpp}
HEADER = ${wildcard include/*.h}
OBJ = ${SRC:.cpp=.o}
TARGET = qq

all: ${SRC} ${OBJ} ${TARGET}

${TARGET}: ${OBJ}
	${CXX} ${LFLAGS} $^ -o $@

%.o: %.cpp ${HEADER}
	${CXX} ${CFLAGS} $< -o $@

clean:
	rm src/*.o ${TARGET}