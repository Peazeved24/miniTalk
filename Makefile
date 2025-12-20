CC = cc
CFLAGS = -Wall -Wextra -Werror

# FONTES
SERVER_SRC = server.c src.c srcserver.c
SERVER_BONUS_SRC = serverbonus.c src.c srcserver.c
CLIENT_SRC = client.c src.c
CLIENT_BONUS_SRC = clientbonus.c src.c

# OBJETOS
OBJS_S = $(SERVER_SRC:.c=.o)
OBJS_SBONUS = $(SERVER_BONUS_SRC:.c=.o)
OBJS_C = $(CLIENT_SRC:.c=.o)
OBJS_CBONUS = $(CLIENT_BONUS_SRC:.c=.o)

# NOMES
NAME_S = server
NAME_SBONUS = serverbonus
NAME_C = client
NAME_CBONUS = clientbonus

# COMPILAÇÃO GERAL
all: $(NAME_S) $(NAME_C) $(NAME_SBONUS) $(NAME_CBONUS)

# Targets
$(NAME_S): $(OBJS_S)
	$(CC) $(CFLAGS) $^ -o $@

$(NAME_SBONUS): $(OBJS_SBONUS)
	$(CC) $(CFLAGS) $^ -o $@

$(NAME_C): $(OBJS_C)
	$(CC) $(CFLAGS) $^ -o $@

$(NAME_CBONUS): $(OBJS_CBONUS)
	$(CC) $(CFLAGS) $^ -o $@

# Regra genérica de compilação
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza
clean:
	rm -f $(OBJS_S) $(OBJS_SBONUS) $(OBJS_C) $(OBJS_CBONUS)

fclean: clean
	rm -f $(NAME_S) $(NAME_SBONUS) $(NAME_C) $(NAME_CBONUS)

re: fclean all

.PHONY: all clean fclean re
