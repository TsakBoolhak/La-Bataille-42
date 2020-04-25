#include "ft_functions.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int	i;
	
	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

void	ft_putnbr(int nb)
{
	if (nb == -2147483648)
	{
		write(1, "-2147483648", 11);
		return ;
	}
	if (nb < 0)
	{
		nb = -nb;
		write(1, "-", 1);
	}
	if (nb < 10)
	{
		ft_putchar(nb + '0');
		return ;
	}
	ft_putnbr(nb / 10);
	ft_putchar(nb % 10 + '0');
}

int		ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(char *src)
{
	int	i;
	char	*dest;

	i = 0;
	while (src[i])
		i++;
	i++;
	dest = (char *)malloc(sizeof(char) * i);
	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strmemcat(char *first, char *second)
{
	char	*dest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (first[i])
		i++;
	while (second[j])
		j++;
	i = i + j + 1;
	dest = (char *)malloc(sizeof(char) * i);
	i = 0;
	j = 0;
	while (first[i])
	{
		dest[i] = first[i];
		i++;
	}
	while (second[j])
	{
		dest[i+j] = second [j];
		j++;
	}
	dest[i+j] = '\0';
	return (dest);
}

char	*ft_set_card_name(int value, int color)
{
	char	*name = NULL;
	char	*copy = NULL;	

	if (value < 2 || value > 15)
		return (NULL);
	switch (value)
	{
		case 2:
			name = ft_strdup("Two");
			break;
		case 3:
			name = ft_strdup("Three");
			break;
		case 4:
			name = ft_strdup("Four");
			break;
		case 5:
			name = ft_strdup("Five");
			break;
		case 6:
			name = ft_strdup("Six");
			break;
		case 7:
			name = ft_strdup("Seven");
			break;
		case 8:
			name = ft_strdup("Eight");
			break;
		case 9:
			name = ft_strdup("Nine");
			break;
		case 10:
			name = ft_strdup("Ten");
			break;
		case 11:
			name = ft_strdup("Jack");
			break;
		case 12:
			name = ft_strdup("Queen");
			break;
		case 13:
			name = ft_strdup("King");
			break;
		case 14:
			name = ft_strdup("Ace");
			break;
		case 15:
			name = ft_strdup("Joker");
			break;
		default:
			name = ft_strdup("None");
	}
	if (value == 15)
		return (name);
	copy = ft_strdup(name);
	free(name);
	name = ft_strmemcat(copy, " of ");
	free(copy);
	copy = ft_strdup(name);
	free(name);
	switch (color)
	{
		case HEARTS:
			name = ft_strmemcat(copy, "Hearts");
			break;
		case SPADES:
			name = ft_strmemcat(copy, "Spades");
			break;
		case DIAMONDS:
			name = ft_strmemcat(copy, "Diamonds");
			break;
		case CLUBS:
			name = ft_strmemcat(copy, "Clubs");
			break;
		default:
			name = ft_strdup("None");
			break;
	}
	free(copy);
	return (name);
}

t_card	*ft_get_unshuffled_deck(void)
{
	t_card	*deck;
	int		cards_count;

	deck = malloc(sizeof(t_card) * 55);
	if (deck == NULL)
		return (NULL);
	cards_count = 0;
	deck[0].value = 2;
	deck[0].color = HEARTS;
	deck[0].name = ft_set_card_name(2, HEARTS);
	cards_count++;
	while (cards_count < 54)
	{
		deck[cards_count].color = deck[cards_count - 1].color;
		if (deck[cards_count - 1].value == 14)
		{
			if (deck[cards_count - 1].color != CLUBS)
			{
				deck[cards_count].value = 2;
				deck[cards_count].color = (deck[cards_count - 1].color) + 1;
			}
			else
			{
				deck[cards_count].value = 15;
				deck[cards_count].color = 0;
			}
		}
		else if (deck[cards_count - 1].value == 15)
			deck[cards_count].value = deck[cards_count - 1].value;
		else
			deck[cards_count].value = (deck[cards_count - 1].value) + 1;
		deck[cards_count].name = ft_set_card_name(deck[cards_count].value, deck[cards_count].color);
		cards_count++;
	}
	deck[cards_count].value = 0;
	return (deck);
}

void	ft_shuffle_deck(t_card *deck)
{
	int		counter;
	int		random;
	int		size;
	t_card	copy;

	counter = 0;
	while (deck[counter].value)
		counter++;
	if (!counter)
		return ;
	size = counter;
	while (counter > 0)
	{
		random = (rand() % size);
		copy = deck[counter - 1];
		deck[counter - 1] = deck[random];
		deck[random] = copy;
		counter--;
	}
	return ;
}

void	ft_free_deck(t_card *deck)
{
	int	counter;

	counter = 0;
	while (deck[counter].value)
	{
		if (deck[counter].name)
			free(deck[counter].name);
		counter++;
	}
	free(deck);
}

t_card	*ft_add_card(t_card card_to_add, t_card *original_deck)
{
	t_card	*new_deck;
	int	counter;

	counter = 0;
	while (original_deck[counter].value)
		counter++;
	counter +=2;
	new_deck = malloc(sizeof(t_card) * counter);
	counter = 0;
	while (original_deck[counter].value)
	{
		new_deck[counter].color = original_deck[counter].color;
		new_deck[counter].value = original_deck[counter].value;
		new_deck[counter].name = ft_set_card_name(new_deck[counter].value, new_deck[counter].color);
		counter++;
	}
	new_deck[counter].value = card_to_add.value;
	new_deck[counter].color = card_to_add.color;
	new_deck[counter].name = ft_set_card_name(new_deck[counter].value, new_deck[counter].color);
	counter++;
	new_deck[counter].value = 0;
	ft_free_deck(original_deck);
	return (new_deck);
}

t_card	*ft_remove_card(int	index_to_del, t_card *original_deck)
{
	t_card	*new_deck;
	int	counter;
	int	counter2;

	counter = 0;
	while (original_deck[counter].value)
		counter++;
	new_deck = malloc(sizeof(t_card) * counter);
	counter = 0;
	counter2 = 0;
	while (original_deck[counter].value)
	{
		if (counter != index_to_del)
		{
			new_deck[counter2].value = original_deck[counter].value;
			new_deck[counter2].color = original_deck[counter].color;
			new_deck[counter2].name = ft_set_card_name(new_deck[counter2].value, new_deck[counter2].color);
			counter2++;
		}
		counter++;
	}
	new_deck[counter2].value = 0;
	ft_free_deck(original_deck);
	return (new_deck);
}

t_card	**ft_distribute(char players_nb, int hand_size, t_card *pile)
{
	int		counter;
	t_card	**decks_tab;
	t_card	*tmp;

	counter = 0;
	while (pile[counter].value)
		counter++;
	if (players_nb * hand_size > counter || players_nb < 1 || hand_size < 1)
		return (NULL);
	decks_tab = malloc(sizeof(t_card *) * (players_nb + 1));
	counter = 0;
	while (counter < players_nb)
	{
		decks_tab[counter] = malloc(sizeof(t_card));
		decks_tab[counter][0].value = 0;
		counter++;
	}
	decks_tab[counter] = malloc(sizeof(t_card));
	decks_tab[counter][0].value = 42;
	counter = 0;
	while (counter < hand_size * players_nb)
	{
		tmp = ft_add_card(pile[0], decks_tab[counter % players_nb]);
		decks_tab[counter % players_nb] = tmp;
		tmp = ft_remove_card(0, pile);
		pile = tmp;
		counter++;
	}
	if (!(pile[0].value))
		ft_free_deck(pile);
	return (decks_tab);
}

void	ft_free_decks_tab(t_card **decks_tab)
{
	int	counter;

	counter = 0;
	while (decks_tab[counter][0].value != 42)
	{
		ft_free_deck(decks_tab[counter]);
		counter++;
	}
	free(decks_tab[counter]);
	free(decks_tab);
}

int		ft_compare_cards(t_card **decks_tab, int index, int *to_compare)
{
	int	max;
	int	count;
	int	count2;
	int	winner;

	max = 0;
	winner = 0;
	while (decks_tab[max][0].value != 42)
		max++;
	count = 0;
	while (count < max)
	{
		count2 = 0;
		while (to_compare[count2] != -1)
		{
			if (to_compare[count2] == count)
				break;
			count2++;
		}
		if (to_compare[count2] == -1)
		{
			count++;
			continue;
		}
		if (decks_tab[winner][index].value < decks_tab[count][index].value)
			winner = count;
		count++;
	}
	return (winner);
}

t_card	**ft_copy_decks_tab(t_card **original_decks_tab)
{
	t_card	**new_decks_tab;
	t_card	*new_deck;
	int	decks_count;
	int	cards_count;

	decks_count = 0;
	while (original_decks_tab[decks_count][0].value != 42)
		decks_count++;
	new_decks_tab = malloc(sizeof(t_card *) * (decks_count + 1));
	new_deck = malloc(sizeof(t_card) * 1);
	new_deck[0].value = 42;
	new_decks_tab[decks_count] = new_deck;
	decks_count = 0;
	while (original_decks_tab[decks_count][0].value != 42)
	{
		cards_count = 0;
		while (original_decks_tab[decks_count][cards_count].value)
			cards_count++;
		new_deck = malloc(sizeof(t_card) * (cards_count + 1));
		new_deck[cards_count].value = 0;
		cards_count = 0;
		while (original_decks_tab[decks_count][cards_count].value)
		{
			new_deck[cards_count].value = original_decks_tab[decks_count][cards_count].value;
			new_deck[cards_count].color = original_decks_tab[decks_count][cards_count].color;
			new_deck[cards_count].name = ft_set_card_name(new_deck[cards_count].value, new_deck[cards_count].color);
			cards_count++;
		}
		new_decks_tab[decks_count] = new_deck;
		decks_count++;
	}
	return (new_decks_tab);
}

t_card	**ft_win_hand(t_card **decks_tab)
{
	int		*winners_tab;
	int		*tmp_int_tab;
	t_card	**new_decks_tab;
	t_card	*tmp;
	t_card	*played_cards;
	int		count;
	int		winner;
	int		players;

	new_decks_tab = ft_copy_decks_tab(decks_tab);
	count = 0;
	while (new_decks_tab[count][0].value != 42)
	{
		ft_putnbr(ft_decklen(new_decks_tab[count]));
		ft_putstr(" cards left");
		count++;
		if (new_decks_tab[count][0].value != 42)
			ft_putstr("      	      ");
	}
	ft_putstr("\n\n\n");
	winners_tab = malloc(sizeof(int) * (count + 1));
	winners_tab[count] = -1;
	while (count > 0)
	{
		count--;
		winners_tab[count] = count;
	}
	count = ft_compare_cards(new_decks_tab, 0, winners_tab);
	free(winners_tab);
	winners_tab = ft_winners_tab(0, count, decks_tab);
	played_cards = malloc(sizeof(t_card));
	played_cards[0].value = 0;
	count = 0;
	while (new_decks_tab[count][0].value != 42)
	{
		if (new_decks_tab[count][0].value)
		{
			ft_putstr(new_decks_tab[count][0].name);
			if (new_decks_tab[count+1][0].value != 42 && new_decks_tab[count+1][0].value)
			{
				winner = 0;
				while (winner < 21 - ft_strlen(new_decks_tab[count][0].name))
				{
					write(1, " ", 1);
					winner++;
				}
				ft_putstr("VS");
				winner = 0;
				while (winner < 21 - ft_strlen(new_decks_tab[count+1][0].name))
				{
					write(1, " ", 1);
					winner++;
				}
			}
			played_cards = ft_add_card(new_decks_tab[count][0], played_cards);
			tmp = ft_remove_card(0, new_decks_tab[count]);
			new_decks_tab[count] = tmp;
		}
		count++;
	}
	ft_putchar('\n');
	while (winners_tab[1] != -1 )
	{
		count = 0;
		ft_putstr("\n                   BATTLE !!!\n");
		while (winners_tab[count] != -1)
		{
			if (new_decks_tab[winners_tab[count]][0].value == 0 || new_decks_tab[winners_tab[count]][1].value == 0)
			{
				if (new_decks_tab[winners_tab[count]][0].value)
				{
					ft_putstr("Player ");
					ft_putnbr((winners_tab[count]) + 1);
					ft_putstr(" puts his last card, face down, into the hand before continuing\n");
					played_cards = ft_add_card(new_decks_tab[winners_tab[count]][0], played_cards);
					tmp = ft_remove_card(0, new_decks_tab[winners_tab[count]]);
					new_decks_tab[winners_tab[count]] = tmp;
				}
				else
				{
					ft_putstr("Player ");
					ft_putnbr((winners_tab[count]) + 1);
					ft_putstr(" has no card left to continue the battle\n");
				}
				count++;
				continue;
			}
			ft_putstr("Player ");
			ft_putnbr((winners_tab[count]) + 1);
			ft_putstr(" puts a card, face down, into the hand before continuing\n");
			played_cards = ft_add_card(new_decks_tab[winners_tab[count]][0], played_cards);
			tmp = ft_remove_card(0, new_decks_tab[winners_tab[count]]);
			new_decks_tab[winners_tab[count]] = tmp;
			count++;
		}
		tmp_int_tab = ft_winners_tab(0, ft_compare_cards(new_decks_tab, 0, winners_tab), new_decks_tab);
		count = 0;
		ft_putchar('\n');
		players = ft_players_left(new_decks_tab);
		while (winners_tab[count] != -1)
		{
			if (new_decks_tab[winners_tab[count]][0].value == 0)
			{
				ft_putstr("Player ");
				ft_putnbr((winners_tab[count]) + 1);
				ft_putstr(" ran out of cards");
				count++;
				continue;
			}
			if (players > 1)
			{
				ft_putstr(new_decks_tab[count][0].name);
				if (new_decks_tab[count+1][0].value != 42 && new_decks_tab[count+1][0].value)
				{
					winner = 0;
					while (winner < 21 - ft_strlen(new_decks_tab[count][0].name))
					{
						write(1, " ", 1);
						winner++;
					}
					ft_putstr("VS");
					winner = 0;
					while (winner < 21 - ft_strlen(new_decks_tab[count+1][0].name))
					{
						write(1, " ", 1);
						winner++;
					}
				}
			}
			players = ft_players_left(new_decks_tab);
			played_cards = ft_add_card(new_decks_tab[winners_tab[count]][0], played_cards);
			tmp = ft_remove_card(0, new_decks_tab[winners_tab[count]]);
			new_decks_tab[winners_tab[count]] = tmp;
			count++;
		}
		ft_putchar('\n');
		free(winners_tab);
		winners_tab = tmp_int_tab;
	}
	winner = winners_tab[0];
	ft_putstr("\n\nPlayer ");
	ft_putnbr(winner+1);
	ft_putstr(" won this hand.\n\nThe hand was composed of the following ");
	ft_putnbr(ft_decklen(played_cards));
	ft_putstr(" cards :\n");
	ft_shuffle_deck(played_cards);
	while (played_cards[0].value)
	{
		ft_putstr(played_cards[0].name);
		write(1, "\n", 1);
		tmp = ft_add_card(played_cards[0], new_decks_tab[winner]);
		new_decks_tab[winner] = tmp;
		tmp = ft_remove_card(0, played_cards);
		played_cards = tmp;
	}
	write(1, "\n\n\n\n\n", 5);
	free(played_cards);
	free(winners_tab);
	ft_free_decks_tab(decks_tab);
	return (new_decks_tab);
}

int		*ft_winners_tab(int index, int winner, t_card **decks_tab)
{
	int	*winners_tab;
	int counter;
	int	winners_count;

	counter = 0;
	winners_count = 0;
	while (decks_tab[counter][0].value != 42)
	{
		if (decks_tab[counter][index].value == decks_tab[winner][index].value)
			winners_count++;
		counter++;
	}
	winners_tab = malloc(sizeof(int) * (winners_count + 1));
	winners_tab[winners_count] = -1;
	counter = 0;
	winners_count = 0;
	while (decks_tab[counter][0].value != 42)
	{
		if (decks_tab[counter][index].value == decks_tab[winner][index].value)
		{
			winners_tab[winners_count] = counter;
			winners_count++;
		}
		counter++;
	}
	return (winners_tab);
}

int		ft_decklen(t_card *deck)
{
	int	i;

	i = 0;
	while (deck[i].value)
		i++;
	return (i);
}

int		ft_players_left(t_card **decks_tab)
{
	int	i;
	int	players;

	i = 0;
	players = 0;
	while (decks_tab[i][0].value != 42)
	{
		if (decks_tab[i][0].value)
			players++;
		i++;
	}
	return (players);
}
