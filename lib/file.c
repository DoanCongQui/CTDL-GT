#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sinhvien.h"

// Function Doc file tu database/data.txt
void docFile(DSSV *ds, const char *filename) {
    ds->sv = NULL;
    ds->count = 0;
    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("Khong the mo tep de doc\n");
        return;
    }

    SV temp;
    while (fscanf(f, "%[^,],%[^,],%[^,],%f\n", temp.MSSV, temp.HoTen, temp.lop, &temp.diem) == 4) {
        ds->sv = realloc(ds->sv, (ds->count + 1) * sizeof(SV));
        ds->sv[ds->count++] = temp;
    }

    fclose(f);
}

// Function Luu file vao database/data.txt
void ghiFile(DSSV *ds, const char *filename, char *index) {
    FILE *f = fopen(filename, index);
    if (f == NULL) {
        printf("Khong mo duoc file de ghi\n");
        return;
    }

    for (int i = 0; i < ds->count; i++) {
        fprintf(f, "%s,%s,%s,%.2f\n",
            ds->sv[i].MSSV, ds->sv[i].HoTen,
            ds->sv[i].lop, ds->sv[i].diem);
    }
    fclose(f);
    if(ds->sv == NULL) printf("Khong co du lieu de luu");
    // else{
    //     printf("Ghi du lieu vao tep thanh cong!\n");
    //     ds->sv = NULL;
    //     ds->count = 0;
    // } 
}