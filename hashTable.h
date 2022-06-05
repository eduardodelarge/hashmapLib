#ifndef HASTABLE_H
# define HASTABLE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

typedef struct s_ht_item
{
	char				*key;
	char				*value;
	struct s_ht_item	*next;
}						t_ht_item;

typedef struct s_ht_table
{
	int					size;
	int					count;
	t_ht_item			**items;
}						t_ht_hash_table;

t_ht_item			*t_ht_new_item(const char *k, const char *v);
t_ht_hash_table		*ht_new_table();
static void			ht_del_item(t_ht_item *item);
void				ht_del_table(t_ht_hash_table *table);
static int			ht_handle_collision(const char *s, const int num_buckets, const int attempt);
static int			ht_hash(const char *s, const int a, const int m);

// ________________ HASH TABLE METHODS ________________ //

void				ht_insert(t_ht_hash_table *ht, const char *key, const char *value);
char				*ht_search(t_ht_hash_table *ht, const char *key);
void				ht_delete(t_ht_hash_table *h, const char *key);

#endif
