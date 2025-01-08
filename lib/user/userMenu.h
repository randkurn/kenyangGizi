#ifndef USER_MENU_H
#define USER_MENU_H

#include "../struct.h"
#include "../database/userDb.h"
#include "../database/pesananDb.h"

// Definisikan IMPLEMENT_STATISTIK sebelum include statistik.h
#define IMPLEMENT_STATISTIK
#include "statistik.h"

// Tambahkan prototype fungsi di sini
void hitungKesehatanPelanggan(const char* username);
void buatPesanan(const char* username);
void lihatRiwayatPesanan(const char* username);
void konfirmasiPesanan(const char* username, int idMenu, int jumlah);
void lihatMenuMakanan(void);

#ifdef IMPLEMENT_USER_MENU
void menuPelanggan(const char* username) {
    int pilihan;
    do {
        system("cls");
        printf("\n=================[ MENU PELANGGAN ]=================\n");
        printf("| 1. Lihat Profil                                 |\n");
        printf("| 2. Hitung Analisis Kesehatan                    |\n"); 
        printf("| 3. Lihat Menu Paket Makanan                     |\n");
        printf("| 4. Buat Pesanan                                 |\n");
        printf("| 5. Lihat Riwayat Pesanan                        |\n");
        printf("| 6. Keluar                                       |\n");
        printf("================================================\n");
        printf(BOLD_YELLOW "\nPilih opsi: " RESET);
        scanf("%d", &pilihan);

        switch(pilihan) {
            case 1:
                lihatProfilPelanggan(username);
                break;
            case 2: 
                hitungKesehatanPelanggan(username);
                break;
            case 3:
                lihatMenuMakanan();
                break;
            case 4:
                buatPesanan(username);
                break;
            case 5:
                lihatRiwayatPesanan(username);
                break;
            case 6:
                return;
            default:
                printf(BOLD_RED "\nPilihan tidak valid!\n" RESET);
        }
        printf(BOLD_YELLOW "\nTekan Enter untuk melanjutkan..." RESET);
        getch();
    } while(pilihan != 6);
}
void hitungKesehatanPelanggan(const char* username) {
    system("cls");
    int jumlahPelanggan;
    struct Pelanggan* daftarPelanggan = bacaPelangganDariCSV(&jumlahPelanggan);
    struct DataKesehatan data;
    
    if (daftarPelanggan == NULL) {
        printf("\nError: Tidak dapat membaca data pelanggan!\n");
        return;
    }
    
    // Cari data pelanggan berdasarkan username
    int found = 0;
    for(int i = 0; i < jumlahPelanggan; i++) {
        if(strcmp(daftarPelanggan[i].username, username) == 0) {
            // Hitung semua metrik kesehatan
            data.bmi = hitungBMI(daftarPelanggan[i].beratBadan, daftarPelanggan[i].tinggiBadan);
            data.bmr = hitungBMR(daftarPelanggan[i].beratBadan, daftarPelanggan[i].tinggiBadan, 
                                daftarPelanggan[i].usia, daftarPelanggan[i].jenisKelamin);
            data.tdee = hitungTDEE(data.bmr, 
                daftarPelanggan[i].tingkatAktivitas,
                daftarPelanggan[i].nilaiPolaHidup);
            data.targetKalori = hitungTargetKalori(data.tdee, daftarPelanggan[i].tujuanProgram);
            
            // Tampilkan rekomendasi
            tampilkanRekomendasi(data, daftarPelanggan[i].tujuanProgram);
            found = 1;
            break;
        }
    }
    
    if(!found) {
        printf("\nError: Data pelanggan tidak ditemukan!\n");
    }
    
    free(daftarPelanggan);
}

void lihatMenuMakanan() {
    int jumlahMenu;
    struct MenuItem* daftarMenu = bacaMenuDariCSV(&jumlahMenu);
    char kembali;
    char kategoriTerpilih[50] = "";
    char cariNama[50] = "";
    int pilihSort;
    
    if (daftarMenu == NULL) {
        printf(BOLD_RED "\n[ERROR] Tidak dapat membaca data menu!\n" RESET);
        return;
    }
    
    do {
        system("cls");
        printf("\n=================== MENU MAKANAN ===================\n");
        printf("1. Tampilkan Semua Menu");
        printf("\n2. Cari Menu");
        printf("\n3. Urutkan Menu");
        printf("\nPilih opsi (1-3): ");
        int opsi;
        scanf("%d", &opsi);
        
        if (opsi == 2) {
            printf("\nMasukkan nama menu yang dicari: ");
            scanf(" %[^\n]s", cariNama);
        } else if (opsi == 3) {
            printf("\n1. Urutkan berdasarkan harga (terendah-tertinggi)");
            printf("\n2. Urutkan berdasarkan kalori (terendah-tertinggi)");
            printf("\nPilih pengurutan: ");
            scanf("%d", &pilihSort);
            
            // Bubble sort
            for (int i = 0; i < jumlahMenu-1; i++) {
                for (int j = 0; j < jumlahMenu-i-1; j++) {
                    if (pilihSort == 1) {
                        if (daftarMenu[j].harga > daftarMenu[j+1].harga) {
                            struct MenuItem temp = daftarMenu[j];
                            daftarMenu[j] = daftarMenu[j+1];
                            daftarMenu[j+1] = temp;
                        }
                    } else if (pilihSort == 2) {
                        if (daftarMenu[j].kalori > daftarMenu[j+1].kalori) {
                            struct MenuItem temp = daftarMenu[j];
                            daftarMenu[j] = daftarMenu[j+1];
                            daftarMenu[j+1] = temp;
                        }
                    }
                }
            }
        }

        printf("\n=================== DAFTAR MENU ===================\n");
        printf(BOLD_CYAN "+----+--------------------------------+---------------+-------------+\n");
        printf("| ID |             Nama Menu          |    Harga     |   Kalori    |\n");
        printf("+----+--------------------------------+---------------+-------------+\n" RESET);
        
        int menuDitemukan = 0;
        for(int i = 0; i < jumlahMenu; i++) {
            if(daftarMenu[i].tersedia && 
               (opsi != 2 || strstr(strlwr(daftarMenu[i].nama), strlwr(cariNama)) != NULL)) {
                
                printf(WHITE "| %-2d | %-30s | Rp.%-9.2f | %-10.2f |\n",
                    daftarMenu[i].id, 
                    daftarMenu[i].nama, 
                    daftarMenu[i].harga, 
                    daftarMenu[i].kalori);
                menuDitemukan = 1;
            }
        }
        printf(BOLD_CYAN "+----+--------------------------------+---------------+-------------+\n" RESET);

        if(!menuDitemukan) {
            printf(BOLD_RED "\nTidak ada menu yang tersedia.\n" RESET);
        }

        printf(BOLD_YELLOW "\nKembali ke menu awal? (Y/N): " RESET);
        scanf(" %c", &kembali);
        
    } while(toupper(kembali) == 'N');
    
    free(daftarMenu);
}

void buatPesanan(const char* username) {
    system("cls");
    int jumlahMenu, jumlahPelanggan;
    struct MenuItem* daftarMenu = bacaMenuDariCSV(&jumlahMenu);
    struct Pelanggan* daftarPelanggan = bacaPelangganDariCSV(&jumlahPelanggan);
    struct DataKesehatan data;
    int pilihan, jumlah;
    
    if (daftarMenu == NULL || daftarPelanggan == NULL) {
        printf(BOLD_RED "\nError: Tidak dapat membaca data!\n" RESET);
        return;
    }

    // Cari data pelanggan dan hitung rekomendasi kalori
    int tujuanProgram = 0;
    for(int i = 0; i < jumlahPelanggan; i++) {
        if(strcmp(daftarPelanggan[i].username, username) == 0) {
            data.bmr = hitungBMR(daftarPelanggan[i].beratBadan, daftarPelanggan[i].tinggiBadan, 
                                daftarPelanggan[i].usia, daftarPelanggan[i].jenisKelamin);
            data.tdee = hitungTDEE(data.bmr, 
                daftarPelanggan[i].tingkatAktivitas,
                daftarPelanggan[i].nilaiPolaHidup);
            data.targetKalori = hitungTargetKalori(data.tdee, daftarPelanggan[i].tujuanProgram);
            tujuanProgram = daftarPelanggan[i].tujuanProgram;
            break;
        }
    }

    // Tampilkan menu dengan rekomendasi
    printf("\n=================== MENU MAKANAN ===================\n");
    printf("Target Kalori Harian Anda: %.2f kal\n", data.targetKalori);
    if(tujuanProgram == 2) { // Bulking
        printf("Program: Bulking (Penambahan Massa Otot)\n");
    } else if(tujuanProgram == 1) { // Cutting
        printf("Program: Cutting (Penurunan Berat Badan)\n");
    } else { // Maintenance
        printf("Program: Maintenance (Menjaga Berat Badan)\n");
    }
    printf("------------------------------------------------------------\n");
    printf("%-5s %-30s %-13s %-10s %s\n", "ID", "Nama", "Harga", "Kalori", "Rekomendasi");
    printf("------------------------------------------------------------\n");
    
    for(int i = 0; i < jumlahMenu; i++) {
        if(daftarMenu[i].tersedia) {
            char rekomendasi[50] = "";
            
            // Kriteria rekomendasi berdasarkan tujuan program
            if(tujuanProgram == 2) { // Bulking
                // Rekomendasi menu dengan kalori dan protein tinggi
                if(daftarMenu[i].kalori >= data.targetKalori/3) {
                    strcpy(rekomendasi, BOLD_GREEN "[RECOMMENDED]" RESET);
                }
            } else if(tujuanProgram == 1) { // Cutting
                // Rekomendasi menu dengan kalori rendah tapi protein cukup
                if(daftarMenu[i].kalori <= data.targetKalori/4) {
                    strcpy(rekomendasi, BOLD_GREEN "[RECOMMENDED]" RESET);
                }
            } else { // Maintenance
                // Rekomendasi menu dengan kalori seimbang
                if(daftarMenu[i].kalori <= data.targetKalori/3) {
                    strcpy(rekomendasi, BOLD_GREEN "[RECOMMENDED]" RESET);
                }
            }
            
            printf("%-5d%-30sRp %-12.2f%-10.2f %s\n",
                daftarMenu[i].id, 
                daftarMenu[i].nama, 
                daftarMenu[i].harga, 
                daftarMenu[i].kalori,
                rekomendasi);
        }
    }
    printf("\n" BOLD_YELLOW "Note:  = Menu yang sesuai dengan target kalori Anda" RESET);
    
    printf("\n\nMasukkan ID Menu yang ingin dipesan: ");
    scanf("%d", &pilihan);
    printf("Jumlah pesanan: ");
    scanf("%d", &jumlah);
    
    konfirmasiPesanan(username, pilihan, jumlah);
    
    free(daftarMenu);
    free(daftarPelanggan);
}

void lihatRiwayatPesanan(const char* username) {
    system("cls");
    int jumlahPesanan;
    struct Order* daftarPesanan = bacaPesananDariCSV(&jumlahPesanan);
    char kembali;
    
    if (daftarPesanan == NULL) {
        printf(BOLD_RED "\n[ERROR] Tidak dapat membaca data pesanan!\n" RESET);
        return;
    }
    
    do {
        printf("\n=================== RIWAYAT PESANAN ===================\n");
        printf(BOLD_CYAN "+----+------------+--------+------------+------------+----------------+\n");
        printf("| ID |  ID Menu  | Jumlah |   Total    |   Status   |    Tanggal     |\n");
        printf("+----+------------+--------+------------+------------+----------------+\n" RESET);
        
        for(int i = 0; i < jumlahPesanan; i++) {
            if(strcmp(daftarPesanan[i].username, username) == 0) {
                char* statusColor = strcmp(daftarPesanan[i].status, "Selesai") == 0 ? BOLD_GREEN :
                                  strcmp(daftarPesanan[i].status, "Pending") == 0 ? BOLD_YELLOW : WHITE;
                
                printf(WHITE "| %-2d | %-10d | %-6d | Rp.%-7.2f | %s%-10s" WHITE " | %-14s |\n" RESET,
                       daftarPesanan[i].idPesanan, 
                       daftarPesanan[i].idMenu,
                       daftarPesanan[i].jumlah, 
                       daftarPesanan[i].totalHarga,
                       statusColor,
                       daftarPesanan[i].status,
                       daftarPesanan[i].tanggalPesan);
            }
        }
        printf(BOLD_CYAN "+----+------------+--------+------------+------------+----------------+\n" RESET);

        printf("\n======================================================\n");
        
        printf(BOLD_YELLOW "\nKembali ke menu awal? (Y/N): " RESET);
        scanf(" %c", &kembali);
        
    } while(toupper(kembali) == 'N');
    
    free(daftarPesanan);
}
void konfirmasiPesanan(const char* username, int idMenu, int jumlah) {
    system("cls");
    int jumlahMenu;
    struct MenuItem* daftarMenu = bacaMenuDariCSV(&jumlahMenu);
    char konfirmasi;
    
    if (daftarMenu == NULL) {
        printf("\nError: Tidak dapat membaca data menu!\n");
        return;
    }
    
    // Cari menu berdasarkan ID
    int found = 0;
    struct MenuItem menuDipesan;
    for(int i = 0; i < jumlahMenu; i++) {
        if(daftarMenu[i].id == idMenu && daftarMenu[i].tersedia) {
            menuDipesan = daftarMenu[i];
            found = 1;
            break;
        }
    }
    
    if(!found) {
        printf("\nMenu dengan ID %d tidak ditemukan atau tidak tersedia!\n", idMenu);
        free(daftarMenu);
        return;
    }
    
    // Tampilkan detail pesanan
    float totalHarga = menuDipesan.harga * jumlah;
    printf("\n=================[ DETAIL PESANAN ]=================\n");
    printf("| Menu        : %-30s |\n", menuDipesan.nama);
    printf("| Jumlah      : %-30d |\n", jumlah);
    printf("| Harga/item  : Rp %-27.2f |\n", menuDipesan.harga);
    printf("| Total Harga : Rp %-27.2f |\n", totalHarga);
    printf("================================================\n");
    
    printf(BOLD_YELLOW "\nKonfirmasi pesanan? (Y/N): " RESET);
    scanf(" %c", &konfirmasi);
    
    if(toupper(konfirmasi) == 'Y') {
        // Gunakan fungsi dari pesananDb
        struct Order pesananBaru;
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        
        pesananBaru.idPesanan = time(NULL);
        strcpy(pesananBaru.username, username);
        pesananBaru.idMenu = idMenu;
        pesananBaru.jumlah = jumlah;
        pesananBaru.totalHarga = totalHarga;
        strcpy(pesananBaru.status, "Pending");
        sprintf(pesananBaru.tanggalPesan, "%d-%02d-%02d %02d:%02d",
                tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, 
                tm.tm_hour, tm.tm_min);
        
        // Tambahkan pesanan menggunakan fungsi dari pesananDb
        if(tambahPesanan(pesananBaru)) {
            printf(BOLD_GREEN "\n✓ Pesanan berhasil disimpan!\n" RESET);
        } else {
            printf(BOLD_RED "\n✗ Gagal menyimpan pesanan!\n" RESET);
        }
    } else {
        printf(BOLD_RED "\n✗ Pesanan dibatalkan.\n" RESET);
    }
    
    free(daftarMenu);
}
#endif

#endif