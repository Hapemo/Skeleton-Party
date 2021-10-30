/*---------------------------------------------------------
 * file:	game.c
 * author:	
 * email:	
*
 * brief:	
*
 * documentation link:
 * https://inside.digipen.edu/main/GSDP:GAM100/CProcessing
*
 * Copyright � 2020 DigiPen, All rights reserved.
* ---------------------------------------------------------*/
/*
Functions to call to modify hp
PlayerSetHealth (int Basehealth)
Playertakedamage(int damageAmt)
PlayerHealed(int healAmt)

// art not included
// contact isaac to instance new hp bar
*/

#include <stdio.h>
#include "cprocessing.h"
#include "game.h"


#define pueple CP_Color_Create(255, 0, 0, 255)

CP_Image hpbar = NULL;


// do not temper any thing from here to next comment
// HealthSystem Object decleration below
#define NewHealthSystem(VarName)	\
	VarName.set = setter;			\
	VarName.get = getter;			\
	VarName.damage = damager;		\
	VarName.heal = healer;

typedef struct HealthSystem {
	int health;
	void (*set)(struct HealthSystem* inst, int);
	int (*get)(struct HealthSystem*);
	void (*damage)(struct HealthSystem* inst, int);
	void (*heal)(struct HealthSystem* inst, int);
} HealthSystem;

HealthSystem p1;

void setter(HealthSystem* inst, int health)
{
	inst->health = health;
}

int getter(HealthSystem* inst)
{
	return inst->health;
}

void damager(HealthSystem* inst, int damageamount)
{
	inst->health -= damageamount;
}

void healer(HealthSystem* inst, int healamount)
{
	inst->health += healamount;
}
// HealthSystem Object decleration above 

//call function to set players base health 
void PlayerSetHealth (int Basehealth)
{
    p1.set(&p1,Basehealth);
}

// call function when player takes damage and enter amount of damage taken 
void Playertakedamage(int damageAmt)
{
    p1.damage(&p1, damageAmt);
}
// call function when player is healed and enter amount healed
void PlayerHealed(int healAmt)
{
    p1.heal(&p1, healAmt);
}
