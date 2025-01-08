#ifndef CRUD_PESANAN_H
#define CRUD_PESANAN_H

#include "../database/pesananDb.h"

void lihatSemuaPesanan(void) {
    int jumlahPesanan;
    struct Order* daftarPesanan = bacaPesananDariCSV(&jumlahPesanan);
    
    if (daftarPesanan == NULL) {
        printf("Tidak ada data pesanan\n");
        return;
    }
    
    printf("\n%s=== Daftar Semua Pesanan ===%s\n", BOLD_CYAN, RESET);
    printf("%sID\tUsername\tMenu ID\tJumlah\tTotal\tStatus\tTanggal%s\n", BOLD_WHITE, RESET);
    for (int i = 0; i < jumlahPesanan; i++) {
        char* statusColor = RESET;
        if (strcmp(daftarPesanan[i].status, "pending") == 0) {
            statusColor = YELLOW;
        } else if (strcmp(daftarPesanan[i].status, "selesai") == 0) {
            statusColor = GREEN;
        } else if (strcmp(daftarPesanan[i].status, "dibatalkan") == 0) {
            statusColor = RED;
        }
        
        printf("%d\t%s\t%d\t%d\t%.2f\t%s%s%s\t%s\n",
            daftarPesanan[i].idPesanan,
            daftarPesanan[i].username,
            daftarPesanan[i].idMenu,
            daftarPesanan[i].jumlah,
            daftarPesanan[i].totalHarga,
            statusColor,
            daftarPesanan[i].status,
            RESET,
            daftarPesanan[i].tanggalPesan);
    }
    
    free(daftarPesanan);
}

void updateStatusPesanan(void) {
    int idPesanan, jumlahPesanan;
    char statusBaru[20];
    
    struct Order* daftarPesanan = bacaPesananDariCSV(&jumlahPesanan);
    if (daftarPesanan == NULL) return;
    
    printf("Masukkan ID Pesanan: ");
    scanf("%d", &idPesanan);
    
    printf("Status Baru (pending/selesai/dibatalkan): ");
    scanf("%s", statusBaru);
    
    bool ditemukan = false;
    for (int i = 0; i < jumlahPesanan; i++) {
        if (daftarPesanan[i].idPesanan == idPesanan) {
            strcpy(daftarPesanan[i].status, statusBaru);
            ditemukan = true;
            break;
        }
    }
    
    if (ditemukan) {
        tulisPesananKeCSV(daftarPesanan, jumlahPesanan);
        printf("Status pesanan berhasil diperbarui!\n");
    } else {
        printf("Pesanan tidak ditemukan!\n");
    }
    
    free(daftarPesanan);
}

void hapusPesanan(void) {
    int idPesanan, jumlahPesanan;
    
    struct Order* daftarPesanan = bacaPesananDariCSV(&jumlahPesanan);
    if (daftarPesanan == NULL) return;
    
    printf("Masukkan ID Pesanan yang akan dihapus: ");
    scanf("%d", &idPesanan);
    
    int indexHapus = -1;
    for (int i = 0; i < jumlahPesanan; i++) {
        if (daftarPesanan[i].idPesanan == idPesanan) {
            indexHapus = i;
            break;
        }
    }
    
    if (indexHapus != -1) {
        for (int i = indexHapus; i < jumlahPesanan - 1; i++) {
            daftarPesanan[i] = daftarPesanan[i + 1];
        }
        jumlahPesanan--;
        
        tulisPesananKeCSV(daftarPesanan, jumlahPesanan);
        printf("Pesanan berhasil dihapus!\n");
    } else {
        printf("Pesanan tidak ditemukan!\n");
    }
    
    free(daftarPesanan);
}

#endif 