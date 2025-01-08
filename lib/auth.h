#ifndef AUTH_H
#define AUTH_H

#include "struct.h"
#include "admin/admin.h"
#include "user/user.h"
#include <unistd.h>


int validasiPelangganCSV(const char* username, const char* password);
int isUsernameExists(const char* username);
void simpanPelangganCSV(const struct Pelanggan *p);
int loginPelanggan(void);
int registerPelanggan(void);
void menuAutentikasi(void);


void menuAutentikasi(void) {
    int pilihan;
    
    do {
        system("cls");
        printf(BOLD_CYAN "\n");
        printf("    ==========================================\n");
        printf("              SELAMAT DATANG DI              \n");
        printf("            SISTEM kenyangGizi               \n");
        printf("    ==========================================\n" RESET);
        
        printf(BOLD_YELLOW "\n    MENU UTAMA:\n");
        printf("    1. Login Pelanggan\n");
        printf("    2. Daftar Pelanggan\n");
        printf("    3. Login Admin\n");
        printf("    4. Keluar\n" RESET);
        
        printf(BOLD_GREEN "\n    Pilihan Anda [1-4]: " RESET);
        
        if(scanf("%d", &pilihan) != 1) {
            while(getchar() != '\n');
            printf(BOLD_RED "\n    [ERROR] Input tidak valid!\n" RESET);
            getch();
            continue;
        }
        
        switch(pilihan) {
            case 1:
                printf(ITALIC CYAN "\n    > Memproses login pelanggan...\n" RESET);
                if(loginPelanggan()) return;
                break;
            case 2:
                printf(ITALIC CYAN "\n    > Memproses pendaftaran pelanggan...\n" RESET);
                if(registerPelanggan()) return;
                break;
            case 3:
                printf(ITALIC CYAN "\n    > Memproses login admin...\n" RESET);
                if(loginAdmin()) return;
                break;
            case 4:
                printf(BOLD_YELLOW "\n    Terima kasih telah menggunakan sistem ini!\n" RESET);
                exit(0);
            default:
                printf(BOLD_RED "\n    [ERROR] Pilihan tidak valid!\n" RESET);
                getch();
        }
    } while(1);
}





// Fungsi untuk login pelanggan
int loginPelanggan(void);

// Fungsi untuk registrasi pelanggan
int registerPelanggan(void);

#endif