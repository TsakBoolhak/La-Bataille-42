#include "ft_functions.h"

int	main(void)
{
	t_card	*deck;
	t_card	**decks_tab;
	int		count;

	srand(time(NULL));
	deck = ft_get_unshuffled_deck();
	ft_shuffle_deck(deck);
	decks_tab = ft_distribute(2, 27, deck);
	count = 0;
	while (decks_tab[0][0].value && decks_tab[1][0].value)
	{
		count++;
		ft_putstr("\t\t\tRound ");
		ft_putnbr(count);
		ft_putstr("\n\n\n");
		ft_putstr("Player 1\t     VS\t        Player 2\n");
		decks_tab = ft_win_hand(decks_tab);
	}
	if (decks_tab[0][0].value)
		ft_putstr("\t\t\tPlayer 1 Win !!!\n\n");
	else
		ft_putstr("\t\t\tPlayer 2 Win !!!\n\n");
	ft_free_decks_tab(decks_tab);
}
