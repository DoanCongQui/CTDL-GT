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
void themSinhVien(DSSV *ds, const char *filename);
void hienThiSinhVien(DSSV *ds);
void hienThiDanhSach(DSSV *ds, const char *filename);
void capNhatSinhVien(DSSV *ds, char *mssv);
void xoaSinhVien(DSSV *ds, const char *filename, char *index);
void timKiemSinhVien(DSSV *ds, char *mssv);
void sapXepSinhVien(DSSV *ds, const char * filename, int tangDan);
/*
==============================================
                    FILE
==============================================
*/
void docFile(DSSV *ds, const char *filename); 
void ghiFile(DSSV *ds, const char *filename, char *index);
void freeStudentList(DSSV *ds);
#endif