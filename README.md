# ÖĞRENCİ BİLGİ SİSTEMİ



Bu çalışma, C programlama dili kullanılarak geliştirilmiş, veri yapıları ve dosya yönetimi prensiplerini temel alan bir yönetim simülasyonudur. Projenin ana odak noktası, statik diziler yerine dinamik bellek yönetimi ve bağlı liste mimarisini kullanarak sistem kaynaklarını verimli kullanmaktır.



## Teknik Özellikler



• Veri Yapısı: Projede Tek Yönlü Bağlı Liste (Singly Linked List) kullanılmıştır. Bu sayede veri ekleme ve silme işlemleri sırasında dizilerdeki gibi kaydırma yapılmasına gerek duyulmaz ve RAM kullanımı çalışma zamanında optimize edilir.



• Veri Kalıcılığı: Girilen veriler ogrenciler.txt dosyası üzerinde saklanır. Program başlatıldığında mevcut veriler dosyadan okunarak bağlı liste yapısına aktarılır; program sonlandırıldığında ise güncel liste dosyaya kaydedilir.



• Dinamik Bellek Yönetimi: malloc ve free fonksiyonları ile bellek tahsisi manuel olarak yönetilmiştir. Program sonlanırken tüm düğümler bellekten temizlenerek bellek sızıntısı (memory leak) oluşması engellenmiştir.



• Akademik Hesaplama Modülü: Vize ve final notları üzerinden ağırlıklı ortalama hesaplanır ve sonuçlar standart harf notu baremine göre sınıflandırılır.



• Hata Denetimi: Sistem, benzersiz ID kontrolü yaparak aynı öğrenci numarasının tekrar kaydedilmesini engeller.



## Kullanılan Fonksiyonlar ve Yapılar



• Struct Yapısı: Öğrenci bilgileri ve sonraki düğüm adresini tutan işaretçileri içeren özelleştirilmiş yapılar.



• CRUD Fonksiyonları: ogrenciEkle, ogrenciSil, ogrenciGuncelle ve listele işlemleri.



• Dosya İşlemleri: fopen, fprintf, fscanf ve fclose ile veri akışı yönetimi.



## Kurulum ve Çalıştırma
Projeyi kendi istemcinizde çalıştırmak için klasörü yükleyip içerisindeki ogrenci_sistemi.exe dosyasını açmanız yeterli olacaktır

Projeyi yerel sisteminizde çalıştırmak için klasörü indirip içerisinden ogrenci\_sistemi.exe adlı exeyi açmanız yeterli olacaktır.



