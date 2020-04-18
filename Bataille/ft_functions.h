#ifndef FT_FUNCTIONS_H
# define FT_FUNCTIONS_H
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

enum {HEARTS, SPADES, DIAMONDS, CLUBS};

typedef struct	s_card
{
	char	*name;
	char	value;
	char	color;
}				t_card;

void	ft_putstr(char *);
char	*ft_strdup(char *src);
char	*ft_strmemcat(char *first, char *second);
char	*ft_set_card_name(char value, char color);
t_card	*ft_get_unshuffled_deck(void);
void	ft_shuffle_deck(t_card *deck);
t_card	*ft_add_card(t_card card_to_add, t_card *original_deck);

#endif
