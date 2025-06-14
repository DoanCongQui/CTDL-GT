#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct thong tin sinh vien
typedef struct SINHVIEN{
    char MSSV[9];
    char HoTen[20];
    int old;
    float diem;
}SV;

// Struct danh sach sinh vien
typedef struct DANHSACHSV{
    SV *sv;
    int count;
}DSSV;

void importSinhVien(DSSV *ds)
{
    ds->sv = realloc(ds->sv, (ds->count + 1)* sizeof(SV));
    SV *sv = &ds->sv[ds->count];

    printf("Nhap MSSV: ");
    scanf("%s", &sv->MSSV);
    fflush(stdin);
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

void freeStudentList(DSSV *ds) {
    free(ds->sv);
}

// void printSinhVien(SV *sv)
// {
//     printf("\n====================\n");
//     printf("MSSV: %s\n", sv->MSSV);
//     printf("Ho & Ten: %s\n", sv->HoTen);
//     printf("Tuoi: %d\n", sv->old);
//     printf("Diem: %g\n", sv->diem);
// }

// Function hien thi sinh vien vua them (Chua duoc luu vao file) 
void printSinhVien(DSSV *ds)
{
    if(ds->sv == NULL){
        printf("Khong co sinh vien nao vua them");
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

// Function Luu file vao database/data.txt
void ghiFile(DSSV *ds, const char *filename) {
    FILE *f = fopen(filename, "a");
    if (f == NULL) {
        printf("Khong mo duoc file de ghi\n");
        return;
    }

    for (int i = 0; i < ds->count; i++) {
        fprintf(f, "%s,%s,%d,%.2f\n",
            ds->sv[i].MSSV, ds->sv[i].HoTen,
            ds->sv[i].old, ds->sv[i].diem);
    }
    fclose(f);
    if(ds->sv == NULL) printf("Khong co du lieu de luu");
    else{
        printf("Ghi du lieu vao tep thanh cong!\n");
        ds->sv = NULL;
        ds->count = 0;
    } 
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
                            printf("Nhap diem moi (0 - 10): ");
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

void docFile(DSSV *ds, const char *filename) {
    ds->sv = NULL;
    ds->count = 0;
    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("Khong the mo tep de doc\n");
        return;
    }

    SV temp;
    while (fscanf(f, "%[^,],%[^,],%d,%f\n", temp.MSSV, temp.HoTen, &temp.old, &temp.diem) == 4) {
        ds->sv = realloc(ds->sv, (ds->count + 1) * sizeof(SV));
        ds->sv[ds->count++] = temp;
    }

    fclose(f);
    printf("Doc du lieu tu tep thanh cong!\n");
}

void hienThiDanhSach(DSSV *ds, const char *filename)
{
    int choice;
    do {
        printf("\n1. Hien thi danh sach vua nhap.\n");
        printf("2. Hien thi sanh sach da duoc luu.\n");
        printf("0. Exit\n");
        scanf("%d", &choice);
        getchar();
        switch (choice)
        {
        case 1:
            printSinhVien(ds);
            break;
        case 2:
            docFile(ds, filename);
            printSinhVien(ds);
            ds->sv = NULL;
            ds->count=0;
            break;

        case 0:
            printf("Thoat va luu thong tin!\n");
            break;
        }
    } while (choice != 0);
}

int main()
{

    // char *filename = "database/data.txt";
    // FILE *f = fopen(filename, "a");

    // if (f == NULL)
    // {
    //     printf("No write the file");
    // }

    // fprintf(f, "DoanCongQui"); 
    // fprintf(f, "\n"); 
    // SV *sv1;

    // importSinhVien(sv1);
    // printSinhVien(sv1);


    DSSV ds = {NULL, 0};
    int choice;

    do {
        printf("\n===== STUDENT MENU =====\n");
        printf("1. Them sinh vien vao danh sach\n");
        printf("2. Display student list\n");
        printf("3. Luu file\n");
        printf("4. Cap nhap thong tin\n");
        printf("5. Hien Thi danh sach\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                importSinhVien(&ds);
                break;

            case 2:
                printSinhVien(&ds);
                break;
            
            case 3:
                ghiFile(&ds, "database/data.txt");
                break;

            case 4:
                char MSSV[9];
                printf("Nhap MSSV can cap nhat: ");
                scanf("%s", MSSV);
                getchar();
                capNhatSinhVien(&ds, MSSV);
                break;
            
            // case 5:
            //     docFile(&ds, "database/data.txt");
            //     printSinhVien(&ds);
            //     break;
            
            case 5:
                hienThiDanhSach(&ds, "database/data.txt");
                break;
        } 
    } while (choice != 0);

    if (ds.sv != NULL) {
        freeStudentList(&ds);
    }

}

