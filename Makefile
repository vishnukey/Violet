app_name=MyGame
libs=-lsfml-system -lsfml-window -lsfml-graphics
SRC=src
BIN=bin
INC=include


all:
	@clang++ -g ${SRC}/*.cpp -o ${BIN}/${app_name} ${libs} -I${INC}

run: all
	@./${BIN}/${app_name}

clean:
	@if [ -e ${BIN}/${app_name} ]; then rm ${BIN}/${app_name}; fi
