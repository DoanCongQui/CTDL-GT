#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sinhvien.h"

void themSinhVien(DSSV *ds)
{
    ds->sv = realloc(ds->sv, (ds->count + 1)* sizeof(SV));
    SV *sv = &ds->sv[ds->count];

    printf("\n======== THEM SINH VIEN =======\n");
    printf("Nhap MSSV: ");
    fgets(sv->MSSV, sizeof(sv->MSSV), stdin);
    sv->MSSV[strcspn(sv->MSSV, "\n")] = '\0';
    printf("Nhap Ho & Ten: ");
    fgets(sv->HoTen, 50, stdin);
    sv->HoTen[strcspn(sv->HoTen, "\n")] = '\0';
    printf("Nhap tuoi: ");
    scanf("%d", &sv->old);
    do{
        printf("Nhap diem: ");
        scanf("%g", &sv->diem);
    }while (sv->diem < 0 || sv->diem > 10);

    ds->count++;
}

void capNhatSinhVien(DSSV *ds, char *mssv) {
    for (int i = 0; i < ds->count; i++) {
        if (strcmp(ds->sv[i].MSSV, mssv) == 0) {
            int choice;
            do {
                printf("\n--- CAP NHAT SINH VIEN ---\n");
                printf("1. Cap nhat ten\n");
                printf("2. Cap nhat tuoi\n");
                printf("3. Cap nhat diem\n");
                printf("0. Thoat va luu\n");
                printf("Luu chon: ");
                scanf("%d", &choice);
                getchar();
                switch (choice) {
                    case 1:
                        printf("Nhap ten moi: ");
                        fgets(ds->sv[i].HoTen, sizeof(ds->sv[i].HoTen), stdin);
                        ds->sv[i].HoTen[strcspn(ds->sv[i].HoTen, "\n")] = '\0';
                        printf("Da cap nhat ten!\n");
                        break;

                    case 2:
                        printf("Nhap tuoi moi: ");
                        scanf("%d", &ds->sv[i].old);
                        printf("Da cap nhat tuoi!\n");
                        break;

                    case 3:
                        do {
                            printf("Nhap diem moi: ");
                            scanf("%f", &ds->sv[i].diem);
                        } while (ds->sv[i].diem < 0 || ds->sv[i].diem > 10);
                        printf("Da cap nhat diem!\n");
                        break;

                    case 0:
                        printf("Thoat va luu thong tin!\n");
                        break;

                    default:
                        printf("Lua chon khong hop le. Vui long chon lai!\n");
                }

            } while (choice != 0);
            return;
        }
    }
    printf("Khong tim thay sinh vien can cap nhat.\n");
}

void hienThiSinhVien(DSSV *ds)
{
    if(ds->sv == NULL){
        printf("\nKhong co sinh vien nao vua them\n");
    }
    else{
        for (int i = 0; i < ds->count; i++) {
            printf("\n====================\n");
            printf("MSSV: %s\n", ds->sv[i].MSSV);
            printf("Ho & Ten: %s\n", ds->sv[i].HoTen);
            printf("Tuoi: %d\n", ds->sv[i].old);
            printf("Diem: %g\n", ds->sv[i].diem);
        }
    }
}

void hienThiDanhSach(DSSV *ds, const char *filename)
{
    int choice;
    DSSV tempDS = {NULL, 0};
    do {
        printf("\n====== HIEN THI SINH VIEN ======");
        printf("\n1. Hien thi danh sach vua nhap.\n");
        printf("2. Hien thi sanh sach da duoc luu.\n");
        printf("0. Exit\n");
        printf("================================\n");
        printf("Lua chon: ");
        scanf("%d", &choice);
        getchar();
        switch (choice)
        {
        case 1:
            hienThiSinhVien(ds);
            break;
        case 2:
            docFile(&tempDS, filename);
            hienThiSinhVien(&tempDS);
            break;

        case 0:
            printf("Thoat va luu thong tin!\n");
            break;

        default:
            printf("Lua chon khong hop le. Vui long chon lai!\n");
        }
    } while (choice != 0);
}

// Tim kiem vs thuat toan Liner Search
void timKiemSinhVien(DSSV *ds, char *mssv) {
    DSSV tempDS = {malloc(sizeof(SV)), 0};
    tempDS.count = 0;
    for (int i = 0; i < ds->count; i++) {
        if (strcmp(ds->sv[i].MSSV, mssv) == 0) {
            tempDS.sv[0] = ds->sv[i];
            tempDS.count = 1;
            hienThiSinhVien(&tempDS);
        }
    }
}

// Xoa sinh vien trong bo nho cache
void xoaSVCache(DSSV *ds, char *mssv) {
    int index = -1;
    for (int i = 0; i < ds->count; i++) {
        if (strcmp(ds->sv[i].MSSV, mssv) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Khong tim thay MSSV can xoa\n");
        return;
    }

    for (int i = index; i < ds->count - 1; i++) {
        ds->sv[i] = ds->sv[i + 1];
    }

    ds->count--;
    ds->sv = realloc(ds->sv, ds->count * sizeof(SV));
    printf("Da xoa sinh vien co MSSV %s\n", mssv);
}

void xoaSinhVien(DSSV *ds, const char *filename) {
    int choice;
    char mssv;
    DSSV tempDS = {NULL, 0};
    do {
        printf("\n======== XOA SINH VIEN =========");
        printf("\n1. Xoa sinh vien vua nhap.\n");
        printf("2. Xoa sinh vien trong danh sach.\n");
        printf("0. Exit\n");
        printf("================================\n");
        printf("Lua chon: ");
        scanf("%d", &choice);
        getchar();
        switch (choice)
        {
        case 1:
            if (ds->sv == NULL){printf("\nChua co sinh vien nao duoc them."); break;}
            printf("Nhap MSSV muon xoa: ");
            scanf("%s", &mssv);
            getchar();
            xoaSVCache(ds, &mssv);
            break;
        case 2:
            if (tempDS.sv == NULL){printf("\nKhong co sinh vien trong danh sach."); break;}
            printf("Nhap MSSV muon xoa: ");
            scanf("%s", &mssv);
            getchar();
            docFile(&tempDS, filename);
            xoaSVCache(&tempDS, &mssv);
            ghiFile(&tempDS, filename);
            break;

        case 0:
            printf("Thoat va luu thong tin!\n");
            break;
        
        default:
            printf("Lua chon khong hop le. Vui long chon lai!\n");
        }
    } while (choice != 0);
}

void freeStudentList(DSSV *ds) {
    free(ds->sv);
}