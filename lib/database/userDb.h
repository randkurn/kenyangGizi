#ifndef USER_DB_H
#define USER_DB_H

#include "../struct.h"
#include "../colors.h"

// Deklarasi fungsi
struct Pelanggan* bacaPelangganDariCSV(int* jumlahPelanggan);
void tulisPelangganKeCSV(struct Pelanggan* daftarPelanggan, int jumlahPelanggan);
void lihatProfilPelanggan(const char* username);

// Implementasi dalam #ifdef
#ifdef IMPLEMENT_PELANGGAN
// Semua implementasi fungsi taruh di sini
struct Pelanggan* bacaPelangganDariCSV(int* jumlahPelanggan) {
    FILE *fp = fopen("database/pelanggan.csv", "r");
    if (fp == NULL) {
        printf("Error: Tidak dapat membuka file pelanggan.csv\n");
        return NULL;
    }

    struct Pelanggan* daftarPelanggan = malloc(MAX_MENU_ITEMS * sizeof(struct Pelanggan));
    char baris[1024];
    *jumlahPelanggan = 0;
    
    // Skip header
    fgets(baris, 1024, fp);
    
    while (fgets(baris, 1024, fp)) {
        struct Pelanggan pelanggan;
        char* token = strtok(baris, ";"); // Menggunakan ; sebagai separator
        
        strcpy(pelanggan.username, token);
        token = strtok(NULL, ";");
        strcpy(pelanggan.password, token);
        token = strtok(NULL, ";");
        strcpy(pelanggan.nama, token);
        token = strtok(NULL, ";");
        strcpy(pelanggan.telepon, token);
        token = strtok(NULL, ";");
        pelanggan.beratBadan = atof(token);
        token = strtok(NULL, ";");
        pelanggan.tinggiBadan = atof(token);
        token = strtok(NULL, ";");
        pelanggan.usia = atoi(token);
        token = strtok(NULL, ";");
        pelanggan.jenisKelamin = token[0];
        token = strtok(NULL, ";");
        pelanggan.tingkatAktivitas = atoi(token);
        token = strtok(NULL, ";");
        pelanggan.tujuanProgram = atoi(token);
        token = strtok(NULL, ";");
        pelanggan.loginCount = atoi(token);
        token = strtok(NULL, ";");
        pelanggan.nilaiPolaHidup = atoi(token);
        
        daftarPelanggan[*jumlahPelanggan] = pelanggan;
        (*jumlahPelanggan)++;
    }
    
    fclose(fp);
    return daftarPelanggan;
}

void tulisPelangganKeCSV(struct Pelanggan* daftarPelanggan, int jumlahPelanggan) {
    FILE *fp = fopen("database/pelanggan.csv", "w");
    if (fp == NULL) {
        printf("Error: Tidak dapat membuka file pelanggan.csv\n");
        return;
    }
    
    // Tulis header dengan format yang mudah dibaca di Excel
    fprintf(fp, "Username;Password;Nama Lengkap;No. Telepon;Berat Badan (kg);Tinggi Badan (cm);Usia;Jenis Kelamin;Tingkat Aktivitas;Tujuan Program;Login Count;Nilai Pola Hidup\n");
    
    // Tulis data dengan format yang rapi
    for (int i = 0; i < jumlahPelanggan; i++) {
        fprintf(fp, "%s;%s;%s;%s;%.2f;%.2f;%d;%c;%d;%d;%d;%d\n",
            daftarPelanggan[i].username,
            daftarPelanggan[i].password,
            daftarPelanggan[i].nama,
            daftarPelanggan[i].telepon,
            daftarPelanggan[i].beratBadan,
            daftarPelanggan[i].tinggiBadan,
            daftarPelanggan[i].usia,
            daftarPelanggan[i].jenisKelamin,
            daftarPelanggan[i].tingkatAktivitas,
            daftarPelanggan[i].tujuanProgram,
            daftarPelanggan[i].loginCount,
            daftarPelanggan[i].nilaiPolaHidup);
    }
    
    fclose(fp);
}

void lihatProfilPelanggan(const char* username) {
    int jumlahPelanggan;
    struct Pelanggan* daftarPelanggan = bacaPelangganDariCSV(&jumlahPelanggan);
    
    if (daftarPelanggan == NULL) {
        printf(COLOR_RESET(BOLD_RED) "\nError: Tidak dapat membaca data pelanggan!\n" RESET);
        return;
    }
    
    int found = 0;
    for(int i = 0; i < jumlahPelanggan; i++) {
        if(strcmp(daftarPelanggan[i].username, username) == 0) {
            printf("\n================= PROFIL PELANGGAN =================\n");
            
            // Data Pribadi
            printf("\n----- DATA PRIBADI -----\n");
            printf("Username     : %s\n", daftarPelanggan[i].username);
            printf("Nama Lengkap : %s\n", daftarPelanggan[i].nama);
            printf("No. Telepon  : %s\n", daftarPelanggan[i].telepon);
            
            // Data Fisik
            printf("\n----- DATA FISIK -----\n");
            printf("Berat Badan  : %.2f kg\n", daftarPelanggan[i].beratBadan);
            printf("Tinggi Badan : %.2f cm\n", daftarPelanggan[i].tinggiBadan);
            printf("Usia         : %d\n", daftarPelanggan[i].usia);
            printf("Jenis Kelamin: %c\n", daftarPelanggan[i].jenisKelamin);
            
            // Informasi Program
            printf("\n----- INFORMASI PROGRAM -----\n");
            
            // Tingkat Aktivitas
            printf("Level Aktivitas: ");
            switch(daftarPelanggan[i].tingkatAktivitas) {
                case 1: printf("Sangat Jarang Olahraga\n"); break;
                case 2: printf("Jarang Olahraga (1-3 hari/minggu)\n"); break;
                case 3: printf("Cukup Aktif (3-5 hari/minggu)\n"); break;
                case 4: printf("Sangat Aktif (6-7 hari/minggu)\n"); break;
                case 5: printf("Ekstra Aktif (Atlet)\n"); break;
                default: printf("Tidak Diketahui\n");
            }
            
            // Tujuan Program
            printf("Tujuan Program: ");
            switch(daftarPelanggan[i].tujuanProgram) {
                case 1: printf("Penurunan Berat Badan\n"); break;
                case 2: printf("Pola Makan Sehat\n"); break;
                case 3: printf("Penambahan Massa Otot\n"); break;
                default: printf("Tidak Diketahui\n");
            }
            
            // Statistik
            printf("\n----- STATISTIK -----\n");
            printf("Jumlah Login : %d\n", daftarPelanggan[i].loginCount);
            printf("Nilai Hidup  : %d\n", daftarPelanggan[i].nilaiPolaHidup);
            
            printf("\n=================================================\n");
            found = 1;
            break;
        }
    }
    
    if(!found) {
        printf(COLOR_RESET(BOLD_RED) "\nError: Data pelanggan tidak ditemukan!\n" RESET);
    }
    
    free(daftarPelanggan);
}
#endif

#endif // PELANGGAN_H