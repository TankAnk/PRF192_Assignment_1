#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "booking.h"

void clear_input_buffer() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

int is_valid_time(int hour, int minute)
{
	if (hour == 21 && minute == 0) return 1;
	return (9 <= hour && hour <= 20 && 0 <= minute && minute <= 59);
}

int is_leap_year(int year)
{
	if (year % 100 == 0) return ((year % 400) == 0);
	return ((year % 4) == 0);
}

int is_valid_date(int day, int month, int year)
{
	if (month < 1 || month > 12) return 0;
	int days[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
	if (day == 29 && month == 2 && is_leap_year(year + 2000)) return 1;
	if (day < 1 || day > days[month - 1]) return 0;
	
	return 1;
}

/*
booking create_booking(
    char id[], int table_no,
    int year, int month, int day,
    int hour, int minute,
    int pax, char name[])
{
    booking b;

    strcpy(b.id, id);
    b.table_no = table_no;
    b.year = year;
    b.month = month;
    b.day = day;
    b.hour = hour;
    b.minute = minute;
    b.pax = pax;
    strcpy(b.name, name);

    return b;
}
*/

int add_booking(booking booking_list[], int *size, int *next_id, int table_number,
int y, int mth, int d, int h, int m, int no_people, char *name)
{		
	if (*size >= MAX_SIZE) return 0;

	sprintf(booking_list[*size].id, "%05d", *next_id);
	booking_list[*size].table_no = table_number;
	booking_list[*size].year = y;
	booking_list[*size].day = d;
	booking_list[*size].month = mth;
	booking_list[*size].hour = h;
	booking_list[*size].minute = m;
	booking_list[*size].pax = no_people;
	strcpy(booking_list[*size].name, name);
	
	(*next_id)++;
	(*size)++;
	
	return 1;
}

void print_border()
{
    printf("+--------+--------+----------+-------+------+----------------------------------------------------+\n");
}

void print_header()
{
    printf("| %-6s | %-6s | %-8s | %-5s | %-4s | %-50s |\n",
           "ID", "Table", "Date", "Time", "Pax", "Name");
}

void print_one_booking(booking b)
{
    printf("| %-6s | %-6d | %02d/%02d/%02d | %02d:%02d | %-4d | %-50s |\n",
           b.id,
           b.table_no,
           b.day, b.month, b.year,
           b.hour, b.minute,
           b.pax,
           b.name);
}

void print_booking(booking booking_list[], int size)
{
    int i;

    print_border();
    print_header();
    print_border();

    if (size == 0)
    {
        printf("| %-80s |\n", "Empty booking list!");
        print_border();
        return;
    }

    for (i = 0; i < size; i++)
        print_one_booking(booking_list[i]);

    print_border();
}

int search_by_id(booking booking_list[], int size, char *id)
{	
	int i;
	for (i = 0; i < size; i++)
		if (strcmp(booking_list[i].id, id) == 0)
			return i;

	return -1;
}

int search_by_name(booking booking_list[], int size, char *name)
{
	int i, found = 0;
	for (i = 0; i < size; i++)
	{
		if (strstr(booking_list[i].name, name) != NULL) 
		{
			found = 1;
			print_one_booking(booking_list[i]);
		}	
	}

	return found;
}

int search_by_table(booking booking_list[], int size, int table)
{	
	int i, found = 0;
	for (i = 0; i < size; i++)
	{
		if (booking_list[i].table_no == table)
		{
			found = 1;
			print_one_booking(booking_list[i]);
		}	
	}

	return found;
}

int search_by_time(booking booking_list[], int size, int h, int m)
{
	int i, found = 0;
	for (i = 0; i < size; i++)
	{
		if (booking_list[i].hour == h && booking_list[i].minute == m)
		{
			found = 1;
			print_one_booking(booking_list[i]);
		}	
	}
	
	return found;
}

int search_by_date(booking booking_list[], int size, int y, int mth, int d)
{
	int i, found = 0;
	for (i = 0; i < size; i++)
	{
		if (booking_list[i].year == y && booking_list[i].day == d && booking_list[i].month == mth )
		{
			found = 1;
			print_one_booking(booking_list[i]);
		}	
	}

	return found;
}

int search_by_pax(booking booking_list[], int size, int pax)
{	
	int i, found = 0;
	for (i = 0; i < size; i++)
	{
		if (booking_list[i].pax == pax)
		{
			found = 1;
			print_one_booking(booking_list[i]);
		}	
	}

	return found;
}

int update_booking(booking booking_list[], int idx, int table_number,
int y, int mth, int d, int h, int m, int p, char *name)
{	
	booking_list[idx].table_no = table_number;
	booking_list[idx].year = y;
	booking_list[idx].day = d;
	booking_list[idx].month = mth;
	booking_list[idx].hour = h;
	booking_list[idx].minute = m;
	booking_list[idx].pax = p;
	strcpy(booking_list[idx].name, name);
	
	return 1;
}

int delete_booking(booking booking_list[], int *size, int idx)
{
	int i;	
	for (i = idx; i < *size - 1; i++)
        booking_list[i] = booking_list[i + 1];
	memset(&booking_list[*size - 1], 0, sizeof(booking));
	(*size)--;
	
	return 1;
}

int clear_booking(booking booking_list[], int *size, int *next_id)
{
	int i;
	for (i = 0; i < *size; i++)
		memset(&booking_list[i], 0, sizeof(booking));
	(*size) = 0;
	(*next_id) = 1;
	
	return 1;
}

void swap_booking(booking *b1, booking *b2)
{
	booking tmp = *b1;
	*b1 = *b2;
	*b2 = tmp;
}

void descending_sort_by_id(booking booking_list[], int size)
{
	int i, j;
	for (i = 0; i < size - 1; i++)
		for (j = i + 1; j < size; j++)
			if (strcmp(booking_list[i].id, booking_list[j].id) < 0)
				swap_booking(&booking_list[i], &booking_list[j]);
}

void ascending_sort_by_id(booking booking_list[], int size)
{
	if (size == 0)
    {
        printf("Empty booking list!\n");
        return;
    }
	
	int i, j;
	for (i = 0; i < size - 1; i++)
		for (j = i + 1; j < size; j++)
			if (strcmp(booking_list[i].id, booking_list[j].id) > 0)
				swap_booking(&booking_list[i], &booking_list[j]);
}

unsigned long time_key(int y, int mth, int d, int h, int m)
{
	return (unsigned long)((unsigned long long)y*100000000ULL + mth*1000000ULL + d*10000ULL + h*100ULL + m);
}

void ascending_sort_by_time(booking booking_list[], int size)
{
	if (size == 0)
    {
        printf("Empty booking list!\n");
        return;
    }
	
	int i, j, min;
	unsigned long time_min, time_j;
	for (i = 0; i < size - 1; i++)
	{
		min = i;
		time_min = time_key(booking_list[min].year, booking_list[min].month, booking_list[min].day,
					booking_list[min].hour, booking_list[min].minute);
		for (j = i + 1; j < size; j++)
		{
			time_j = time_key(booking_list[j].year, booking_list[j].month, booking_list[j].day,
						booking_list[j].hour, booking_list[j].minute);
			if (time_min > time_j)
			{
				min = j;
				time_min = time_j;
			}
		}
		if (min != i) swap_booking(&booking_list[i], &booking_list[min]);
	}
}

void descending_sort_by_time(booking booking_list[], int size)
{
	if (size == 0)
    {
        printf("Empty booking list!\n");
        return;
    }
	
	int i, j, max;
	unsigned long time_max, time_j;
	for (i = 0; i < size - 1; i++)
	{
		max = i;
		time_max = time_key(booking_list[max].year, booking_list[max].month, booking_list[max].day,
					booking_list[max].hour, booking_list[max].minute);
		for (j = i + 1; j < size; j++)
		{
			time_j = time_key(booking_list[j].year, booking_list[j].month, booking_list[j].day,
						booking_list[j].hour, booking_list[j].minute);
			if (time_max < time_j)
			{
				max = j;
				time_max = time_j;
			}
		}
		if (max != i) swap_booking(&booking_list[i], &booking_list[max]);
	}
}

void ascending_sort_by_pax(booking booking_list[], int size)
{
	if (size == 0)
    {
        printf("Empty booking list!\n");
        return;
    }
	
	int i, j, min;
	for (i = 0; i < size - 1; i++)
	{
		min = i;
		for (j = i + 1; j < size; j++)
		{
			if (booking_list[min].pax > booking_list[j].pax)
			{
				min = j;
			}
		}
		if (min != i) swap_booking(&booking_list[i], &booking_list[min]);
	}
}

void descending_sort_by_pax(booking booking_list[], int size)
{
	if (size == 0)
    {
        printf("Empty booking list!\n");
        return;
    }
	
	int i, j, max;
	for (i = 0; i < size - 1; i++)
	{
		max = i;
		for (j = i + 1; j < size; j++)
		{
			if (booking_list[max].pax < booking_list[j].pax)
			{
				max = j;
			}
		}
		if (max != i) swap_booking(&booking_list[i], &booking_list[max]);
	}
}

int save_line(booking booking_item, FILE *output)
{
	if (fprintf(output, "%s ", booking_item.id) < 0) return 0;
	if (fprintf(output, "%d ", booking_item.table_no) < 0) return 0;
	if (fprintf(output, "%d ", booking_item.year) < 0) return 0;	
	if (fprintf(output, "%d ", booking_item.month) < 0) return 0;	
	if (fprintf(output, "%d ", booking_item.day) < 0) return 0;
	if (fprintf(output, "%d ", booking_item.hour) < 0)	return 0;
	if (fprintf(output, "%d ", booking_item.minute) < 0) return 0;	
	if (fprintf(output, "%d ", booking_item.pax) < 0) return 0;	
	if (fprintf(output, "%s\n", booking_item.name) < 0) return 0;
	
	return 1;
}

int save_file(booking booking_list[], int size, char *file_name)
{
	FILE *output = fopen(file_name, "w");
	if (output == NULL)
	{
		printf("Cannot open %s\n", file_name);
		return 0;
	}
	
	int i;
	for (i = 0; i < size; i++)
		if (!save_line(booking_list[i], output))
		{
			printf("Cannot write to %s!\n", file_name);
			fclose(output);
			return 0;
		}
		
	if (fclose(output) != 0)
	{
		printf("Cannot close %s\n", file_name);
		return 0;
	}
	
	printf("Successfully save to %s!\n", file_name);
	return 1;
}

int count_line(FILE *file)
{
	char c, last = '\0';
	int count = 0, not_empty = 0;
	while ((c = fgetc(file)) != EOF)
	{
		if (c == '\n' && last != '\n')
		{
			not_empty = 1;
			count++;
		}
		last = c;
	}
	
	if (last != '\n' && not_empty != 0) count++;
				
	return count;
}

// Return 1 if the file is empty
int is_empty_file(FILE *file) {
	fseek(file, 0, SEEK_END);
	int file_size = ftell(file);
	return (file_size == 0);
}

int load_file(booking booking_list[], int *size, int *next_id, char *file_name)
{
	FILE *input = fopen(file_name, "r");
	if (input == NULL)
	{
		printf("Cannot open %s\n", file_name);
		return 0;
	}
	
	if (is_empty_file(input))
	{
		printf("%s is empty!\n", file_name);
		return 0;
	}
	rewind(input);// Put the pointer back to the start of the file;
	
	int line = count_line(input);	
	if (line == 0)
	{
		printf("Empty file!\n");
		return 0;
	}
	
	if (*size + line > MAX_SIZE)
		printf("Maximum capacity reached! Loaded incomplete file!\n");
	
	rewind(input);
	int i, max_id = 0, current_id = 0;
	for (i = *size; i < *size + line && i < MAX_SIZE; i++)
	{
		if (fscanf(input, "%5s %d %d %d %d %d %d %d %50[^\n]", //Arrays decay to pointers automatically
		booking_list[i].id,
		&booking_list[i].table_no,
		&booking_list[i].year,
		&booking_list[i].month,
		&booking_list[i].day,
		&booking_list[i].hour,
		&booking_list[i].minute,
		&booking_list[i].pax,
		booking_list[i].name) != 9)
		{
			printf("Unable to read data from %s!\n", file_name);
			return 0;
		}
		
		current_id = atoi(booking_list[i].id);
		if (current_id > max_id) max_id = current_id;
	}
	
	(*next_id) = max_id + 1;
	*size += line;
	
	if (fclose(input) != 0)
	{
		printf("Cannot close %s!\n", file_name);
		return 0;
	}

	return 1;
}

void remove_invalid_booking(booking booking_list[], int *size)
{
    int i;
    for (i = 0; i < *size; i++)
    {
        if (!is_valid_time(booking_list[i].hour, booking_list[i].minute) ||
            !is_valid_date(booking_list[i].day, booking_list[i].month, booking_list[i].year) ||
            booking_list[i].year < 26 || booking_list[i].year > 99 ||
            booking_list[i].table_no <= 0 || booking_list[i].table_no > MAX_TABLE ||
            booking_list[i].pax <= 0 || booking_list[i].pax > MAX_PAX)
        {
            delete_booking(booking_list, size, i);
            i--;
        }
    }
}

void remove_id_collision(booking booking_list[], int *size)
{
    int i, j;
    for (i = 0; i < *size - 1; i++)
    {
        for (j = i + 1; j < *size; j++)
        {
            if (strcmp(booking_list[i].id, booking_list[j].id) == 0)
            {
                delete_booking(booking_list, size, j);
                j--;
            }
        }
    }
}

void remove_time_collision(booking booking_list[], int *size)
{
    int i, j;

    for (i = 0; i < *size - 1; i++)
    {
        int t1 = booking_list[i].hour * 60 + booking_list[i].minute;

        for (j = i + 1; j < *size; j++)
        {
            if (booking_list[i].year == booking_list[j].year &&
                booking_list[i].month == booking_list[j].month &&
                booking_list[i].day == booking_list[j].day &&
                booking_list[i].table_no == booking_list[j].table_no)
            {
                int t2 = booking_list[j].hour * 60 + booking_list[j].minute;
                int time_diff = (t1 > t2) ? (t1 - t2) : (t2 - t1);

                if (time_diff < TIME_LIMIT)
                {
                    delete_booking(booking_list, size, j);
                    j--;
                }
            }
        }
    }
}
