# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/13 00:57:41 by bbouagou          #+#    #+#              #
#    Updated: 2023/01/18 16:08:52 by bbouagou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLIENTNAME = client
SERVERNAME = server
CLIENTNAME_BONUS = client_bonus
SERVERNAME_BONUS = server_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror

CLIENTOBJ = client.o
SERVEROBJ = server.o

CLIENTOBJ_BONUS = client_bonus.o
SERVEROBJ_BONUS = server_bonus.o server_utils_bonus.o

LIBFT = libft/libft.a

DEPS = minitalk.h

%.o: %.c $(DEPS)
	$(CC) -c $< $(CFLAGS)

all : compile $(CLIENTNAME) $(SERVERNAME)

$(CLIENTNAME) : $(CLIENTOBJ)
	$(CC) $(LIBFT) $(CLIENTOBJ) $(CFLAGS) -o $(CLIENTNAME)

$(SERVERNAME) : $(SERVEROBJ)
	$(CC) $(LIBFT) $(SERVEROBJ) $(CFLAGS) -o $(SERVERNAME)

$(CLIENTNAME_BONUS) : $(CLIENTOBJ_BONUS)
	$(CC) $(LIBFT) $(CLIENTOBJ_BONUS) $(CFLAGS) -o $(CLIENTNAME_BONUS)

$(SERVERNAME_BONUS) : $(SERVEROBJ_BONUS)
	$(CC) $(LIBFT) $(SERVEROBJ_BONUS) $(CFLAGS) -o $(SERVERNAME_BONUS)

bonus : compile $(SERVERNAME_BONUS) $(CLIENTNAME_BONUS)

compile :
	$(MAKE) -C libft

clean :
	$(MAKE) clean -C libft
	rm -rf *.o

fclean : clean
	$(MAKE) fclean -C libft
	@rm -rf $(CLIENTNAME_BONUS)
	@rm -rf $(SERVERNAME_BONUS)
	@rm -rf $(CLIENTNAME)
	@rm -rf $(SERVERNAME)

re : fclean all