Encoder okuma kodlarımı modüler olarak struct şeklinde yazdım. Hem daha sistematik hem de main de kalabalık olmadı böylece. Main içinde ise timer4 modülünü 10 ms zamana ayarladım ve her taşma olduğunda enkoder verileri tekrar hesaplanacak.

  RPM Hesabı=  [Puls/Sn * 60] / CPR
Açısal Hız (Rad/s)=(Puls/Sn * 2 * pi) / CPR


Filtre olarak şimdilik Üstel Hareketli Ortalama filtresi kullandım. 
                                 y [ i ]=α⋅x [i ]+( 1−α )⋅y [ i−1 ]
işlem sırası;
1.	Ham Veri Alımı: Timer'dan delta pulse okunur.
2.	Filtreleme: filtered_pulse hesaplanır.
3.	Hız Dönüşümü: Filtrelenmiş pulse değeri üzerinden RPM ve Radyan/Saniye hesaplanır.

![7386827c-2ae1-4bbc-a178-e470c92daae6](https://github.com/user-attachments/assets/dbb23c12-d0e5-49aa-abe9-64493c3672da)
![d7cd8cc3-7f73-4c22-8423-655fe60fd65e](https://github.com/user-attachments/assets/65cb59c7-21c1-4ad3-afee-1edbf45b9c89)
<img width="945" height="456" alt="image" src="https://github.com/user-attachments/assets/522008d3-db87-4657-a782-16bd8548d3c2" />
