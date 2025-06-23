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

// Ham check sinh vien xem co danh sach co bi rong khong
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

// Ham nhap kiem tra MSSV
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

// Ham nhap lop kiem tra ki tu
void nhapLop(SV *sv){
    do{
        printf("Nhap Lop: ");
        fgets(sv->lop, 15, stdin);
        sv->lop[strcspn(sv->lop, "\n")] = '\0';

        if (strlen(sv->lop) > 13) {printf("Qua han ky tu. Vui long nhap lai!\n"); continue;}
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
    nhapMSSV(sv, filename, 1);

    printf("Nhap Ho & Ten: ");
    fgets(sv->HoTen, 50, stdin);
    sv->HoTen[strcspn(sv->HoTen, "\n")] = '\0';

    nhapLop(sv);

    do{
        printf("Nhap diem: ");
        scanf("%g", &sv->diem);
    }while (sv->diem < 0 || sv->diem > 10);

    ds->count++;
}

// Ham lua chon cap nhat sv
void capNhatSinhVien(DSSV *ds, const char *filename, char *mssv) {
    for (int i = 0; i < ds->count; i++) {
        if (strcmp(ds->sv[i].MSSV, mssv) == 0) {
            int choice;
            do {
                int *count = &i;
                printf("\n--- CAP NHAT SINH VIEN ---\n");
                hienThiSinhVien(ds, 0, count);
                printf("\n--------------------------\n");
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
                        printf("Nhap lop moi: ");
                        fgets(ds->sv[i].HoTen, sizeof(ds->sv[i].HoTen), stdin);
                        ds->sv[i].HoTen[strcspn(ds->sv[i].HoTen, "\n")] = '\0';
                        printf("Da cap nhat lop!\n");
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
                        do
                        {
                            printf("Ban co chac chan muon thoat. Chon y/n: ");
                            scanf("%c", &checkOUT);
                            getchar();
                            if(checkOUT == 'n') break;
                            else if(checkOUT=='y'){
                                printf("Thoat va luu thong tin!\n");
                                ghiFile(ds, filename, "w");
                                return;
                            }

                            else {printf("Khong hop le");}
                        }while(checkOUT != 'y' || checkOUT != 'n');
                        break;

                    default:
                        printf("Lua chon khong hop le. Vui long chon lai!\n");
                }

            } while (1);
        }
    }
    printf("Khong tim thay sinh vien can cap nhat.\n");
}

// Ham main cap nhat sinh vien
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
// Func hien thi sinh vien (cac ham khac co the su dung lai)
void hienThiSinhVien(DSSV *ds, int check, int *count)
{
    printf("\n==================================================================================\n");
    printf("| %-5s | %-15s | %-25s | %-15s | %-6s |\n", 
           "STT", "MSSV", "Ho & Ten", "Lop", "Diem");
    printf("----------------------------------------------------------------------------------\n");

    if (check && count == NULL)
    {
        for (int i = 0; i < ds->count; i++) {
            printf("| %-5d | %-15s | %-25s | %-15s | %-6.2f |\n",
                   i + 1,
                   ds->sv[i].MSSV,
                   ds->sv[i].HoTen,
                   ds->sv[i].lop,
                   ds->sv[i].diem);
        }
    }
    else if (count != NULL)
    {
        int i = *count;
        printf("| %-5d | %-15s | %-25s | %-15s | %-6.2f |\n",
               i + 1,
               ds->sv[i].MSSV,
               ds->sv[i].HoTen,
               ds->sv[i].lop,
               ds->sv[i].diem);
    }

    printf("==================================================================================\n");
}

// Main hien thi danh sach sinh vien 
void hienThiDanhSach(DSSV *ds, const char *filename){
    DSSV *temp = NULL;
    if(checkSinhVien(ds, filename, &temp)){
        hienThiSinhVien(temp, 1, NULL);
    }
    else printf("Khong co sinh vien trong danh sach");
}

// Func tim kiem sinh vien voi cac lua chon 
void timKiemSinhVien(DSSV *ds, const char *filename){
    DSSV *temp = NULL;
    SV *sv = malloc(sizeof(SV));
    if(checkSinhVien(ds, filename, &temp))
    {
        int index;
        // nhapMSSV(sv, filename, 0);
        // linearSearch(temp, filename, sv->MSSV); 
        // ds = temp;
        while (1)
        {
            printf("\n1. Linear Search");
            printf("\n2. Binary Search");
            printf("\n0. Exit");
            printf("\nChon: ");
            scanf("%d", &index);
            getchar();
            if(index==1) {nhapMSSV(sv, filename, 0); linearSearch(temp, sv->MSSV); continue;}
            if(index==2) {InsertionSort(temp); nhapMSSV(sv, filename, 0); binarySearch(temp, sv->MSSV); continue;}
            else if (index == 0) break;
            else {printf("Lua chon k hop le vui long nhap lai.\n"); continue;}
        }
    }
    else printf("Khong tin thay sinh vien\n");
}

// Xoa sinh 1 sinh vien co ma trung vs mssv trong danh sach
void xoaSV(DSSV *ds, char *mssv) {
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

// Main xoa sinh vien voi cac lua chon(choice)
void xoaDSSinhVien(DSSV *ds, const char *filename) {
    int choice;
    DSSV *temp = NULL;
    SV *sv = malloc(sizeof(SV));
    do {
        printf("\n======== XOA SINH VIEN =========");
        printf("\n1. Nhap MSSV de xoa sinh vien.\n");
        printf("2. Save & Exit\n");
        printf("0. Exit\n");
        printf("================================\n");
        printf("Lua chon: ");
        scanf("%d", &choice);
        getchar();
        switch (choice)
        {
        case 1:
            if(checkSinhVien(ds, filename, &temp))
            {        
                char checkOUT;
                int index = 0;
                nhapMSSV(sv, filename, 0);
                for (int i = 0; i < temp->count; i++) {
                    if (strcmp(temp->sv[i].MSSV, sv->MSSV) == 0) {
                        index = 1;
                        hienThiSinhVien(temp, 0, &i);
                        do
                        {
                            printf("Ban co chac muon xoa sinh vien nay. Chon y/n: ");
                            scanf("%c", &checkOUT);
                            getchar();
                            if(checkOUT == 'n') break;
                            else if(checkOUT=='y'){
                                xoaSV(temp, sv->MSSV); 
                                break;
                            }
                            else {printf("Khong hop le\n");}
                        }while(checkOUT != 'y' || checkOUT != 'n');
                    }
                }
                if(!index) printf("MSSV khong co trong danh sach. Vui long nhap lai!\n");
                break; 
            }
            else printf("Danh sach rong. Vui long kiem tra!\n");
            break;

        case 2:
            char checkOUT;
            if(temp == NULL) return;
            else{
            do
            {
                printf("Ban muon Save & Exit. Chon y/n: ");
                scanf("%c", &checkOUT);
                getchar();
                if(checkOUT == 'n') return;
                else if(checkOUT=='y'){
                    printf("Thoat va luu thong tin!\n");
                    ds = temp;
                    ghiFile(ds, filename, "w");
                    break;
                }

                else {printf("Khong hop le");}
            }while(checkOUT != 'y' || checkOUT != 'n');}
            break;
        
        case 0:
            // char check;
            do
            {
                printf("Ban muon Exit. Chon y/n: ");
                scanf("%c", &checkOUT);
                getchar();
                if(checkOUT == 'n') break;
                else if(checkOUT=='y') return;
                else {printf("Khong hop le\n");}
            }while(checkOUT != 'y' || checkOUT != 'n');
            break;
        default:
            printf("Lua chon khong hop le. Vui long chon lai!\n");
        }
    } while (1);
}

// Function sap xep sinh vien voi cac lua chon
void sapXepSinhVien(DSSV *ds, const char *filename){
    DSSV *temp = NULL;
    if(checkSinhVien(ds, filename, &temp))
    {
        int choice;
        ds = temp;
        while (1)
            {
                printf("\n1. Interchange sort");
                printf("\n2. Bubble sort");
                printf("\n3. Insertion sort");
                printf("\n4. Selection sort");
                printf("\n5. Quick sort");
                printf("\n0. Exit");
                printf("\nChon: ");
                scanf("%d", &choice);
                getchar();
                if(choice==1) {InterchangeSort(ds); hienThiSinhVien(ds, 1, NULL); continue;}
                else if (choice==2) {BubbleSort(ds); hienThiSinhVien(ds, 1, NULL); continue;}
                else if (choice==3) {InsertionSort(ds); hienThiSinhVien(ds, 1, NULL); continue;}
                else if (choice==4) {SelectionSort(ds); hienThiSinhVien(ds, 1, NULL); continue;}
                else if (choice==5) {QuickSort(ds); hienThiSinhVien(ds, 1, NULL); continue;}
                else if(choice == 0) break;
                else {printf("Lau chon khong hop le.\n"); continue;}
            }
    }
    else printf("Khong tin thay sinh vien\n");
}

// Giai phong bo nho
void freeStudentList(DSSV *ds) {
    free(ds->sv);
}