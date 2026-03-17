#ifndef BOOKING_H
#define BOOKING_H

#define MAX_SIZE 500
#define MAX_TABLE 100
#define MAX_PAX 6
#define MAX_ID_LENGTH 5
#define MAX_NAME_LENGTH 50
#define TIME_LIMIT 180
#define MAX_FILE_NAME_LENGTH 100

typedef struct booking
{
	char id[MAX_ID_LENGTH + 1]; //5 char + \0
	int table_no;
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int pax;
	char name[MAX_NAME_LENGTH + 1]; //50 char + \0
} booking;

void clear_input_buffer();
int is_valid_time(int hour, int minute);
int is_valid_date(int day, int month, int year);
booking create_booking(char id[], int table_no, int year, int month, int day, int hour, int minute, int pax, char name[]);
int add_booking(booking booking_list[], int *size, int *next_id, int table_number, int y, int mth, int d, int h, int m, int no_people, char *name);
void print_border();
void print_header();
void print_one_booking(booking b);
void print_booking(booking booking_list[], int size);
int search_by_id(booking booking_list[], int size, char *id);
int search_by_name(booking booking_list[], int size, char *name);
int search_by_table(booking booking_list[], int size, int table);
int search_by_time(booking booking_list[], int size, int h, int m);
int search_by_date(booking booking_list[], int size, int y, int mth, int d);
int search_by_pax(booking booking_list[], int size, int pax);
int update_booking(booking booking_list[], int idx, int table_number, int y, int mth, int d, int h, int m, int p, char *name);
int delete_booking(booking booking_list[], int *size, int idx);
int clear_booking(booking booking_list[], int *size, int *next_id);
void swap_booking(booking *b1, booking *b2);
void descending_sort_by_id(booking booking_list[], int size);
void ascending_sort_by_id(booking booking_list[], int size);
unsigned long time_key(int y, int mth, int d, int h, int m);
void ascending_sort_by_time(booking booking_list[], int size);
void descending_sort_by_time(booking booking_list[], int size);
void ascending_sort_by_pax(booking booking_list[], int size);
void descending_sort_by_pax(booking booking_list[], int size);
int save_line(booking booking_item, FILE *output);
int save_file(booking booking_list[], int size, char *file_name);
int count_line(FILE *input);
int is_empty_file(FILE *file);
int load_file(booking booking_list[], int *size, int *next_id, char *file_name);
void remove_invalid_booking(booking booking_list[], int *size);
void remove_id_collision(booking booking_list[], int *size);
void remove_time_collision(booking booking_list[], int *size);

#endif
