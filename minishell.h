/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 08:11:56 by kzerri            #+#    #+#             */
/*   Updated: 2023/10/01 15:32:52 by kzerri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_tree
{
	char			**strs;
	struct s_tree	*right;
	struct s_tree	*left;
}t_tree;

typedef struct s_vars
{
	int		i;
	int		start;
	int		j;
	int		count;
	char	c;
	char	**splited;
	int		in_quote;
	char	*white_spaces;
}t_vars;

int		ft_strlen(char *str);
int		ft_strchar(char *str, char c);
char	*ft_strchr(char *s, int c);
char	*ft_strtrim(char *s1, char *set);
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize);
char	**ft_split2(char *str);
void	process_operator(char **final, char **str, int *index);
void	count_word_helper(char **str, int *in_quote, char *c, int *count);
char	*ft_strncpy(char *s1, char *s2, int n);
void	check_op(char **str, int *i, int *in_quote, char *c);
void	helper(int *in_quote, int *i, int *j, int *start);
char	*helper2(char *str, int *i, int *start);
void	helper3(char *str, int *in_quote, int *i, char *c);
void	helper4(int *in_quote, int *i, char *c);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *b, size_t n);
int		ft_strcmp(char *s1, char *s2);
char	*get_str_ready(char *str);
char	*final_str(char *str);
int		count_words(char *str);
void	helper3(char *str, int *in_quote, int *i, char *c);
void	helper4(int *in_quote, int *i, char *c);
int		count_redirections(char *str, int start, char c);
int		check_redirections(char *str);
int		check_ampersand(char *str);
int		is_valide(char *str);
void	error(char c);

char	**redir(char **strs, int sig);
void	get_redir(t_tree **tree,char **command);
void	build_tree(t_tree **tree, char **strs);
void	get_tree(t_tree **tree, char **command, int sig);
t_tree	*create(char **strs);
char	**pipe_command(char **strs, int sig, char *s);
int		search_redicrection(char **strs);
int		search_pipe(char **strs, int index);

#endif