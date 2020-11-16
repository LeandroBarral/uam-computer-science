#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>

#define BLOCK_SIZE 10

typedef struct {
    char name[30];
    int yearOfBirth;
    float amountPaid;
} Customer;

void customerRegisterFlow();
void amountPaidByCustomerName();
void printCustomer(Customer *customer);
void updateCustomerAmount();
void endMonth();
void bestBuyer();
void initializeCustomers();
void reallocCustomers();
void bubbleSort();
void pressAnyKeyToContinue();
void listAll();

Customer * pCustomers;
int *pCustomersSize;

int main()
{
	setlocale(LC_ALL, "Portuguese");

	initializeCustomers();

    int customerSize = -1;
    pCustomersSize = &customerSize;

    int menuOption = 99;
    while(menuOption > 0) {
        system("cls");
        printf("Menu\n\n");
        printf("1 - Cadastrar cliente\n");
        printf("2 - Gastos totais por cliente\n");
        printf("3 - Melhor comprador\n");
        printf("4 - Remover cliente\n");
        printf("5 - Atualizar gastos do cliente\n");
        printf("6 - Virada de mês\n");
        printf("\n0 - Sair\n\n");

        printf("Escolha uma opção: ");
        scanf("%i", &menuOption);

        system("cls");
        switch(menuOption) {
            case 1:
                customerRegisterFlow();
                break;
            case 2:
                amountPaidByCustomerName();
                break;
            case 3:
                bestBuyer();
                break;
            case 4:
                removeCustomerByName();
                break;
            case 5:
                updateCustomerAmount();
                break;
            case 6:
                endMonth();
                break;
            case 99:
                listAll();
                break;
        }
    }

	free(pCustomers);
	pCustomers = NULL;

    return 0;
}

void customerRegisterFlow() {
    printf("Cadastro de cliente\n\n");

    *pCustomersSize = *pCustomersSize + 1;

    Customer *customer = &pCustomers[*pCustomersSize];
    strcpy(customer->name, "");
    customer->yearOfBirth = 0;
    customer->amountPaid = -1;

    while(strlen(customer->name) < 2) {
        printf("Digite o nome: ");
        scanf(" %[^\n]s", &customer->name);

        if(strlen(customer->name) < 2) {
            printf("Entrada inválida!\n");
        }
    }

    while(customer->yearOfBirth < 1){
        printf("\nEm que ano '%s' nasceu? ", customer->name);
        scanf("%i", &customer->yearOfBirth);

        if(customer->yearOfBirth < 1) {
            printf("Entrada inválida!\n");
        }
    }

    while(customer->amountPaid < 0) {
        printf("\nLegal! E quanto '%s' (nascido em %i) gastou esse mês? (Para decimais use ,) ", customer->name, customer->yearOfBirth);
        scanf("%f", &customer->amountPaid);

        if(customer->amountPaid < 0) {
            printf("Entrada inválida!\n");
        }
    }

    printf("\n\nCadastro realizado com sucesso!\n'%s' (nascido em %i) gastou R$ %.2f esse mês!", customer->name, customer->yearOfBirth, customer->amountPaid);

    if(*pCustomersSize % BLOCK_SIZE == 0) {
        reallocCustomers();
    }

    bubbleSort();

    pressAnyKeyToContinue();
}

void amountPaidByCustomerName() {
    printf("Gastos totais por cliente\n\n");
    char name[30] = "";
    while(strlen(name) < 2) {
        printf("Digite o nome: ");
        scanf(" %[^\n]s", &name);

        if(strlen(name) < 2) {
            printf("Entrada inválida!\n");
        }
    }

    int i;
    for (i = 0; i <= *pCustomersSize; i++) {
        Customer *customer = &pCustomers[i];

        if(strcmp(customer->name, name) == 0) {
            printCustomer(customer);
        }
    }

    pressAnyKeyToContinue();
}

void updateCustomerAmount() {
    printf("Atualizar gastos totais por cliente\n\n");
    char name[30] = "";
    while(strlen(name) < 2) {
        printf("Digite o nome: ");
        scanf(" %[^\n]s", &name);

        if(strlen(name) < 2) {
            printf("Entrada inválida!\n");
        }
    }

    int i;
    for (i = 0; i <= *pCustomersSize; i++) {
        Customer *customer = &pCustomers[i];

        if(strcmp(customer->name, name) == 0) {
            printCustomer(customer);

            while(customer->amountPaid < 0) {
                printf("\nQual o novo valor gasto? (Para decimais use ,) ");
                scanf("%f", &customer->amountPaid);

                if(customer->amountPaid < 0) {
                    printf("Entrada inválida!\n");
                }
            }
        }
    }

    pressAnyKeyToContinue();
}

void removeCustomerByName() {
    printf("Remoção de cliente por nome\n\n");
    char name[30] = "";
    while(strlen(name) < 2) {
        printf("Digite o nome: ");
        scanf(" %[^\n]s", &name);

        if(strlen(name) < 2) {
            printf("Entrada inválida!\n");
        }
    }

    int i, removed = 0;
    for (i = 0; i <= *pCustomersSize; i++) {
        Customer *customer = &pCustomers[i];

        if(strcmp(customer->name, name) == 0) {
            strcpy(customer->name, "");
            customer->yearOfBirth = 0;
            customer->amountPaid = -1;

            ++removed;
        }
    }

    bubbleSort();

    *pCustomersSize = *pCustomersSize - removed;

    listAll();

    pressAnyKeyToContinue();
}

void bestBuyer() {
    Customer *customer = &pCustomers[0];
    printf("Melhor comprador\n\n");
    printCustomer(customer);

    pressAnyKeyToContinue();
}

void endMonth() {
    printf("Virada de mês\n\n");

    int i;
    for (i = 0; i <= *pCustomersSize; i++) {
        Customer *customer = &pCustomers[i];
        customer->amountPaid = 0;
    }

    pressAnyKeyToContinue();
}

void listAll() {
    printf("Lista de clientes\n\n");

    int i;
    for (i = 0; i <= *pCustomersSize; i++) {
        Customer *customer = &pCustomers[i];

        printCustomer(customer);
    }

    pressAnyKeyToContinue();
}

void printCustomer(Customer * customer) {
    printf("'%s' (nascido em %i), gastou R$ %.2f esse mês!\n", customer->name, customer->yearOfBirth, customer->amountPaid);
}

void pressAnyKeyToContinue() {
    printf("\n\nPressione qualquer tecla para continuar...");
    getch();
}

void initializeCustomers() {
    pCustomers = (Customer *) malloc(BLOCK_SIZE * sizeof(Customer));

    if (pCustomers == NULL)
    {
        printf("Memória insuficiente! Não é possivel continuar.");
        printf("\n\nPressione qualquer tecla para finalizar...");
        getch();
        exit(1);
    }
}

void reallocCustomers() {
    pCustomers = (Customer *) realloc(pCustomers, BLOCK_SIZE * sizeof(Customer));

    if (pCustomers == NULL)
    {
        printf("Memória insuficiente! Não é possivel continuar.");
        printf("\n\nPressione qualquer tecla para finalizar...");
        getch();
        exit(1);
    }
}

void bubbleSort(){
    int i, contador;
    Customer aux;

    for (contador = -1; contador < *pCustomersSize; contador++) {
       for (i = 0; i <= *pCustomersSize - 1; i++) {
            Customer *customer = &pCustomers[i];
            Customer *customer2 = &pCustomers[i + 1];
            if (customer->amountPaid < customer2->amountPaid) {
                aux = *customer2;
                *customer2 = *customer;
                *customer = aux;
            }
        }
    }
}
