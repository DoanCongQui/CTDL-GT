#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib/sinhvien.h"


// void test(DSSV *ds)
// {
//     int index;
//     printf("\n0. Tang dan");
//     printf("\n1. Giam dan");
//     printf("\nChon: ");
//     scanf("%d", &index);
//     sapXepSinhVien(ds, "database/data.txt", index);
//     hienThiSinhVien(ds, 1, NULL);
// }

int main()
{
    DSSV ds = {NULL, 0};
    int choice;
    // char MSSV[10];
    int index;

    do {
        printf("\n====== QUAN LY SINH VIEN ======\n");
        printf("1. Them sinh vien vao danh sach\n");
        printf("2. Hien thi danh sach sinh vien\n");
        printf("3. Tim kiem\n");
        printf("4. Xoa sinh vien\n");
        printf("5. Cap nhap thong tin\n");
        printf("6. Sap xep\n");
        printf("7. Luu file\n");
        printf("0. Exit\n");
        printf("===============================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                docFile(&ds, "database/data.txt");
                themSinhVien(&ds, "database/data.txt");
                break;

            case 2:
                hienThiDanhSach(&ds, "database/data.txt");
                break;
            
            case 3:
                while (1)
                {
                    printf("\n1. Linear Search");
                    printf("\n2. Binary Search");
                    printf("\n0. Exit");
                    printf("\nChon: ");
                    scanf("%d", &index);
                    getchar();
                    if(index==1) {timKiemSinhVien(&ds, "database/data.txt"); continue;}
                    if(index==2) {timKiemSinhVien(&ds, "database/data.txt"); continue;}
                    else if (index == 0) break;
                    else {printf("Lua chon k hop le vui long nhap lai.\n"); continue;}
                }
                break;

            case 4:
                xoaSinhVien(&ds, "database/data.txt", "a");
                break;

            case 5:
                capNhatDanhSach(&ds, "database/data.txt");
                break;

            case 6:
                sapXepSinhVien(&ds, "database/data.txt");
                break;

            case 7:
                ghiFile(&ds, "database/data.txt", "w");
                break;

            case 0:
                if(ds.sv != NULL){
                    char save;
                    do {
                    printf("Ban co muon luu truoc khi thoat hay khong y/n: ");
                    scanf("%s", &save);
                    getchar();
                        if(save == 'y') {ghiFile(&ds, "database/data.txt", "w"); break;}
                        if(save == 'n') break;
                    }while(save != 'y' || save != 'n');
                }
                break;

            default:
                printf("Lua chon khong hop le. Vui long chon lai!\n");
        } 
    } while (choice != 0);

    if (ds.sv != NULL) {
        freeStudentList(&ds);
    }

}

