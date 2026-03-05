#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Öğrenci yapısı (Düğüm / Node)
struct Ogrenci {
    int id;
    char ad[50];
    float vize;
    float final;
    float ortalama;
    char harf[3];
    struct Ogrenci* next;
};

struct Ogrenci* head = NULL;

// Fonksiyon Prototipleri
void menu();
void ogrenciEkle();       // C - Create
void ogrencileriListele();// R - Read
void ogrenciAra();        // R - Read
void ogrenciSil();        // D - Delete
void ogrenciGuncelle();   // U - Update
float ortalamaHesapla(float vize, float final);
void harfNotuHesapla(float ortalama, char* harf);
void dosyayaKaydet();
void dosyadanOku();
void bellegiTemizle();

int main() {
    int secim;
    
    dosyadanOku();

    do {
        menu();
        printf("Seciminizi giriniz: ");
        scanf("%d", &secim);

        switch(secim) {
            case 1: ogrenciEkle(); break;
            case 2: ogrencileriListele(); break;
            case 3: ogrenciAra(); break;
            case 4: ogrenciGuncelle(); break;
            case 5: ogrenciSil(); break;
            case 6:
                printf("Veriler kaydediliyor ve bellek temizleniyor...\n");
                dosyayaKaydet();
                bellegiTemizle();
                break;
            default:
                printf("Gecersiz secim! Lutfen tekrar deneyin.\n");
        }
    } while(secim != 6);

    return 0;
}

void menu() {
    printf("\n=== OGRENCI BILGI SISTEMI (CRUD) ===\n");
    printf("1- Ogrenci Ekle\n");
    printf("2- Ogrencileri Listele\n");
    printf("3- Ogrenci Ara (ID ile)\n");
    printf("4- Ogrenci Guncelle (ID ile)\n");
    printf("5- Ogrenci Sil (ID ile)\n");
    printf("6- Cikis\n");
}

void ogrenciEkle() {
    struct Ogrenci* yeni = (struct Ogrenci*)malloc(sizeof(struct Ogrenci));
    if (yeni == NULL) {
        printf("Bellek tahsis edilemedi!\n");
        return;
    }

    printf("Ogrenci ID: ");
    scanf("%d", &yeni->id);

    // Çakışma kontrolü
    struct Ogrenci* temp = head;
    while(temp != NULL) {
        if(temp->id == yeni->id) {
            printf("Bu ID'ye sahip bir ogrenci zaten var!\n");
            free(yeni);
            return;
        }
        temp = temp->next;
    }

    printf("Ogrenci Adi: ");
    scanf("%s", yeni->ad);
    printf("Vize Notu: ");
    scanf("%f", &yeni->vize);
    printf("Final Notu: ");
    scanf("%f", &yeni->final);

    yeni->ortalama = ortalamaHesapla(yeni->vize, yeni->final);
    harfNotuHesapla(yeni->ortalama, yeni->harf);
    yeni->next = NULL;

    if (head == NULL) {
        head = yeni;
    } else {
        temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = yeni;
    }

    dosyayaKaydet();
    printf("Ogrenci basariyla eklendi!\n");
}

void ogrencileriListele() {
    if (head == NULL) {
        printf("Sistemde kayitli ogrenci yok.\n");
        return;
    }

    struct Ogrenci* temp = head;
    printf("\n--- OGRENCI LISTESI ---\n");
    while (temp != NULL) {
        printf("ID: %d | Ad: %s | Ort: %.2f | Harf: %s\n", 
               temp->id, temp->ad, temp->ortalama, temp->harf);
        temp = temp->next;
    }
}

void ogrenciAra() {
    if (head == NULL) {
        printf("Sistemde ogrenci yok.\n");
        return;
    }
    
    int arananId;
    printf("Aranacak Ogrenci ID: ");
    scanf("%d", &arananId);
    
    struct Ogrenci* temp = head;
    while (temp != NULL) {
        if (temp->id == arananId) {
            printf("\n--- OGRENCI BULUNDU ---\n");
            printf("ID: %d\nAd: %s\nVize: %.2f\nFinal: %.2f\nOrtalama: %.2f\nHarf Notu: %s\n", 
                   temp->id, temp->ad, temp->vize, temp->final, temp->ortalama, temp->harf);
            return;
        }
        temp = temp->next;
    }
    printf("Ogrenci bulunamadi!\n");
}

void ogrenciGuncelle() {
    if (head == NULL) {
        printf("Sistemde guncellenecek ogrenci yok.\n");
        return;
    }

    int guncellenecekId;
    printf("Guncellenecek Ogrenci ID: ");
    scanf("%d", &guncellenecekId);

    struct Ogrenci* temp = head;
    
    // Öğrenciyi bulana kadar listeyi tara
    while (temp != NULL) {
        if (temp->id == guncellenecekId) {
            printf("\n--- %s ADLI OGRENCIYI GUNCELLEYIN ---\n", temp->ad);
            
            // Yeni bilgileri al
            printf("Yeni Ogrenci Adi (Eski: %s): ", temp->ad);
            scanf("%s", temp->ad);
            
            printf("Yeni Vize Notu (Eski: %.2f): ", temp->vize);
            scanf("%f", &temp->vize);
            
            printf("Yeni Final Notu (Eski: %.2f): ", temp->final);
            scanf("%f", &temp->final);

            // Notlar değiştiği için ortalama ve harf notunu yeniden hesapla
            temp->ortalama = ortalamaHesapla(temp->vize, temp->final);
            harfNotuHesapla(temp->ortalama, temp->harf);

            // Değişiklikleri dosyaya yansıt
            dosyayaKaydet();
            
            printf("Ogrenci basariyla guncellendi!\n");
            return; // İşlem bitti, fonksiyondan çık
        }
        temp = temp->next;
    }
    
    // Döngü biter ve return çalışmazsa öğrenci bulunamamış demektir
    printf("Ogrenci bulunamadi!\n");
}

void ogrenciSil() {
    if (head == NULL) {
        printf("Sistemde silinecek ogrenci yok.\n");
        return;
    }

    int silinecekId;
    printf("Silinecek Ogrenci ID: ");
    scanf("%d", &silinecekId);

    struct Ogrenci* temp = head;
    struct Ogrenci* prev = NULL;

    if (temp != NULL && temp->id == silinecekId) {
        head = temp->next;
        free(temp);
        dosyayaKaydet();
        printf("Ogrenci basariyla silindi!\n");
        return;
    }

    while (temp != NULL && temp->id != silinecekId) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Ogrenci bulunamadi!\n");
        return;
    }

    prev->next = temp->next;
    free(temp);
    
    dosyayaKaydet();
    printf("Ogrenci basariyla silindi!\n");
}

float ortalamaHesapla(float vize, float final) {
    return (vize * 0.4) + (final * 0.6);
}

void harfNotuHesapla(float ortalama, char* harf) {
    if(ortalama >= 90) strcpy(harf, "AA");
    else if(ortalama >= 85) strcpy(harf, "BA");
    else if(ortalama >= 80) strcpy(harf, "BB");
    else if(ortalama >= 75) strcpy(harf, "CB");
    else if(ortalama >= 65) strcpy(harf, "CC");
    else if(ortalama >= 58) strcpy(harf, "DC");
    else if(ortalama >= 50) strcpy(harf, "DD");
    else strcpy(harf, "FF");
}

void dosyayaKaydet() {
    FILE *dosya = fopen("ogrenciler.txt", "w");
    if(dosya == NULL) return;

    struct Ogrenci* temp = head;
    while(temp != NULL) {
        fprintf(dosya, "%d %s %.2f %.2f %.2f %s\n", 
                temp->id, temp->ad, temp->vize, 
                temp->final, temp->ortalama, temp->harf);
        temp = temp->next;
    }
    
    fclose(dosya);
}

void dosyadanOku() {
    FILE *dosya = fopen("ogrenciler.txt", "r");
    if(dosya == NULL) return;

    int id; char ad[50]; float vize, final, ortalama; char harf[3];

    while(fscanf(dosya, "%d %s %f %f %f %s", &id, ad, &vize, &final, &ortalama, harf) != EOF) {
        struct Ogrenci* yeni = (struct Ogrenci*)malloc(sizeof(struct Ogrenci));
        yeni->id = id;
        strcpy(yeni->ad, ad);
        yeni->vize = vize;
        yeni->final = final;
        yeni->ortalama = ortalama;
        strcpy(yeni->harf, harf);
        yeni->next = NULL;

        if (head == NULL) {
            head = yeni;
        } else {
            struct Ogrenci* temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = yeni;
        }
    }
    fclose(dosya);
}

void bellegiTemizle() {
    struct Ogrenci* temp = head;
    struct Ogrenci* sonraki;

    while (temp != NULL) {
        sonraki = temp->next;
        free(temp);
        temp = sonraki;
    }
    head = NULL;
}