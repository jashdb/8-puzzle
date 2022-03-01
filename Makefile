CXX = g++
CPPFLAGS= ./src/

SRCS = common_function.c user_solve.c machine_solve.c
OBJS = common_function.o user_solve.o machine_solve.o

all	:	main	clean

main:	main.o	${OBJS}
	g++ -o main main.o ${OBJS}
main.o:	${CPPFLAGS}main.c
	${CXX} -c ${CPPFLAGS}main.c
user_solve.o: ${CPPFLAGS}user_solve.c 
	${CXX} -c ${CPPFLAGS}user_solve.c
machine_solve.o: ${CPPFLAGS}machine_solve.c
	${CXX} -c ${CPPFLAGS}machine_solve.c
common_function.o: ${CPPFLAGS}common_function.c
	${CXX} -c ${CPPFLAGS}common_function.c

clean:
	rm -f *.o *~