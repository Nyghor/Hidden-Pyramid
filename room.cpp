#include <iostream>
#include "room.h"
#include "exit.h"
#include "creature.h"
#include "item.h"
#include "globals.h"

using namespace std;

Room::Room(const char* name, const char* description) :
	Entity(name, description,nullptr) {

	type = ROOM;
}

Room::~Room() {

}

void Room::look() const {
	cout << name << endl;
	cout << description << endl;
	bool first = true;

	for (list<Entity*>::const_iterator it = entitiesInside.begin(); it != entitiesInside.cend(); ++it) {
		if ((*it)->type == EXIT) {
			if (first) {
				cout << "You can see an exit, ";
				lookThing((*it));
				first = false;
			}
			else {
				cout << ", ";
				lookThing((*it));
			}
		}
	}
	cout << endl;
	first = true;

	for (list<Entity*>::const_iterator it = entitiesInside.begin(); it != entitiesInside.cend(); ++it) {
		if ((*it)->type == CREATURE) {
			if (first) {
				cout << "You see a ";
				lookThing((*it));
				first = false;
			}
			else {
				cout << ", ";
				lookThing((*it));
			}
		}
	}
	cout << endl;
	first = true;

	for (list<Entity*>::const_iterator it = entitiesInside.begin(); it != entitiesInside.cend(); ++it) {
		if ((*it)->type == ITEM) {
			if (first) {
				cout << "Items you can see: ";
				lookThing((*it));
				first = false;
			}
			else {
				cout << ", ";
				lookThing((*it));
			}
		}
	}
	cout << endl;
}

void Room::lookThing(const Entity* entity) const {
	switch (entity->type) {
		case EXIT:
		{
			if (same(((Exit*)entity)->getSource()->name, name))
				cout << ((Exit*)entity)->description;
			else
				cout << ((Exit*)entity)->getSecondDescr();
		}
		case CREATURE:
		{
			if (((Creature*)entity)->isAlive())
				cout << ((Creature*)entity)->name;
			else
				cout << "corpse of a " << ((Creature*)entity)->name;
		}
		case ITEM:
		{
			cout << ((Item*)entity)->name;
		}
	}
}