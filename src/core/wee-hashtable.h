/*
 * Copyright (C) 2010 Sebastien Helleu <flashcode@flashtux.org>
 *
 * This file is part of WeeChat, the extensible chat client.
 *
 * WeeChat is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * WeeChat is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with WeeChat.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __WEECHAT_HASHTABLE_H
#define __WEECHAT_HASHTABLE_H 1

struct t_hashtable;
struct t_infolist_item;

typedef unsigned int (t_hashtable_hash_key)(struct t_hashtable *hashtable,
                                            const void *key);
typedef int (t_hashtable_keycmp)(struct t_hashtable *hashtable,
                                 const void *key1, const void *key2);
typedef void (t_hashtable_map)(void *data,
                               struct t_hashtable *hashtable,
                               const void *key, const void *value);

/*
 * Hashtable is a structure with an array "htable", each entry is a pointer
 * to a linked list, and it is read with hashed key (as unsigned int).
 * Keys with same hashed key are grouped in a linked list pointed by htable.
 * htable is not sorted, linked list is sorted.
 *
 * Example of a hashtable with size 8 and 6 items added inside, items are:
 * "weechat", "fast", "light", "extensible", "chat", "client"
 * Keys "fast" and "light" have same hashed value, so they are together in
 * linked list.
 *
 * Result is:
 * +-----+
 * |   0 |
 * +-----+
 * |   1 |
 * +-----+
 * |   2 | --> "extensible"
 * +-----+
 * |   3 | --> "fast" --> "light"
 * +-----+
 * |   4 | --> "weechat"
 * +-----+
 * |   5 | --> "chat"
 * +-----+
 * |   6 | --> "client"
 * +-----+
 * |   7 |
 * +-----+
 */

enum t_hashtable_type
{
    HASHTABLE_INTEGER = 0,
    HASHTABLE_STRING,
    HASHTABLE_POINTER,
    HASHTABLE_BUFFER,
    HASHTABLE_TIME,
    /* number of hashtable types */
    HASHTABLE_NUM_TYPES,
};

struct t_hashtable_item
{
    void *key;                          /* item key                         */
    int key_size;                       /* size of key (in bytes)           */
    void *value;                        /* pointer to value                 */
    int value_size;                     /* size of value (in bytes)         */
    struct t_hashtable_item *prev_item; /* link to previous item            */
    struct t_hashtable_item *next_item; /* link to next item                */
};

struct t_hashtable
{
    int size;                          /* hashtable size                    */
    struct t_hashtable_item **htable;  /* table to map hashes with linked   */
                                       /* lists                             */
    int items_count;                   /* number of items in hashtable      */
    
    /* type for keys and values */
    enum t_hashtable_type type_keys;   /* type for keys: int/str/pointer    */
    enum t_hashtable_type type_values; /* type for values: int/str/pointer  */
    
    /* callbacks */
    t_hashtable_hash_key *callback_hash_key; /* hash key to integer value   */
    t_hashtable_keycmp *callback_keycmp;     /* compare two keys            */

    /* keys */
    char *keys;                        /* keys list (NULL if never asked)   */
};

extern struct t_hashtable *hashtable_new (int size,
                                          const char *type_keys,
                                          const char *type_values,
                                          t_hashtable_hash_key *hash_key_cb,
                                          t_hashtable_keycmp *keycmp_cb);
extern int hashtable_set_with_size (struct t_hashtable *hashtable,
                                    void *key, int key_size,
                                    void *value, int value_size);
extern int hashtable_set (struct t_hashtable *hashtable, void *key,
                          void *value);
extern void *hashtable_get (struct t_hashtable *hashtable, const void *key);
extern int hashtable_has_key (struct t_hashtable *hashtable, const void *key);
extern void hashtable_map (struct t_hashtable *hashtable,
                           t_hashtable_map *callback_map,
                           void *callback_map_data);
extern int hashtable_get_integer (struct t_hashtable *hashtable,
                                  const char *property);
extern const char *hashtable_get_string (struct t_hashtable *hashtable,
                                         const char *property);
extern int hashtable_add_to_infolist (struct t_hashtable *hashtable,
                                      struct t_infolist_item *infolist_item,
                                      const char *prefix);
extern void hashtable_remove (struct t_hashtable *hashtable, const void *key);
extern void hashtable_remove_all (struct t_hashtable *hashtable);
extern void hashtable_free (struct t_hashtable *hashtable);
extern void hashtable_print_log (struct t_hashtable *hashtable,
                                 const char *name);

#endif /* __WEECHAT_HASHTABLE_H */