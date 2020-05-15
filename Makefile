NAME = ush
INC = inc/ush.h
SRC := $(wildcard src/*.c)
OBJ = $(addprefix obj/, $(notdir $(SRC:%.c=%.o)))
LIBMX = libmx/libmx.a
FLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic
SANFLAG = -g -fsanitize=address


# SRCD = src
# INCD = inc
# OBJD = obj
# LBMXD = libmx
# LIBMX = libmx

# SRC = *.c parse

# LBMXS = $(addprefix $(LBMXD)/, $(LBMX))
# INCS = $(addprefix $(INCD)/, $(INC))
# SRCS = $(addprefix $(SRCD)/, $(SRC))
# OBJS = $(addprefix $(OBJD)/, $(SRC:%.c=%.o))
	
# CFLAGS = -std=c11 $(addprefix -W, all extra error pedantic)
# CC = clang

all: $(NAME)

install: $(NAME)

$(NAME): $(LIBMX) $(OBJ)
	@make clean
	@clang $(FLAGS) $(OBJ) $(LIBMX) -o $(NAME)
	@printf "\x1b[32;1m$(NAME) created\x1b[0m\n"

$(LIBMX):
	@make -C libmx

$(OBJ): | obj

obj:
	@mkdir obj

obj/%.o: src/%.c $(INC)
	@clang $(FLAGS) -c $< -o $@
	@printf "\x1b[32mcompiled: \x1b[0m[$<]\n"

clean:
	@rm -rf *.o ush.dSYM
	@make clean -C libmx

uninstall: clean
	@make uninstall -C libmx
	@make clean
	@rm -rf ./obj
	@rm -rf $(NAME)

reinstall: uninstall install

# install:
# 	# @make l
# 	@clang $(CFLAGS) $(SANFLAG) src/*.c src/parse/*.c libmx/libmx.a -o ush
# 	@make clean
l:
	@make -C libmx

d:
	@clang $(FLAGS) $(SANFLAG) src/*.c libmx/libmx.a -o ush --debug
