#ifndef STATISTIK_ADMIN_H
#define STATISTIK_ADMIN_H

#include "../database/userDb.h"
#include "../database/pesananDb.h"
#include "../database/menuDb.h"

void statistikPelanggan(void) {
    int jumlahPelanggan;
    struct Pelanggan* daftarPelanggan = bacaPelangganDariCSV(&jumlahPelanggan);
    
    if (daftarPelanggan == NULL) {
        printf("Error: Tidak dapat membaca data pelanggan\n");
        return;
    }

    // Inisialisasi variabel statistik
    int totalPelanggan = jumlahPelanggan;
    int pelangganAktif = 0;
    int pelangganPria = 0, pelangganWanita = 0;
    int tujuanTurunBB = 0, tujuanNaikBB = 0, tujuanSehat = 0;
    float rataUsia = 0, rataBB = 0, rataTB = 0;

    // Hitung statistik
    for(int i = 0; i < jumlahPelanggan; i++) {
        if(daftarPelanggan[i].loginCount > 0) pelangganAktif++;
        if(daftarPelanggan[i].jenisKelamin == 'L') pelangganPria++;
        if(daftarPelanggan[i].jenisKelamin == 'P') pelangganWanita++;
        
        switch(daftarPelanggan[i].tujuanProgram) {
            case 1: tujuanTurunBB++; break;
            case 2: tujuanNaikBB++; break;
            case 3: tujuanSehat++; break;
        }

        rataUsia += daftarPelanggan[i].usia;
        rataBB += daftarPelanggan[i].beratBadan;
        rataTB += daftarPelanggan[i].tinggiBadan;
    }

    // Hitung rata-rata
    if(totalPelanggan > 0) {
        rataUsia /= totalPelanggan;
        rataBB /= totalPelanggan;
        rataTB /= totalPelanggan;
    }

    // Tampilkan statistik
    printf("\n%s=== Statistik Pelanggan ===%s\n", BOLD_CYAN, RESET);
    printf("%sTotal Pelanggan      : %s%d\n", BOLD_WHITE, RESET, totalPelanggan);
    printf("%sPelanggan Aktif      : %s%d\n", BOLD_WHITE, RESET, pelangganAktif);
    printf("%sPelanggan Pria       : %s%d\n", BOLD_WHITE, RESET, pelangganPria);
    printf("%sPelanggan Wanita     : %s%d\n", BOLD_WHITE, RESET, pelangganWanita);
    printf("%sRata-rata Usia       : %s%.1f tahun\n", BOLD_WHITE, RESET, rataUsia);
    printf("%sRata-rata Berat Badan: %s%.1f kg\n", BOLD_WHITE, RESET, rataBB);
    printf("%sRata-rata Tinggi     : %s%.1f cm\n", BOLD_WHITE, RESET, rataTB);
    printf("\n%sTujuan Program:%s\n", BOLD_CYAN, RESET);
    printf("%s- Turun Berat Badan  : %s%d orang\n", BOLD_WHITE, RESET, tujuanTurunBB);
    printf("%s- Naik Berat Badan   : %s%d orang\n", BOLD_WHITE, RESET, tujuanNaikBB);
    printf("%s- Pola Hidup Sehat   : %s%d orang\n", BOLD_WHITE, RESET, tujuanSehat);

    free(daftarPelanggan);
}

void statistikPesanan(void) {
    int jumlahPesanan;
    struct Order* daftarPesanan = bacaPesananDariCSV(&jumlahPesanan);
    
    if (daftarPesanan == NULL) {
        printf("Error: Tidak dapat membaca data pesanan\n");
        return;
    }

    // Inisialisasi variabel statistik
    int totalPesanan = jumlahPesanan;
    int pesananPending = 0, pesananSelesai = 0, pesananBatal = 0;
    float totalPendapatan = 0;

    // Hitung statistik
    for(int i = 0; i < jumlahPesanan; i++) {
        if(strcmp(daftarPesanan[i].status, "pending") == 0) pesananPending++;
        else if(strcmp(daftarPesanan[i].status, "selesai") == 0) {
            pesananSelesai++;
            totalPendapatan += daftarPesanan[i].totalHarga;
        }
        else if(strcmp(daftarPesanan[i].status, "dibatalkan") == 0) pesananBatal++;
    }

    // Tampilkan statistik
    printf("\n=== Statistik Pesanan ===\n");
    printf("Total Pesanan     : %d\n", totalPesanan);
    printf("Pesanan Pending   : %d\n", pesananPending);
    printf("Pesanan Selesai   : %d\n", pesananSelesai);
    printf("Pesanan Dibatalkan: %d\n", pesananBatal);
    printf("Total Pendapatan  : Rp %.2f\n", totalPendapatan);

    free(daftarPesanan);
}

void statistikMenu(void) {
    int jumlahMenu;
    struct MenuItem* daftarMenu = bacaMenuDariCSV(&jumlahMenu);
    
    if (daftarMenu == NULL) {
        printf("Error: Tidak dapat membaca data menu\n");
        return;
    }

    // Inisialisasi variabel statistik
    int totalMenu = jumlahMenu;
    int menuTersedia = 0;
    float rataHarga = 0, rataKalori = 0;
    float maxHarga = 0, minHarga = 999999999;
    float maxKalori = 0, minKalori = 999999999;

    // Hitung statistik
    for(int i = 0; i < jumlahMenu; i++) {
        if(daftarMenu[i].tersedia) menuTersedia++;
        
        rataHarga += daftarMenu[i].harga;
        rataKalori += daftarMenu[i].kalori;
        
        if(daftarMenu[i].harga > maxHarga) maxHarga = daftarMenu[i].harga;
        if(daftarMenu[i].harga < minHarga) minHarga = daftarMenu[i].harga;
        
        if(daftarMenu[i].kalori > maxKalori) maxKalori = daftarMenu[i].kalori;
        if(daftarMenu[i].kalori < minKalori) minKalori = daftarMenu[i].kalori;
    }

    // Hitung rata-rata
    if(totalMenu > 0) {
        rataHarga /= totalMenu;
        rataKalori /= totalMenu;
    }

    // Tampilkan statistik
    printf("\n=== Statistik Menu ===\n");
    printf("Total Menu        : %d\n", totalMenu);
    printf("Menu Tersedia     : %d\n", menuTersedia);
    printf("Menu Tidak Tersedia: %d\n", totalMenu - menuTersedia);
    printf("\nStatistik Harga:\n");
    printf("- Rata-rata       : Rp %.2f\n", rataHarga);
    printf("- Tertinggi       : Rp %.2f\n", maxHarga);
    printf("- Terendah        : Rp %.2f\n", minHarga);
    printf("\nStatistik Kalori:\n");
    printf("- Rata-rata       : %.2f kal\n", rataKalori);
    printf("- Tertinggi       : %.2f kal\n", maxKalori);
    printf("- Terendah        : %.2f kal\n", minKalori);

    free(daftarMenu);
}

#endif 