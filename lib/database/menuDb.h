#ifndef MENU_DB_H
#define MENU_DB_H

#include "../struct.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <time.h>
#include <ctype.h>

#define MAX_MENU_ITEMS 100

struct MenuItem* bacaMenuDariCSV(int* jumlahMenu);
void tulisMenuKeCSV(struct MenuItem* daftarMenu, int jumlahMenu);
int validasiMenu(struct MenuItem menu);
void inisialisasiMenu(struct MenuItem* menu);

#ifdef IMPLEMENT_MENU_DB

float hitungKalori(float protein, float karbohidrat, float lemak) {
    // 1g protein = 4 kalori
    // 1g karbohidrat = 4 kalori
    // 1g lemak = 9 kalori
    return (protein * 4) + (karbohidrat * 4) + (lemak * 9);
}

struct MenuItem* bacaMenuDariCSV(int* jumlahMenu) {
    FILE *fp = fopen("menu.csv", "r");
    if (fp == NULL) {
        // Buat file baru jika belum ada
        fp = fopen("menu.csv", "w");
        if (fp == NULL) {
            printf("Error: Tidak dapat membuat file menu.csv\n");
            return NULL;
        }
        // Tulis header untuk file baru
        fprintf(fp, "ID;Nama Menu;Harga;Kategori;Tersedia;Protein (g);Karbohidrat (g);Lemak (g)\n");
        fclose(fp);
        
        // Alokasi memori untuk array kosong
        struct MenuItem* daftarMenu = (struct MenuItem*)malloc(MAX_MENU_ITEMS * sizeof(struct MenuItem));
        if (daftarMenu == NULL) {
            printf("Error: Gagal mengalokasikan memori\n");
            return NULL;
        }
        *jumlahMenu = 0;
        return daftarMenu;
    }

    struct MenuItem* daftarMenu = (struct MenuItem*)malloc(MAX_MENU_ITEMS * sizeof(struct MenuItem));
    if (daftarMenu == NULL) {
        printf("Error: Gagal mengalokasikan memori\n");
        fclose(fp);
        return NULL;
    }

    char baris[1024];
    *jumlahMenu = 0;
    
    // Skip baris header
    fgets(baris, 1024, fp);
    
    while (fgets(baris, 1024, fp)) {
        struct MenuItem menu;
        inisialisasiMenu(&menu);  // Inisialisasi menu baru
        
        char* token = strtok(baris, ";");
        if (token == NULL) {
            continue;  // Skip baris kosong
        }
        
        // Parsing setiap kolom
        menu.id = atoi(token);
        
        token = strtok(NULL, ";");
        strcpy(menu.nama, token);
        
        token = strtok(NULL, ";");
        menu.harga = atof(token);
        
        token = strtok(NULL, ";");
        strcpy(menu.kategori, token);
        
        token = strtok(NULL, ";");
        menu.tersedia = atoi(token);
        
        token = strtok(NULL, ";");
        menu.protein = atof(token);
        
        token = strtok(NULL, ";");
        menu.karbohidrat = atof(token);
        
        token = strtok(NULL, ";");
        menu.lemak = atof(token);
        
        // Hitung kalori berdasarkan makronutrien
        menu.kalori = hitungKalori(menu.protein, menu.karbohidrat, menu.lemak);
        
        // Validasi data menu sebelum menambahkan
        if (!validasiMenu(menu)) {
            printf("Warning: Data menu tidak valid, melewati baris\n");
            continue;
        }
        
        // Tambahkan ke array
        daftarMenu[*jumlahMenu] = menu;
        (*jumlahMenu)++;
        
        // Cek apakah array penuh
        if (*jumlahMenu >= MAX_MENU_ITEMS) {
            printf("Warning: Jumlah menu maksimum tercapai\n");
            break;
        }
    }
    
    fclose(fp);
    return daftarMenu;
}
// Fungsi untuk menulis menu ke CSV
void tulisMenuKeCSV(struct MenuItem* daftarMenu, int jumlahMenu) {
    FILE *fp = fopen("menu.csv", "w");
    if (fp == NULL) {
        printf("Error: Tidak dapat membuka file menu.csv\n");
        return;
    }
    
    // Tulis header dengan format yang mudah dibaca di Excel
    fprintf(fp, "ID;Nama Menu;Harga;Kategori;Tersedia;Protein (g);Karbohidrat (g);Lemak (g)\n");
    
    // Tulis data menu
    for (int i = 0; i < jumlahMenu; i++) {
        fprintf(fp, "%d;%s;%.2f;%s;%d;%.2f;%.2f;%.2f\n",
            daftarMenu[i].id,
            daftarMenu[i].nama,
            daftarMenu[i].harga,
            daftarMenu[i].kategori,
            daftarMenu[i].tersedia,
            daftarMenu[i].protein,
            daftarMenu[i].karbohidrat,
            daftarMenu[i].lemak);
    }
    
    fclose(fp);
    printf("Menu berhasil disimpan ke file menu.csv\n");
}

int validasiMenu(struct MenuItem menu) {
    if (menu.id <= 0 || 
        strlen(menu.nama) == 0 || 
        menu.harga < 0 || 
        strlen(menu.kategori) == 0 ||
        menu.protein < 0 || 
        menu.karbohidrat < 0 || 
        menu.lemak < 0) {
        return 0;
    }
    return 1;
}

void inisialisasiMenu(struct MenuItem* menu) {
    menu->id = 0;
    menu->nama[0] = '\0';
    menu->harga = 0;
    menu->kategori[0] = '\0';
    menu->tersedia = 0;
    menu->protein = 0;
    menu->karbohidrat = 0;
    menu->lemak = 0;
    menu->kalori = 0;
}

#endif

#endif