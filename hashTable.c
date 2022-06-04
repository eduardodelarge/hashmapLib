#include "hashTable.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

/**
* @brief initialization of ht_items. Allocates a chunk of memory the size of an ht_item and saves a copy of the strings k and v in the new chunk.
* @param k 
* @param v 
* @return t_ht_item 
 */
static t_ht_item*	ht_new_item(const char *k, const char *v)
{
	t_ht_item	item;

	item.key = strdup(k);
	item.value = strdup(v);
	item.next = NULL;
	return (t_ht_item*)malloc(sizeof(t_ht_item));
}

/**
* @brief Initialize a new hash table. size defines how many items we can store. items is set to NULL to indicate that no items are stored yet. 
* 
* @return t_ht 
 */
t_ht_hash_table	*ht_new_table()
{
	t_ht_hash_table	*table;

	table = malloc(sizeof(t_ht_hash_table));
	table->size = 0;
	table->count = 0;
	table->items = NULL;
	return (table);
}

/**
* @brief Free the memory allocated for an item.
*
* @param item 
 */
static void ht_del_item(t_ht_item *item)
{
	free(item->key);
	free(item->value);
	free(item);
}

/**
* @brief Free the memory allocated for the hash table.
 *
 *@param table 
 */
void ht_del_table(t_ht_hash_table *table)
{
	int		i;

	i = 0;
	while (i < table->size)
	{
		if (table->items[i])
			ht_del_item(table->items[i]);
		i++;
	}
	free(table->items);
	free(table);
}

/**
 /*@brief Handles collisions by double hashing.
 /*
 /*@param s 
 /*@param num_buckets 
 /*@param attempt 
 /*@return int 
 */
static int ht_handle_collision(const char *s, const int num_buckets, const int attempt)
{
	const int hash_a = ht_hash(s, 163, num_buckets);
	const int hash_b = ht_hash(s, 163, num_buckets);
	return (hash_a + (attempt * (hash_b + 1))) % num_buckets;
}

/**
 *@brief Turn input string into an index for the hash table.
 *
 * @param s: input string
 * @param a: a prime number higher than 128
 * @param m: size of the hash table
 */
static int ht_hash(const char *s, const int a, const int m)
{
	long hash = 0;
	const int len_s = strlen(s);
	int i = 0;

	while (i < len_s)
	{
		hash += (long)pow(a, len_s - (i + 1)) * s[i];
		hash = hash % m;
		i++;
	}
	return (hash);
}

/**
 *@brief Insert a new item into the hash table.
 *
 *@param ht 
 *@param key 
 *@param value 
 */
void ht_insert(t_ht_hash_table* ht, const char* key, const char* value)
{
	t_ht_item *item = ht_new_item(key, value);
	int			index = ht_handle_collision(item->key, ht->size, 0);
	t_ht_item	*cur_item = ht->items[index];
	int i = 1;
	while(cur_item)
	{
		index = ht_handle_collision(item->key, ht->size, i);
		cur_item = ht->items[index];
		i++;
	}
	ht->items[index] = item;
	ht->count++;
}

char* ht_search(t_ht_hash_table* ht, const char* key)
{
	int			index = ht_handle_collision(key, ht->size, 0);
	t_ht_item	*cur_item = ht->items[index];
	int i = 1;
	while(cur_item)
	{
		if (strcmp(cur_item->key, key) == 0)
			return (cur_item->value);
		index = ht_handle_collision(key, ht->size, i);
		cur_item = ht->items[index];
		i++;
	}
	return (NULL);
}

void ht_delete(t_ht_hash_table* h, const char* key)
{
	int			index = ht_handle_collision(key, h->size, 0);
	t_ht_item	*cur_item = h->items[index];
	int i = 1;
	while(cur_item)
	{
		if (strcmp(cur_item->key, key) == 0)
		{
			ht_del_item(cur_item);
			h->items[index] = NULL;
			h->count--;
			return ;
		}
		index = ht_handle_collision(key, h->size, i);
		cur_item = h->items[index];
		i++;
	}
}