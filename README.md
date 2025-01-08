# kenyangGizi
Solusi inovatif yang dirancang untuk membantu masyarakat perkotaan yang sibuk dalam menjaga pola makan sehat. 

## Nama Anggota Kelompok 5 MKB 1C
- Burhan Abdur Rahman (2410073)
- Kaylla Asyifa (2402730)
- Muhammad Thoriq Salahudin Haryoto (2403154)
- Muhammad Randy Kurniawan (2405315)
- Sekar Ayu Kinanti (2404201)
- Zaldi Arifa (2406326)

### Untuk Pelanggan
- Registrasi dan login akun
- Survei pola hidup dan kesehatan
- Perhitungan BMI, BMR, dan TDEE
- Rekomendasi asupan kalori harian
- Pemesanan makanan
- Riwayat pesanan
- Pemantauan profil kesehatan

### Untuk Admin
- Manajemen menu makanan
- Manajemen data pelanggan
- Manajemen pesanan
- Statistik program:
  - Statistik pelanggan
  - Statistik pesanan
  - Statistik menu

## Struktur Proyek
```
kenyangGizi/
├── lib/
│ ├── admin/
│ │ ├── admin.h
│ │ ├── crudMenu.h
│ │ ├── crudPesanan.h
│ │ ├── crudUser.h
│ │ ├── menuAdmin.h
│ │ └── statistikAdmin.h
│ ├── database/
│ │ ├── menuDb.h
│ │ ├── pesananDb.h
│ │ └── userDb.h
│ ├── user/
│ │ ├── statistik.h
│ │ ├── userMenu.h
│ │ └── user.h
│ ├── auth.h
│ ├── colors.h
│ └── struct.h
├── database/
│ ├── menu.csv
│ ├── pelanggan.csv
│ └── pesanan.csv
└── main.c
```



## Rilis Patch v1.1.0

### Perbaikan
1. Perbaikan bug pada perhitungan kalori menu
2. Optimalisasi penyimpanan data ke CSV
3. Peningkatan validasi input pengguna

### Fitur Baru
1. Survei pola hidup berkala (setiap 3x login)
2. Perbandingan hasil survei dengan sebelumnya
3. Peningkatan tampilan statistik admin
4. Penambahan warna pada status pesanan

### Perubahan Teknis
1. Restrukturisasi kode untuk memudahkan maintenance
2. Penambahan komentar pada fungsi-fungsi utama
3. Optimalisasi penggunaan memori
4. Peningkatan keamanan validasi input
