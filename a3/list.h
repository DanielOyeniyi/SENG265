/** @file listy.h
 *  @brief Function prototypes for the linked list.
 */
#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#define MAX_WORD_LEN 50

/**
 * @brief An struct that represents a node in the linked list.
 */
typedef struct node_t
{
	char *airline_name;	
	char *airline_icao_unique_code;	
	char *airline_country;	
	char *from_airport_name;	
	char *from_airport_city;	
	char *from_airport_country;
	char *from_airport_icao_unique_code;	
	char *to_airport_name;	
	char *to_airport_city;	
	char *to_airport_country;
	char *to_airport_icao_unique_code;	
	int frequency;
	struct node_t *next;
} node_t;

/**
 * Function protypes associated with a linked list.
 */
node_t *new_node();
void delete_node(node_t *);
node_t *add_front(node_t *, node_t *);
node_t *add_end(node_t *, node_t *);
node_t *add_inorder(node_t *, node_t *, char *);
node_t *copy(node_t *);
node_t *peek_front(node_t *);
node_t *remove_front(node_t *);
void apply(node_t *, void (*fn)(node_t *, void *), void *arg);

#endif
