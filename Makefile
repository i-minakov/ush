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
	
CFLAGS = -std=c11 -g $(addprefix -W, all extra error pedantic)
CC = clang
SANFLAG = -g -fsanitize=address

all: install

install:
	# @make -C libmx
	@clang $(SANFLAG) src/*.c src/parse/*.c libmx/libmx.a -o ush
	@make clean

# $(LBMXS):
# 	@make -sC $(LBMXD)

# $(LIBMX): $(LBMXS)
# 	@make -sC $(LBMXD)
	
# $(NAME): $(OBJS) $(LIBMX)
# 	@$(CC) $(CFLAGS) $(LBMXS) $(OBJS) -o $@
# 	@printf "\x1b[32;1m$@ created\x1b[0m\n"

# $(OBJD)/%.o: $(SRCD)/%.c $(INCS)
# 	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)
# 	@printf "\x1b[32mcompiled: \x1b[0m[$(<:$(SRCD)/%.c=%.c)]\n"

# $(OBJS): | $(OBJD)

# $(OBJD):
# 	@mkdir -p $@

uninstall: clean
	@make -sC $(LBMXD) $@
	@rm -rf $(NAME)
	@printf "\x1b[34;1mdeleted $(NAME)\x1b[0m\n"

clean:
	@make -sC $(LBMXD) $@
	@rm -rf $(OBJD)
	@printf "\x1b[34;1mdeleted $(OBJD)\x1b[0m\n"

reinstall: uninstall install

d:
	clang  libmx.a src/*.c src/parse/*.c -o ush --debug
	@make clean
