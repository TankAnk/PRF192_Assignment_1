#include <stdio.h>
#include <string.h>
#include "booking.h"

int is_full(booking booking_list[], int size, int y, int mth, int d)
{
	int i, table, count = 0, booked[MAX_TABLE] = {0};
	for (i = 0; i < size; i++)
	{
		table = booking_list[i].table_no - 1;
		if (booking_list[i].year == y && booking_list[i].month == mth && booking_list[i].day == d &&
			booked[table] == 0)
		{
			booked[table] = booking_list[i].pax;
			count++;
		}
	}
	
	return (count >= MAX_TABLE);
}

int is_available(booking booking_list[], int size, int table_number, int y, int mth, int d, int h, int m)
{
	if (size >= MAX_SIZE)
	{
		printf("Maxmimum capacity reached!\n");
		return 0;
	}
	
	int i, t1, time_diff, t2 = h * 60 + m;
	for (i = 0; i < size; i++)
	{
		t1 = (booking_list[i].hour) * 60 + (booking_list[i].minute);
		time_diff = (t1 - t2 > 0) ? t1 - t2 : t2 - t1;
		if (booking_list[i].table_no == table_number && time_diff < TIME_LIMIT &&
			booking_list[i].day == d && booking_list[i].month == mth && booking_list[i].year == y)
			return 0;
	}
	
	return 1;	
}

void print_menu()
{
	printf("=========== OKAMI AYCE BOOKING SYSTEM ===========\n");
	printf("1.  Add booking\n");
	printf("2.  Delete booking by ID\n");
	printf("3.  Update booking by ID\n");
	printf("4.  Search booking\n");
	printf("5.  Display all bookings\n");
	printf("6.  Sort bookings\n");
	printf("7.  Save bookings to text file\n");
	printf("8.  Load bookings from text file\n");
	printf("9.  Delete all bookings\n");
	printf("10. Clean bookings\n");
	printf("0.  Exit\n");
	printf("=================================================\n");
	printf("Option: ");
}

int int_input()
{
    int x;

    if (scanf("%d", &x) != 1)
    {
        clear_input_buffer();
        return -1;
    }

    clear_input_buffer();
    return x;
}

int case_1(booking booking_list[], int *size, int *next_id)
{
	int t, y, mth, d, h, m, p;//table, year, month, day, hour, minute, pax
	char name[MAX_NAME_LENGTH + 1];
	
			
	printf("Enter day: ");
	d = int_input();
	if (d < 1 || d > 31)
	{
		printf("Invalid day!\n");
		return 0;
	}
			
	printf("Enter month: ");
	mth = int_input();
	if (mth < 1 || mth > 12)
	{
		printf("Invalid month!\n");
		return 0;
	}
	
	printf("Enter year (26 - 99): ");
	y = int_input();
	if (y < 26 || y > 99)
	{
		printf("Invalid year!\n");
		return 0;
	}
	
	if (!is_valid_date(d, mth, y))
	{
		printf("Invalid booking date!\n");
		return 0;
	}
			
	
	if (is_full(booking_list, *size, y, mth, d))
	{
		printf("Fully booked on %02d/%02d/%d!\n", d, mth, y);
		return 0;
	}
			
	printf("Enter table number (1 - %d): ", MAX_TABLE);
	t = int_input();
	if (t < 1 || t > MAX_TABLE)
	{
		printf("Invalid table number!\n");
		return 0;
	}
	
	printf("Enter hour (Accepting booking from 9am - 9pm): ");
	h = int_input();
	if (h < 9 || h > 21)
	{
		printf("Invalid hour!\n");
		return 0;
	}
			
	printf("Enter minute: ");
	m = int_input();
	if (m < 0 || m > 59)
	{
		printf("Invalid minute!\n");
		return 0;
	}
	
	if (!is_valid_time(h, m))
	{
		printf("Invalid booking time!\n");
		return 0;
	}
	
	if (!is_available(booking_list, *size, t, y, mth, d, h, m))
    {
    	printf("Table %d is not available on %02d/%02d/%d at %02d:%02d!\n",
				t, d, mth, y, h, m);
    	return 0;
    }
	
	printf("Enter number of customers (1 - 6): ");
	p = int_input();
	if (p < 1 || p > 6)
	{
		printf("Invalid number of customers!\n");
		return 0;
	}
			
	printf("Enter customer's name: ");
	if (scanf("%50[^\n]", name) != 1)
	{
		printf("Invalid name!\n");
		clear_input_buffer();
		return 0;
	}
	clear_input_buffer();
	
	return add_booking(booking_list, size, next_id, t, y, mth, d, h, m ,p, name);
}

int case_2(booking booking_list[], int *size)
{
	if (*size == 0)
    {
        printf("Empty booking list!\n");
        return 0;
    }
	
	char id[MAX_ID_LENGTH + 1];
	printf("Enter ID to delete (5 digits): ");
	if (scanf("%5s", id) != 1)
	{
		printf("Invalid ID!\n");
		clear_input_buffer();
		return 0;
	}
	clear_input_buffer();
	
	int idx = search_by_id(booking_list, *size, id);
	if (idx == -1)
	{
		printf("ID booking not found!\n");
		return 0;
	}
	
	return delete_booking(booking_list, size, idx);
}

int case_3(booking booking_list[], int size)
{
	if (size == 0)
    {
        printf("Empty booking list!\n");
        return 0;
    }
	
	char id[MAX_ID_LENGTH + 1], name[MAX_NAME_LENGTH + 1];
	int t, y, mth, d, h, m, p;
	
	printf("Enter ID to update (5 digits): ");
	if (scanf("%5s", id) != 1)
	{
		printf("Invalid ID!\n");
		clear_input_buffer();
		return 0;
	}
	clear_input_buffer();
	
	int idx = search_by_id(booking_list, size, id);
	if (idx == -1)
	{
		printf("ID booking not found!\n");
		return 0;
	}
			
	printf("Enter new day: ");
	d = int_input();
	if (d < 1 || d > 31)
	{
		printf("Invalid day!\n");
		return 0;
	}
			
	printf("Enter new month: ");
	mth = int_input();
	if (mth < 1 || mth > 12)
	{
		printf("Invalid month!\n");
		return 0;
	}
	
			
	printf("Enter new year (26 - 99): ");
	y = int_input();
	if (y < 26 || y > 99)
	{
		printf("Invalid year!\n");
		return 0;
	}
	
	if (!is_valid_date(d, mth, y))
	{
		printf("Invalid booking date!\n");
		return 0;
	}
	
	if (is_full(booking_list, size, y, mth, d))
	{
		printf("Fully booked on %02d/%02d/%d!\n", d, mth, y);
		return 0;
	}
			
	printf("Enter new table number (1 - MAX_TABLE): ");
	t = int_input();
	if (t < 1 || t > MAX_TABLE)
	{
		printf("Invalid table number!\n");
		return 0;
	}
	
	printf("Enter new hour (Accepting booking from 9am - 9pm): ");
	h = int_input();
	if (h < 9 || h > 21)
	{
		printf("Invalid hour!\n");
		return 0;
	}
			
	printf("Enter new minute: ");
	m = int_input();
	if (m < 0 || m > 59)
	{
		printf("Invalid minute!\n");
		return 0;
	}
	
	if (!is_valid_time(h, m))
	{
		printf("Invalid booking time!\n");
		return 0;
	}
	
	if (!is_available(booking_list, size, t, y, mth, d, h, m))
    {
    	printf("Table %d is not available on %02d/%02d/%d at %02d:%02d!\n",
				t, d, mth, y, h, m);
    	return 0;
    }
	
	printf("Enter new number of customers (1 - 6): ");
	p = int_input();
	if (p < 1 || p > 6)
	{
		printf("Invalid number of customers!\n");
		return 0;
	}
			
	printf("Enter new customer's name: ");
	if (scanf("%50[^\n]", name) != 1)
	{
		printf("Invalid name!\n");
		clear_input_buffer();
		return 0;
	}
	clear_input_buffer();
	
	return update_booking(booking_list, idx, t, y, mth, d, h, m, p, name);
}

void print_search_menu()
{
	printf("========== SEARCH MENU ==========\n");
	printf("	1. Search by ID\n");
	printf("	2. Search by name\n");
	printf("	3. Search by table number\n");
	printf("	4. Search by booking time\n");
	printf("	5. Search by booking date\n");
	printf("	6. Search by pax\n");
	printf("	0. Exit\n");
	printf("================================\n");
	printf("	Option: ");
}

int case_4_1(booking booking_list[], int size)
{
	if (size == 0)
    {
        printf("	Empty booking list!\n");
        return -1;
    }
    
    char id[MAX_ID_LENGTH + 1];
    printf("	Enter ID to search (5 digits): ");
	if (scanf("%5s", id) != 1)
	{
		printf("	Invalid ID!\n");
		clear_input_buffer();
		return 0;
	}
	clear_input_buffer();
	
	return search_by_id(booking_list, size, id);
}

int case_4_2(booking booking_list[], int size)
{
	if (size == 0)
    {
        printf("	Empty booking list!\n");
        return 0;
    }
    
    char name[MAX_NAME_LENGTH + 1];
    printf("	Enter customer's name to search (at least 2 characters): ");
	if (scanf("%50[^\n]", name) != 1)
	{
		printf("	Invalid name!\n");
		clear_input_buffer();
		return 0;
	}
	clear_input_buffer();
	
	if (strlen(name) < 2)
	{
		printf("	Please enter at least 2 characters!\n");
		return 0;
	}
	
	return search_by_name(booking_list, size, name);
}

int case_4_3(booking booking_list[], int size)
{
	if (size == 0)
    {
        printf("	Empty booking list!\n");
        return 0;
    }
    
    printf("	Enter table number to search: ");
    int t = int_input();
    if (t < 0 || t > MAX_TABLE)
    {
    	printf("	Invalid table number!\n");
    	return 0;
    }
    
    return search_by_table(booking_list, size, t);
}

int case_4_4(booking booking_list[], int size)
{
	if (size == 0)
    {
        printf("	Empty booking list!\n");
        return 0;
    }
	
	int h, m;
			
	printf("	Enter hour: ");
	h = int_input();
	if (h < 9 || h > 21)
	{
		printf("	Invalid hour!\n");
		return 0;
	}
			
	printf("	Enter minute: ");
	m = int_input();
	if (m < 0 || m > 59)
	{
		printf("	Invalid minute!\n");
		return 0;
	}
	
	if (!is_valid_time(h, m))
	{
		printf("	Invalid booking time!\n");
		return 0;
	}
	
	return search_by_time(booking_list, size, h, m);
}

int case_4_5(booking booking_list[], int size)
{
	if (size == 0)
    {
        printf("	Empty booking list!\n");
        return 0;
    }
	
	int y, mth, d;
	printf("	Enter day: ");
	d = int_input();
	if (d < 1 || d > 31)
	{
		printf("	Invalid day!\n");
		return 0;
	}
			
	printf("	Enter month: ");
	mth = int_input();
	if (mth < 1 || mth > 12)
	{
		printf("	Invalid month!\n");
		return 0;
	}
		
	printf("	Enter year (26 - 99): ");
	y = int_input();
	if (y < 26 || y > 99)
	{
		printf("	Invalid year!\n");
		return 0;
	}
	
	if (!is_valid_date(d, mth, y))
	{
		printf("	Invalid booking date!\n");
		return 0;
	}
	
	return search_by_date(booking_list, size, y, mth, d);
}

int case_4_6(booking booking_list[], int size)
{
	if (size == 0)
    {
        printf("	Empty booking list!\n");
        return 0;
    }
    
    printf("	Enter pax to search: ");
	int p = int_input();
	if (p < 1 || p > 6)
	{
		printf("	Invalid number of customers!\n");
		return 0;
	}
	
	return search_by_pax(booking_list, size, p);
}

int case_4(booking booking_list[], int size)
{
	print_search_menu();
	int choice = int_input();
	if (choice < 0 || choice > 6)
	{
		printf("	Invalid option!\n");
		return 0;
	}
	
	switch (choice)
	{
		case 0: return 0;
		
		case 1:
		{
			int idx = case_4_1(booking_list, size);
			if (idx == -1)
			{
				printf("	Booking ID not found!\n");					
				return 0;
			}
			else
			{
				printf("	Booking ID found at index %d!\n", idx);
				return 1;
			}
		}
		
		case 2:
		{
			if (!case_4_2(booking_list, size))
			{
				printf("	Booking name not found!\n");
				return 0;
			}
			return 1;
		}
		
		case 3:
		{
			if (!case_4_3(booking_list, size))
			{
				printf("	No booking on the table yet!\n");
				return 0;
			}
			return 1;
		}
		
		case 4:
		{
			if (!case_4_4(booking_list, size))
			{
				printf("	No booking matched the time!\n");
				return 0;
			}
			return 1;
		}
		
		case 5:
		{
			if (!case_4_5(booking_list, size))
			{
				printf("	No booking matched the date!\n");
				return 0;
			}
			return 1;
		}
		
		case 6:
		{
			if (!case_4_6(booking_list, size))
			{
				printf("	No booking matched the pax!\n");
				return 0;
			}
			return 1;
		}
	}
	
	return 0;
}

void print_sort_menu()
{
	printf("========== SORT MENU ==========\n");
	printf("	1. Descending sort by ID\n");
	printf("	2. Ascending sort by ID\n");
	printf("	3. Descending sort by time\n");
	printf("	4. Ascending sort by time\n");
	printf("	5. Descending sort by pax\n");
	printf("	6. Ascending sort by pax\n");
	printf("	0. Exit\n");
	printf("===============================\n");
	printf("	Option: ");
}

int case_6(booking booking_list[], int size)
{
	print_sort_menu();
	int choice = int_input();
	if (choice < 0 || choice > 6)
	{
		printf("	Invalid option!\n");
		return 0;
	}
	
	switch (choice)
	{
		case 0: return 0;
		
		case 1:
			descending_sort_by_id(booking_list, size);
			break;		
		
		case 2:
			ascending_sort_by_id(booking_list, size);
			break;
		
		case 3:
			descending_sort_by_time(booking_list, size);
			break;
		
		case 4:
			ascending_sort_by_time(booking_list, size);
			break;
		
		case 5:
			descending_sort_by_pax(booking_list, size);
			break;
		
		case 6:
			ascending_sort_by_pax(booking_list, size);
			break;
	}
	
	return 1;
}

int case_7(booking booking_list[], int size)
{
	if (size == 0)
	{
		printf("Cannot save empty booking list!\n");
		return 0;
	}
	
	char file_name[MAX_FILE_NAME_LENGTH];
	printf("Enter file name to save to: ");
	if (scanf("%100[^\n]", file_name) != 1)
	{
		printf("Invalid file name!\n");
		clear_input_buffer();
		return 0;
	}
	clear_input_buffer();
	
	return save_file(booking_list, size, file_name);
}

int case_8(booking booking_list[], int *size, int *next_id)
{	
	char file_name[MAX_FILE_NAME_LENGTH];
	printf("Enter file name to open: ");
	if (scanf("%100[^\n]", file_name) != 1)
	{
		printf("Invalid file name!\n");
		clear_input_buffer();
		return 0;
	}
	clear_input_buffer();
	
	return load_file(booking_list, size, next_id, file_name);
}

int confirm()
{
	printf("Are you sure? Enter [Y/N] to proceed: ");
	char c;
	scanf("%c", &c);
	clear_input_buffer();
	if (c == 'Y' || c == 'y') return 1;
	return 0;
}

int case_9(booking booking_list[], int *size, int *next_id)
{
	if (*size == 0)
	{
		printf("Empty bookinglist!\n");
		return 0;
	}
	
	if (!confirm())
	{
		printf("Operation cancelled!\n");
		return 0;
	}
	
	return clear_booking(booking_list, size, next_id);
}

int case_10(booking booking_list[], int *size)
{
	if (*size == 0)
	{
		printf("Empty booking list!\n");
		return 0;
	}
	
	remove_invalid_booking(booking_list, size);
	remove_id_collision(booking_list, size);
	remove_time_collision(booking_list, size);
	
	return 1;
}

int main()
{
    int choice, size = 0, next_id = 1;
    booking booking_list[MAX_SIZE];
	load_file(booking_list, &size, &next_id, "default.txt");
	printf("Bookings automatically loaded!\n");
	
	do
	{
		print_menu();
		choice = int_input();
		if (choice < 0 || choice > 10)
		{
			printf("Invalid option!\n");
			if (size > 0) save_file(booking_list, size, "output.txt");
			return 0;
		}
		
		switch (choice)
		{
			case 0:
				if (size > 0) save_file(booking_list, size, "output.txt");
				return 0;
			
			case 1:
				if (case_1(booking_list, &size, &next_id)) 
					printf("Add booking successfully!\n");
				break;
				
			case 2:
				if (case_2(booking_list, &size))
					printf("Delete booking successfully!\n");
				break;
				
			case 3:
				if (case_3(booking_list, size))
					printf("Update booking successfully!\n");
				break;
				
			case 4:
				if (case_4(booking_list, size))
					printf("Search booking successfully!\n");
				break;
				
			case 5:
				print_booking(booking_list, size);
				break;
				
			case 6:
				if (case_6(booking_list, size))
					printf("Sort booking successfully!\n");
				break;
				
			case 7:
				if (case_7(booking_list, size))
					printf("Save to text file successfully!\n");
				break;
				
			case 8:
				if (case_8(booking_list, &size, &next_id))
					printf("Load text file successfully!\n");
				break;
				
			case 9:
				if (case_9(booking_list, &size, &next_id))
					printf("Delete all booking successfully!\n");
				break;
				
			case 10:
				if (case_10(booking_list, &size))
					printf("Clean booking successfully!\n");
				break;				
		}
		
	} while (1);
	
    return 0;
}
