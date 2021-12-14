/**
 *************** IPC FINALS Q1 ***************
 * Group Members
 * 1. Bachitar Singh
 *      ID: 130504210
 *      Email: Bsingh325@myseneca.ca
 * 2. Fardeen Sohil Panjwani
 *      ID: 119588218
 *      Email: fspanjwani@myseneca.ca
 * 3. Yashita Kapoor
 *      ID: 121497218
 *      Email: ykapoor3@myseneca.ca
 */
#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>

#include<string.h>

#include<stdlib.h>

#define MAX_PRODUCT_NAME_LEN 25
#define MAX_PRODUCT_SIZE 25
struct SingleSaleRecord {
  int numberSold;
  double salePrice;
  struct Date {
    int month, day, year;
  }
  saleDate;
};

struct ProductSalesList {
  char productName[MAX_PRODUCT_NAME_LEN];
  struct SingleSaleRecord saleRecord;
};

struct DailySalesList {
  struct Date saleDate;
  double revenue;
};

void addSale(struct ProductSalesList * prodList, struct DailySalesList * salesList, char * productName, struct SingleSaleRecord * salesRecord) {
  int x;
  for (x = 0; prodList[x].productName[0] != '\0'; x++)
  ;

  strcpy(prodList[x].productName, productName);
  prodList[x].saleRecord = * salesRecord;

  for (x = 0; salesList[x].revenue != 0.0; x++) {
    if (salesList[x].saleDate.day == salesRecord -> saleDate.day &&
      salesList[x].saleDate.month == salesRecord -> saleDate.month &&
      salesList[x].saleDate.year == salesRecord -> saleDate.year) {
      salesList[x].revenue += salesRecord -> salePrice;
      break;
    }
  }

  if (salesList[x].revenue == 0.0) {
    salesList[x].saleDate = salesRecord -> saleDate;
    salesList[x].revenue = salesRecord -> salePrice;
  }
}

int reasalesListFile(FILE * fp, struct ProductSalesList * prodList, struct DailySalesList * dailySales) {

  int numberSalesRead = 0, valuesRead;
  struct SingleSaleRecord saleRecord = {
    0
  };
  char productName[MAX_PRODUCT_NAME_LEN];

  while (!feof(fp)) {
    valuesRead = fscanf(fp, "%[^/]/%d/%lf/%d/%d/%d%*c",
      productName, & saleRecord.numberSold, & saleRecord.salePrice, &
      saleRecord.saleDate.month, & saleRecord.saleDate.day, &
      saleRecord.saleDate.year);
    if (valuesRead > 0) {
      addSale(prodList, dailySales, productName, & saleRecord);
      numberSalesRead++;
    }
  }
  return numberSalesRead;
}

void getByDate(struct ProductSalesList * prodList, int N) {
  int x;
  printf("\nDAY MONTH YEAR                        PRODUCT #SOLD   PRICE\n");
  for (x = 0; x < N; x++) {
    printf(" %02d    %02d %4d %30s  %4d    %.2f\n", prodList[x].saleRecord.saleDate.day,
      prodList[x].saleRecord.saleDate.month, prodList[x].saleRecord.saleDate.year,
      prodList[x].productName, prodList[x].saleRecord.numberSold, prodList[x].saleRecord.salePrice);
  }
}

void sort(struct DailySalesList * dailySale) {
  int fix, comp, pos;

  struct DailySalesList temp;
  int Count;

  for (Count = 0; dailySale[Count].revenue != 0.0; Count++)
  ;
  for (fix = 0; fix < Count; fix++) {
    pos = fix;
    for (comp = fix + 1; comp < Count; comp++) {
      if (dailySale[comp].revenue > dailySale[pos].revenue)
        pos = comp;
    }

    temp = dailySale[fix];
    dailySale[fix] = dailySale[pos];
    dailySale[pos] = temp;
  }
}

void getByProduct(struct ProductSalesList productList[], int N) {

  struct ProductSalesList temp[MAX_PRODUCT_SIZE] = {
    0
  };
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
      temp[index].saleRecord.numberSold += productList[x].saleRecord.numberSold;
      temp[index].saleRecord.salePrice += productList[x].saleRecord.salePrice;
    }
  }

  printf("\n              PRODUCT  #SOLD REVENUE");
  for (x = 0; x < pos; x++) {
    printf("\n %20s    %3d %7.2f", temp[x].productName, temp[x].saleRecord.numberSold, temp[x].saleRecord.salePrice);
  }
  printf("\n");
}

char menu() {
  char choice;
  printf("\nSelect one of the following options:");
  printf("\n1-View All Sales");
  printf("\n2-View Sales By Product");
  printf("\n3-View Sales by Date sorted by revenue");
  printf("\n0-Exit\n");
  fflush(stdin);
  scanf(" %c", & choice);
  while (choice < '0' || choice > '3') {
    printf("Enter a valid integer between 0 and 3: ");
    scanf(" %c", & choice);
  }
  return choice;
}

void getDailySales(struct DailySalesList * dailySales) {
  int x;
  printf("\n   REVENUE  DAY  MONTH  YEAR");
  for (x = 0; dailySales[x].revenue != 0.0; x++) {
    printf("\n %9.2f   %02d     %02d  %4d", dailySales[x].revenue, dailySales[x].saleDate.day, dailySales[x].saleDate.month, dailySales[x].saleDate.year);
  }
  printf("\n");
}

int main() {
  FILE * f;
  int x;
  char choice;
  int totalItemsInList = 0;
  f = fopen("SampleData.txt", "r");
  if (f == NULL)
    printf("\n SampleData.txt File not found ");
  else {
    struct ProductSalesList prodList[MAX_PRODUCT_SIZE] = {
      0
    };
    struct DailySalesList salesList[MAX_PRODUCT_SIZE] = {
      0
    };
    totalItemsInList = reasalesListFile(f, prodList, salesList);
    printf("\n****** Seneca Gardens ******");
    do {
      choice = menu();
      switch (choice) {
      case '1':
        getByDate(prodList, totalItemsInList);
        break;
      case '2':
        getByProduct(prodList, totalItemsInList);
        break;
      case '3':
        sort(salesList);
        getDailySales(salesList);
        break;
      }

    } while (choice != '0');
  }

  printf("Good Bye");
  fclose(f);
  return (0);
}
