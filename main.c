#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib/sinhvien.h"

int main()
{
    DSSV ds = {NULL, 0};
    int choice;
    char MSSV[10];

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
                themSinhVien(&ds);
                break;

            case 2:
                hienThiDanhSach(&ds, "database/data.txt");
                break;
            
            case 3:
                printf("Nhap MSSV can tim: ");
                scanf("%s", MSSV);
                timKiemSinhVien(&ds, MSSV);
                break;

            case 4:
                xoaSinhVien(&ds, "database/data.txt", "a");
                break;

            case 5:
                printf("Nhap MSSV can cap nhat: ");
                scanf("%s", MSSV);
                getchar();
                capNhatSinhVien(&ds, MSSV);
                break;

            case 7:
                ghiFile(&ds, "database/data.txt", "a");
                break;

            case 0:
                if(ds.sv != NULL){
                    char save;
                    do {
                    printf("Ban co muon luu truoc khi thoat hay khong y/n: ");
                    scanf("%s", &save);
                    getchar();
                        if(save == 'y') {ghiFile(&ds, "database/data.txt", "a"); break;}
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

