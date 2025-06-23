#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sinhvien.h"

// Ham input tang giam 
int tangGiam()
{
    int index;
    printf("\n0. Giam dan");
    printf("\n1. Tang dan");
    printf("\nChon: ");
    scanf("%d", &index);
    return index;
}

// Ham ss sap xep
int soSanhSinhVien(SV a, SV b, int tangDan) {
    // So sanh diem
    if (a.diem != b.diem) {
        return tangDan ? (a.diem > b.diem) : (a.diem < b.diem);
    }

    // So sanh (HoTen)
    int tenCmp = strcmp(a.HoTen, b.HoTen);
    if (tenCmp != 0) {
        return tangDan ? (tenCmp > 0) : (tenCmp < 0);
    }

    // So sanh MSSV
    int mssvCmp = strcmp(a.MSSV, b.MSSV);
    return tangDan ? (mssvCmp > 0) : (mssvCmp < 0);
}

// Ham hoan vi giua 2 sinh vien
void Swap(SV *a, SV *b) {
    SV temp = *a;
    *a = *b;
    *b = temp;
}

// Ham so sanh theo chieu tang/giam
int soSanhDiem(SV a, SV b, int tang) {
    return tang ? (a.diem > b.diem) : (a.diem < b.diem);
}

// 1. Interchange Sort 
void InterchangeSort(DSSV *ds) {
    int tang = tangGiam();
    for (int i = 0; i < ds->count - 1; i++) {
        for (int j = i + 1; j < ds->count; j++) {
            if (soSanhSinhVien(ds->sv[i], ds->sv[j], tang))
                Swap(&ds->sv[i], &ds->sv[j]);
        }
    }
}

// 2. Bubble Sort 
void BubbleSort(DSSV *ds) {
    int tang = tangGiam();
    for (int i = 0; i < ds->count - 1; i++) {
        for (int j = ds->count - 1; j > i; j--) {
            if (soSanhSinhVien(ds->sv[j - 1], ds->sv[j], tang))
                Swap(&ds->sv[j], &ds->sv[j - 1]);
        }
    }
}

// 3. Insertion Sort
void InsertionSort(DSSV *ds) {
    int tang = tangGiam();
    for (int i = 1; i < ds->count; i++) {
        SV x = ds->sv[i];
        int j = i - 1;
        while (j >= 0 && soSanhSinhVien(ds->sv[j], x, tang)) {
            ds->sv[j + 1] = ds->sv[j];
            j--;
        }
        ds->sv[j + 1] = x;
    }
}

// 4. Selection Sort
void SelectionSort(DSSV *ds) {
    int tang = tangGiam();
    for (int i = 0; i < ds->count - 1; i++) {
        int minmax = i;
        for (int j = i + 1; j < ds->count; j++) {
            if (soSanhSinhVien(ds->sv[minmax], ds->sv[j], tang))
                minmax = j;
        }
        if (minmax != i)
            Swap(&ds->sv[i], &ds->sv[minmax]);
    }
}

// 5. Quick Sort
void quickSort(DSSV *ds, int left, int right, int tang) {
    int i = left, j = right;
    float pivot = ds->sv[(left + right) / 2].diem;
    while (i <= j) {
        while (tang ? (ds->sv[i].diem < pivot) : (ds->sv[i].diem > pivot)) i++;
        while (tang ? (ds->sv[j].diem > pivot) : (ds->sv[j].diem < pivot)) j--;
        if (i <= j) {
            Swap(&ds->sv[i], &ds->sv[j]);
            i++; j--;
        }
    }
    if (left < j) quickSort(ds, left, j, tang);
    if (i < right) quickSort(ds, i, right, tang);
}

void QuickSort(DSSV *ds) {
    int tang = tangGiam();  // 0 = giảm, 1 = tăng
    quickSort(ds, 0, ds->count - 1, tang);
}



