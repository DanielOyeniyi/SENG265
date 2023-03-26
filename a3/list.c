/** @file list.c
 *  @brief Implementation of a linked list.
 *
 * Based on the implementation approach described in "The Practice
 * of Programming" by Kernighan and Pike (Addison-Wesley, 1999).
 *
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "emalloc.h"
#include "list.h"

#define STR_BUFF 100

/**
 * Function:  new_node
 * -------------------
 * @brief  Allows to dynamically allocate memory for a new node to be added to the linked list.
 *
 * This function should confirm that the argument being passed is not NULL (i.e., using the assert library). Then,
 * It dynamically allocates memory for the new node using emalloc(), and assign values to attributes associated with the node (i.e., val and next).
 *
 *
 * @return node_t* A pointer to the node created.
 *
 */
node_t *new_node()
{
	node_t *temp = (node_t *)emalloc(sizeof(node_t));

	temp->airline_name = (char *)emalloc(sizeof(char) * STR_BUFF);	
	temp->airline_icao_unique_code = (char *)emalloc(sizeof(char) * STR_BUFF);	
	temp->airline_country = (char *)emalloc(sizeof(char) * STR_BUFF);	
	temp->from_airport_name = (char *)emalloc(sizeof(char) * STR_BUFF);	
	temp->from_airport_city = (char *)emalloc(sizeof(char) * STR_BUFF);	
	temp->from_airport_country = (char *)emalloc(sizeof(char) * STR_BUFF);	
	temp->from_airport_icao_unique_code = (char *)emalloc(sizeof(char) * STR_BUFF);	
	temp->to_airport_name = (char *)emalloc(sizeof(char) * STR_BUFF);	
	temp->to_airport_city = (char *)emalloc(sizeof(char) * STR_BUFF);	
	temp->to_airport_country = (char *)emalloc(sizeof(char) * STR_BUFF);	
	temp->to_airport_icao_unique_code = (char *)emalloc(sizeof(char) * STR_BUFF);	
	temp->frequency = 0;

	temp->next = NULL;

    return temp;
}

/**
 * Function: delete_node 
 * --------------------
 * @brief  frees the memory allocated to the node and deletes the node.
 *
 * @param temp the node to be deleted. 
 *
 * @return node_t* A pointer to the new head of the list.
 *
 */
void delete_node(node_t *temp) {
	free(temp->airline_name);
	free(temp->airline_icao_unique_code);	
	free(temp->airline_country);	
	free(temp->from_airport_name);	
	free(temp->from_airport_city);	
	free(temp->from_airport_country);	
	free(temp->from_airport_icao_unique_code);	
	free(temp->to_airport_name);	
	free(temp->to_airport_city);	
	free(temp->to_airport_country);	
	free(temp->to_airport_icao_unique_code);	
	free(temp);
}

/**
 * Function:  add_front
 * --------------------
 * @brief  Allows to add a node at the front of the list.
 *
 * @param list The list where the node will be added (i.e., a pointer to the first element in the list).
 * @param new The node to be added to the list.
 *
 * @return node_t* A pointer to the new head of the list.
 *
 */
node_t *add_front(node_t *list, node_t *new)
{
    new->next = list;
    return new;
}

/**
 * Function:  add_end
 * ------------------
 * @brief  Allows to add a node at the end of the list.
 *
 * @param list The list where the node will be added (i.e., a pointer to the first element in the list).
 * @param new The node to be added to the list.
 *
 * @return node_t* A pointer to the head of the list.
 *
 */
node_t *add_end(node_t *list, node_t *new)
{
    node_t *curr;

    if (list == NULL)
    {
        new->next = NULL;
        return new;
    }

    for (curr = list; curr->next != NULL; curr = curr->next)
        ;
    curr->next = new;
    new->next = NULL;
    return list;
}

/**
 * Function:  add_inorder
 * ----------------------
 * @brief  Allows to add a new node to the list respecting an order.
 *
 * @param list The list where the node will be added (i.e., a pointer to the first element in the list).
 * @param new The node to be added to the list.
 * @param question indicates what values should be compared. 
 *
 * @return node_t* A pointer to the node created.
 *
 */
node_t *add_inorder(node_t *list, node_t *new, char *question)
{
    node_t *prev = NULL;
    node_t *curr = NULL;

    if (new == NULL) {
	return list;
    }

    if (list == NULL)
    {
        return new;
    }

    for (curr = list; curr != NULL; curr = curr->next)
    {
	if (new->frequency < curr->frequency) {
		prev = curr;

	} else if (new->frequency == curr->frequency) {
		if ((!strcmp(question, "1") && strcmp(new->airline_name, curr->airline_name) > 0) ||
		    (!strcmp(question, "2") && strcmp(new->to_airport_country, curr->to_airport_country) > 0) ||
		    (!strcmp(question, "3") && strcmp(new->to_airport_name, curr->to_airport_name) > 0))
		{
		    prev = curr;

		} else {
			break;
		}
	}
        else
        {
            break;
        }
    }

    new->next = curr;

    if (prev == NULL)
    {
        return (new);
    }
    else
    {
        prev->next = new;
        return list;
    }
}

/**
 * Function: copy 
 * ----------------------
 * @brief  creates a duplicate of the inputed node.
 *
 * @param src The node to be duplicated.
 *
 * @return node_t* A pointer to the node created.
 *
 */
node_t *copy(node_t *src) {
	node_t *new = new_node();

	strcpy(new->airline_name, src->airline_name);
	strcpy(new->airline_icao_unique_code, src->airline_icao_unique_code);	
	strcpy(new->airline_country, src->airline_country);	
	strcpy(new->from_airport_name, src->from_airport_name);	
	strcpy(new->from_airport_city, src->from_airport_city);	
	strcpy(new->from_airport_country, src->from_airport_country);	
	strcpy(new->from_airport_icao_unique_code, src->from_airport_icao_unique_code);
	strcpy(new->to_airport_name, src->to_airport_name);	
	strcpy(new->to_airport_city, src->to_airport_city);	
	strcpy(new->to_airport_country, src->to_airport_country);	
	strcpy(new->to_airport_icao_unique_code, src->to_airport_icao_unique_code);	
	new->frequency = src->frequency;
	
	new->next = NULL;
	return new;
}

/**
 * Function:  peek_front
 * ---------------------
 * @brief  Allows to get the head node of the list.
 *
 * @param list The list to get the node from.
 *
 * @return node_t* A pointer to the head of the list.
 *
 */
node_t *peek_front(node_t *list)
{
    return list;
}

/**
 * Function:  remove_front
 * -----------------------
 * @brief  Allows removing the head node of the list.
 *
 * @param list The list to remove the node from.
 *
 * @return node_t* A pointer to the head of the list.
 *
 */
node_t *remove_front(node_t *list)
{
    if (list == NULL)
    {
	    delete_node(list);
        return NULL;
    }
	node_t *temp = list->next;
	delete_node(list);
    return temp;
}

/**
 * Function: apply
 * --------------
 * @brief  Allows to apply a function to the list.
 *
 * @param list The list (i.e., pointer to head node) where the function will be applied.
 * @param fn The pointer of the function to be applied.
 * @param arg The arguments to be applied.
 *
 */
void apply(node_t *list,
           void (*fn)(node_t *list, void *),
           void *arg)
{
    for (; list != NULL; list = list->next)
    {
        (*fn)(list, arg);
    }
}
