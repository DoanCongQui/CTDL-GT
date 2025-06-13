#include <stdio.h>
#include <math.h>

// Struct thong tin sinh vien
typedef struct SINHVIEN{
    char MSSV[9];
    char HoTen[20];
    int old;
    float diem;
}SV;

// Struct danh sach sinh vien
typedef struct DANHSACHSV
{
    SV *sv;
}DSSV;

// void importSinhVien(SV ds[])
// {

// }

int main()
{
    // SV sv1;
    // printf("Nhap MSSV: ");
    // scanf("%s", &sv1.MSSV);
    // fflush(stdin);

    // printf("Nhap Ho & Ten Sinh Vien: ");
    // scanf("%s", &sv1.HoTen);
    // fflush(stdin);
    // printf("MSSV: %s", sv1.MSSV);

    char *filename = "database/data.txt";
    FILE *f = fopen(filename, "a");

    if (f == NULL)
    {
        printf("Khong ghi duoc vao file");
    }

    fprintf(f, "DoanCongQui"); 
    fprintf(f, "\n"); 
    


}

