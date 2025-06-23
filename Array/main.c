#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib/sinhvien.h"

int main()
{
    DSSV ds = {NULL, 0};
    int choice;

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
                timKiemSinhVien(&ds, "database/data.txt");
                break;

            case 4:
                xoaDSSinhVien(&ds, "database/data.txt");
                break;

            case 5:
                capNhatDanhSach(&ds, "database/data.txt");
                break;

            case 6:
                sapXepSinhVien(&ds, "database/data.txt");
                break;

            case 7:
                if(ds.sv == NULL) {printf("Chua co sinh vien nao duoc chinh sua\n"); break;}
                ghiFile(&ds, "database/data.txt", "w");
                printf("Danh sach da duoc luu");
                ds.sv = NULL;
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

