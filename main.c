#include <stdio.h>

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
  struct SingleSaleRecord sales[100];
};

struct DailySalesList {};

void addSale(struct ProductSalesList *prodList, struct DailySalesList *dailySales, char productName[MAX_PRODUCT_NAME_LEN], struct SingleSaleRecord *saleRec);

int readSalesFile(FILE* fp, struct ProductSalesList* prodList, struct DailySalesList* dailySales) {
  int numberSalesRead = 0, valuesRead;
  struct SingleSaleRecord saleRec = { 0 };
  char productName[MAX_PRODUCT_NAME_LEN];

  while (!feof(fp)) {
    valuesRead = fscanf_s(fp, "%[^/]/%d/%lf/%d/%d/%d%*c",
        productName, &saleRec.numberSold, &saleRec.salePrice,
        &saleRec.saleDate.month, &saleRec.saleDate.day,
        &saleRec.saleDate.year);

    if (valuesRead > 0) {
      addSale(prodList, dailySales, productName, &saleRec);
      numberSalesRead++;
    }
  }
  return numberSalesRead;
}

void addSale(
    struct ProductSalesList *prodList, 
    struct DailySalesList *dailySales, 
    char productName[MAX_PRODUCT_NAME_LEN], 
    struct SingleSaleRecord *saleRec
) {

}
