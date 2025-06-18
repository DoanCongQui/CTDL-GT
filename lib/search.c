#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sinhvien.h"

void linearSearch(DSSV *ds, const char *filename, char *mssv) {
    for (int i = 0; i < ds->count; i++) {
        if (strcmp(ds->sv[i].MSSV, mssv) == 0) {
            int *count = &i;
            printf("\n--- SINH VIEN CAN TIM LA ---\n");
            hienThiSinhVien(ds, 0, count);
        }
        else {printf("Sinh vien tren khong co trong danh sach\n"); break;}
    }
}

int binarySearchMSSV(DSSV *ds, const char *mssv) {
    int left = 0, right = ds->count - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        int cmp = strcmp(ds->sv[mid].MSSV, mssv);
        if (cmp == 0) return mid;
        else if (cmp < 0) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}