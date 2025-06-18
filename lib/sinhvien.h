#ifndef SINHVIEN_H
#define SINHVIEN_H

typedef struct SINHVIEN {
    char MSSV[10];
    char HoTen[50];
    char lop[15];
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
int checkMSSV(const char *mssv, const char *filename);
int checkSinhVien(DSSV *ds, const char *filename,DSSV **dsout);
void nhapMSSV(SV *sv, const char * filename, int check);
void nhapLop(SV *sv);
void themSinhVien(DSSV *ds, const char *filename);
void hienThiSinhVien(DSSV *ds, int check, int *count);
void hienThiDanhSach(DSSV *ds, const char *filename);
void capNhatSinhVien(DSSV *ds, const char *filename, char *mssv);
void capNhatDanhSach(DSSV *ds, const char *filename);
void xoaSinhVien(DSSV *ds, const char *filename, char *index);
void timKiemSinhVien(DSSV *ds, const char *filename);
void sapXepSinhVien(DSSV *ds, const char * filename);
void linearSearch(DSSV *ds, const char *filename, char *mssv);

/*
==============================================
                    FILE
==============================================
*/
void docFile(DSSV *ds, const char *filename); 
void ghiFile(DSSV *ds, const char *filename, char *index);
void freeStudentList(DSSV *ds);


/*
==============================================
                    SORT
==============================================
*/
void InterchangeSort(DSSV *ds); 
void BubbleSort(DSSV *ds);
void InsertionSort(DSSV *ds);
void SelectionSort(DSSV *ds);
void QuickSort(DSSV *ds, int left, int right); 


/*
==============================================
                    SEARCH
==============================================
*/
void linearSearch(DSSV *ds, const char *filename, char *mssv);
int binarySearchMSSV(DSSV *ds, const char *mssv);
#endif