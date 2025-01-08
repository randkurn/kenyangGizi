#ifndef ADMIN_H
#define ADMIN_H


#include "menuadmin.h"

int loginAdmin(void);



// Implementasi fungsi loginAdmin
int loginAdmin(void) {
    struct Admin admin = {"admin", "admin123"}; // kredensial default
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    int percobaan = 0;
    
    do {
        system("cls");
        printf("\n%s=== Login Admin ===%s\n", BOLD_CYAN, RESET);
        
        // Bersihkan buffer
        while(getchar() != '\n');
        
        printf("%sUsername:%s ", BOLD_WHITE, RESET);
        if(fgets(username, sizeof(username), stdin)) {
            username[strcspn(username, "\n")] = 0; // Hapus newline
        }
        
        printf("%sPassword:%s ", BOLD_WHITE, RESET);
        if(fgets(password, sizeof(password), stdin)) {
            password[strcspn(password, "\n")] = 0; // Hapus newline
        }
        
        if(strcmp(username, admin.username) == 0 && strcmp(password, admin.password) == 0) {
            printf("\n%sLogin admin berhasil!%s\n", BOLD_GREEN, RESET);
            printf("%sSelamat datang, Admin!%s\n", BOLD_CYAN, RESET);
            getch();
            menuAdmin();
            return 1;
        } else {
            printf("\n%sUsername atau password salah!%s\n", BOLD_RED, RESET);
            printf("%sSisa percobaan: %d%s\n", YELLOW, 3 - percobaan, RESET);
            percobaan++;
            if(percobaan < 3) {
                printf("Coba lagi? (Y/N): ");
                char lanjut;
                scanf(" %c", &lanjut);
                if(toupper(lanjut) != 'Y') break;
            }
        }
    } while(percobaan < 3);
    
    if(percobaan >= 3) {
        printf("\n%sTerlalu banyak percobaan gagal!%s\n", BOLD_RED, RESET);
        printf("%sSilakan coba lagi nanti.%s\n", BOLD_CYAN, RESET);
        getch();
    }
    return 0;
}

#endif
