#include "laps.h"
/**
 * chec - checks if id is in list
 * @head: head of list of cars
 * @id: id to search for
 * Return: pointer to node
 */
car_t *chec(car_t *head, int id)
{
	while (head != NULL)
	{
		if (head->id == id)
			return (head);
		head = head->next;
	}
	return (NULL);
}

/**
 * _free - frees a linked-list
 * @head: head of list
 * Return: void
 */
void _free(car_t *head)
{
	car_t *next;

	if (head == NULL)
		return;

	next = head;
	while (next != NULL)
	{
		next = next->next;
		free(head);
		head = next;
	}
}

/**
 * insert - inserts a car
 * @head: pointer to pointer
 * @id: id of new car
 * Return: new list
 */
car_t *insert(car_t **head, int id)
{
	car_t *curr = NULL;
	car_t *new = NULL;

	if (!head)
		return (NULL);

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->id = id;
	new->laps = 0;
	new->next = NULL;
	printf("Car %d joined the race\n", new->id);

	if (!*head)
		return (new);

	curr = (*head);
	if (id < curr->id)
	{
		new->next = *head;
		*head = new;
	}
	else
	{
		while (curr->next && curr->next->id < id)
			curr = curr->next;

		new->next = curr->next;
		curr->next = new;
	}
	return (*head);
}

/**
 * print_cars - prints list
 * @list: list of cars
 * Return: void
 */
void print_cars(car_t *list)
{
	car_t *curr;

	curr = list;

	while (curr != NULL)
	{
		printf("Car %d [%lu laps]\n", curr->id, curr->laps);
		curr = curr->next;
	}
}

/**
 * race_state - keeps track
 * cars in a race
 * @id: array of int
 * @size: size of array
 * Return: void
 */
void race_state(int *id, size_t size)
{
	static car_t *car;
	car_t *check;
	size_t i = 0;

	if (!size)
	{
		_free(car);
		return;
	}
	if (car == NULL)
	{
		car = insert(&car, id[0]);
		car->laps = -1;
	}
	for (i = 0; i < size; i++)
	{
		check = chec(car, id[i]);
		if (check == NULL)
		{
			insert(&car, id[i]);
			continue;
		}
		check->laps++;
	}

	printf("Race state:\n");
	print_cars(car);
}
