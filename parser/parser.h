#ifndef PARSER_H
# define PARSER_H
# include "../minishell.h"


int			ft_strstr(const char *dest, const char *src);
int			strl(char *str);
char		*strj(char *s1, char s2);
int			get_next_line(int fd, char **line);

#endif