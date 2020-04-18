#include "ft_functions.h"

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

char	*ft_set_card_name(char value, char color)
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
	char	cards_count;

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
	counter--;
	size = counter;
	while (counter >= 0)
	{
		random = (rand() % size);
		copy = deck[counter];
		deck[counter] = deck[random];
		deck[random] = copy;
		counter--;
	}
	return ;
}

t_card	*ft_add_card(t_card card_to_add, t_card *original_deck)
{
	t_card	*new_deck;
	int	counter;

	counter = 0;
	while (original_deck[counter].value)
		counter++;
	if (!counter)
		counter++;
	counter +=2;
	new_deck = malloc(sizeof(t_card) * counter);
	counter = 0;
	while (original_deck[counter].value)
	{
		new_deck[counter] = original_deck[counter];
		new_deck[counter].name = ft_set_card_name(new_deck[counter].value, new_deck[counter].color);
		counter++;
	}
	new_deck[counter] = card_to_add;
	new_deck[counter].name = ft_set_card_name(new_deck[counter].value, new_deck[counter].color);
	counter++;
	new_deck[counter].value = 0;
	return (new_deck);
}
