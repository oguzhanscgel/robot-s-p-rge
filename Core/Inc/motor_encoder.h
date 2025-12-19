#ifndef INC_MOTOR_ENCODER_H_
#define INC_MOTOR_ENCODER_H_

#include "stdint.h"
#include  "main.h"

typedef struct{
	int16_t velocity;
	int64_t position;
	int32_t son_counter;

	float rpm;             // Dakikadaki devir
	float rad_s;           // Radyan/saniye (PID için)
	float filtered_pulse;  // Filtrelenmiş pulse değişimi (Gürültü önlemek için)

}encoder_str;


void update_encoder(encoder_str *encoder_value, TIM_HandleTypeDef *htim);
void reset_encoder(encoder_str *encoder_value);
void calculate_velocity(encoder_str *encoder_value, float dt_seconds);



#endif /* INC_MOTOR_ENCODER_H_ */
