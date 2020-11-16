#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>

struct Vehicle {
    char brand[100];
	int year;
	char model[100];
	char plate[8];
};

struct Vehicle vehicles[10];
int lastVehicleIndex = -1;
int close = 0;

void pressAnyKey() {
    printf("Pressione qualquer tecla para continuar...");
    getch();
}

void bubbleSort(){
    int i, contador;
    struct Vehicle aux;

    for (contador = 1; contador < 10; contador++) {
       for (i = 0; i < 10 - 1; i++) {
         if (vehicles[i].year > vehicles[i + 1].year) {
           aux = vehicles[i];
           vehicles[i] = vehicles[i + 1];
           vehicles[i + 1] = aux;
         }
       }
     }
}

void printVehicle(struct Vehicle vehicle) {
    if(vehicle.year > 0) {
        printf("%s %s (%d) %s\n", vehicle.brand, vehicle.model, vehicle.year, vehicle.plate);
    }
}

void filterByYear(bool exact) {
    int year;
    printf("\nDigite o ano: ");
    scanf("%d", &year);

	int i;
	for(i = 0; i < 10; i++){
        if((exact && vehicles[i].year == year) || (!exact && vehicles[i].year > year)) {
            printVehicle(vehicles[i]);
		}
	}

	getch();
}

void filterByModel() {
    char model[100];
    printf("\nDigite o modelo: ");
    scanf("%s", model);

	int i;
	for(i = 0; i < 10; i++){
        if(strcmp(vehicles[i].model, model) == 0) {
            printVehicle(vehicles[i]);
		}
	}

	getch();
}

void listAllVehicles() {
	int i;
	for(i = 0; i < 10; i++){
        if(vehicles[i].year > 0) {
            printVehicle(vehicles[i]);
		}
	}

	getch();
}

void printVehicleListMenu()
{
	printf("Escolha uma opção\n\n");

	printf("1 - Filtrar por ano\n");
	printf("2 - Filtrar por ano acima de\n");
	printf("3 - Filtrar por modelo\n");

	int selectedOption;
	scanf("%d", &selectedOption);

	switch (selectedOption)
	{
	case 1:
		filterByYear(true);
		break;

	case 2:
		filterByYear(false);
		break;

	case 3:
		filterByModel();
		break;
	default:
		break;
	}
}

void printAddVehicleMenu()
{
	// system("cls");

	if (lastVehicleIndex == 9) {
		printf("ATENÇÃO: O primeiro item da lista será substituído!\n\n");
	}

	lastVehicleIndex = lastVehicleIndex < 9 ? lastVehicleIndex + 1 : 0;

    printf("Adicionar veículo\n");

    printf("\nDigite a marca: ");
    scanf("%s", vehicles[lastVehicleIndex].brand);

    printf("\nDigite o modelo: ");
    scanf("%s", vehicles[lastVehicleIndex].model);

    printf("\nDigite o ano: ");
    scanf("%d", &vehicles[lastVehicleIndex].year);

    printf("\nDigite a placa: ");
    scanf("%s", vehicles[lastVehicleIndex].plate);

    printf("\n\nCarro adicionado com sucesso!\n");
    printVehicle(vehicles[lastVehicleIndex]);

	bubbleSort();

    pressAnyKey();
};

void printMainMenu()
{
	system("cls");

	printf("\nEscolha uma opção\n\n");

	printf("1 - Inserir novo veículo\n");
	printf("2 - Listar todos os veículos\n");
	printf("3 - Filtrar veículos\n");
	printf("\n4 - Sair\n");

	int selectedOption;
	scanf("%d", &selectedOption);

	switch (selectedOption)
	{
	case 1:
		printAddVehicleMenu();
		break;

	case 2:
		listAllVehicles();
		break;

	case 3:
		printVehicleListMenu();
		break;

	case 4:
		close = 1;
		break;
	default:
		break;
	}
};

int main()
{
	setlocale(LC_ALL, "Portuguese");

    int i;
	for(i = 0; i <= 10; i++){
        strcpy(vehicles[i].brand, "");
        strcpy(vehicles[i].model, "");
        strcpy(vehicles[i].plate, "");
		vehicles[i].year = 0;
	}

	/*
	//MOCK
	strcpy(vehicles[0].brand, "Marca 1");
	strcpy(vehicles[0].model, "Modelo1");
    vehicles[0].year = 2222;

	strcpy(vehicles[1].brand, "Marca 2");
	strcpy(vehicles[1].model, "Modelo2");
    vehicles[1].year = 1111;
    */

    while(close == 0) {
		printMainMenu();
	}

    return 0;
}
