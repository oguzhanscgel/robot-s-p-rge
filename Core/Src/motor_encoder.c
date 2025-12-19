#include "motor_encoder.h"
#include <math.h> // M_PI için (Eğer hata verirse en başa #define PI 3.14159265 ekle)

// Pololu Motor Redüktör Çıkışı CPR Değeri
#define ROBOT_ENCODER_CPR 2248.86f
#define PI 3.14159265f

// Filtre Katsayısı (0.0 - 1.0 arası).
// 1.0 = Filtre yok, 0.1 = Çok yavaş/yumuşak tepki.
// 0.3 robotlar için genelde iyi bir başlangıçtır.
#define FILTRE_KS 0.3f






void update_encoder(encoder_str *encoder_value, TIM_HandleTypeDef *htim)
{
	uint32_t temp_counter =__HAL_TIM_GET_COUNTER(htim);
	static uint8_t baslama_ani = 0; //static tanımladım cünkü gorev 1 icin tek teker verisi isteniyor
                                    //2 teker için struct icine alicam degiskeni
	if(!baslama_ani)
	{
		encoder_value ->velocity = 0;
		baslama_ani = 1;

	}
	else
	{
		if(temp_counter == encoder_value ->son_counter)  //counter yeni  degeri =counter eski degeri
		{
			encoder_value->velocity =0;
		}
		else if(temp_counter> encoder_value->son_counter)  //counter eski degeri =counter yeni degeri
		{
			if(__HAL_TIM_IS_TIM_COUNTING_DOWN(htim))  //overflow
			{
				encoder_value ->velocity = -encoder_value ->son_counter-
						(__HAL_TIM_GET_AUTORELOAD(htim)-temp_counter);
			}
			else
			{
				encoder_value ->velocity =temp_counter - encoder_value ->son_counter;
			}

		}
		else
		{
			if(__HAL_TIM_IS_TIM_COUNTING_DOWN(htim))
			{
				encoder_value ->velocity =temp_counter - encoder_value ->son_counter;
			}
			else //overflow
			{
				encoder_value ->velocity=temp_counter +
						(__HAL_TIM_GET_AUTORELOAD(htim)- encoder_value ->son_counter);
			}
		}
	}
	encoder_value ->position+=encoder_value->velocity;
	encoder_value ->son_counter=temp_counter;

}

void calculate_velocity(encoder_str *encoder_value, float dt_seconds)
{

   encoder_value->filtered_pulse = (FILTRE_KS * encoder_value->velocity) +
                                    ((1.0f - FILTRE_KS) * encoder_value->filtered_pulse);

    // Saniyedeki Pulse Hızını Bulma
    if(dt_seconds <= 0.0f) return;

    float pulse_per_second = encoder_value->filtered_pulse / dt_seconds;

    // RPM Hesabı
    // Formül: (Pulse/Sn * 60) / CPR
    encoder_value->rpm = (pulse_per_second * 60.0f) / ROBOT_ENCODER_CPR;

    // Radyan/Saniye Hesabı
    // Formül: (Pulse/Sn * 2 * PI) / CPR
    encoder_value->rad_s = (pulse_per_second * 2.0f * PI) / ROBOT_ENCODER_CPR;
}



void reset_encoder(encoder_str *encoder_value)
{

	encoder_value-> velocity =0;
}

