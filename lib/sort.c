#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sinhvien.h"

int soSanhSinhVien(SV a, SV b, int tangDan) {
    // So sánh điểm
    if (a.diem != b.diem) {
        return tangDan ? (a.diem > b.diem) : (a.diem < b.diem);
    }

    // So sánh tên (HoTen)
    int tenCmp = strcmp(a.HoTen, b.HoTen);
    if (tenCmp != 0) {
        return tangDan ? (tenCmp > 0) : (tenCmp < 0);
    }

    // So sánh MSSV
    int mssvCmp = strcmp(a.MSSV, b.MSSV);
    return tangDan ? (mssvCmp > 0) : (mssvCmp < 0);
}

void hoanVi(SV *a, SV *b) {
    SV temp = *a;
    *a = *b;
    *b = temp;
}

int partition(SV *arr, int low, int high, int tangDan) {
    SV pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (soSanhSinhVien(arr[j], pivot, tangDan)) {
            i++;
            hoanVi(&arr[i], &arr[j]);
        }
    }
    hoanVi(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quickSort(SV *arr, int low, int high, int tangDan) {
    if (low < high) {
        int pi = partition(arr, low, high, tangDan);
        quickSort(arr, low, pi - 1, tangDan);
        quickSort(arr, pi + 1, high, tangDan);
    }
}

void sapXepSinhVien(DSSV *ds, const char * filename, int tangDan) {
    docFile(ds, filename);
    quickSort(ds->sv, 0, ds->count - 1, tangDan);
}

