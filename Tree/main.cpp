#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//-------------------- Ham khoi tao -------------------

typedef struct TuDien{
    char tuTA[50];       
    char nghiaTV[100];  
    char loaiTu[20];    
    char viDu[200];   
	char tuDN[100]; 
}TD;

typedef struct TNODE
{
	TD data;
	TNODE *pLeft, *pRight;
} *TREE;

void Init(TREE &t);
TNODE* GetNode(TD td);
void Insert(TREE &T, TD td);
TREE SearchAV(TREE T, const char *tuTA);
TREE SearchVA(TREE T, const char *tuTV);
TREE SearchDN(TREE T, const char *tuDN);
void SearchStandFor(TREE &T, TNODE *p);
void RemoveNode(TREE &T, const char *tuTA);
void Edit(TREE &T, const char *tuTA);

void docFile(TREE &T, const char *tenFile);
void saveFile(TREE &T, const char *tenFile);
void LNR (TREE T);
void NLR(TREE T);
void menu();

int main()
{
	TREE T;
	Init(T);
	int chon, inp;
    TD td;
    char tuKhoa[50], key[2];
    docFile(T, "data.txt");
    do {
        menu();
        printf("Chon: ");
        scanf("%d", &chon);
        fflush(stdin);

        switch(chon) {
            case 1:
                printf("Nhap tu TA: "); gets(td.tuTA);
                printf("Nhap loai tu: "); gets(td.loaiTu);
                printf("Nhap nghia TV: "); gets(td.nghiaTV);
                printf("Nhap vi du: "); gets(td.viDu);
                printf("Co tu dong nghia ? (y/n): "); gets(key);
                do
            	{
            		if(strcmp(key, "y") == 0) {
            			printf("Nhap tu dong nghia (cach \",\" neu > 2 tu) : "); gets(td.tuDN);
						break;	
					}
					if(strcmp(key, "n") == 0)
						break;
				}while(strcmp(key, "y") != 0 || strcmp(key, "y") != 0);
                
                Insert(T, td);
                break;
            case 2:
            	{
	            	do
					{
						TNODE *p = new TNODE;
						printf("1. Anh - Viet.\n");
						printf("2. Viet - Anh.\n");
						printf("0. Exit\n");
						printf("Chon: ");
						scanf("%d", &inp);
						getchar();
						switch(inp){
							case 1:
								printf("Nhap tu can tra cuu: "); gets(tuKhoa);
				                p = SearchAV(T, tuKhoa);
				                if (p) {
				//                    printf("Nghia: %s\nLoai tu: %s\nVi du: %s\n", p->data.nghiaTV, p->data.loaiTu, p->data.viDu);
				                    printf("+------------------------------------------------------------+\n");
							        printf("| Tu:      %-50s|\n", p->data.tuTA);
							        printf("| Loai tu: %-50s|\n", p->data.loaiTu);
							        printf("| Nghia:   %-50s|\n", p->data.nghiaTV);
							        printf("| Vi du:   %-50s|\n", p->data.viDu);
							        printf("+------------------------------------------------------------+\n\n");
								} else {
				                    printf("Tu khong ton tai.\n");
				                }
				                break;
				            case 2:
				            	printf("Nhap tu can tra cuu: "); gets(tuKhoa);
				                p = SearchVA(T, tuKhoa);
				                if (p) {
				//                    printf("Nghia: %s\nLoai tu: %s\nVi du: %s\n", p->data.nghiaTV, p->data.loaiTu, p->data.viDu);
				                    printf("+------------------------------------------------------------+\n");
				                    
							        printf("| Tu:        %-50s|\n", p->data.nghiaTV);
							        printf("| Tieng Anh: %-50s|\n", p->data.tuTA);
							        printf("| Loai tu:   %-50s|\n", p->data.loaiTu);
							        printf("| Vi du:     %-50s|\n", p->data.viDu);
							        printf("+------------------------------------------------------------+\n\n");
								} else {
				                    printf("Tu khong ton tai.\n");
				                }
				                
				            default:
				            	if(inp!=0) printf("Lua chon sai. Vui long nhap lai!\n");   
							}
						
					}while(inp!=0);	
	                break;
				}
            	
            case 3:
                {
            		TNODE *p = new TNODE;
	                printf("Nhap tu can sua: "); gets(tuKhoa);
	                p = SearchAV(T, tuKhoa);
	                if(p) {printf("Ban co muon cap nhat tu khong (y/n): "); gets(key);}
	                else {printf("Tu khong ton tai.\n");break;}
	                do
	            	{
	            		if(strcmp(key, "y") == 0) {
	            			Edit(T, tuKhoa);
							break;	
						}
						if(strcmp(key, "n") == 0)
							break;
					}while(strcmp(key, "y") != 0 || strcmp(key, "y") != 0);
					saveFile(T, "data.txt");
	                break;
				}
				
            case 4:
            	{
            		TNODE *p = new TNODE;
	                printf("Nhap tu can xoa: "); gets(tuKhoa);
	                p = SearchAV(T, tuKhoa);
	                if(p) {printf("Ban co muon xoa tu khong (y/n): "); gets(key);}
	                else {printf("Tu khong ton tai.\n");break;}
	                do
	            	{
	            		if(strcmp(key, "y") == 0) {
	            			RemoveNode(T, tuKhoa);
							break;	
						}
						if(strcmp(key, "n") == 0)
							break;
					}while(strcmp(key, "y") != 0 || strcmp(key, "y") != 0);
					saveFile(T, "data.txt");
	                break;
				}
				
            case 5:
            	{
            		TNODE *p = new TNODE;
            		printf("Nhap tu dong nghia: "); gets(tuKhoa);
            		p = SearchDN(T, tuKhoa);
	                if (p) 
					{
	                	if(strcmp(p->data.tuDN, "")!=0)
						{
		                	printf("+------------------------------------------------------------+\n");
					        printf("| Tu:      %-50s|\n", p->data.tuTA);
					        printf("| Nghia:   %-50s|\n", p->data.nghiaTV);
					        printf("| Tu DN:   %-50s|\n", p->data.tuDN);
					        printf("+------------------------------------------------------------+\n\n");	
						}
						else printf("Tu %s khong co tu dong nghia.\n", p->data.tuTA);

					} else printf("Tu khong ton tai.\n");
	                break;
				}
				
            case 6:
            	printf("+-----------------+----------------+-----------------------------------+--------------------------------------------------+\n");
    			printf("|     Tu TA       |    Loai tu     |             Nghia TV              |                      Vi du                       |\n");
    			printf("+-----------------+----------------+-----------------------------------+--------------------------------------------------+\n");
                LNR(T);
                printf("+-----------------+----------------+-----------------------------------+--------------------------------------------------+\n\n");
                break;
        }
    } while (chon != 0);
}


void Init(TREE &t)
{
	t = NULL;
}

// --------------- Ham tao TNODE -------------------------
TNODE* GetNode(TD td) 
{
    TNODE *p = new TNODE;
    p->data = td;
    p->pLeft = p->pRight = NULL;
    return p;
}

// ---------------- Ham them tu vao TNODE -------------------
void Insert(TREE &T, TD td) 
{
    if (T == NULL) 
	{
        T = GetNode(td); 
    } 
	else 
	{
        int cmp = strcmp(td.tuTA, T->data.tuTA); 

        if (cmp < 0)
            Insert(T->pLeft, td);     
        else if (cmp > 0)
            Insert(T->pRight, td);  
        else
            printf("Tu '%s' da ton tai!\n", td.tuTA); 
    }
}

// ------------------ Ham hien thi LNR ------------------
void printRow(TREE T) {
    printf("| %-15s | %-14s | %-33s | %-48s |\n",
           T->data.tuTA, T->data.loaiTu, T->data.nghiaTV, T->data.tuDN);
}

void LNR(TREE T) {

    if (T != NULL) {
        LNR(T->pLeft);
        printRow(T);
        LNR(T->pRight);
    }
}

void NLR(TREE T) {
    if (T != NULL) {
    	printf("\nTu: %s\nLoai tu: %s\nNghia: %s\nVi du: %s\n", T->data.tuTA, T->data.loaiTu, T->data.nghiaTV, T->data.viDu);
        NLR(T->pLeft);
        NLR(T->pRight);
    }
}
// ----------------- Ham tim tu dien --------------------
TREE SearchAV(TREE T, const char *tuTA) 
{
    if (T == NULL) return NULL;
    int cmp = strcmp(tuTA, T->data.tuTA);
    if (cmp == 0)
        return T;
    else if (cmp < 0)
        return SearchAV(T->pLeft, tuTA);
    else
        return SearchAV(T->pRight, tuTA);
}

TREE SearchVA(TREE T, const char *tuTV) 
{
    if (T == NULL) return NULL;
    int cmp = strcmp(tuTV, T->data.nghiaTV);
    if (cmp == 0)
        return T;
    else if (cmp < 0)
        return SearchVA(T->pLeft, tuTV);
    else
        return SearchVA(T->pRight, tuTV);
}

TREE SearchDN(TREE T, const char *tuDN) 
{
    if (T == NULL) return NULL;
    int cmp = strcmp(tuDN, T->data.tuTA);
    if (cmp == 0)
        return T;
    else if (cmp < 0)
        return SearchDN(T->pLeft, tuDN);
    else
        return SearchDN(T->pRight, tuDN);
}

// ----------------- Ham doc file -----------------------
void docFile(TREE &T, const char *tenFile) 
{
    FILE *fp = fopen(tenFile, "r");
    if (!fp) return;

    char line[500];
    TD tu;
    while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\n")] = '\0';
        char *token = strtok(line, "|");
        if (token) strcpy(tu.tuTA, token);
        token = strtok(NULL, "|");
        if (token) strcpy(tu.nghiaTV, token);
        token = strtok(NULL, "|");
        if (token) strcpy(tu.loaiTu, token);
        token = strtok(NULL, "|");
        if (token) strcpy(tu.viDu, token);
        token = strtok(NULL, "|");
        if (token) strcpy(tu.tuDN, token);
        else strcpy(tu.tuDN, "");
        Insert(T, tu);
    }
    fclose(fp);
}

// ----------------- Ham save file txt-------------------
void saveTree(FILE *fp, TREE &T) {
    if (T != NULL) {
        saveTree(fp, T->pLeft);
        fprintf(fp, "%s|%s|%s|%s\n", T->data.tuTA, T->data.nghiaTV, T->data.loaiTu, T->data.viDu);
        saveTree(fp, T->pRight);
    }
}

void saveFile(TREE &T, const char *tenFile) 
{
	FILE *fp = fopen(tenFile, "w");
	if (fp) {
        saveTree(fp, T);
        fclose(fp);
    }
}

// ----------------- Ham tim node thay the --------------
void SearchStandFor(TREE &T, TNODE *p)
{
	if(T->pRight) SearchStandFor(T->pRight, p);
	else 
	{
		p->data = T->data;
		p=T;
		T=T->pLeft;
	}
}

// ------------- Ham xoa tu ra khoi tu dien -------------
void RemoveNode(TREE &T, const char *tuTA) {
    if (T == NULL) return;
    int cmp = strcmp(tuTA, T->data.tuTA);
    if (cmp < 0)
        RemoveNode(T->pLeft, tuTA);
    else if (cmp > 0)
        RemoveNode(T->pRight, tuTA);
    else 
	{
        TREE p = T;
        if (p->pLeft == NULL) T = p->pRight;
        else if (p->pRight == NULL) T = p->pLeft;
        else SearchStandFor(T->pLeft, p);
        delete(p);
    }
}

void Edit(TREE &T, const char *tuTA) {
    TREE p = SearchAV(T, tuTA);
    if (p == NULL) {
        printf("Tu khong ton tai!\n");
        return;
    }
    int chon;
    do
    {
		printf("+========================+\n");
		printf("|          Edit          |\n");
		printf("+------------------------+\n");
		printf("| 1. Nghia tu            |\n");
		printf("| 2. Loai tu             |\n");
		printf("| 3. Vi du               |\n");
		printf("| 0. Thoat               |\n");
		printf("+------------------------+\n");
		printf("Chon: ");
        scanf("%d", &chon);
        fflush(stdin);
	    switch(chon)
	    {
	    	case 1: 
	    		printf("Nhap nghia moi: "); fflush(stdin); gets(p->data.nghiaTV);
	    		break;
	    	case 2: 
	    		printf("Nhap loai tu moi: "); gets(p->data.loaiTu);
	    		break;
	    	case 3: 
	    		printf("Nhap vi du moi: "); gets(p->data.viDu);
	    		break;
		}
	} while(chon!=0);
    printf("Da cap nhat.\n");
}
// ------------------ Menu -----------------------
void menu() {
    printf("+========================================+\n");
    printf("|         TU DIEN ANH - VIET             |\n");
    printf("+========================================+\n");
    printf("| 1. Them tu                             |\n");
    printf("| 2. Tra cuu tu                          |\n");
    printf("| 3. Cap nhat                            |\n");
    printf("| 4. Xoa tu                              |\n");
    printf("| 5. Tu dien tu dong nghia               |\n");
    printf("| 6. Duyet tu dien Anh - Viet            |\n");
    printf("| 0. Thoat                               |\n");
    printf("+========================================+\n");
}


