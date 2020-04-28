#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>

typedef struct s_card
{
	char	name[50];
	int	value;
	char	color[10];
}s_card;

char	*ft_strcpy(char *dest, char *src);
void	print_card(s_card card);
void	print_carddeck(s_card *deck, int size);
s_card	*get_deck(void);
void	shuffle_cards(s_card *tab, int size);
void	card_division(s_card *deck, s_card *player1, s_card *player2);
void	game(s_card *player1, s_card *player2);
void	add_card_top(s_card card, s_card *deck);
void	add_card_bot(s_card *table, s_card *deck);
void	remove_card(s_card *deck, int removed_card);
int		ft_decklen(s_card *deck);

int	main(void)
{
		//SETTINGS
	int	debugg;
	//int	i;
	s_card	*deck;
	s_card	*player1;
	s_card	*player2;
	srand(time(NULL));

	debugg = 0; 
	//i = 0;
	deck = get_deck();
	player1 = malloc(sizeof(s_card)*55);
	player2 = malloc(sizeof(s_card)*55);
		//FONCTIONS
	shuffle_cards(deck, 54);
	card_division(deck, player1, player2);
	game(player1, player2);
	if (debugg)
	{
		print_carddeck(deck, 55);
		print_carddeck(player1, 55);
		print_carddeck(player2, 55);
	}
	free(player1);
	free(player2);
	return(0);
}

			//FONCTIONS

char	*ft_strcpy(char *dest, char *src)
{
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	while(dest[i])
		i++;
	while(src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	return(dest);
}

void	print_card(s_card card)
{
	if (card.value <= 10)
		printf("%d de %s", card.value, card.color);
	else if (card.value == 11)
		printf("valet de %s", card.color);
	else if (card.value == 12)
		printf("dame de %s", card.color);
	else if (card.value == 13)
		printf("roi de %s", card.color);
	else if (card.value == 14)
		printf("as de %s", card.color);
	else if (card.value == 15)
		printf("joker");
	else
		printf("unknown card");
}

void	print_carddeck(s_card *deck, int size)
{
	int	i;

	i = 0;
	printf("##########\n");
	while(i < size)
	{
	//	if (deck[i].value > 1 && deck[i].value != 42)
	//	{
			print_card(deck[i]);
			printf("\n");
	//	}
		i++;
	}
}

s_card	*get_deck(void)
{
	int	i;
	int	j;
	s_card	*deck;

	deck = malloc(sizeof(s_card)*55);
	i = 0;
	j = 2;
	while(i < 52)
	{
		deck[i].value = j;
		j++;
		if (j == 15 && i < 53)
			j = 2;
		if (i / 13 == 0)
			ft_strcpy(deck[i].color, "coeur");
		else if (i / 13 == 1)
			ft_strcpy(deck[i].color, "pic");
		else if (i / 13 == 2)
			ft_strcpy(deck[i].color, "carreaux");
		else
			ft_strcpy(deck[i].color, "trefle");
		i++;

	}
	while(i < 54)
	{
		deck[i].value = 15;
		ft_strcpy(deck[i].color, "joker");
		i++;
	}
	deck[i].value = 42;
	return(deck);
}


void	shuffle_cards(s_card *tab, int size)
{
	int	i;
	int	j;
	s_card	d;
	
	i = 0;
	while(i < size)
	{
		j = rand()% size;
		d = tab[i];
		tab[i] = tab[j];
		tab[j] = d;
		i++;
	}
}

void	card_division(s_card *deck, s_card *player1, s_card *player2)
{
	//int	deck_counter;
	int	p1_counter;
	int	p2_counter;
	int	i;

	i = 0;
	p1_counter = 0;
	p2_counter = 0;
	while(i < 54)
	{
		if (i % 2 == 0)
		{
			player1[p1_counter] = deck[i];
			p1_counter++;
		}
		else
		{
			player2[p2_counter] = deck[i];
			p2_counter++;
		}
		i++;
	}
	player1[p1_counter].value = 42;
	player2[p2_counter].value = 42;
}

void	game(s_card *player1, s_card *player2)
{
	//int	i;
	//int	j;
	s_card	*table;

	//i = 0;
	//j = 0;
	table = malloc(sizeof(s_card)*55);
	table[0].value = 42;
	while (player1[0].value != 42 && player2[0].value != 42)
	{
		print_card(player1[0]);
		printf(" vs ");
		print_card(player2[0]);
		printf(": ");
		add_card_top(player1[0], table);
		add_card_top(player2[0], table);
		shuffle_cards(table, 2);
		if(player1[0].value < player2[0].value)
		{
			add_card_bot(table, player2);
			printf("player2 win\n");
		}
		/*else if(player1[0].value == player2[0].value)
		{
			remove_card(player1, 0);
			add_card_top(player1[0], table);
			remove_card(player2, 0);
			add_card_top(player2[0], table);
			add_card_bot(table, player2);
			printf("player2 win\n");
		}*/
		else
		{
			add_card_bot(table, player1);
			printf("player1 win\n");
		}
		remove_card(player1, 0);
		remove_card(player2, 0);
		print_carddeck(player2, 55);
		printf("Player 1 has %d cards left, Player 2 has %d cards left\n\n", ft_decklen(player1), ft_decklen(player2));
		while(table[0].value != 42)
			remove_card(table, 0);
	}
	if (player2[0].value == 42)
		printf("player1 win\n");
	else
		printf("player2 win\n");
	free(table);
}

int		ft_decklen(s_card *deck)
{
	int	i;

	i = 0;
	while (deck[i].value != 42)
		i++;
	return (i);
}

void	add_card_top(s_card card, s_card *deck)
{
	int	i;
	int	j;
	s_card	*cpy_deck;

	i = 1;
	j = 0;
	cpy_deck = malloc(sizeof(s_card)*55);
	while(deck[j].value != 42)
	{
		cpy_deck[i + j] = deck[j];
		j++;
	}
	cpy_deck[i + j].value = 42; 
	cpy_deck[0] = card;
	j = 0;
	while(cpy_deck[j].value != 42)
	{
		deck[j] = cpy_deck[j];
		j++;
	}
	deck[j] = cpy_deck[j];
	free(cpy_deck);
}


void	add_card_bot(s_card *table, s_card *deck)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(deck[i].value != 42)
		i++;
	while(table[j].value != 42)
	{
		deck[i] = table[j];
		i++;
		j++;
	}
	deck[i].value = 42;
}

void	remove_card(s_card *deck, int removed_card)
{
	int	i;

	i = removed_card;
	while(deck[i - 1].value != 42)
	{
		deck[i] = deck[i + 1];
		i++;
	}
}
