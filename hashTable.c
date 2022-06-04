#include "hashTable.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief initialization of ht_items. Allocates a chunk of memory the size of an
 *ht_item and saves a copy of the strings k and v in the new chunk.
 * @params k and v
 **/
static ht_item ht_new_item(const char *k, const char *v) {
  ht_item *i = malloc(sizeof(ht_item));
  i->key = strdup(k);
  i->value = strdup(v);

  return i;
}

ht_hash_table *ht_new_table() {
  ht_hash_table ht = malloc(sizeof(ht_hash_table));

  ht->size = 53;
  ht->count = 0;
  ht->items = calloc((size_t)ht.size, sizeof(ht_item *));

  return ht;
}
