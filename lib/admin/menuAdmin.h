#ifndef MENUADMIN_H
#define MENUADMIN_H
#include "crudUser.h"
#include "crudMenu.h"
#include "crudPesanan.h"
#include "statistikAdmin.h"

void menuAdmin(void);

void menuAdmin(void) {
    int pilihan;
    do {
        system("cls");
        printf("\n%s=== Menu Admin ===%s\n", BOLD_CYAN, RESET);
        printf("%s1.%s Statistik Program\n", BOLD_YELLOW, RESET);
        printf("%s2.%s Kelola Menu Makanan\n", BOLD_YELLOW, RESET);
        printf("%s3.%s Kelola Data Pelanggan\n", BOLD_YELLOW, RESET);
        printf("%s4.%s Kelola Pesanan\n", BOLD_YELLOW, RESET);
        printf("%s5.%s Keluar\n", BOLD_RED, RESET);
        printf("%sPilih opsi:%s ", BOLD_WHITE, RESET);
        scanf("%d", &pilihan);

        switch(pilihan) {
            case 1:
                printf("\n%s=== Statistik Program ===%s\n", BOLD_CYAN, RESET);
                printf("%s1.%s Statistik Pelanggan\n", BOLD_YELLOW, RESET);
                printf("%s2.%s Statistik Pesanan\n", BOLD_YELLOW, RESET);
                printf("%s3.%s Statistik Menu\n", BOLD_YELLOW, RESET);
                printf("%sPilih opsi:%s ", BOLD_WHITE, RESET);
                int statPilihan;
                scanf("%d", &statPilihan);
                switch(statPilihan) {
                    case 1: statistikPelanggan(); break;
                    case 2: statistikPesanan(); break;
                    case 3: statistikMenu(); break;
                    default: printf("Pilihan tidak valid!\n");
                }
                break;
            case 2: 
                printf("\n%s=== Kelola Menu Makanan ===%s\n", BOLD_CYAN, RESET);
                printf("%s1.%s Tambah Menu\n", BOLD_YELLOW, RESET);
                printf("%s2.%s Edit Menu\n", BOLD_YELLOW, RESET);
                printf("%s3.%s Hapus Menu\n", BOLD_YELLOW, RESET);
                printf("%s4.%s Lihat Semua Menu\n", BOLD_YELLOW, RESET);
                printf("%sPilih opsi:%s ", BOLD_WHITE, RESET);
                int menuPilihan;
                scanf("%d", &menuPilihan);
                switch(menuPilihan) {
                    case 1: tambahMenu(); break;
                    case 2: editMenu(); break;
                    case 3: hapusMenu(); break;
                    case 4: lihatSemuaMenu(); break;
                    default: printf("Pilihan tidak valid!\n");
                }
                break;
            case 3:
                printf("\n%s=== Kelola Data Pelanggan ===%s\n", BOLD_CYAN, RESET);
                printf("%s1.%s Lihat Data Pelanggan\n", BOLD_YELLOW, RESET);
                printf("%s2.%s Edit Data Pelanggan\n", BOLD_YELLOW, RESET);
                printf("%s3.%s Hapus Data Pelanggan\n", BOLD_YELLOW, RESET);
                printf("%sPilih opsi:%s ", BOLD_WHITE, RESET);
                int pelangganPilihan;
                scanf("%d", &pelangganPilihan);
                switch(pelangganPilihan) {
                    case 1: lihatDataPelanggan(); break;
                    case 2: editDataPelanggan(); break;
                    case 3: hapusDataPelanggan(); break;
                    default: printf("Pilihan tidak valid!\n");
                }
                break;
            case 4:
                printf("\n%s=== Kelola Pesanan ===%s\n", BOLD_CYAN, RESET);
                printf("%s1.%s Lihat Semua Pesanan\n", BOLD_YELLOW, RESET);
                printf("%s2.%s Update Status Pesanan\n", BOLD_YELLOW, RESET);
                printf("%s3.%s Hapus Pesanan\n", BOLD_YELLOW, RESET);
                printf("%sPilih opsi:%s ", BOLD_WHITE, RESET);
                int pesananPilihan;
                scanf("%d", &pesananPilihan);
                switch(pesananPilihan) {
                    case 1: lihatSemuaPesanan(); break;
                    case 2: updateStatusPesanan(); break;
                    case 3: hapusPesanan(); break;
                    default: printf("Pilihan tidak valid!\n");
                }
                break;
            case 5: 
                return;
            default: 
                printf("Pilihan tidak valid!\n");
        }
        getch();
    } while(pilihan != 5);
}

#endif
