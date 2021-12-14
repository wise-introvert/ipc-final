#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX_PRODUCT_NAME_LEN 25
#define MAX_PRODUCT_SIZE 25
//Declaration of struct SingleSaleRecord, which holds the information of one transaction
// the data part of it is taken as per the data specified in the text file.
struct SingleSaleRecord {
  int numberSold;
  double salePrice;
  struct Date {
    int month, day, year;
  }
  saleDate;
};

// Declaration of struct ProductSalesList
// data part is taken as per the data given in already provided function  and sample output
struct ProductSalesList {
  char productName[MAX_PRODUCT_NAME_LEN];
  struct SingleSaleRecord saleRec;
};

// Declaration of struct DailySalesList
// data part is taken as per the data given in already provided function and sample output

struct DailySalesList {
  struct Date saleDate;
  double revenue;
};

void addSale(struct ProductSalesList * pList, struct DailySalesList * dSales, char * pName, struct SingleSaleRecord * sRec) {
  int x;
  for (x = 0; pList[x].productName[0] != '\0'; x++) // finding count of elements in the list
  ;

  strcpy(pList[x].productName, pName); // assigning new product name info to xth index of list
  pList[x].saleRec = * sRec; // assigning sale record information at xth index of the list

  for (x = 0; dSales[x].revenue != 0.0; x++) // Adding revenue to daily das;e record
  {
    if (dSales[x].saleDate.day == sRec -> saleDate.day &&
      dSales[x].saleDate.month == sRec -> saleDate.month &&
      dSales[x].saleDate.year == sRec -> saleDate.year) {
      dSales[x].revenue += sRec -> salePrice;
      break;
    }
  }

  if (dSales[x].revenue == 0.0) // if the date not already added in daily sale then add new record in daily sale list
  {
    dSales[x].saleDate = sRec -> saleDate;
    dSales[x].revenue = sRec -> salePrice;
  }
}

/**   Below code already provided at assignement */
int readSalesFile(FILE* fp, struct ProductSalesList * prodList, struct DailySalesList * dailySales) {

  int numberSalesRead = 0, valuesRead;
  struct SingleSaleRecord saleRec = {
    0
  };
  char productName[MAX_PRODUCT_NAME_LEN];

  while (!feof(fp)) {
    valuesRead = fscanf(fp, "%[^/]/%d/%lf/%d/%d/%d%*c",
      productName, & saleRec.numberSold, & saleRec.salePrice, &
      saleRec.saleDate.month, & saleRec.saleDate.day, &
      saleRec.saleDate.year);
    if (valuesRead > 0) {
      addSale(prodList, dailySales, productName, & saleRec);
      numberSalesRead++;
    }
  }
  return numberSalesRead;
}

/* show ProductList*/
void showpList(struct ProductSalesList * pList, int N) {
  int x;
  printf("\nDAY MONTH YEAR                        PRODUCT #SOLD   PRICE\n");
  for (x = 0; x < N; x++) {
    printf(" %02d    %02d %4d %30s  %4d    %.2f\n", pList[x].saleRec.saleDate.day,
      pList[x].saleRec.saleDate.month, pList[x].saleRec.saleDate.year,
      pList[x].productName, pList[x].saleRec.numberSold, pList[x].saleRec.salePrice);
  }
}

// sorting daily sale on the descending order of revenue
void sortSaleOnRevenue(struct DailySalesList * dailySale) {
  int fix, comp, pos;

  struct DailySalesList temp;
  int Count;

  // finding count of items in the list
  for (Count = 0; dailySale[Count].revenue != 0.0; Count++)
  ;
  // Sorting list using selection sort
  for (fix = 0; fix < Count; fix++) {
    pos = fix;
    for (comp = fix + 1; comp < Count; comp++) {
      if (dailySale[comp].revenue > dailySale[pos].revenue)
        pos = comp;
    }

    // swapping pos index element with fix index element
    temp = dailySale[fix];
    dailySale[fix] = dailySale[pos];
    dailySale[pos] = temp;
  }
}

/* showing product sale details arranged on product name */
void showSaleByProduct(struct ProductSalesList productList[], int N) {

  struct ProductSalesList temp[MAX_PRODUCT_SIZE] = {
    0
  }; // initialized by 0
  int x, y, pos, index = 0;
  int isFound = 0;

  for (pos = x = 0; x < N; x++) {
    for (isFound = 0, y = 0; y < pos; y++) {
      if (strcmp(temp[y].productName, productList[x].productName) == 0) {
        isFound = 1;
        index = y;
      }
    }
    if (isFound == 0) {
      temp[pos] = productList[x];
      pos++;
    } else {
      temp[index].saleRec.numberSold += productList[x].saleRec.numberSold;
      temp[index].saleRec.salePrice += productList[x].saleRec.salePrice;
    }
  }

  printf("\n              PRODUCT  #SOLD REVENUE");
  for (x = 0; x < pos; x++) {
    printf("\n %20s    %3d %7.2f", temp[x].productName, temp[x].saleRec.numberSold, temp[x].saleRec.salePrice);
  }
}

/* menu system for UI */
char menu() {
  char choice;
  printf("\nSelect one of the following options:");
  printf("\n1-View All Sales");
  printf("\n2-View Sales By Product");
  printf("\n3-View Sales by Date sorted by revenue");
  printf("\n0-Exit\n");
  fflush(stdin);
  scanf("%c", & choice);
  while (choice < '0' || choice > '3') {
    printf("Enter a valid integer between 0 and 3: ");
    scanf(" %c", & choice);
  }
  return choice;
}

/* Displaying daily sale data */
void showDailySale(struct DailySalesList * dailySales) {
  int x;
  printf("\n   REVENUE  DAY  MONTH  YEAR");
  for (x = 0; dailySales[x].revenue != 0.0; x++) {
    printf("\n %9.2f   %02d     %02d  %4d", dailySales[x].revenue, dailySales[x].saleDate.day, dailySales[x].saleDate.month, dailySales[x].saleDate.year);
  }
}

/* The main() function */
int main() {
  FILE * f;
  int x;
  char choice;
  int totalItemsInList = 0;
  f = fopen("SampleData.txt", "r"); /* Opening the data file */
  if (f == NULL)
    printf("\n SampleData.txt File not found ");
  else {
    struct ProductSalesList pList[MAX_PRODUCT_SIZE] = {
      0
    };
    struct DailySalesList dSales[MAX_PRODUCT_SIZE] = {
      0
    };
    totalItemsInList = readSalesFile(f, pList, dSales);
    printf("\n*** Seneca Gardens ***");
    do {
      choice = menu(); // show menu
      switch (choice) // switch on the user's choice
      {
      case '1':
        showpList(pList, totalItemsInList);
        break;
      case '2':
        showSaleByProduct(pList, totalItemsInList);
        break;
      case '3':

        sortSaleOnRevenue(dSales);
        showDailySale(dSales);
        break;
      }

    } while (choice != '0');
  }

  fclose(f);
  return (0);
}
