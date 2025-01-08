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
    if(jenisKelamin == 'P') {
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
    printf("\n=== Hasil Analisis Kesehatan ===\n");
    printf("BMI: %.2f\n", data.bmi);
    
    // Interpretasi BMI
    if(data.bmi < 18.5) {
        printf("Kategori: Berat Badan Kurang\n");
    } else if(data.bmi < 25) {
        printf("Kategori: Berat Badan Normal\n");
    } else if(data.bmi < 30) {
        printf("Kategori: Berat Badan Berlebih\n");
    } else {
        printf("Kategori: Obesitas\n");
    }
    
    printf("\nBMR: %.2f kalori\n", data.bmr);
    printf("TDEE: %.2f kalori\n", data.tdee);
    printf("\nRekomendasi Kalori Harian: %.2f kalori\n", data.targetKalori);
    
    // Rekomendasi berdasarkan tujuan
    printf("\nRekomendasi Program:\n");
    switch(tujuanProgram) {
        case 1:
            printf("- Target defisit kalori: 500 kalori per hari\n");
            printf("- Potensi penurunan berat badan: 0.5-1 kg per minggu\n");
            printf("- Fokus pada makanan tinggi protein dan serat\n");
            break;
        case 2:
            printf("- Target surplus kalori: 500 kalori per hari\n");
            printf("- Potensi kenaikan berat badan: 0.5-1 kg per minggu\n");
            printf("- Fokus pada makanan tinggi protein dan karbohidrat kompleks\n");
            break;
        case 3:
            printf("- Fokus pada keseimbangan nutrisi\n");
            printf("- Utamakan makanan segar dan bervariasi\n");
            printf("- Jaga pola makan teratur\n");
            break;
    }
}
#endif

#endif