#ifndef CRUD_MENU_H
#define CRUD_MENU_H

#define IMPLEMENT_MENU_DB
#define IMPLEMENT_CRUD_MENU

#include "../struct.h"
#include "../database/menuDb.h"

// Deklarasi fungsi
void tambahMenu(void);
void editMenu(void);
void hapusMenu(void);
void lihatSemuaMenu(void);
void konfirmasiPesanan(const char* username, int idMenu, int jumlah);
struct MenuItem* bacaMenuDariCSV(int* jumlahMenu);
void tulisMenuKeCSV(struct MenuItem* daftarMenu, int jumlahMenu);

#ifdef IMPLEMENT_CRUD_MENU


// Semua implementasi fungsi taruh di sini
void lihatSemuaMenu(void) {
    int jumlahMenu;
    struct MenuItem* daftarMenu = bacaMenuDariCSV(&jumlahMenu);
    
    if (daftarMenu == NULL) {
        printf("Error: Gagal membaca data menu\n");
        return;
    }
    
    printf("\n%s+------------------- DAFTAR MENU -------------------+%s\n", BOLD_CYAN, RESET);
    printf("%s| %-5s %-30s %-10s %-15s %-10s %-10s %-10s %-10s %-10s |%s\n", 
           BOLD_WHITE,
           "ID", "Nama", "Harga", "Kategori", "Tersedia", "Protein", "Karbo", "Lemak", "Kalori",
           RESET);
    printf("%s+---------------------------------------------------------------------------------------------------------------------+%s\n",
           BOLD_WHITE, RESET);
    
    for (int i = 0; i < jumlahMenu; i++) {
        printf("%s|%s %-5d %-30s %s%-10.2f%s %-15s %s%-10d%s %-10.2f %-10.2f %-10.2f %-10.2f %s|%s\n",
               BOLD_WHITE, RESET,
               daftarMenu[i].id,
               daftarMenu[i].nama,
               CYAN,
               daftarMenu[i].harga,
               RESET,
               daftarMenu[i].kategori,
               daftarMenu[i].tersedia ? GREEN : RED,
               daftarMenu[i].tersedia,
               RESET,
               daftarMenu[i].protein,
               daftarMenu[i].karbohidrat,
               daftarMenu[i].lemak,
               daftarMenu[i].kalori,
               BOLD_WHITE, RESET);
    }
    printf("%s+---------------------------------------------------------------------------------------------------------------------+%s\n",
           BOLD_WHITE, RESET);
    
    free(daftarMenu);
}

void tambahMenu(void) {
    int jumlahMenu;
    struct MenuItem* daftarMenu = bacaMenuDariCSV(&jumlahMenu);
    
    if (daftarMenu == NULL) {
        printf("Error: Gagal membaca data menu\n");
        return;
    }
    
    if (jumlahMenu >= MAX_MENU_ITEMS) {
        printf("Error: Jumlah menu sudah maksimal\n");
        free(daftarMenu);
        return;
    }
    
    struct MenuItem menuBaru;
    menuBaru.id = jumlahMenu + 1;
    
    do {
        printf("\n%s=== TAMBAH MENU BARU ===%s\n", BOLD_CYAN, RESET);
        printf("%sNama menu (maksimal 30 karakter):%s ", BOLD_WHITE, RESET);
        scanf(" %49[^\n]", menuBaru.nama);
        
        if (strlen(menuBaru.nama) > 30) {
            printf("%sError: Nama menu tidak boleh lebih dari 30 karakter!%s\n", BOLD_RED, RESET);
            printf("Silakan masukkan nama menu yang lebih pendek.\n");
        }
    } while (strlen(menuBaru.nama) > 30);
    
    printf("Harga: ");
    scanf("%f", &menuBaru.harga);
    
    printf("Kategori (Bulking, Diet, Sehat): ");
    scanf(" %49[^\n]", menuBaru.kategori);
    
    menuBaru.tersedia = 1; // Default tersedia
    
    printf("Protein (g): ");
    scanf("%f", &menuBaru.protein);
    
    printf("Karbohidrat (g): ");
    scanf("%f", &menuBaru.karbohidrat);
    
    printf("Lemak (g): ");
    scanf("%f", &menuBaru.lemak);
    
    menuBaru.kalori = hitungKalori(menuBaru.protein, menuBaru.karbohidrat, menuBaru.lemak);
    
    daftarMenu[jumlahMenu] = menuBaru;
    jumlahMenu++;
    
    tulisMenuKeCSV(daftarMenu, jumlahMenu);
    free(daftarMenu);
    printf("%sMenu berhasil ditambahkan!%s\n", BOLD_GREEN, RESET);
}

void editMenu(void) {
    int jumlahMenu;
    struct MenuItem* daftarMenu = bacaMenuDariCSV(&jumlahMenu);
    
    if (daftarMenu == NULL) {
        printf("Error: Gagal membaca data menu\n");
        return;
    }
    
    printf("\n%s+------------------- DAFTAR MENU -------------------+%s\n", BOLD_CYAN, RESET);
    printf("%s| %-5s %-30s %-10s %-15s %-10s %-10s %-10s %-10s %-10s |%s\n", 
           BOLD_WHITE,
           "ID", "Nama", "Harga", "Kategori", "Tersedia", "Protein", "Karbo", "Lemak", "Kalori",
           RESET);
    printf("%s+---------------------------------------------------------------------------------------------------------------------+%s\n",
           BOLD_WHITE, RESET);
    
    for (int i = 0; i < jumlahMenu; i++) {
        printf("%s|%s %-5d %-30s %s%-10.2f%s %-15s %s%-10d%s %-10.2f %-10.2f %-10.2f %-10.2f %s|%s\n",
               BOLD_WHITE, RESET,
               daftarMenu[i].id,
               daftarMenu[i].nama,
               CYAN,
               daftarMenu[i].harga,
               RESET,
               daftarMenu[i].kategori,
               daftarMenu[i].tersedia ? GREEN : RED,
               daftarMenu[i].tersedia,
               RESET,
               daftarMenu[i].protein,
               daftarMenu[i].karbohidrat,
               daftarMenu[i].lemak,
               daftarMenu[i].kalori,
               BOLD_WHITE, RESET);
    }
    printf("%s+---------------------------------------------------------------------------------------------------------------------+%s\n",
           BOLD_WHITE, RESET);
    
    int idMenu;
    printf("\n%sMasukkan ID menu yang akan diedit:%s ", BOLD_WHITE, RESET);
    scanf("%d", &idMenu);
    
    int index = -1;
    for (int i = 0; i < jumlahMenu; i++) {
        if (daftarMenu[i].id == idMenu) {
            index = i;
            break;
        }
    }
    
    if (index == -1) {
        printf("%sError: Menu dengan ID %d tidak ditemukan%s\n", BOLD_RED, idMenu, RESET);
        free(daftarMenu);
        return;
    }
    
    printf("\n%s=== EDIT MENU ===%s\n", BOLD_CYAN, RESET);
    printf("Nama menu (%s): ", daftarMenu[index].nama);
    scanf(" %49[^\n]", daftarMenu[index].nama);
    
    printf("Harga (%.2f): ", daftarMenu[index].harga);
    scanf("%f", &daftarMenu[index].harga);
    
    printf("Kategori (%s): ", daftarMenu[index].kategori);
    scanf(" %49[^\n]", daftarMenu[index].kategori);
    
    printf("Tersedia (1/0) (%d): ", daftarMenu[index].tersedia);
    scanf("%d", &daftarMenu[index].tersedia);
    
    printf("Protein (%.2f g): ", daftarMenu[index].protein);
    scanf("%f", &daftarMenu[index].protein);
    
    printf("Karbohidrat (%.2f g): ", daftarMenu[index].karbohidrat);
    scanf("%f", &daftarMenu[index].karbohidrat);
    
    printf("Lemak (%.2f g): ", daftarMenu[index].lemak);
    scanf("%f", &daftarMenu[index].lemak);
    
    daftarMenu[index].kalori = hitungKalori(daftarMenu[index].protein, 
                                           daftarMenu[index].karbohidrat, 
                                           daftarMenu[index].lemak);
    
    tulisMenuKeCSV(daftarMenu, jumlahMenu);
    free(daftarMenu);
    printf("\n%sMenu berhasil diupdate!%s\n", BOLD_GREEN, RESET);
}

void hapusMenu(void) {
    int jumlahMenu;
    struct MenuItem* daftarMenu = bacaMenuDariCSV(&jumlahMenu);
    
    if (daftarMenu == NULL) {
        printf("Error: Gagal membaca data menu\n");
        return;
    }
    
    int idMenu;
    printf("\n%sMasukkan ID menu yang akan dihapus:%s ", BOLD_WHITE, RESET);
    scanf("%d", &idMenu);
    
    int index = -1;
    for (int i = 0; i < jumlahMenu; i++) {
        if (daftarMenu[i].id == idMenu) {
            index = i;
            break;
        }
    }
    
    if (index == -1) {
        printf("%sError: Menu dengan ID %d tidak ditemukan%s\n", BOLD_RED, idMenu, RESET);
        free(daftarMenu);
        return;
    }
    
    // Geser semua menu setelah index yang dihapus
    for (int i = index; i < jumlahMenu - 1; i++) {
        daftarMenu[i] = daftarMenu[i + 1];
        daftarMenu[i].id = i + 1; // Update ID
    }
    
    jumlahMenu--;
    tulisMenuKeCSV(daftarMenu, jumlahMenu);
    free(daftarMenu);
    printf("%sMenu berhasil dihapus%s\n", BOLD_GREEN, RESET);
}

#endif
#endif