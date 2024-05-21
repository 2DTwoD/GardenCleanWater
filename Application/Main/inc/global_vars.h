#ifndef GLOBAL_VARS_H
#define GLOBAL_VARS_H

#include "coil.h"
#include "simple_input.h"
#include "sequence.h"
#include "common_timer.h"
#include "on_delay.h"
#include "pulse.h"

//Входа/выхода
SimpleInputDelayed B1(GPIOA, 0, 200);
SimpleInputDelayed H1(GPIOA, 1, 200);
SimpleInputDelayed B2(GPIOA, 2, 200);
SimpleInputDelayed H2(GPIOA, 3, 200);
SimpleInputDelayed B3(GPIOA, 4, 200);
SimpleInputDelayed H3(GPIOA, 5, 200);
SimpleInputDelayed S4(GPIOA, 6, 5000);
SimpleInputDelayed S5(GPIOA, 7, 5000);
SimpleInputDelayed S6(GPIOA, 8, 10000);
Coil C1(GPIOA, 9);
Coil O1(GPIOA, 10);
Coil D1(GPIOA, 15);
CoilPulse M1(GPIOB, 0, 1000);
Coil C2(GPIOB, 1);
Coil O2(GPIOB, 3);
Coil D2(GPIOB, 4);
CoilPulse M2(GPIOB, 5, 1000);
Coil C3(GPIOB, 6);
Coil O3(GPIOB, 7);
Coil D3(GPIOB, 8);
CoilPulse M3(GPIOB, 9, 1000);
Coil D4(GPIOB, 10);
Coil M6(GPIOB, 11);
Coil M7(GPIOB, 12);
Coil Me1(GPIOB, 13);
Coil Me2(GPIOB, 14);
Coil Me3(GPIOB, 15);

//Последовательности
//Бак отстойника1:
uint8_t OB1step;
Sequence OB1s0(&OB1step, 0);
SequenceDelayed OB1s1(&OB1step, 1, 120000);//2 минуты
SequenceDelayed OB1s2(&OB1step, 2, 30000);//30 секунд
Sequence OB1s3(&OB1step, 3);
SequenceDelayed OB1s4(&OB1step, 4, 345600000);//96 часов
Sequence OB1s5(&OB1step, 5);
Pulse OB1s4MeTimer(3600000);//1 час

//Чистый бак:
uint8_t CHBstep;
Sequence CHBs0(&CHBstep, 0);
SequenceDelayed CHBs1(&CHBstep, 1, 15000);//15 секунд
Sequence CHBs2(&CHBstep, 2);

//Очередь
Sequence *queue[] = {nullptr, nullptr, nullptr};

IUpdated1ms *update1msObjects[] = {
	&B1,
	&H1,
	&B2,
	&H2,
	&B3,
	&H3,
	&S4,
	&S5,
	&S6,
	&M1,
	&M2,
	&M3,
	&OB1s1,
	&OB1s2,
	&OB1s4,
	&OB1s4MeTimer,
	&CHBs1
};

uint8_t updateObjectsSize = sizeof(update1msObjects) / sizeof(*update1msObjects);
#endif //GLOBAL_VARS_H