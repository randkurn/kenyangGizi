#ifndef STRUCT_H
#define STRUCT_H

#define MAX_MENU_ITEMS 100
#define MAX_ORDERS 1000
#define MAX_USERNAME 50
#define MAX_PASSWORD 50
#define MAX_NAME 100
#define MAX_PHONE 15
#define MAX_STATUS 20
#define MAX_TANGGAL 20

// Definisi struktur Pelanggan
struct Pelanggan {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    char nama[MAX_NAME];
    char telepon[MAX_PHONE];
    float beratBadan;
    float tinggiBadan;
    int usia;
    char jenisKelamin;
    int tingkatAktivitas;
    int tujuanProgram;
    int loginCount;
    int nilaiPolaHidup;
};

// Definisi struktur MenuItem
struct MenuItem {
    int id;
    char nama[100];
    float harga;
    char kategori[50];
    int tersedia;
    float protein;     
    float karbohidrat; 
    float lemak;      
    float kalori;     
};

// Definisi struktur Order/Pesanan
struct Order {
    int idPesanan;              
    char username[MAX_USERNAME]; 
    int idMenu;                 
    int jumlah;                 
    float totalHarga;           
    char status[MAX_STATUS];    
    char tanggalPesan[MAX_TANGGAL]; 
};

// Definisi struktur Admin
struct Admin {
    char username[50];
    char password[50];
};

// Definisi struktur DataKesehatan
struct DataKesehatan {
    float bmi;
    float bmr;
    float tdee;
    float targetKalori;
};

#endif // STRUCT_H