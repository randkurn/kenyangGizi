#ifndef PESANAN_DB_H
#define PESANAN_DB_H

#include <stdbool.h>

struct Order* bacaPesananDariCSV(int* jumlahPesanan);
void tulisPesananKeCSV(struct Order* daftarPesanan, int jumlahPesanan);
bool tambahPesanan(struct Order pesanan);

#ifdef IMPLEMENT_MENU_DB

struct Order* bacaPesananDariCSV(int* jumlahPesanan) {
    FILE *fp = fopen("pesanan.csv", "r");
    if (fp == NULL) {
        printf("Error: Tidak dapat membuka file pesanan.csv\n");
        return NULL;
    }

    struct Order* daftarPesanan = malloc(MAX_ORDERS * sizeof(struct Order));
    char baris[1024];
    *jumlahPesanan = 0;
    
    // Skip header
    fgets(baris, 1024, fp);
    
    while (fgets(baris, 1024, fp)) {
        struct Order pesanan;
        char* token = strtok(baris, ";"); // Menggunakan ; sebagai separator
        
        pesanan.idPesanan = atoi(token);
        
        token = strtok(NULL, ";");
        strcpy(pesanan.username, token);
        
        token = strtok(NULL, ";");
        pesanan.idMenu = atoi(token);
        
        token = strtok(NULL, ";");
        pesanan.jumlah = atoi(token);
        
        token = strtok(NULL, ";");
        pesanan.totalHarga = atof(token);
        
        token = strtok(NULL, ";");
        strcpy(pesanan.status, token);
        
        token = strtok(NULL, ";");
        strcpy(pesanan.tanggalPesan, token);
        
        daftarPesanan[*jumlahPesanan] = pesanan;
        (*jumlahPesanan)++;
        
        if (*jumlahPesanan >= MAX_ORDERS) {
            printf("Warning: Jumlah pesanan maksimum tercapai\n");
            break;
        }
    }
    
    fclose(fp);
    return daftarPesanan;
}

// Fungsi untuk menulis pesanan ke CSV
void tulisPesananKeCSV(struct Order* daftarPesanan, int jumlahPesanan) {
    FILE *fp = fopen("pesanan.csv", "w");
    if (fp == NULL) {
        printf("Error: Tidak dapat membuka file pesanan.csv\n");
        return;
    }
    
    // Tulis header
    fprintf(fp, "ID Pesanan;Username;ID Menu;Jumlah;Total Harga;Status;Tanggal Pesan\n");
    
    // Tulis data pesanan
    for (int i = 0; i < jumlahPesanan; i++) {
        fprintf(fp, "%d;%s;%d;%d;%.2f;%s;%s\n",
            daftarPesanan[i].idPesanan,
            daftarPesanan[i].username,
            daftarPesanan[i].idMenu,
            daftarPesanan[i].jumlah,
            daftarPesanan[i].totalHarga,
            daftarPesanan[i].status,
            daftarPesanan[i].tanggalPesan);
    }
    
    fclose(fp);
}

bool tambahPesanan(struct Order pesanan) {
    int lastId = 0;
    FILE *readFile = fopen("pesanan.csv", "r");
    
    if (readFile != NULL) {
        char line[1024];
        // Skip header
        fgets(line, sizeof(line), readFile);
        
        // Baca semua baris untuk mendapatkan ID terakhir
        while (fgets(line, sizeof(line), readFile)) {
            int currentId;
            sscanf(line, "%d;", &currentId);
            if (currentId > lastId) {
                lastId = currentId;
            }
        }
        fclose(readFile);
    }

    // Set ID baru = ID terakhir + 1
    pesanan.idPesanan = lastId + 1;

    FILE *file = fopen("pesanan.csv", "a");
    if (file == NULL) {
        system("mkdir data 2> nul");
        file = fopen("pesanan.csv", "a");
        if (file == NULL) {
            printf("Error: Tidak dapat membuat file pesanan.csv\n");
            return false;
        }
    }

    // Tulis header jika file kosong
    if (lastId == 0) {
        fprintf(file, "ID Pesanan;Username;ID Menu;Jumlah;Total Harga;Status;Tanggal Pesan\n");
    }

    // Tulis data pesanan dengan \n di akhir
    fprintf(file, "%d;%s;%d;%d;%.2f;%s;%s\n",
            pesanan.idPesanan,
            pesanan.username,
            pesanan.idMenu,
            pesanan.jumlah,
            pesanan.totalHarga,
            pesanan.status,
            pesanan.tanggalPesan);

    fclose(file);
    return true;
}

#endif

#endif