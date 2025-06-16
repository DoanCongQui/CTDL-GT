#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sinhvien.h"

// Ham check xem mssv co bi trung khi nhap vao hay k return true fasle
int checkMSSV(const char *mssv, const char *filename) {
    DSSV tempDS = {malloc(sizeof(SV)), 0};
    docFile(&tempDS, filename);
    for (int i = 0; i < tempDS.count; i++) {
        if (strcmp(tempDS.sv[i].MSSV, mssv) == 0) {
            return 1;
        }
    }
    return 0;
}

int checkSinhVien(DSSV *ds, const char *filename,DSSV **dsout){
    DSSV *temp = malloc(sizeof(DSSV));
    temp->sv = malloc(sizeof(SV));
    temp->count = 0;

    docFile(temp, filename);
    if(ds->sv==NULL){
        if(temp->sv!=NULL) {*dsout = temp; return 1;}
        else {free(temp->sv); free(temp); return 0;}
    }

    *dsout = ds;
    return 1;
}

void nhapMSSV(SV *sv, const char * filename, int check){
    do{
        printf("Nhap MSSV: ");
        fgets(sv->MSSV, 10, stdin);
        sv->MSSV[strcspn(sv->MSSV, "\n")] = '\0';

        if (strlen(sv->MSSV) != 8) {printf("MSSV phai du 8 ky tu. Vui long nhap lai!\n"); continue;}
        if(check) {
            if (checkMSSV(sv->MSSV, filename)) {printf("Sinh vien nay da ton tai. Vui long nhap lai!\n"); continue;} else break;
        }
        else break;
    // }while (strlen(sv->MSSV) != 8 || checkMSSV(ds, filename));
    }while (1);
}

// Ham them sinh vien 
void themSinhVien(DSSV *ds, const char *filename)
{
    ds->sv = realloc(ds->sv, (ds->count + 1)* sizeof(SV));
    SV *sv = &ds->sv[ds->count];

    printf("\n======== THEM SINH VIEN =======\n");
    // do{
    //     printf("Nhap MSSV: ");
    //     fgets(sv->MSSV, 10, stdin);
    //     sv->MSSV[strcspn(sv->MSSV, "\n")] = '\0';

    //     if (strlen(sv->MSSV) != 8) {printf("MSSV phai du 8 ky tu. Vui long nhap lai!\n"); continue;}
    //     if (checkMSSV(sv->MSSV, filename)) {printf("Sinh vien nay da ton tai. Vui long nhap lai!\n"); continue;} else break;
    // }while (1);
    nhapMSSV(sv, filename, 1);

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

void capNhatSinhVien(DSSV *ds, const char *filename, char *mssv) {
    for (int i = 0; i < ds->count; i++) {
        if (strcmp(ds->sv[i].MSSV, mssv) == 0) {
            int choice;
            do {
                int *count = &i;
                printf("\n--- CAP NHAT SINH VIEN ---\n");
                // printf("\n%d\n", i);
                hienThiSinhVien(ds, 0, count);
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
                        char checkOUT;
                        while(1)
                        {
                            printf("Ban co chac chan muon thoat. Chon y/n: ");
                            scanf("%s", &checkOUT);
                            getchar();
                            if(checkOUT=='y'){
                                printf("Thoat va luu thong tin!\n");
                                ghiFile(ds, filename, "w");
                                break;
                            }

                            else if(checkOUT == 'n') return;
                            else printf("Khong hop le");
                        }
                        return;

                    default:
                        printf("Lua chon khong hop le. Vui long chon lai!\n");
                }

            } while (choice != 0);
            return;
        }
    }
    printf("Khong tim thay sinh vien can cap nhat.\n");
}

void capNhatDanhSach(DSSV *ds, const char *filename){
    DSSV *temp = NULL;
    SV *sv = malloc(sizeof(SV));
    if(checkSinhVien(ds, filename, &temp))
    {
        nhapMSSV(sv, filename, 0);
        capNhatSinhVien(temp, filename, sv->MSSV); 
        ds = temp;
    }
    else printf("Khong tin thay sinh vien\n");
}

void hienThiSinhVien(DSSV *ds, int check, int *count)
{
    /*
    * Kiem tra xem check dung va gia tri count bang NULL thi lap toan danh sach 
    * Nguoc lai thi lap 1 sinh vien
    */
    if(check && count==NULL)
    {
        for (int i = 0; i < ds->count; i++) {
            printf("\n====================\n");
            printf("MSSV: %s\n", ds->sv[i].MSSV);
            printf("Ho & Ten: %s\n", ds->sv[i].HoTen);
            printf("Tuoi: %d\n", ds->sv[i].old);
            printf("Diem: %g\n", ds->sv[i].diem);
        }
    }
    else 
    {
        printf("\n====================\n");
        printf("MSSV: %s\n", ds->sv[*count].MSSV);
        printf("Ho & Ten: %s\n", ds->sv[*count].HoTen);
        printf("Tuoi: %d\n", ds->sv[*count].old);
        printf("Diem: %g\n", ds->sv[*count].diem);
    }
}



void hienThiDanhSach(DSSV *ds, const char *filename){
    DSSV *temp = NULL;
    // docFile(&temp, filename);
    // if(ds->sv==NULL){
    //     if(temp.sv!=NULL) {hienThiSinhVien(&temp);}
    //     else {printf("Khong co sinh vien trong danh sach");}
    // }
    // else {hienThiSinhVien(ds);}
    if(checkSinhVien(ds, filename, &temp)){
        hienThiSinhVien(temp, 1, NULL);
    }
    else printf("Khong co sinh vien trong danh sach");
}

// void hienThiDanhSach(DSSV *ds, const char *filename)
// {
//     int choice;
//     DSSV tempDS = {NULL, 0};
//     do {
//         printf("\n====== HIEN THI SINH VIEN ======");
//         printf("\n1. Hien thi danh sach vua nhap.\n");
//         printf("2. Hien thi sanh sach da duoc luu.\n");
//         printf("0. Exit\n");
//         printf("================================\n");
//         printf("Lua chon: ");
//         scanf("%d", &choice);
//         getchar();
//         switch (choice)
//         {
//         case 1:
//             hienThiSinhVien(ds);
//             break;
//         case 2:
//             docFile(&tempDS, filename);
//             hienThiSinhVien(&tempDS);
//             break;
//         case 0:
//             printf("Thoat va luu thong tin!\n");
//             break;
//         default:
//             printf("Lua chon khong hop le. Vui long chon lai!\n");
//         }
//     } while (choice != 0);
// }

// Tim kiem vs thuat toan Liner Search
void timKiemSinhVien(DSSV *ds, char *mssv) {
    DSSV tempDS = {malloc(sizeof(SV)), 0};
    tempDS.count = 0;
    for (int i = 0; i < ds->count; i++) {
        if (strcmp(ds->sv[i].MSSV, mssv) == 0) {
            tempDS.sv[0] = ds->sv[i];
            tempDS.count = 1;
            hienThiSinhVien(&tempDS, 1, NULL);
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

void xoaSinhVien(DSSV *ds, const char *filename, char *index) {
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
            docFile(&tempDS, filename);
            if (tempDS.sv == NULL){printf("\nKhong co sinh vien trong danh sach."); break;}
            printf("Nhap MSSV muon xoa: ");
            scanf("%s", &mssv);
            getchar();
            xoaSVCache(&tempDS, &mssv);
            ghiFile(&tempDS, filename, "w");
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