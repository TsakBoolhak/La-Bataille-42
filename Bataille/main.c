#include "ft_functions.h"

int	main(void)
{
	t_card	*deck;
	t_card	**decks_tab;
	int		decks_count;
	int		cards_count;

	srand(time(NULL));
	deck = ft_get_unshuffled_deck();
	while (deck[0].value != deck[1].value || deck[4].value != deck[5].value)
		ft_shuffle_deck(deck);
	decks_tab = ft_distribute(2, 27, deck);
	decks_count = 0;
	while (decks_tab[decks_count][0].value != 42)
	{
		cards_count = 0;
		ft_putstr("\t\tDeck Number ");
		ft_putnbr(decks_count + 1);
		ft_putstr("\n");
		while (decks_tab[decks_count][cards_count].value)
		{
			ft_putstr(decks_tab[decks_count][cards_count].name);
			write(1, "\n", 1);
			cards_count++;
		}
		decks_count++;
	}
	write(1, "\n", 1);
	ft_putstr("Now let's see the decks after a hand is played\n\n");
	decks_tab = ft_win_hand(decks_tab);
	decks_count = 0;
	while (decks_tab[decks_count][0].value != 42)
	{
		cards_count = 0;
		ft_putstr("\t\tDeck Number ");
		ft_putnbr(decks_count + 1);
		write(1, "\n", 1);
		while (decks_tab[decks_count][cards_count].value)
		{
			ft_putstr(decks_tab[decks_count][cards_count].name);
			write(1, "\n", 1);
			cards_count++;
		}
		decks_count++;
	}
	ft_putstr("\n\nNow let's see the rest of the game\n\n");
	if (decks_tab[0][0].value)
	{
		ft_putstr(decks_tab[0][0].name);
		cards_count = 0;
		while (cards_count < 28 - ft_strlen(decks_tab[0][0].name))
		{
			write(1, " ", 1);
			cards_count++;
		}
	}
	else
		ft_putstr("No card left                ");
	ft_putstr("Versus");
	if (decks_tab[1][0].value)
	{
		cards_count = 0;
		while (cards_count < 28 - ft_strlen(decks_tab[1][0].name))
		{
			write(1, " ", 1);
			cards_count++;
		}
		ft_putstr(decks_tab[1][0].name);
	}
	else
		ft_putstr("                No card left");
	write(1, "\n\n", 2);
	while (decks_tab[0][0].value && decks_tab[1][0].value)
	{
		decks_tab = ft_win_hand(decks_tab);
		if (decks_tab[0][0].value)
		{
			ft_putstr(decks_tab[0][0].name);
			cards_count = 0;
			while (cards_count < 28 - ft_strlen(decks_tab[0][0].name))
			{
				write(1, " ", 1);
				cards_count++;
			}
		}
		else
			ft_putstr("No card left                ");
		ft_putstr("Versus");
		if (decks_tab[1][0].value)
		{
			cards_count = 0;
			while (cards_count < 28 - ft_strlen(decks_tab[1][0].name))
			{
				write(1, " ", 1);
				cards_count++;
			}
			ft_putstr(decks_tab[1][0].name);
		}
		else
			ft_putstr("                No card left");
		write(1, "\n\n", 2);
	}
	decks_count = 0;
	while (decks_tab[decks_count][0].value != 42)
	{
		cards_count = 0;
		ft_putstr("\n\t\tDeck Number ");
		ft_putnbr(decks_count + 1);
		write(1, "\n\n", 1);
		while (decks_tab[decks_count][cards_count].value)
		{
			ft_putstr(decks_tab[decks_count][cards_count].name);
			write(1, "\n", 1);
			cards_count++;
		}
		decks_count++;
	}
	if (decks_tab[0][0].value)
		ft_putstr("\n\n\t\t\tPlayer 1 Win !!!\n");
	else
		ft_putstr("\n\n\t\tPlayer 2 Win !!!\n");
	ft_free_decks_tab(decks_tab);
}
