#ifndef USER_H
#define USER_H

#include "../struct.h"
#include "../colors.h"
#include "userMenu.h"
#include "statistik.h"

// Deklarasi fungsi
int loginPelanggan(void);
int registerPelanggan(void);
int validasiPelangganCSV(const char* username, const char* password);
int isUsernameExists(const char* username);
void simpanPelangganCSV(const struct Pelanggan *p);
int surveyPolaHidup(int isAfterRegister, float existingWeight, float existingHeight, const char* username);
void menuPelanggan(const char* username);

void printSeparator() {
    printf("+-------------------------------+\n");
}

void validasi(int *pilihan, int min, int max) {
        do {
            printf("Pilihan Anda (antara %d-%d): ", min, max);
            scanf("%d", pilihan);
            if (*pilihan < min || *pilihan > max) {
                printf(RED "Input tidak valid. Harap masukkan angka antara %d dan %d.\n" RESET, min, max);
            }
        } while (*pilihan < min || *pilihan > max);
    }



int surveyPolaHidup(int isAfterRegister, float existingWeight, float existingHeight, const char* username) {
    int n = 0; // Inisialisasi n dengan 0
    int merokok = 0; // Inisialisasi merokok dengan 0
    int pilihan; // Deklarasi variabel pilihan yang digunakan dalam validasi()

    // Header dengan warna cyan tebal
    printf(BOLD_CYAN);
    printf("====================================\n");
    printf("        Survei Pola Hidup\n");
    printf("====================================\n");
    printf(RESET);
    
    printf(ITALIC "Pilih jawaban sesuai kebiasaan Anda sehari-hari.\n\n" RESET);

    // Fungsi validasi input
    

    // Pertanyaan 1
    printSeparator();
    printf(BOLD "| %-30s |" RESET "\n", "1. Berapa kali Anda berolahraga?");
    printSeparator();
    printf(CYAN "| A. Tidak pernah              |\n");
    printf("| B. 1-2 kali                  |\n");
    printf("| C. 3-4 kali                  |\n");
    printf("| D. Lebih dari 4 kali         |\n" RESET);
    printSeparator();
    char jawaban;
    do {
        printf("Pilihan Anda (A/B/C/D): ");
        scanf(" %c", &jawaban);
        jawaban = toupper(jawaban);
        if (jawaban < 'A' || jawaban > 'D') {
            printf(RED "Input tidak valid. Harap masukkan A, B, C, atau D.\n" RESET);
        }
    } while (jawaban < 'A' || jawaban > 'D');
    
    switch (jawaban) {
        case 'A': n -= 5; break;
        case 'B': n += 10; break;
        case 'C': n += 20; break;
        case 'D': n += 30; break;
    }

    // Pertanyaan 2
    printSeparator();
    printf(BOLD "| %-30s |" RESET "\n", "2. Seberapa sering makan cepat saji?");
    printSeparator();
    printf(CYAN "| A. Setiap hari               |\n");
    printf("| B. 2-3 kali seminggu         |\n");
    printf("| C. 1 kali seminggu           |\n");
    printf("| D. Jarang atau tidak pernah  |\n" RESET);
    printSeparator();
    char jawaban2;
    do {
        printf("Pilihan Anda (A/B/C/D): ");
        scanf(" %c", &jawaban2);
        jawaban2 = toupper(jawaban2);
        if (jawaban2 < 'A' || jawaban2 > 'D') {
            printf(RED "Input tidak valid. Harap masukkan A, B, C, atau D.\n" RESET);
        }
    } while (jawaban2 < 'A' || jawaban2 > 'D');
    
    switch (jawaban2) {
        case 'A': n -= 7; break;
        case 'B': n += 10; break;
        case 'C': n += 20; break;
        case 'D': n += 30; break;
    }

    // Pertanyaan 3
    printSeparator();
    printf(BOLD "| %-30s |" RESET "\n", "3. Berapa jam rata-rata tidur?");
    printSeparator();
    printf(CYAN "| A. Kurang dari 5 jam         |\n");
    printf("| B. 5-6 jam                   |\n");
    printf("| C. 7-8 jam                   |\n");
    printf("| D. Lebih dari 8 jam          |\n" RESET);
    printSeparator();
    char jawaban3;
    do {
        printf("Pilihan Anda (A/B/C/D): ");
        scanf(" %c", &jawaban3);
        jawaban3 = toupper(jawaban3);
        if (jawaban3 < 'A' || jawaban3 > 'D') {
            printf(RED "Input tidak valid. Harap masukkan A, B, C, atau D.\n" RESET);
        }
    } while (jawaban3 < 'A' || jawaban3 > 'D');
    
    switch (jawaban3) {
        case 'A': break;
        case 'B': n += 10; break;
        case 'C': n += 20; break;
        case 'D': n += 30; break;
    }

    // Pertanyaan 4
    printSeparator();
    printf(BOLD "| %-30s |" RESET "\n", "4. Apakah Anda merokok?");
    printSeparator();
    printf(CYAN "| A. Ya                        |\n");
    printf("| B. Tidak                     |\n" RESET);
    printSeparator();
    char jawaban4;
    do {
        printf("Pilihan Anda (A/B): ");
        scanf(" %c", &jawaban4);
        jawaban4 = toupper(jawaban4);
        if (jawaban4 < 'A' || jawaban4 > 'B') {
            printf(RED "Input tidak valid. Harap masukkan A atau B.\n" RESET);
        }
    } while (jawaban4 < 'A' || jawaban4 > 'B');
    
    switch (jawaban4) {
        case 'A':
            n -= 10;
            merokok = 1;
            break;
        case 'B': break;
    }

    // Pertanyaan 5
    printSeparator();
    printf(BOLD "| %-30s |" RESET "\n", "5. Berapa liter air diminum?");
    printSeparator();
    printf(CYAN "| A. Kurang dari 1 liter       |\n");
    printf("| B. 1-2 liter                 |\n");
    printf("| C. 2-3 liter                 |\n");
    printf("| D. Lebih dari 3 liter        |\n" RESET);
    printSeparator();
    char jawaban5;
    do {
        printf("Pilihan Anda (A/B/C/D): ");
        scanf(" %c", &jawaban5);
        jawaban5 = toupper(jawaban5);
        if (jawaban5 < 'A' || jawaban5 > 'D') {
            printf(RED "Input tidak valid. Harap masukkan A, B, C, atau D.\n" RESET);
        }
    } while (jawaban5 < 'A' || jawaban5 > 'D');
    
    switch (jawaban5) {
        case 'A': n -= 5; break;
        case 'B': n += 10; break;
        case 'C': n += 20; break;
        case 'D': n += 30; break;
    }

    // Menambahkan input berat dan tinggi badan terbaru
    float beratBaru, tinggiBaru;
    if (isAfterRegister) {
        // Langsung gunakan data yang sudah ada dari registrasi
        beratBaru = existingWeight;
        tinggiBaru = existingHeight;
    } else {
        // Kode input berat dan tinggi badan tetap ada untuk update rutin
        printf("\nUpdate data kesehatan Anda:\n");
        do {
            printf("Berat Badan Terkini (kg): ");
            if(scanf("%f", &beratBaru) != 1 || beratBaru <= 0) {
                printf(RED "Berat badan tidak valid!\n" RESET);
                while(getchar() != '\n');
                continue;
            }
            break;
        } while(1);
        
        do {
            printf("Tinggi Badan Terkini (cm): ");
            if(scanf("%f", &tinggiBaru) != 1 || tinggiBaru <= 0) {
                printf(RED "Tinggi badan tidak valid!\n" RESET);
                while(getchar() != '\n');
                continue;
            }
            break;
        } while(1);
    }

    // Menentukan tingkat aktivitas berdasarkan nilai n
    int tingkatAktivitas;
    if (n < 30) {
        tingkatAktivitas = 1; // Rendah
    } else if (n < 70) {
        tingkatAktivitas = 2; // Sedang
    } else {
        tingkatAktivitas = 3; // Tinggi
    }

    // Menentukan tujuan program berdasarkan BMI dan tingkat aktivitas
    float bmi = beratBaru / ((tinggiBaru/100) * (tinggiBaru/100));
    int tujuanProgram;
    
    if (bmi < 18.5) {
        tujuanProgram = 1; // Program penambahan berat badan
    } else if (bmi >= 25) {
        tujuanProgram = 2; // Program penurunan berat badan
    } else {
        tujuanProgram = 3; // Program maintenance
    }

    // Menampilkan hasil
    printf("\n");
    printf(BOLD_CYAN "====================================\n");
    printf("           Hasil Survei\n");
    printf("====================================\n" RESET);
    
    printf(ITALIC "Total poin Anda dihitung berdasarkan kebiasaan harian Anda.\n" RESET);

    if (n < 30) {
        printf(BOLD_RED "\nKategori: Kurang Sehat\n" RESET);
        printf(RED "Saran: Perbaiki pola makan, tambahkan olahraga, dan hindari kebiasaan tidak sehat.\n" RESET);
    } else if (n < 70) {
        printf(BOLD_YELLOW "\nKategori: Sehat\n" RESET);
        printf(YELLOW "Saran: Lanjutkan kebiasaan baik Anda, tetapi tetap perhatikan keseimbangan hidup.\n" RESET);
    } else {
        printf(BOLD_GREEN "\nKategori: Sangat Sehat\n" RESET);
        printf(GREEN "Saran: Pertahankan gaya hidup sehat Anda dan jadilah inspirasi bagi orang lain.\n" RESET);
    }

    // Pesan pengingat untuk berhenti merokok
    if (merokok == 1) {
        printf(BOLD_RED "\nPesan Penting: " RESET);
        printf(RED "Merokok merusak kesehatan. Pertimbangkan untuk berhenti demi hidup yang lebih sehat.\n" RESET);
    }

    printf("\nBerdasarkan hasil survei:\n");
    printf(BOLD "Tingkat Aktivitas: " RESET);
    switch(tingkatAktivitas) {
        case 1: printf(RED "Rendah\n" RESET); break;
        case 2: printf(YELLOW "Sedang\n" RESET); break;
        case 3: printf(GREEN "Tinggi\n" RESET); break;
    }

    printf(BOLD "BMI Anda: %.1f\n" RESET, bmi);
    printf(BOLD "Program yang Disarankan: " RESET);
    switch(tujuanProgram) {
        case 1: printf(CYAN "Program Penambahan Berat Badan\n" RESET); break;
        case 2: printf(CYAN "Program Penurunan Berat Badan\n" RESET); break;
        case 3: printf(CYAN "Program Maintenance\n" RESET); break;
    }

    // Update data pelanggan
    int jumlahPelanggan;
    struct Pelanggan* daftarPelanggan = bacaPelangganDariCSV(&jumlahPelanggan);
    for(int i = 0; i < jumlahPelanggan; i++) {
        if(strcmp(daftarPelanggan[i].username, username) == 0) {
            daftarPelanggan[i].beratBadan = beratBaru;
            daftarPelanggan[i].tinggiBadan = tinggiBaru;
            daftarPelanggan[i].tingkatAktivitas = tingkatAktivitas;
            daftarPelanggan[i].tujuanProgram = tujuanProgram;
            break;
        }
    }
    tulisPelangganKeCSV(daftarPelanggan, jumlahPelanggan);
    free(daftarPelanggan);

    printf(BOLD_CYAN "====================================\n" RESET);

    return n;
}


// Implementasi fungsi
int loginPelanggan(void) {
    char username[50], password[50];
    int percobaan = 0;
    
    do {
        system("cls");
        printf(BOLD_CYAN "\n=== Login Pelanggan ===\n" RESET);
        
        // Clear input buffer
        while(getchar() != '\n');
        
        printf("Username: ");
        if(fgets(username, sizeof(username), stdin)) {
            username[strcspn(username, "\n")] = 0;
        }
        
        printf("Password: ");
        if(fgets(password, sizeof(password), stdin)) {
            password[strcspn(password, "\n")] = 0;
        }
        
        if(validasiPelangganCSV(username, password)) {
            // Baca data pelanggan yang ada
            int jumlahPelanggan;
            struct Pelanggan* daftarPelanggan = bacaPelangganDariCSV(&jumlahPelanggan);
            
            // Cari pelanggan yang login
            for(int i = 0; i < jumlahPelanggan; i++) {
                if(strcmp(daftarPelanggan[i].username, username) == 0) {
                    // Increment login count
                    daftarPelanggan[i].loginCount++;
                    
                    // Cek apakah perlu survei (setiap 3x login)
                    if(daftarPelanggan[i].loginCount % 3 == 0) {
                        printf("\nSaatnya melakukan survei pola hidup berkala!\n");
                        printf("(Dilakukan setiap 3 kali login)\n");
                        printf("\nTekan Enter untuk memulai survei...");
                        getchar();
                        
                        // Lakukan survei dan simpan hasilnya
                        daftarPelanggan[i].nilaiPolaHidup = surveyPolaHidup(0, 
                            daftarPelanggan[i].beratBadan, 
                            daftarPelanggan[i].tinggiBadan,
                            username);
                        
                        // Tampilkan perbandingan dengan survei sebelumnya
                        printf("\nPerbandingan dengan survei sebelumnya:\n");
                        if(daftarPelanggan[i].nilaiPolaHidup > daftarPelanggan[i].nilaiPolaHidup) {
                            printf(GREEN "Selamat! Pola hidup Anda mengalami peningkatan!\n" RESET);
                        } else if(daftarPelanggan[i].nilaiPolaHidup < daftarPelanggan[i].nilaiPolaHidup) {
                            printf(YELLOW "Pola hidup Anda sedikit menurun. Tetap semangat untuk meningkatkannya!\n" RESET);
                        } else {
                            printf(CYAN "Pola hidup Anda stabil. Pertahankan dan tingkatkan!\n" RESET);
                        }
                        
                        printf("\nTekan Enter untuk melanjutkan...");
                        getchar();
                    }
                    
                    // Tulis kembali ke CSV
                    tulisPelangganKeCSV(daftarPelanggan, jumlahPelanggan);
                    
                    printf(BOLD_GREEN "\nLogin berhasil!\n" RESET);
                    printf(CYAN "Selamat datang kembali, %s!\n" RESET, daftarPelanggan[i].nama);
                    
                    printf(ITALIC "Ini adalah login ke-%d Anda.\n" RESET, daftarPelanggan[i].loginCount);
                    if(daftarPelanggan[i].loginCount % 3 == 2) {
                        printf(BOLD_YELLOW "Pada login berikutnya, Anda akan diminta mengisi survei pola hidup.\n" RESET);
                    }
                    
                    free(daftarPelanggan);
                    printf("\nTekan Enter untuk melanjutkan...");
                    getchar();
                    menuPelanggan(username);
                    return 1;
                }
            }
            free(daftarPelanggan);
        } else {
            printf(BOLD_RED "\nUsername atau password salah!\n" RESET);
            percobaan++;
            if(percobaan < 3) {
                printf("Sisa percobaan: %d\n", 3 - percobaan);
                printf("Coba lagi? (Y/N): ");
                char lanjut;
                scanf(" %c", &lanjut);
                if(toupper(lanjut) != 'Y') break;
            }
        }
    } while(percobaan < 3);
    
    if(percobaan >= 3) {
        printf("\nTerlalu banyak percobaan gagal!\n");
        printf("Silakan coba lagi nanti.\n");
        printf("\nTekan Enter untuk kembali...");
        getchar();
    }
    return 0;
}

int registerPelanggan(void) {
    struct Pelanggan pelangganBaru;
    char konfirmasiPassword[MAX_PASSWORD];
    
    system("cls");
    printf(BOLD_CYAN "\n=== Pendaftaran Pelanggan ===\n" RESET);
    
    // Input dan validasi username
    do {
        printf("Username (5-50 karakter): ");
        scanf("%49s", pelangganBaru.username);
        
        if(strlen(pelangganBaru.username) < 5) {
            printf(RED "Username terlalu pendek! Minimal 5 karakter.\n" RESET);
            continue;
        }
        
        // Cek karakter yang diperbolehkan
        int valid = 1;
        for(int i = 0; pelangganBaru.username[i]; i++) {
            if(!isalnum(pelangganBaru.username[i]) && pelangganBaru.username[i] != '_') {
                valid = 0;
                break;
            }
        }
        if(!valid) {
            printf("Username hanya boleh mengandung huruf, angka, dan underscore!\n");
            continue;
        }
        
        // Cek keunikan username
        if(isUsernameExists(pelangganBaru.username)) {
            printf("Username sudah digunakan! Silakan pilih username lain.\n");
            continue;
        }
        break;
    } while(1);
    
    // Input dan validasi password
    do {
        printf("Password (6-50 karakter): ");
        scanf("%49s", pelangganBaru.password);
        
        if(strlen(pelangganBaru.password) < 6) {
            printf("Password terlalu pendek! Minimal 6 karakter.\n");
            continue;
        }
        
        printf("Konfirmasi password: ");
        scanf("%49s", konfirmasiPassword);
        
        if(strcmp(pelangganBaru.password, konfirmasiPassword) != 0) {
            printf("Password tidak cocok! Coba lagi.\n");
            continue;
        }
        break;
    } while(1);
    
    // Input data pribadi
    printf("\nData Pribadi:\n");
    printf("Nama Lengkap: ");
    while(getchar() != '\n');
    scanf("%[^\n]s", pelangganBaru.nama);
    
    // Input dan validasi nomor telepon
    do {
        printf("Nomor Telepon (10-15 digit): ");
        scanf("%14s", pelangganBaru.telepon);
        
        if(strlen(pelangganBaru.telepon) < 10 || strlen(pelangganBaru.telepon) > 15) {
            printf("Panjang nomor telepon tidak valid!\n");
            continue;
        }
        
        int valid = 1;
        for(int i = 0; pelangganBaru.telepon[i]; i++) {
            if(!isdigit(pelangganBaru.telepon[i])) {
                valid = 0;
                break;
            }
        }
        if(!valid) {
            printf("Nomor telepon hanya boleh berisi angka!\n");
            continue;
        }
        break;
    } while(1);
    
    // Input data kesehatan
    printf("\nData Kesehatan:\n");
    do {
        printf("Berat Badan (kg): ");
        if(scanf("%f", &pelangganBaru.beratBadan) != 1 || pelangganBaru.beratBadan <= 0) {
            printf("Berat badan tidak valid!\n");
            while(getchar() != '\n');
            continue;
        }
        break;
    } while(1);
    
    do {
        printf("Tinggi Badan (cm): ");
        if(scanf("%f", &pelangganBaru.tinggiBadan) != 1 || pelangganBaru.tinggiBadan <= 0) {
            printf("Tinggi badan tidak valid!\n");
            while(getchar() != '\n');
            continue;
        }
        break;
    } while(1);
    
    do {
        printf("Usia (tahun): ");
        if(scanf("%d", &pelangganBaru.usia) != 1 || pelangganBaru.usia <= 0) {
            printf("Usia tidak valid!\n");
            while(getchar() != '\n');
            continue;
        }
        break;
    } while(1);
    
    do {
        printf("Jenis Kelamin (P/W): ");
        while(getchar() != '\n');
        scanf("%c", &pelangganBaru.jenisKelamin);
        
        pelangganBaru.jenisKelamin = toupper(pelangganBaru.jenisKelamin);
        if(pelangganBaru.jenisKelamin != 'P' && pelangganBaru.jenisKelamin != 'W') {
            printf("Pilih P untuk Pria atau W untuk Wanita!\n");
            continue;
        }
        break;
    } while(1);
    
    // Input tingkat aktivitas
    system("cls");

    
    // Inisialisasi loginCount dan nilaiPolaHidup
    pelangganBaru.loginCount = 0;
    
    // Lakukan survei pola hidup di awal registrasi
    printf("\n=== Survei Pola Hidup Awal ===\n");
    printf("Silakan ikuti survei singkat untuk menilai pola hidup Anda.\n");
    printf("\nTekan Enter untuk memulai survei...");
    while(getchar() != '\n');
    getchar();
    
    pelangganBaru.nilaiPolaHidup = surveyPolaHidup(1, 
        pelangganBaru.beratBadan, 
        pelangganBaru.tinggiBadan,
        pelangganBaru.username);
    
    // Simpan ke CSV
    int jumlahPelanggan;
    struct Pelanggan* daftarPelanggan = bacaPelangganDariCSV(&jumlahPelanggan);
    if (daftarPelanggan == NULL) {
        daftarPelanggan = malloc(sizeof(struct Pelanggan));
        jumlahPelanggan = 0;
    }
    daftarPelanggan[jumlahPelanggan] = pelangganBaru;
    jumlahPelanggan++;
    tulisPelangganKeCSV(daftarPelanggan, jumlahPelanggan);
    free(daftarPelanggan);
    
    printf(BOLD_GREEN "\nPendaftaran berhasil!\n" RESET);
    printf(CYAN "Selamat datang %s!\n" RESET, pelangganBaru.nama);
    printf("\nTekan tombol apa saja untuk melanjutkan...");
    getch();
    
    // Langsung login setelah registrasi
    menuPelanggan(pelangganBaru.username);
    return 1;
}

// Fungsi untuk validasi login pelanggan
int validasiPelangganCSV(const char* username, const char* password) {
    FILE *fp = fopen("database/pelanggan.csv", "r");
    if(fp == NULL) return 0;
    
    char line[1024];
    char *token;
    
    // Skip header
    fgets(line, 1024, fp);
    
    while(fgets(line, 1024, fp)) {
        char lineCopy[1024];
        strcpy(lineCopy, line);
        
        // Ubah pemisah menjadi titik koma
        token = strtok(lineCopy, ";");
        if(token != NULL && strcmp(token, username) == 0) {
            token = strtok(NULL, ";");
            if(token != NULL && strcmp(token, password) == 0) {
                fclose(fp);
                return 1;
            }
        }
    }
    
    fclose(fp);
    return 0;
}

// Fungsi untuk mengecek username yang sudah ada
int isUsernameExists(const char* username) {
    FILE *fp = fopen("database/pelanggan.csv", "r");
    if(fp == NULL) return 0;
    
    char line[1024];
    char *token;
    
    // Skip header
    fgets(line, 1024, fp);
    
    while(fgets(line, 1024, fp)) {
        // Ubah pemisah menjadi titik koma
        token = strtok(line, ";");
        if(token != NULL && strcmp(token, username) == 0) {
            fclose(fp);
            return 1;
        }
    }
    
    fclose(fp);
    return 0;
}

// Fungsi untuk menyimpan data pelanggan ke CSV
void simpanPelangganCSV(const struct Pelanggan *p) {
    FILE *fp = fopen("database/pelanggan.csv", "a");
    if(fp == NULL) {
        printf("Error: Tidak dapat membuka file!\n");
        return;
    }
    
    // Jika file baru, tulis header dengan pemisah titik koma
    fseek(fp, 0, SEEK_END);
    if(ftell(fp) == 0) {
        fprintf(fp, "username;password;nama;telepon;berat_badan;tinggi_badan;usia;jenis_kelamin;tingkat_aktivitas;tujuan_program\n");
    }
    
    // Tulis data pelanggan dengan pemisah titik koma
    fprintf(fp, "%s;%s;%s;%s;%.2f;%.2f;%d;%c;%d;%d\n",
            p->username,
            p->password,
            p->nama,
            p->telepon,
            p->beratBadan,
            p->tinggiBadan,
            p->usia,
            p->jenisKelamin,
            p->tingkatAktivitas,
            p->tujuanProgram);
    
    fclose(fp);
}

#endif
