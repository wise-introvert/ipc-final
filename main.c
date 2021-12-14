#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCT_NAME_LEN 30

struct SaleDate {
  int month;
  int day;
  int year;
};

struct SingleSaleRecord {
  int numberSold;
  double salePrice;
  struct SaleDate saleDate;
};

struct ProductSalesList {
  double revenue;
  int unitsSold;
  char productName[MAX_PRODUCT_NAME_LEN];
};

struct DailySalesList {
  double revenue;
  struct SaleDate saleDate;
};

void addSale(struct ProductSalesList *prodList[], struct DailySalesList *dailySales[], char productName[MAX_PRODUCT_NAME_LEN], struct SingleSaleRecord *saleRec, int *numberSalesRead);

int readSalesFile(FILE* fp, struct ProductSalesList* prodList[], struct DailySalesList* dailySales[]) {
  int numberSalesRead = 0, valuesRead;
  struct SingleSaleRecord saleRec = { 0 };
  char productName[MAX_PRODUCT_NAME_LEN];

  while (!feof(fp)) {
    printf("\n\n\t!feof(fp): %d", !feof(fp));
    valuesRead = fscanf(fp, "%[^/]/%d/%lf/%d/%d/%d%*c",
        productName, &saleRec.numberSold, &saleRec.salePrice,
        &saleRec.saleDate.month, &saleRec.saleDate.day,
        &saleRec.saleDate.year);

    printf("\n\n====================PRODUCT FOUND: %s====================\n\n", productName);

    if (valuesRead > 0) {
      addSale(prodList, dailySales, productName, &saleRec, &numberSalesRead);
      numberSalesRead++;
    }
    printf("\n\n\tnumberSalesRead: %d\n\n", numberSalesRead);
  }
  return numberSalesRead;
}

void addSale(
    struct ProductSalesList *prodList[], 
    struct DailySalesList *dailySales[], 
    char productName[MAX_PRODUCT_NAME_LEN], 
    struct SingleSaleRecord *saleRec,
    int *numberSalesRead
) {
  printf("\n\t========================================");
  printf("\n\tPROCESSING %s....", productName);
  // check if prodList already has an entry for the given
  // product
  int i = *numberSalesRead;
  int productIndex = -1;
  printf("\n\tChecking if item already in the array...");
  // TODO: Replace 5 with a dynamic calculation
  /*
  for(i = 0; i < numberSalesRead; i++) {
    printf("\n\n\t\tstrcmp(%s, \"\") = %d", prodList[i]->productName, strcmp(prodList[i]->productName, ""));
    if(strcmp(prodList[i]->productName, "") != 0 && strcmp(prodList[i]->productName, productName) == 0) {
      printf("\n\tMATCH FOUND");
      // product already in the array
      productIndex = i;
    }
  }

  if(productIndex > -1) {
    printf("\n\tUPDATING ITEM...");
    // product was found in the array
    // update the revenue
    prodList[productIndex]->revenue = saleRec->salePrice * saleRec->numberSold;
    // update quantity sold
    prodList[productIndex]->unitsSold = prodList[productIndex]->unitsSold + saleRec->numberSold;
  } else {
    */
    printf("\n\tCREATING NEW ENTRY AT INDEX %d...", i);
    // create a new entry
    // TODO: replace [i] with a pre-calculated index
    strcpy(prodList[i]->productName, productName);
    prodList[i]->revenue = saleRec->salePrice * saleRec->numberSold;
    prodList[i]->unitsSold = saleRec->numberSold;
    printf("\n\tNEW ITEM CREATED");
    printf("\n\tNEW ITEM INDEX: %d", i);
    printf("\n\tNEW ITEM NAME IN THE ARRAY: %s", prodList[i]->productName);

  printf("\n\t========================================\n\t");
}

int main(void) {
  FILE *fp;
  struct ProductSalesList *prodList;
  struct DailySalesList *dailySales;

  fp = fopen("./data.txt", "r");
  readSalesFile(fp, &prodList, &dailySales);
  fclose(fp);

  return 0;
}
