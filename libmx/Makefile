NAME = libmx.a

INC = inc/libmx.h

SRCR = *.c

SRC = src/*.c

OBJR = *.o

OBJ = obj/*.o

FLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

all: install

install: clean
	@mkdir obj
	@clang $(FLAGS) -c $(SRC)
	@mv $(OBJR) obj
	@ar -rcs $(NAME) $(OBJ)
	@make clean

uninstall: clean
	@rm -rf ./obj
	@rm -rf $(NAME)

clean:
	@rm -rf $(OBJR)

reinstall: uninstall install
