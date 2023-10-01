NAME		=	minishell

header	=	minishell.h

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror -lreadline 

RM			=	rm -rf

SRCS		=	lib/ft_strlen.c lib/ft_strchar.c lib/ft_strchr.c lib/ft_strncpy.c lib/ft_strlcpy.c lib/ft_strcmp.c lib/ft_strtrim.c lib/ft_calloc.c main.c PARSER/token_utils.c PARSER/token_utils2.c \
				PARSER/check_redirections.c PARSER/isValide.c PARSER/error_print.c AST/build_tree.c AST/get_redir.c

OBJS		= $(SRCS:.c=.o)

$(NAME)		: $(OBJS) $(header)
			$(CC)  $(CFLAGS) $(OBJS) -o $(NAME)

%o:%c $(header)
	$(CC) -c $< -o $@

all			:	$(NAME)

cm			:	all clean
	
clean		:
			$(RM) $(OBJS)

mc			: all clean

fclean		: clean
			$(RM) $(NAME)

re			: fclean all