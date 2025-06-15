#ifndef SINHVIEN_H
#define SINHVIEN_H

typedef struct SINHVIEN {
    char MSSV[10];
    char HoTen[50];
    int old;
    float diem;
} SV;

typedef struct DANHSACHSV {
    SV *sv;
    int count;
} DSSV;

/*
==============================================
                    Manager
==============================================
*/
void themSinhVien(DSSV *ds);
void hienThiSinhVien(DSSV *ds);
void hienThiDanhSach(DSSV *ds, const char *filename);
void capNhatSinhVien(DSSV *ds, char *mssv);
void xoaSinhVien(DSSV *ds, const char *filename);
void timKiemSinhVien(DSSV *ds, char *mssv);
/*
==============================================
                    FILE
==============================================
*/
void docFile(DSSV *ds, const char *filename); 
void ghiFile(DSSV *ds, const char *filename);
void freeStudentList(DSSV *ds);
#endif