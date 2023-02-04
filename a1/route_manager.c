/** @file route_manager.c
 *  @brief A pipes & filters program that uses conditionals, loops, and string processing tools in C to process airline routes.
 *  @author Felipe R.
 *  @author Hausi M.
 *  @author Jose O.
 *  @author Saasha J.
 *  @author Victoria L.
 *  @author Daniel O. 
 *
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct input {
	int input_case;
	char data[100];
	char airline[100];
	char src_city[100];
	char src_country[100];
	char dest_city[100];
	char dest_country[100];
};

struct line_data {
	char airline_name[100];
	char airline_icao_unique_code[100];
	char airline_country[100];
	char from_airport_name[100];
	char from_airport_city[100];
	char from_airport_country[100];
	char from_airport_icao_unique_code[100];
	char to_airport_name[100];
	char to_airport_city[100];
	char to_airport_country[100];
	char to_airport_icao_unique_code[100];
};

// function prototypes
struct input extract_args(int argc, char *argv[], struct input cmd_args); 
struct input extract_args_helper(char entry[], char val[], struct input cmd_args); 
void proccess_file(struct input cmd_args); 
struct line_data extract_line_data(char line[], struct line_data curr_line); 
struct line_data splice_copy(char line[], struct line_data curr_line, int start_index, int end_index, int column);
struct line_data splice_copy_helper(struct line_data curr_line, int char_index, int column, char val);
void write_file(FILE *ofp, struct input cmd_args, struct line_data curr_line);

/**
 * Function: extract_args
 * ----------------------
 * @brief extracts the values of the arguments passed in command line.
 *
 * @param argc The number of arguments passkiike
 * @param argv The list of arguments passed to the program.
 * @param cmd_args A struct that stores the respective values of the command line arguments. 
 * @return struct Input return a struct containing the updated command line arguments.
 *
 */
struct input extract_args(int argc, char *argv[], struct input cmd_args) {
	char entry[100];
	char val[100];
	for (int i = 1; i < argc; i++) {
		sscanf(argv[i], "--%[^=]=%[^=]", entry, val);		//spliting the argument string to obtain its value.
		cmd_args = extract_args_helper(entry, val, cmd_args);
	}
	
	return cmd_args;
}

/**
 * Function: extract_args_helper
 * -----------------------------
 * @brief Identifies the entry and copies it to the respective value in the passed struct.
 *
 * @param entry A string the specifies the value type.
 * @param val A string containing the value of the respective entry.
 * @return struct Input return a struct containing the updated command line arguments.
 *
 */
struct input extract_args_helper(char entry[], char val[], struct input cmd_args) {
	if (!strcmp(entry, "DATA")) {
		strcpy(cmd_args.data, val);
	}

	if (!strcmp(entry, "AIRLINE")) {
		strcpy(cmd_args.airline, val);
	}

	if (!strcmp(entry, "SRC_CITY")) {
		strcpy(cmd_args.src_city, val);
	}

	if (!strcmp(entry, "SRC_COUNTRY")) {
		strcpy(cmd_args.src_country, val);
	}

	if (!strcmp(entry, "DEST_CITY")) {
		strcpy(cmd_args.dest_city, val);
	}

	if (!strcmp(entry, "DEST_COUNTRY")) {
		strcpy(cmd_args.dest_country, val);
	}

	return cmd_args;
}	

/**
 * Function: process_file
 * ----------------------
 * @brief Reads each line in the file, processes them, then writes the processed data to the output file. 
 *
 * @param cmd_args A struct that stores the respective values of the command line arguments. 
 * @return void nothing. 
 *
 */
void process_file(struct input cmd_args) {
	FILE *ofp;
	FILE *ifp;
	int line_size = 1024;					//line buffer size recommended by instructor
	char line[line_size];
	struct line_data curr_line;
	
	ofp = fopen("output.txt", "w");
	ifp = fopen(cmd_args.data, "r");
	if(ifp != NULL) {
		while(fgets(line, line_size, ifp) != NULL) {
			curr_line = extract_line_data(line, curr_line);
			write_file(ofp, cmd_args, curr_line);
		}
	}	
	if(ftell(ofp) == 0) {
		fprintf(ofp,"NO RESULTS FOUND.\n");
	}
	fclose(ofp);
	fclose(ifp);
}

/**
 * Function: extract_line_data
 * ---------------------------
 * @brief Takes the input line(string) and stores the extracted values(columns) in the passed struct. 
 *
 * @param line The line(string) that we want to process, each line has 13 columns
 * @param curr_line A struct that contains the extracted column values from a line.  
 * @return struct line_data A struct containng the updated column values.  
 *
 */
struct line_data extract_line_data(char line[], struct line_data curr_line) {
	int column = 0;
	int start_index = 0;										//Attempting to replicate pythons array splicing
	int end_index = 0;

	for (int i = 0; i <= strlen(line); i++) {
		if (line[i] != ',' && line[i] != '\0' && line[i] != '\n') {				//columns are seperated by ',' 
			end_index++;
		} else {
			curr_line = splice_copy(line, curr_line, start_index, end_index, column);
			end_index++;
			start_index = end_index;
			column++;
		}
	}

	return curr_line;	
}

/**
 * Function: splice_copy
 * ---------------------
 * @brief Copys a section of the given string into the respective values in the passed struct.
 *
 * @param line The line(string) that we want to process, each line has 13 columns
 * @param curr_line A struct that contains the extracted column values from a line.  
 * @param start_index An int containing the start of the section that is going to be copied.
 * @param end_index An int containing the end of the section that is going to be copied.
 * @param column An int representing the current column of the data that is being copied.
 * @return struct line_data A struct containng the updated column values.  
 *
 */
struct line_data splice_copy(char line[], struct line_data curr_line, int start_index, int end_index, int column) {
	int char_index = 0;
	while(start_index < end_index) {
		if (line[start_index] != ',') { 
			curr_line = splice_copy_helper(curr_line, char_index, column, line[start_index]);
			char_index++;
		}
		start_index++;
	}
	curr_line = splice_copy_helper(curr_line, char_index, column, '\0');
	return curr_line;
}	

/**
 * Function: splice_copy_helper 
 * ----------------------------
 * @brief Copies the character at the specfied index to the respective index and value in the passed struct.
 *
 * @param curr_line A struct that contains the extracted column values from a line.  
 * @param char_index An int reprenting the index of the character to be copied.
 * @param column An int representing the current column of the data that is being copied.
 * @param val The character that we want to copy.
 * @return struct line_data A struct containng the updated column values.  
 *
 */
struct line_data splice_copy_helper(struct line_data curr_line, int char_index, int column, char val) {
	switch(column) {
		case 0:
			curr_line.airline_name[char_index] = val;	
			break;
		case 1:
			curr_line.airline_icao_unique_code[char_index] = val;	
			break;
		case 2:
			curr_line.airline_country[char_index] = val; 
			break;
		case 3:
			curr_line.from_airport_name[char_index] = val; 
			break;
		case 4:
			curr_line.from_airport_city[char_index] = val; 
			break;
		case 5:
			curr_line.from_airport_country[char_index] = val; 
			break;
		case 6:
			curr_line.from_airport_icao_unique_code[char_index] = val; 
			break;								//columns 7, 12 are excluded because altitude is never used
		case 8:
			curr_line.to_airport_name[char_index] = val; 
			break;
		case 9:
			curr_line.to_airport_city[char_index] = val; 
			break;
		case 10:
			curr_line.to_airport_country[char_index] = val; 
			break;
		case 11:
			curr_line.to_airport_icao_unique_code[char_index] = val; 
			break;
	}
	
	return curr_line;
}

/**
 * Function: write_file 
 * --------------------
 * @brief checks if the current line matches the desired data, formats it, then stores the data in an output file. 
 *
 * @param *ofp The output file that we write to. 
 * @param cmd_args A struct that stores the respective values of the command line arguments. 
 * @param curr_line A struct that contains the extracted column values from a line.  
 * @return void nothing. 
 *
 */
void write_file(FILE *ofp, struct input cmd_args, struct line_data curr_line) {
	switch(cmd_args.input_case) {
		case 1:
			if(!strcmp(cmd_args.airline, curr_line.airline_icao_unique_code)  && 
			   !strcmp(cmd_args.dest_country, curr_line.to_airport_country)) {
				if(ftell(ofp) == 0) {
					fprintf(ofp, "FLIGHTS TO %s BY %s (%s):\n", cmd_args.dest_country,
										    curr_line.airline_name,
										    cmd_args.airline);
				}

				fprintf(ofp, "FROM: %s, %s, %s TO: %s (%s), %s\n", curr_line.from_airport_icao_unique_code,
										   curr_line.from_airport_city, 
										   curr_line.from_airport_country,
										   curr_line.to_airport_name,
										   curr_line.to_airport_icao_unique_code,
										   curr_line.to_airport_city);
			} 
			
			break;
		case 2:
			if(!strcmp(cmd_args.src_country, curr_line.from_airport_country)  && 
			   !strcmp(cmd_args.dest_city, curr_line.to_airport_city)  && 
			   !strcmp(cmd_args.dest_country, curr_line.to_airport_country)) {
				if(ftell(ofp) == 0) {
					fprintf(ofp, "FLIGHTS FROM %s TO %s, %s:\n", cmd_args.src_country,
										    cmd_args.dest_city,
										    cmd_args.dest_country);
				} 

				fprintf(ofp, "AIRLINE: %s (%s) ORIGIN: %s (%s), %s\n", curr_line.airline_name,
										       curr_line.airline_icao_unique_code, 
										       curr_line.from_airport_name,
										       curr_line.from_airport_icao_unique_code,
										       curr_line.from_airport_city);
			} 

			break;
		case 3: 
			if(!strcmp(cmd_args.src_city, curr_line.from_airport_city)  && 
			   !strcmp(cmd_args.src_country, curr_line.from_airport_country)  && 
			   !strcmp(cmd_args.dest_city, curr_line.to_airport_city)  && 
			   !strcmp(cmd_args.dest_country, curr_line.to_airport_country)) {
				if(ftell(ofp) == 0) {
					fprintf(ofp, "FLIGHTS FROM %s, %s TO %s, %s:\n", cmd_args.src_city,
										         cmd_args.src_country,
										         cmd_args.dest_city,
										         cmd_args.dest_country);
				}

				fprintf(ofp, "AIRLINE: %s (%s) ROUTE: %s-%s\n", curr_line.airline_name,
										curr_line.airline_icao_unique_code, 
										curr_line.from_airport_icao_unique_code,
										curr_line.to_airport_icao_unique_code);
			}
				
			break;
	}
}

/**
 * Function: main
 * --------------
 * @brief The main function and entry point of the program.
 *
 * @param argc The number of arguments passed to the program.
 * @param argv The list of arguments passed to the program.
 * @return int 0: No errors; 1: Errors produced.
 *
 */
int main(int argc, char *argv[])
{
	struct input cmd_args;
	
	cmd_args = extract_args(argc, argv, cmd_args);
		
	switch(argc) {						// cases are determined by the number of arguments entered
		case 4:
			cmd_args.input_case = 1;
			break;
		case 5:
			cmd_args.input_case = 2;
			break;
		case 6:
			cmd_args.input_case = 3;
			break;
	}
	process_file(cmd_args);
    exit(0);
}
