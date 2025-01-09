#ifndef CRUDUSER_H
#define CRUDUSER_H

#include "../struct.h"
#include "../database/userDb.h"

// Deklarasi semua fungsi di awal
void lihatDataPelanggan(void);
void hapusDataPelanggan(void);
void editDataPelanggan(void);
void tampilkanDataPelanggan(struct Pelanggan* daftarPelanggan, int jumlahPelanggan);
void cariDataPelanggan(struct Pelanggan* daftarPelanggan, int jumlahPelanggan, char* keyword);
void urutkanDataPelanggan(struct Pelanggan* daftarPelanggan, int jumlahPelanggan, int kriteria);

// Pindahkan semua implementasi fungsi ke dalam #ifdef
#ifdef IMPLEMENT_CRUD_USER
// Semua implementasi fungsi taruh di sini
void lihatDataPelanggan(void) {
    int jumlahPelanggan;
    struct Pelanggan* daftarPelanggan = bacaPelangganDariCSV(&jumlahPelanggan);
    char kembali;
    char pilihan;
    char keyword[50];
    int kriteriaSorting;
    
    if (daftarPelanggan == NULL) {
        printf("\nError: Tidak dapat membaca data pelanggan!\n");
        return;
    }

    do {
        printf("\n%s=== MENU LIHAT DATA ===%s\n", BOLD_CYAN, RESET);
        printf("1. Lihat Semua Data\n");
        printf("2. Cari Data\n");
        printf("3. Urutkan Data\n");
        printf("4. Kembali\n");
        printf("\nPilihan: ");
        scanf(" %c", &pilihan);

        switch(pilihan) {
            case '1':
                tampilkanDataPelanggan(daftarPelanggan, jumlahPelanggan);
                break;
                
            case '2':
                printf("\nMasukkan kata kunci pencarian: ");
                scanf(" %[^\n]s", keyword);
                cariDataPelanggan(daftarPelanggan, jumlahPelanggan, keyword);
                break;
                
            case '3':
                printf("\n%sPilih kriteria pengurutan:%s\n", BOLD_CYAN, RESET);
                printf("1. Nama\n");
                printf("2. Username\n");
                printf("3. Usia\n");
                printf("4. Berat Badan\n");
                printf("5. Tinggi Badan\n");
                printf("Pilihan: ");
                scanf("%d", &kriteriaSorting);
                urutkanDataPelanggan(daftarPelanggan, jumlahPelanggan, kriteriaSorting);
                tampilkanDataPelanggan(daftarPelanggan, jumlahPelanggan);
                break;
                
            case '4':
                free(daftarPelanggan);
                return;
        }
        
        printf("\nKembali ke menu lihat data? (Y/N): ");
        scanf(" %c", &kembali);
        
    } while(toupper(kembali) == 'Y');
    
    free(daftarPelanggan);
}

// Fungsi helper untuk menampilkan data
void tampilkanDataPelanggan(struct Pelanggan* daftarPelanggan, int jumlahPelanggan) {
    if (jumlahPelanggan == 0) {
        printf("\n%sBelum ada data pelanggan.%s\n", BOLD_YELLOW, RESET);
        return;
    }

    printf("\n%s=== DATA PELANGGAN ===%s\n", BOLD_CYAN, RESET);
    printf("%s%-20s%-30s%-15s%-10s%-10s%-8s%-15s%s\n",
           BOLD_WHITE,
           "USERNAME", "NAMA", "TELEPON", "BERAT", "TINGGI", "USIA", "JENIS KELAMIN",
           RESET);
    printf("%s------------------------------------------------------------------------------------%s\n",
           BOLD_WHITE, RESET);
    
    for(int i = 0; i < jumlahPelanggan; i++) {
        printf("%-20s%-30s%-15s%s%-10.1f%-10.1f%-8d%s%-15c\n",
            daftarPelanggan[i].username,
            daftarPelanggan[i].nama,
            daftarPelanggan[i].telepon,
            CYAN,
            daftarPelanggan[i].beratBadan,
            daftarPelanggan[i].tinggiBadan,
            daftarPelanggan[i].usia,
            RESET,
            daftarPelanggan[i].jenisKelamin);
    }
    
    printf("\n%sInformasi Tambahan:%s\n", BOLD_CYAN, RESET);
    printf("%sTingkat Aktivitas: %s1=Ringan, 2=Sedang, 3=Berat\n", BOLD_WHITE, RESET);
    printf("%sTujuan Program: %s1=Turun BB, 2=Naik BB, 3=Hidup Sehat\n", BOLD_WHITE, RESET);
}

// Fungsi untuk mencari data
void cariDataPelanggan(struct Pelanggan* daftarPelanggan, int jumlahPelanggan, char* keyword) {
    struct Pelanggan hasilPencarian[MAX_MENU_ITEMS];
    int jumlahHasil = 0;
    
    for(int i = 0; i < jumlahPelanggan; i++) {
        if(strstr(strlwr(daftarPelanggan[i].nama), strlwr(keyword)) != NULL ||
           strstr(strlwr(daftarPelanggan[i].username), strlwr(keyword)) != NULL ||
           strstr(daftarPelanggan[i].telepon, keyword) != NULL) {
            hasilPencarian[jumlahHasil++] = daftarPelanggan[i];
        }
    }
    
    tampilkanDataPelanggan(hasilPencarian, jumlahHasil);
}

// Fungsi untuk mengurutkan data
void urutkanDataPelanggan(struct Pelanggan* daftarPelanggan, int jumlahPelanggan, int kriteria) {
    for(int i = 0; i < jumlahPelanggan-1; i++) {
        for(int j = 0; j < jumlahPelanggan-i-1; j++) {
            int tukar = 0;
            
            switch(kriteria) {
                case 1: // Nama
                    tukar = strcmp(daftarPelanggan[j].nama, daftarPelanggan[j+1].nama) > 0;
                    break;
                case 2: // Username
                    tukar = strcmp(daftarPelanggan[j].username, daftarPelanggan[j+1].username) > 0;
                    break;
                case 3: // Usia
                    tukar = daftarPelanggan[j].usia > daftarPelanggan[j+1].usia;
                    break;
                case 4: // Berat Badan
                    tukar = daftarPelanggan[j].beratBadan > daftarPelanggan[j+1].beratBadan;
                    break;
                case 5: // Tinggi Badan
                    tukar = daftarPelanggan[j].tinggiBadan > daftarPelanggan[j+1].tinggiBadan;
                    break;
            }
            
            if(tukar) {
                struct Pelanggan temp = daftarPelanggan[j];
                daftarPelanggan[j] = daftarPelanggan[j+1];
                daftarPelanggan[j+1] = temp;
            }
        }
    }
}

// Modifikasi fungsi hapusDataPelanggan
void hapusDataPelanggan(void) {
    int jumlahPelanggan;
    struct Pelanggan* daftarPelanggan = bacaPelangganDariCSV(&jumlahPelanggan);
    char username[MAX_USERNAME];
    char konfirmasi;
    int ditemukan;
    
    if (daftarPelanggan == NULL) {
        printf("\n%sError: Gagal membaca data pelanggan!%s\n", BOLD_RED, RESET);
        return;
    }

    do {
        system("cls"); // Bersihkan layar
        tampilkanDataPelanggan(daftarPelanggan, jumlahPelanggan);
        ditemukan = 0;
        
        printf("\n%sMasukkan username pelanggan yang akan dihapus (0 untuk batal):%s ", BOLD_WHITE, RESET);
        scanf("%s", username);
        
        if (strcmp(username, "0") == 0) {
            free(daftarPelanggan);
            return;
        }
        
        // Konfirmasi penghapusan
        printf("\n%sAnda yakin ingin menghapus user '%s'? (Y/N):%s ", BOLD_YELLOW, username, RESET);
        scanf(" %c", &konfirmasi);
        
        if (toupper(konfirmasi) != 'Y') {
            printf("\n%sPenghapusan dibatalkan.%s\n", BOLD_YELLOW, RESET);
            continue;
        }
        
        struct Pelanggan* tempPelanggan = malloc(MAX_MENU_ITEMS * sizeof(struct Pelanggan));
        if (tempPelanggan == NULL) {
            printf("\n%sError: Gagal mengalokasi memori!%s\n", BOLD_RED, RESET);
            free(daftarPelanggan);
            return;
        }
        
        int newCount = 0;
        for(int i = 0; i < jumlahPelanggan; i++) {
            if(strcmp(daftarPelanggan[i].username, username) != 0) {
                tempPelanggan[newCount++] = daftarPelanggan[i];
            } else {
                ditemukan = 1;
            }
        }

        if(ditemukan) {
            tulisPelangganKeCSV(tempPelanggan, newCount);
            printf("\n%sData pelanggan berhasil dihapus!%s\n", BOLD_GREEN, RESET);
        } else {
            printf("\n%sPelanggan dengan username '%s' tidak ditemukan!%s\n", BOLD_RED, username, RESET);
        }
        
        free(tempPelanggan);
        
        printf("\nHapus data pelanggan lain? (Y/N): ");
        scanf(" %c", &konfirmasi);
        
    } while(toupper(konfirmasi) == 'Y');
    
    free(daftarPelanggan);
}
// Modifikasi fungsi editDataPelanggan
void editDataPelanggan() {
    int jumlahPelanggan;
    struct Pelanggan* daftarPelanggan = bacaPelangganDariCSV(&jumlahPelanggan);
    char username[MAX_USERNAME];
    char konfirmasi;
    
    if (daftarPelanggan == NULL) {
        printf("\n%sError: Gagal membaca data pelanggan!%s\n", BOLD_RED, RESET);
        return;
    }
    
    do {
        system("cls"); // Bersihkan layar
        tampilkanDataPelanggan(daftarPelanggan, jumlahPelanggan);
        
        printf("\n%sMasukkan username pelanggan yang akan diedit (0 untuk batal):%s ", BOLD_WHITE, RESET);
        scanf("%s", username);
        
        if (strcmp(username, "0") == 0) {
            free(daftarPelanggan);
            return;
        }
        
        int found = 0;
        for(int i = 0; i < jumlahPelanggan; i++) {
            if(strcmp(daftarPelanggan[i].username, username) == 0) {
                printf("\n%sData Pelanggan ditemukan!%s\n", BOLD_GREEN, RESET);
                printf("\n%s=== Data Saat Ini ===%s\n", BOLD_CYAN, RESET);
                printf("%-20s: %s\n", "Username", daftarPelanggan[i].username);
                printf("%-20s: %s\n", "Nama", daftarPelanggan[i].nama);
                printf("%-20s: %s\n", "Telepon", daftarPelanggan[i].telepon);
                printf("%-20s: %.1f kg\n", "Berat Badan", daftarPelanggan[i].beratBadan);
                printf("%-20s: %.1f cm\n", "Tinggi Badan", daftarPelanggan[i].tinggiBadan);
                printf("%-20s: %d tahun\n", "Usia", daftarPelanggan[i].usia);
                printf("%-20s: %c\n", "Jenis Kelamin", daftarPelanggan[i].jenisKelamin);
                
                printf("\n%sEdit data ini? (Y/N):%s ", BOLD_YELLOW, RESET);
                scanf(" %c", &konfirmasi);
                
                if (toupper(konfirmasi) != 'Y') {
                    printf("\n%sEdit dibatalkan.%s\n", BOLD_YELLOW, RESET);
                    break;
                }
                
                printf("\n%s=== Masukkan Data Baru ===%s\n", BOLD_CYAN, RESET);
                
                printf("Nama: ");
                scanf(" %[^\n]s", daftarPelanggan[i].nama);
                
                printf("Telepon: ");
                scanf("%s", daftarPelanggan[i].telepon);
                
                do {
                    printf("Berat Badan (kg): ");
                    scanf("%f", &daftarPelanggan[i].beratBadan);
                } while(daftarPelanggan[i].beratBadan <= 0);
                
                do {
                    printf("Tinggi Badan (cm): ");
                    scanf("%f", &daftarPelanggan[i].tinggiBadan);
                } while(daftarPelanggan[i].tinggiBadan <= 0);
                
                do {
                    printf("Usia: ");
                    scanf("%d", &daftarPelanggan[i].usia);
                } while(daftarPelanggan[i].usia <= 0);
                
                do {
                    printf("Jenis Kelamin (L/P): ");
                    scanf(" %c", &daftarPelanggan[i].jenisKelamin);
                    daftarPelanggan[i].jenisKelamin = toupper(daftarPelanggan[i].jenisKelamin);
                } while(daftarPelanggan[i].jenisKelamin != 'L' && daftarPelanggan[i].jenisKelamin != 'P');
                
                tulisPelangganKeCSV(daftarPelanggan, jumlahPelanggan);
                printf("\n%sData pelanggan berhasil diupdate!%s\n", BOLD_GREEN, RESET);
                
                found = 1;
                break;
            }
        }
        
        if(!found) {
            printf("\n%sPelanggan dengan username '%s' tidak ditemukan!%s\n", BOLD_RED, username, RESET);
        }
        
        printf("\nEdit data pelanggan lain? (Y/N): ");
        scanf(" %c", &konfirmasi);
        
    } while(toupper(konfirmasi) == 'Y');
    
    free(daftarPelanggan);
}
#endif

#endif // CRUDUSER_H
