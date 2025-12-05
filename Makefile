
 ##flgas de cump.
CC = cc
CFLAGS = -Wall -Wextra -Werror

# FONTES - server
SERVER_SRC = server.c src.c srcserver.c
OBJS_S = $(SERVER_SRC:.c=.o)
NAME_S = server

# FONTES - client
CLIENT_SRC = client.c src.c
OBJS_C= $(CLIENT_SRC:.c=.o)
NAME_C = client

#comp geral.
all: $(NAME_S) $(NAME_C)

#server cump
$(NAME_S): $(OBJS_S)
	$(CC) $(CFLAGS) $^ -o $@

#server cump
$(NAME_C): $(OBJS_C)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
 
clean:
	rm -f $(OBJS_S) $(OBJS_C)

fclean: clean
	rm -f $(NAME_S) $(NAME_C)

re: fclean all

.PHONY: all clean fclean re,