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

void	ft_putchar(char c);
void	ft_putstr(char *);
void	ft_putnbr(int nb);
int		ft_strlen(char *str);
char	*ft_strdup(char *src);
char	*ft_strmemcat(char *first, char *second);
char	*ft_set_card_name(int value, int color);
t_card	*ft_get_unshuffled_deck(void);
void	ft_shuffle_deck(t_card *deck);
void	ft_free_deck(t_card *deck);
t_card	*ft_add_card(t_card card_to_add, t_card *original_deck);
t_card	*ft_remove_card(int index_to_del, t_card *original_deck);
t_card	**ft_distribute(char players_nb, int hand_size, t_card *pile);
void	ft_free_decks_tab(t_card **decks_tab);
int		ft_compare_cards(t_card **decks_tab, int index, int *to_compare);
t_card	**ft_copy_decks_tab(t_card **original_decks_tab);
t_card	**ft_win_hand(t_card **decks_tab);
int		*ft_winners_tab(int index, int winner, t_card **decks_tab);
int		ft_decklen(t_card *deck);
int		ft_players_left(t_card **decks_tab);

#endif
