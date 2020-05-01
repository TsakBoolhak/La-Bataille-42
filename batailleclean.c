#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>

typedef struct s_card
{
	char	name[50];
	int	value;
	char	color[10];
}t_card;

char	*ft_strcpy(char *dest, char *src);
int	ft_decklen(t_card *deck);
void	print_card(t_card card);
void	print_carddeck(t_card *deck, int size);
void	print_decklen(t_card *deck);
t_card	*get_deck(void);
void	shuffle_cards(t_card *tab, int size);
void	card_division(t_card *deck, t_card *player1, t_card *player2);
void	set_battle(t_card *player1, t_card *player2, t_card *table);
void	battle(t_card p1_card, t_card p2_card, t_card *player1, t_card *player2, t_card *table);
void	war(t_card p1_card, t_card p2_card, t_card *player1, t_card *player2, t_card *table);
void	rounds(t_card *player1, t_card *player2, t_card *table);
void	add_card_top(t_card card, t_card *deck);
void	add_card_bot(t_card *table, t_card *deck);
void	remove_card(t_card *deck, int removed_card);
void	game(t_card *deck, t_card *player1, t_card *player2, t_card *table);

int	main(void)
{
	t_card	*deck;
	t_card	*table;
	t_card	*player1;
	t_card	*player2;
	srand(time(NULL));

	deck = get_deck();
	table = malloc(sizeof(t_card)*55);
	table[0].value = 42;
	player1 = malloc(sizeof(t_card)*55);
	player2 = malloc(sizeof(t_card)*55);
	game(deck, player1, player2, table);
	free(player1);
	free(player2);
	free(table);
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

void	print_decklen(t_card *deck)
{
	int i = 0;
	while(i < ft_decklen(deck))
	{
		printf("#");
		i++;
	}
	printf("\n");
}

void	print_card(t_card card)
{
	if (card.value <= 10)
		printf("%d of %s", card.value, card.color);
	else if (card.value == 11)
		printf("jack of %s", card.color);
	else if (card.value == 12)
		printf("queen of %s", card.color);
	else if (card.value == 13)
		printf("king of %s", card.color);
	else if (card.value == 14)
		printf("ace of %s", card.color);
	else if (card.value == 15)
		printf("joker");
	else
		printf("unknown card");
}

void	print_carddeck(t_card *deck, int size)
{
	int	i;

	i = 0;
	printf("##########\n");
	while(i < size)
	{
		if(deck[i].value > 1)
		{
			print_card(deck[i]);
			printf("\n");
		}
		i++;
	}
}

t_card	*get_deck(void)
{
	int	i;
	int	j;
	t_card	*deck;

	i = 0;
	j = 2;
	deck = malloc(sizeof(t_card)*55);
	while(i < 52)
	{
		deck[i].value = j;
		j++;
		if (j == 15 && i < 53)
			j = 2;
		if (i / 13 == 0)
			ft_strcpy(deck[i].color, "hearts");
		else if (i / 13 == 1)
			ft_strcpy(deck[i].color, "spades");
		else if (i / 13 == 2)
			ft_strcpy(deck[i].color, "diamonds");
		else
			ft_strcpy(deck[i].color, "clubs");
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


void	shuffle_cards(t_card *tab, int size)
{
	int	i;
	int	j;
	t_card	d;
	
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

void	card_division(t_card *deck, t_card *player1, t_card *player2)
{
	int	i;
	int	p1_counter;
	int	p2_counter;

	i = 0;
	p1_counter = 0;
	p2_counter = 0;
	while(i < 54)
	{
		if (i % 2 == 0)
			player1[p1_counter++] = deck[i];
		else
			player2[p2_counter++] = deck[i];
		i++;
	}
	player1[p1_counter].value = 42;
	player2[p2_counter].value = 42;
}

void	set_battle(t_card *player1, t_card *player2, t_card *table)
{
	print_card(player1[0]);
	printf(" vs ");
	print_card(player2[0]);
	printf(": ");
	add_card_top(player1[0], table);
	add_card_top(player2[0], table);
	remove_card(player1, 0);
	remove_card(player2, 0);
	shuffle_cards(table, ft_decklen(table));
}

void	battle(t_card p1_card, t_card p2_card, t_card *player1, t_card *player2, t_card *table)
{
	if (p1_card.value < p2_card.value)
	{
		add_card_bot(table, player2);
		printf("player2 win\n");
	}
	else if (p2_card.value < p1_card.value)
	{
		add_card_bot(table, player1);
		printf("player1 win\n");
	}
	else
	{
		printf("	WAR:	");
		war(p1_card, p2_card, player1, player2, table);
	}
}

void	war(t_card p1_card, t_card p2_card, t_card *player1, t_card *player2, t_card *table)
{
	if(player1[0].value != 42 && player2[0].value != 42)
	{
		printf("	SECRET CARD...");
		add_card_top(player1[0], table);
		add_card_top(player2[0], table);
		remove_card(player1, 0);
		remove_card(player2, 0);
		if(player1[0].value != 42 && player2[0].value != 42)
		{
			p1_card = player1[0];
			p2_card = player2[0];
			set_battle(player1, player2, table);
			battle(p1_card, p2_card, player1, player2, table);
		}
		else
		{
			if(player1[0].value == 42)
			{
				add_card_bot(table, player2);
				printf("player1 has not enough cards, player2 win\n");
			}
			else
			{
				add_card_bot(table, player1);
				printf("player2 has not enough cards, player1 win\n");
			}
		}
	}
	else
	{
		if(player1[0].value == 42)
		{
			add_card_bot(table, player2);
			printf("player1 has not enough cards, player2 win\n");
		}
		else
		{
			add_card_bot(table, player1);
			printf("player2 has not enough cards, player1 win\n");
		}
	}
}

void	rounds(t_card *player1, t_card *player2, t_card *table)
{
	int	counter;
	t_card	p1_playedcard;
	t_card	p2_playedcard;

	counter = 0;
	while (player1[0].value != 42 && player2[0].value != 42 && player1[0].value != 0 && player2[0].value != 0)
	{
		p1_playedcard = player1[0];
		p2_playedcard = player2[0];
		set_battle(player1, player2, table);
		battle(p1_playedcard, p2_playedcard, player1, player2, table);
		while(table[0].value != 42)
			remove_card(table, 0);
		printf("player1 has %d cards left left, player2 has %d cards left\n\n", ft_decklen(player1), ft_decklen(player2));
		printf("player1: ");
		print_decklen(player1);
		printf("player2: ");
		print_decklen(player2);
		system("clear");
		counter++;
	}
	if (player2[0].value == 42 || player2[0].value == 0)
		printf("player1 win\n");
	else
		printf("player2 win\n");
	printf("La partie a duree %d manches\n", counter);
}

int	ft_decklen(t_card *deck)
{
	int	i;
	
	i = 0;
	while (deck[i].value != 42)
		i++;
	return(i);
}

void	add_card_top(t_card card, t_card *deck)
{
	int	i;
	int	j;
	t_card	*cpy_deck;

	i = 1;
	j = 0;
	cpy_deck = malloc(sizeof(t_card)*55);
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


void	add_card_bot(t_card *table, t_card *deck)
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

void	remove_card(t_card *deck, int removed_card)
{
	int	i;

	i = removed_card;
	while(deck[i - 1].value != 42)
	{
		deck[i] = deck[i + 1];
		i++;
	}
	while(i < 55)
	{
		deck[i].value = 0;
		i++;
	}
}

void	game(t_card *deck, t_card *player1, t_card *player2, t_card *table)
{
	shuffle_cards(deck, ft_decklen(deck));
	card_division(deck, player1, player2);
	rounds(player1, player2, table);
}
