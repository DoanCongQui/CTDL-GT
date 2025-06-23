#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sinhvien.h"

// Thuat toan tiem kiem linear search
void linearSearch(DSSV *ds, const char *mssv) {
    int index = 0;
    for (int i = 0; i < ds->count; i++) {
        if (strcmp(ds->sv[i].MSSV, mssv) == 0) {
            printf("\n\t\t\t\tSINH VIEN CAN TIM\n");
            hienThiSinhVien(ds, 0, &i);
            index = 1;
        }
    }
    if(!index){printf("Khong co sinh vien trong danh sach. Vui long nhap lai.!\n");}
}

// Thuat toan tiem kiem binary search
void binarySearch(DSSV *ds, const char *mssv) {
    int left = 0, right = ds->count - 1;
    int found = 0;
    while (left <= right) {
        int mid = (left + right) / 2;
        int cmp = strcmp(ds->sv[mid].MSSV, mssv);
        if (cmp == 0) {
            printf("\n\t\t\t\tSINH VIEN CAN TIM\n");
            hienThiSinhVien(ds, 0, &mid);
            found = 1;
            break; 
        }
        else if (cmp < 0) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    if (!found) {
        printf("Khong co sinh vien trong danh sach. Vui long nhap lai.!\n");
    }
}
