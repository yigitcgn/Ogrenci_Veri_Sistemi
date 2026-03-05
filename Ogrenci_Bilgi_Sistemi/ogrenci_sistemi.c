#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Ogrenci {
    int id;
    char ad[50];
    float vize;
    float final;
    float ortalama;
    char harf[3];
    struct Ogrenci* next;
} Ogrenci;

Ogrenci* head = NULL;

float guvenliNotAl(const char* mesaj) {
    char tampon[64];
    float deger;
    while (1) {
        printf("%s", mesaj);
        scanf("%s", tampon);

        if (strlen(tampon) > 3) {
            printf("[HATA] En fazla 3 hane ve maksimum 100 girebilirsiniz!\n");
            continue;
        }

        deger = atof(tampon);
        if (deger < 0 || deger > 100) {
            printf("[HATA] Not 0-100 arasinda olmalidir!\n");
        } else if (deger == 0 && tampon[0] != '0') {
            printf("[HATA] Gecersiz giris!\n");
        } else {
            return deger;
        }
    }
}

float hesaplaOrtalama(float v, float f) { return (v * 0.4) + (f * 0.6); }

void belirleHarfNotu(float ort, char* h) {
    if(ort >= 90) strcpy(h, "AA");
    else if(ort >= 80) strcpy(h, "BA");
    else if(ort >= 70) strcpy(h, "BB");
    else if(ort >= 60) strcpy(h, "CC");
    else if(ort >= 50) strcpy(h, "DD");
    else strcpy(h, "FF");
}

void dosyayaKaydet() {
    FILE* f = fopen("database.txt", "w");
    if(!f) return;
    Ogrenci* t = head;
    while(t) {
        fprintf(f, "%d|%s|%.2f|%.2f|%.2f|%s\n", t->id, t->ad, t->vize, t->final, t->ortalama, t->harf);
        t = t->next;
    }
    fclose(f);
}

void listeyeEkle(Ogrenci* yeni) {
    if (!head) head = yeni;
    else {
        Ogrenci* t = head;
        while (t->next) t = t->next;
        t->next = yeni;
    }
}

void dosyadanYukle() {
    FILE* f = fopen("database.txt", "r");
    if(!f) return;
    while(!feof(f)) {
        Ogrenci* y = (Ogrenci*)malloc(sizeof(Ogrenci));
        if(fscanf(f, "%d|%[^|]|%f|%f|%f|%s\n", &y->id, y->ad, &y->vize, &y->final, &y->ortalama, y->harf) == 6) {
            y->next = NULL;
            listeyeEkle(y);
        } else free(y);
    }
    fclose(f);
}

void yeniKayit() {
    Ogrenci* y = (Ogrenci*)malloc(sizeof(Ogrenci));
    printf("ID: "); scanf("%d", &y->id);
    Ogrenci* t = head;
    while(t) {
        if(t->id == y->id) { printf("[!] ID mevcut!\n"); free(y); return; }
        t = t->next;
    }
    printf("Ad Soyad: "); getchar();
    fgets(y->ad, 50, stdin); y->ad[strcspn(y->ad, "\n")] = 0;
    
    y->vize = guvenliNotAl("Vize (0-100): ");
    y->final = guvenliNotAl("Final (0-100): ");
    y->ortalama = hesaplaOrtalama(y->vize, y->final);
    belirleHarfNotu(y->ortalama, y->harf);
    y->next = NULL;
    listeyeEkle(y);
    dosyayaKaydet();
    printf("[OK] Eklendi.\n");
}

void listele() {
    Ogrenci* t = head;
    printf("\n%-5s %-20s %-8s %-5s\n", "ID", "AD SOYAD", "ORT", "NOT");
    while(t) {
        printf("%-5d %-20s %-8.2f %-5s\n", t->id, t->ad, t->ortalama, t->harf);
        t = t->next;
    }
}

void sil() {
    int id; printf("Silinecek ID: "); scanf("%d", &id);
    Ogrenci *curr = head, *prev = NULL;
    while(curr && curr->id != id) { prev = curr; curr = curr->next; }
    if(!curr) return;
    if(!prev) head = curr->next;
    else prev->next = curr->next;
    free(curr);
    dosyayaKaydet();
    printf("[OK] Silindi.\n");
}

void guncelle() {
    int id; printf("Guncellenecek ID: "); scanf("%d", &id);
    Ogrenci* t = head;
    while(t) {
        if(t->id == id) {
            t->vize = guvenliNotAl("Yeni Vize: ");
            t->final = guvenliNotAl("Yeni Final: ");
            t->ortalama = hesaplaOrtalama(t->vize, t->final);
            belirleHarfNotu(t->ortalama, t->harf);
            dosyayaKaydet();
            return;
        }
        t = t->next;
    }
}

void bellekTahliye() {
    Ogrenci* t;
    while(head) { t = head; head = head->next; free(t); }
}

int main() {
    dosyadanYukle();
    int s;
    do {
        printf("\n1.Ekle 2.Listele 3.Guncelle 4.Sil 5.Cikis\nSecim: ");
        if(scanf("%d", &s) != 1) { while(getchar() != '\n'); continue; }
        if(s == 1) yeniKayit();
        else if(s == 2) listele();
        else if(s == 3) guncelle();
        else if(s == 4) sil();
    } while(s != 5);
    dosyayaKaydet();
    bellekTahliye();
    return 0;
}
