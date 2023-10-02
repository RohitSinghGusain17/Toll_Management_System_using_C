#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Vehicle {
    char owner_name[50];
    char vehicle_num[20];
    int balance;
};

void add_record();
void update_record();
void delete_record();
void search_record();
void fetch_records();

void add_record() {
    FILE *fp;
    struct Vehicle vehicle;
    printf("Enter Owner Name: ");
    scanf(" %[^\n]", vehicle.owner_name);
    printf("Enter Vehicle Number: ");
    scanf(" %s", vehicle.vehicle_num);
    printf("Enter Balance: ");
    scanf("%d", &vehicle.balance);
    fp = fopen("records.txt", "a");
    fprintf(fp, "%s %s %d\n", vehicle.owner_name, vehicle.vehicle_num, vehicle.balance);
    fclose(fp);
	printf("Record Added Successfully!\n");
}

void update_record() {
	FILE *fp, *temp;
	struct Vehicle vehicle;
	char vehicle_num[20];
	int found = 0;
	printf("Enter Vehicle Number to Update: ");
	scanf(" %s", vehicle_num);
	fp = fopen("records.txt", "r");
	temp = fopen("temp.txt", "w");
	while (fscanf(fp, "%s %s %d",vehicle.owner_name,vehicle.vehicle_num,&vehicle.balance) != EOF) {
		if (strcmp(vehicle_num, vehicle.vehicle_num) == 0) {
			found = 1;
			printf("Enter Owner Name: ");
			scanf(" %[^\n]", vehicle.owner_name);
			printf("Enter New Balance: ");
			scanf("%d", &vehicle.balance);
			fprintf(temp, "%s %s %d\n", vehicle.owner_name, vehicle.vehicle_num, vehicle.balance);
			printf("Record Updated Successfully!\n");
		}
		else {
			fprintf(temp, "%s %s %d\n", vehicle.owner_name, vehicle.vehicle_num, vehicle.balance);
		}
	}
	fclose(fp);
	fclose(temp);
	if (found == 0) {
		printf("Record Not Found!\n");
	}
	else {	
		remove("records.txt");
		rename("temp.txt", "records.txt");
	}
}

void delete_record() {
	FILE *fp, *temp;
	struct Vehicle vehicle;
	char vehicle_num[20];
	int found = 0;
	printf("Enter Vehicle Number to Delete: ");
	scanf(" %s", vehicle_num);
	fp = fopen("records.txt", "r");
	temp = fopen("temp.txt", "w");
	while (fscanf(fp, "%s %s %d",vehicle.owner_name,vehicle.vehicle_num, &vehicle.balance) != EOF) {
		if (strcmp(vehicle_num, vehicle.vehicle_num) == 0) {
			found = 1;
			printf("Record Deleted Successfully!\n");
		}
		else {
			fprintf(temp, "%s %s %d\n", vehicle.owner_name, vehicle.vehicle_num, vehicle.balance);
		}
	}
	fclose(fp);
	fclose(temp);
	if (found == 0) {
		printf("Record Not Found!\n");
	}
	else {
		remove("records.txt");
		rename("temp.txt", "records.txt");
	}
}

void search_record() {
	FILE *fp;
	struct Vehicle vehicle;
	char search_str[50];
	int found = 0;
	printf("Enter Owner Name or Vehicle Number to Search: ");
	scanf(" %[^\n]", search_str);
	fp = fopen("records.txt", "r");
	while (fscanf(fp, "%s %s %d", vehicle.owner_name, vehicle.vehicle_num, &vehicle.balance) != EOF) {
		if (strcmp(search_str, vehicle.owner_name) == 0 || strcmp(search_str, vehicle.vehicle_num) == 0) {
		printf("Owner Name: %s\nVehicle Number: %s\nBalance: %d\n",vehicle.owner_name,vehicle.vehicle_num,vehicle.balance);
		found = 1;
		}
	}
	fclose(fp);
	if (found == 0) {
		printf("Record Not Found!\n");
	}
}

void fetch_records() {
	FILE *fp;
	struct Vehicle vehicle;
	fp = fopen("records.txt", "r");
	while (fscanf(fp, "%s %s %d", vehicle.owner_name, vehicle.vehicle_num, &vehicle.balance) != EOF) {
		printf("Owner Name: %s\nVehicle Number: %s\nBalance: %d\n\n", vehicle.owner_name,vehicle.vehicle_num,vehicle.balance);
	}
	fclose(fp);
}

int main() {
	int choice;
	do {
	printf("\nToll Management System\n");
	printf("----------------------\n");
	printf("1. Add Record\n");
	printf("2. Update Record\n");
	printf("3. Delete Record\n");
	printf("4. Search Record\n");
	printf("5. Fetch All Records\n");
	printf("6. Exit\n");
	printf("Enter Your Choice: ");
	scanf("%d", &choice);
	switch (choice) {
	case 1:
		add_record();
		break;
	case 2:
		update_record();
		break;
	case 3:
		delete_record();
		break;
	case 4:
		search_record();
		break;
	case 5:
		fetch_records();
		break;
	case 6:
		printf("Exiting Program...\n");
		break;
	default:
		printf("Invalid Choice!\n");
		break;
	}
	} while (choice != 6);
	return 0;
}
