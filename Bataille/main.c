#include "ft_functions.h"

int	main(void)
{
	t_card	*deck;
	t_card	*tmp;
	char	cards_count;

	deck = ft_get_unshuffled_deck();
	cards_count = 0;
	ft_putstr("Unshuffled deck :\n\n");
	while (deck[cards_count].value)
	{
		ft_putstr(deck[cards_count].name);
		write(1, "\n", 1);
		cards_count++;
	}
	srand(time(NULL));
	ft_shuffle_deck(deck);
	cards_count = 0;
	ft_putstr("\n\nShuffled deck :\n\n");
	while (deck[cards_count].value)
	{
		ft_putstr(deck[cards_count].name);
		write(1, "\n", 1);
		cards_count++;
	}
	cards_count--;
	ft_putstr("\n\nceci est un test\n\n");
	tmp = ft_add_card(deck[cards_count], deck);
	cards_count = 0;
	while (deck[cards_count].value)
	{
		if (deck[cards_count].name);
			free(deck[cards_count].name);
		cards_count++;
	}
	free(deck);
	deck = tmp;
	cards_count = 0;
	ft_putstr("\n\nDeck After a card were added :\n\n");
	while (deck[cards_count].value)
	{
		ft_putstr(deck[cards_count].name);
		write(1, "\n", 1);
		cards_count++;
	}
	cards_count = 0;
	while (deck[cards_count].value)
	{
		if (deck[cards_count].name);
			free(deck[cards_count].name);
		cards_count++;
	}
	free(deck); 
	return (0);
}
