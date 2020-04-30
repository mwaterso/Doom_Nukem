* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   libft.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mwaterso <mwaterso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/04 12:21:37 by beduroul     #+#   ##    ##    #+#       */
/*   Updated: 2020/03/05 16:55:36 by mwaterso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

/*
** Include
*/

# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include "get_next_line.h"

/*
** Memory
*/

void				*ft_memset(void *s, int c, ssize_t n);
void				*ft_memcpy(void *dest, const void *src, ssize_t n);
void				*ft_memccpy(void *dest, const void *src, int c, ssize_t n);
void				*ft_memmove(void *dest, const void *src, ssize_t n);
void				*ft_memchr(const void *s, int c, ssize_t n);
int					ft_memcmp(const void *s1, const void *s2, ssize_t n);
void				ft_memdel(void **ap);
void				*ft_memalloc(ssize_t size);
void				ft_bzero(void *s, ssize_t n);

/*
** String
*/

int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strncpy(char *dest, char *src, unsigned int n);
int					ft_strncmp(const char *s1, const char *s2, ssize_t n);
char				*ft_strcpy(char *dest, char *src);
ssize_t				ft_strlen(const char *str);
char				*ft_strdup(const char *s);
char				*ft_strcat(char *dest, const char *src);
char				*ft_strncat(char *dest, const char *src, ssize_t n);
ssize_t				ft_strlcat(char *dst, const char *src
						, ssize_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strnstr(const char *haystack, const char *needle,
						ssize_t len);
char				*ft_strrchr(const char *s, int c);
char				*ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strjoin2(char const *s1, char const *s2, int index_free);
char				*ft_strnew(ssize_t size);
void				ft_strdel(char **as);
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, ssize_t n);
char				*ft_strsub(char const *s, unsigned int start, ssize_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_strrev(char *str);
int					ft_strcchr(char *str, char c);
int					ft_avlen(char **av);
void				ft_avswap(char **a, char **b);
void    			ft_2dstrdel(char ***as);
int					ft_strnequ_word(char const *s1, char const *s2, ssize_t n);
int     			ft_strnchr(char *str, char c);

/*
** Print
*/

typedef enum        s_putstr_style
{
	NONE =			0,
    BOLD =			1,
    UNDERLINE = 	2,
    ITALIC =		4
}                   t_putstr_style;


void				ft_putchar(char c);
ssize_t				ft_putstr(const char *s);
void				ft_putendl(char *s);
void				ft_putnbr(int nb);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putspace(int n);
void				ft_putendl_color(const char *s, const char *color);
void				ft_putstr_color(const char *s, const char *color);
void       			ft_putstr_hexa(char *str, t_putstr_style type, u_int32_t color);
void       			ft_putendl_hexa(char *str, t_putstr_style type, u_int32_t color);
void       			ft_putnbr_hexa(int nbr, t_putstr_style type, u_int32_t color);

/*
** Maths
*/

int					ft_intsize(int n);
int					ft_factorial(int nb);
int					ft_power(int nb, int power);
int					ft_is_prime(int nb);
void				ft_swap(int *a, int *b);
int					*ft_range(int min, int max);
int					ft_sqrt(int nb);
int					ft_up_rounded(double n);

/*
** List
*/

typedef struct		s_list
{
	void			*content;
	ssize_t			content_size;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(void const *content, ssize_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, ssize_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, ssize_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

/*
** Other
*/

int					ft_atoi(const char *str);
char				*ft_itoa(int n);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isprint(int c);
int					ft_isascii(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
void				ft_foreach(int *tab, int length, void (*f)(int));
char				*color_txt(char *str, char *name, char *color);
void				rspace(int nb, char *str);
int     			ft_tablen(void **tab);
int					ft_ispace(int c);
float          		ft_atof(const char *str);

#endif
