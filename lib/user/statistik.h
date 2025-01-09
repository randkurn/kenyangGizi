#ifndef STATISTIK_H
#define STATISTIK_H


// Deklarasi fungsi untuk perhitungan kesehatan
float hitungBMI(float beratBadan, float tinggiBadan);
float hitungBMR(float beratBadan, float tinggiBadan, int usia, char jenisKelamin);
float hitungTDEE(float bmr, int tingkatAktivitas, int nilaiPolaHidup);
float hitungTargetKalori(float tdee, int tujuanProgram);
void tampilkanRekomendasi(struct DataKesehatan data, int tujuanProgram);

#ifdef IMPLEMENT_STATISTIK
// Implementasi fungsi perhitungan kesehatan
float hitungBMI(float beratBadan, float tinggiBadan) {
    // Konversi tinggi dari cm ke m
    float tinggiMeter = tinggiBadan / 100;
    return beratBadan / (tinggiMeter * tinggiMeter);
}

float hitungBMR(float beratBadan, float tinggiBadan, int usia, char jenisKelamin) {
    if(jenisKelamin == 'L') {
        return 66.5 + (13.75 * beratBadan) + (5.003 * tinggiBadan) - (6.75 * usia);
    } else {
        return 655.1 + (9.563 * beratBadan) + (1.850 * tinggiBadan) - (4.676 * usia);
    }
}

float hitungTDEE(float bmr, int tingkatAktivitas, int nilaiPolaHidup) {
    float faktorAktivitas;
    
    // Sesuaikan faktor aktivitas berdasarkan nilai pola hidup
    if (nilaiPolaHidup < 30) {
        // Pola hidup kurang sehat
        faktorAktivitas = 1.2; // Aktivitas ringan
    } else if (nilaiPolaHidup < 70) {
        // Pola hidup cukup sehat
        faktorAktivitas = 1.55; // Aktivitas sedang
    } else {
        // Pola hidup sangat sehat
        faktorAktivitas = 1.9; // Aktivitas berat
    }
    
    return bmr * faktorAktivitas;
}

float hitungTargetKalori(float tdee, int tujuanProgram) {
    switch(tujuanProgram) {
        case 1: return tdee - 500;  // Menurunkan berat badan
        case 2: return tdee + 500;  // Menaikkan berat badan
        case 3: return tdee;        // Menjaga pola hidup sehat
        default: return tdee;
    }
}

void tampilkanRekomendasi(struct DataKesehatan data, int tujuanProgram) {
    printf("\n============================================\n");
    printf("           HASIL ANALISIS KESEHATAN          \n");
    printf("============================================\n\n");
    
    printf("INDEKS MASSA TUBUH (BMI)\n");
    printf("------------------------\n");
    printf("Nilai BMI     : %.2f\n", data.bmi);
    
    printf("Kategori      : ");
    if(data.bmi < 18.5) {
        printf("Berat Badan Kurang\n");
    } else if(data.bmi < 25) {
        printf("Berat Badan Normal\n");
    } else if(data.bmi < 30) {
        printf("Berat Badan Berlebih\n");
    } else {
        printf("Obesitas\n");
    }
    
    printf("\nKEBUTUHAN ENERGI\n");
    printf("------------------------\n");
    printf("BMR          : %.2f kalori\n", data.bmr);
    printf("TDEE         : %.2f kalori\n", data.tdee);
    printf("Target Kalori: %.2f kalori\n", data.targetKalori);
    
    printf("\nREKOMENDASI PROGRAM\n");
    printf("------------------------\n");
    switch(tujuanProgram) {
        case 1:
            printf("Program Penurunan Berat Badan:\n");
            printf(" Target defisit    : 500 kalori/hari\n");
            printf(" Potensi penurunan : 0.5-1 kg/minggu\n");
            printf(" Fokus nutrisi     : Protein dan serat tinggi\n");
            break;
        case 2:
            printf("Program Penambahan Berat Badan:\n");
            printf(" Target surplus    : 500 kalori/hari\n");
            printf(" Potensi kenaikan  : 0.5-1 kg/minggu\n");
            printf(" Fokus nutrisi     : Protein dan karbohidrat kompleks\n");
            break;
        case 3:
            printf("Program Pola Hidup Sehat:\n");
            printf(" Keseimbangan nutrisi\n");
            printf(" Konsumsi makanan segar dan bervariasi\n");
            printf(" Pola makan teratur\n");
            break;
    }
    printf("\n============================================\n");
}
#endif

#endif