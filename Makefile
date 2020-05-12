NAME = ush

SRCD = src
INCD = inc
OBJD = obj
LBMXD = libmx
LIBMX = libmx

LBMX = libmx.a
INC = ush.h
SRC = *.c parse

INCLUDE = -I $(LBMXD) \
	-I $(INCD) \

LBMXS = $(addprefix $(LBMXD)/, $(LBMX))
INCS = $(addprefix $(INCD)/, $(INC))
SRCS = $(addprefix $(SRCD)/, $(SRC))
OBJS = $(addprefix $(OBJD)/, $(SRC:%.c=%.o))
	
CFLAGS = -std=c11 $(addprefix -W, all extra error pedantic)
CC = clang
# SANFLAG = -g -fsanitize=address

all: install

install:
	# @make -C libmx
	@clang $(CFLAGS) $(SANFLAG) src/*.c src/parse/*.c libmx/libmx.a -o ush
	@make clean

d:
	@clang $(CFLAGS) $(SANFLAG) src/*.c src/parse/*.c libmx/libmx.a  -o ush --debug
	@make clean
e:
	@clang $(CFLAGS) $(SANFLAG) libmx/libmx.a src/echo_bin/echo_bin.c src/mx_getopt1.c -o echo --debug


uninstall: clean
	@make -sC $(LBMXD) $@
	@rm -rf $(NAME)
	@printf "\x1b[34;1mdeleted $(NAME)\x1b[0m\n"

clean:
	@make -sC $(LBMXD) $@
	@rm -rf $(OBJD)
	@printf "\x1b[34;1mdeleted $(OBJD)\x1b[0m\n"

reinstall: uninstall install

