#include <iostream>
#include "mummy.h"
#include "player.h"

Mummy::Mummy(const char* name, const char* description, Entity* entity, const bool& autoRespawn) :
	Creature(name, description, entity), autoRespawn(autoRespawn) {

	type = CREATURE;
	healthPoints = 15;
	maxHealth = 15;

	damage = 2;
	avoiding = false;
	blind = false;
	cdAvoid = 20.f;
	cdAvoidLeft = 20.f;
	cdAvoidTime = 3.f;
	cdAvoidTimeLeft = 3.f;
	minCdAttack = 5.f;
	maxCdAttack = 10.f;
	cdAttack = minCdAttack + (((float)rand()) / (float)RAND_MAX) * (maxCdAttack - minCdAttack);
	cdAttackLeft = cdAttack;
	frameTime = 0.f;
}

Mummy::~Mummy() {

}

bool Mummy::Update(const float& frameTime) {
	this->frameTime = frameTime;
	if (isAlive() == true) {
		target = findPlayer(parent);

		if (target == nullptr)
			return false;

		if (target->inCombat == false && target->isAlive()) {
			target->inCombat = true;
			inCombat = true;
			((Player*)target)->statePlayer = WAITING;
			((Player*)target)->target = this;
			cout << endl << "\nA " << name << " attacks you!" << endl;
			return true;
		}

		if (inCombat) {
			updateCds();
			if (cdAttackLeft <= 0.f && avoiding == false) {
				attack();
				cdAttack = minCdAttack + (((float)rand()) / (float)RAND_MAX) * (maxCdAttack - minCdAttack);
				cdAttackLeft = cdAttack;
				return true;
			}
			else if (cdAvoidLeft <= 0.f && avoiding == false) {
				avoiding = true;
				cdAvoidLeft = cdAvoid;
				cout << "\nThe mummy vanishes, and only some bands are found on the floor" << endl;
				return true;
			}
			else if (cdAvoidTimeLeft <= 0.f) {
				avoiding = false;
				cdAvoidTimeLeft = cdAvoidTime;
				cout << "\nThe bands merge and the mummy appears again" << endl;
				return true;
			}
		}
	}
	else {
		target = nullptr;
		inCombat = false;
		if (autoRespawn) {
			if (findPlayer(parent) == nullptr) {
				healthPoints = maxHealth;
			}
		}
	}
	return false;
}

void Mummy::updateCds() {
	if (cdAvoidLeft > 0.f)
		cdAvoidLeft -= frameTime;
	if (avoiding && cdAvoidTimeLeft > 0.f)
		cdAvoidTimeLeft -= frameTime;
	if (cdAttackLeft > 0.f)
		cdAttackLeft -= frameTime;
}

void Mummy::attack() const {
	if (((Player*)target)->avoiding == false) {
		target->healthPoints -= damage;
		cout << "\nThe mummy gives you a punch, ouch!" << endl;
	}
	else {
		cout << "\nThe mummy tries to punch you, but you avoid the attack!" << endl;
	}
}

void Mummy::increaseMinCdAttack() {
	minCdAttack += 3;
}