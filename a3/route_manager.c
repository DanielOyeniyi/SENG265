/** @file route_manager.c
 *  @brief A small program to analyze airline routes data.
 *  @author Mike Z.
 *  @author Felipe R.
 *  @author Hausi M.
 *  @author Jose O.
 *  @author Saasha J.
 *  @author Victoria L.
 *  @author Daniel O.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "list.h"

#define OUTPUT_FILE "output.csv"
#define MAX_LINE_LEN 1024 

// function prototypes
void process_file(char *[], FILE *, FILE *);
char *strpchr(char *);
void store_column_val(node_t *, char *, int);
node_t *question1(node_t *, node_t *);
node_t *question2(node_t *, node_t *);
node_t *question3(node_t *, node_t *);
void write_file(char *[], FILE *, node_t *);
void analysis(node_t *);

/**
 * @brief reads through the lines in the file and processes the values 
 *
 * @param argv The list of arguments passed to the program.
 * @param in_file the pointer to the file that the program will read. 
 * @param out_file the pointer to the file that the program will write to. 
 *
 */
void process_file(char *argv[], FILE *in_file, FILE *out_file) {
	node_t* list = NULL;

	// argv[2] is the question the program needs to answer
	char* question;
	question = strchr(argv[2], '=');
	question++;

	char *line; 
	line = (char*)malloc(sizeof(char) * MAX_LINE_LEN);

	// getting rid of first entry
	char *state;
	state = fgets(line, MAX_LINE_LEN, in_file);
	while(state != NULL) {
		node_t* data;
		data = new_node(); 
		// there are 13 columns  
		for (int i = 0; i < 13; i++) {
			state = fgets(line, MAX_LINE_LEN, in_file);
			if (state == NULL)
				break;

			char* token;
			token = strchr(line, ':');

			// getting rid of ':' and white space
			token = token + 2; 
			char* new = strpchr(token);
			strcpy(token, new);
			free(new);
			store_column_val(data, token, i);
		}

		if(state == NULL) {
			delete_node(data);
			break;
		}
		if (!strcmp(question, "1")) {
			list = question1(data, list);

		} else if (!strcmp(question, "2")) {
			list = question2(data, list);

		} else {
			list = question3(data, list);
		}
	}

	free(line);

	// sorting the list
	node_t *head = list;	
	node_t *temp_n = NULL;	
	node_t *sorted = NULL;
	for (; head != NULL; head = temp_n) {
		temp_n = head->next;
		node_t *data = copy(head);
		sorted = add_inorder(sorted, data, question);
	}
	
	write_file(argv, out_file, sorted);

	// freeing the remaining lists 
	temp_n = NULL;
	for (; sorted != NULL; sorted = temp_n) {
		temp_n = sorted->next;
		delete_node(sorted);
	}

	temp_n = NULL;
	for (; list != NULL; list = temp_n) {
		temp_n = list->next;
		delete_node(list);
	}

}

/**
 * @brief strips the input string of any unwanted characters 
 *
 * @param str the pointer to the original string.
 * @return a pointer to the modified string. 
 *
 */
char *strpchr(char *str) {
	char *new = (char *)malloc(sizeof(char) * strlen(str));
	int i = 0;
	int j = 0;
	// tracks if we have hit the first word
	int start = 0;
	while (str[i] != '\0') {
		// making sure only alphabets, non leading spaces, and - are included
		if (isalpha(str[i]) || (start == 1 && (str[i] == ' ' || str[i] == '-'))) {
			new[j] = str[i];
			start = 1;
			j++;
		}
		i++;
	}
	new[j] = '\0';
	return new;
}



/**
 * @brief takes a string and stores it in the relative field in the data node 
 *
 * @param data the node that will store the token data.
 * @param token points to the string to store in the data node. 
 * @param column represents the column that we are storing.
 *
 */
void store_column_val(node_t *data, char *token, int column) {
	// altitude is not used so we do not store it
	switch(column) {
		case 0:
			strcpy(data->airline_name, token);	
			break;
		case 1:
			strcpy(data->airline_icao_unique_code, token);	
			break;
		case 2:
			strcpy(data->airline_country, token);	
			break;
		case 3:
			strcpy(data->from_airport_name, token);	
			break;
		case 4:
			strcpy(data->from_airport_city, token);	
			break;
		case 5:
			strcpy(data->from_airport_country, token);	
			break;
		case 6:
			strcpy(data->from_airport_icao_unique_code, token);	
			break;
		case 8:
			strcpy(data->to_airport_name, token);	
			break;
		case 9:
			strcpy(data->to_airport_city, token);	
			break;
		case 10:
			strcpy(data->to_airport_country, token);	
			break;
		case 11:
			strcpy(data->to_airport_icao_unique_code, token);	
			break;
	}
}

/**
 * @brief adds the data node to the front of the list if it 
 * satisfies the conditions for question 1
 *
 * @param data the node that will store the token data.
 * @param list the head of the list that data will join. 
 * @return the new head of the list  
 *
 */
node_t *question1(node_t *data, node_t *list) {
	node_t *head = list;
	node_t *temp_n = NULL;
	if (!strcmp(data->to_airport_country, "Canada")) {
		head = list;
		temp_n = NULL;	
		int in = 0;
		for (; head != NULL; head = temp_n) {
			temp_n = head->next;
			if (!strcmp(data->airline_name,head->airline_name)) {
				in = 1;
				head->frequency++;
				delete_node(data);
			}
		}
		if (!in) {
			data->frequency = 1;
			list = add_front(list,data);
		}
	} else {
		delete_node(data);
	}
	return list;
}

/**
 * @brief adds the data node to the front of the list if it 
 * satisfies the conditions for question 2 
 *
 * @param data the node that will store the token data.
 * @param list the head of the list that data will join. 
 * @return the new head of the list  
 *
 */
node_t *question2(node_t *data, node_t *list) {
	node_t *head = list;
	node_t *temp_n = NULL;
	head = list;
	temp_n = NULL;	
	int in = 0;
	for (; head != NULL; head = temp_n) {
		temp_n = head->next;
		if (!strcmp(data->to_airport_country,head->to_airport_country)) {
			in = 1;
			head->frequency--;
			delete_node(data);
		}
	}
	if (!in) {
		data->frequency = -1;
		list = add_front(list,data);
	}
	return list;
}

/**
 * @brief adds the data node to the front of the list if it 
 * satisfies the conditions for question 3 
 *
 * @param data the node that will store the token data.
 * @param list the head of the list that data will join. 
 * @return the new head of the list  
 *
 */
node_t *question3(node_t *data, node_t *list) {
	node_t *head = list;
	node_t *temp_n = NULL;
	head = list;
	temp_n = NULL;	
	int in = 0;
	for (; head != NULL; head = temp_n) {
		temp_n = head->next;
		if (!strcmp(data->to_airport_name,head->to_airport_name)) {
			in = 1;
			head->frequency++;
			delete_node(data);
		}
	}
	if (!in) {
		data->frequency = 1;
		list = add_front(list,data);
	}
	return list;
}

/**
 * @brief extracts data from the sorted list and write it to the output file.
 *
 * @param argv The list of arguments passed to the program.
 * @param out_file the pointer to the file that the program will write to. 
 * @param sorted the sorted list to extract data from.
 *
 */
void write_file(char *argv[], FILE *out_file, node_t *sorted) {
	char* question;
	question = strchr(argv[2], '=');
	question++;
	
	char* N;
	N = strchr(argv[3], '=');
	N++;
	int n = atoi(N);

	node_t *temp_n = NULL;
	fprintf(out_file, "subject,statistic\n");
	for (int i = 0; sorted != NULL && i < n; sorted = temp_n) {
		temp_n = sorted->next;
		if (!strcmp(question, "1")) {
			fprintf(out_file, "%s (%s),%d\n", sorted->airline_name, 
							  sorted->airline_icao_unique_code, 
							  sorted->frequency);

		} else if (!strcmp(question, "2")) {
			fprintf(out_file, "%s,%d\n", sorted->to_airport_country, 
						     sorted->frequency * -1);

		} else {
			fprintf(out_file, "\"%s (%s), %s, %s\",%d\n", sorted->to_airport_name, 
								      sorted->to_airport_icao_unique_code,
				                                      sorted->to_airport_city, 
								      sorted->to_airport_country, sorted->frequency);

		}
		i++;
	}
}	

/**
 * @brief Serves as an incremental counter for navigating the list.
 *
 * @param p The pointer of the node to print.
 * @param arg The pointer of the index.
 *
 */
void inccounter(node_t *p, void *arg)
{
    int *ip = (int *)arg;
    (*ip)++;
}

/**
 * @brief Allows to print out the content of a node.
 *
 * @param p The pointer of the node to print.
 * @param arg The format of the string.
 *
 */
void print_node(node_t *p, void *arg)
{
    char *fmt = (char *)arg;
    printf(fmt, p->to_airport_country, p->frequency);
}

/**
 * @brief Allows to print each node in the list.
 *
 * @param l The first node in the list
 *
 */
void analysis(node_t *l)
{
    int len = 0;

    apply(l, inccounter, &len);
    printf("Number of words: %d\n", len);

    apply(l, print_node, "%s:%d\n");
}

/**
 * @brief The main function and entry point of the program.
 *
 * @param argc The number of arguments passed to the program.
 * @param argv The list of arguments passed to the program.
 * @return int 0: No errors; 1: Errors produced.
 *
 */
int main(int argc, char *argv[])
{
	FILE *in_file;
	FILE *out_file;

	out_file = fopen(OUTPUT_FILE, "w");

	// argv[1] is the data file that we are extracting from 
	char* token;
	token = strchr(argv[1], '=');
	token++;
	in_file = fopen(token, "r");

	process_file(argv, in_file, out_file);
	
	fclose(in_file);
	fclose(out_file);

    exit(0);
}
