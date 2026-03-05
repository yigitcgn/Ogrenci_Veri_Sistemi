# 🎓 Öğrenci Bilgi Sistemi (Student Information System)

Bu proje, C programlama dili kullanılarak geliştirilmiş, dinamik bellek yönetimi ve veri kalıcılığı (file handling) içeren tam kapsamlı bir *CRUD* (Create, Read, Update, Delete) konsol uygulamasıdır. 

Sabit boyutlu diziler (arrays) yerine **Tek Yönlü Bağlı Liste (Singly Linked List)** mimarisi kullanılarak geliştirilmiş olup, RAM kullanımı optimize edilmiştir.

## 🚀 Özellikler (Features)
* **Tam CRUD Operasyonları:** Öğrenci ekleme, listeleme, güncelleme ve silme.
* **Dinamik Bellek Yönetimi:** `malloc` ve `free` fonksiyonları ile ihtiyaca göre bellek tahsisi ve bellek sızıntısı (memory leak) koruması.
* **Dosya İşlemleri (Data Persistence):** Girilen veriler `ogrenciler.txt` dosyasına kaydedilir ve program kapatılıp açıldığında veri kaybı yaşanmaz.
* **Otomatik Hesaplamalar:** Vize ve final notlarına göre ağırlıklı ortalama ve harf notu (AA, BA, BB vb.) hesaplama algoritması.
* **ID Kontrolü:** Aynı ID ile birden fazla öğrenci eklenmesini engelleyen güvenlik kontrolü.

## 💻 Kurulum ve Çalıştırma

Projeyi yerel makinenizde çalıştırmak için aşağıdaki adımları izleyebilirsiniz:

1. Repoyu klonlayın:
   ```bash
   git clone https://github.com/yigitcgn/ogrenci-bilgi-sistemi.git

2. Proje dizinine gidin:
cd ogrenci-bilgi-sistemi

3. C dosyasını derleyin (GCC kullanarak):
gcc main.c -o ogrenci_sistemi

4. Programı çalıştırın:
./ogrenci_sistemi
