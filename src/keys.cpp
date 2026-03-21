#include "trigger.h"
#include "keys.h"
#include <cstdio>
#include <cstring>

std::list<Key*> keys;

void addkey(char* name, int keycode) {
	for (auto* k : keys)
		if (k->code == keycode) return;

	Key* key = new Key();
	key->code = keycode;
	key->name = name;
	keys.push_front(key);
}

void execkey(char* type, int keycode) {
	const size_t typelen = strlen(type);
	for (auto* k : keys) {
		if (k->code == keycode) {
			const size_t len = typelen + strlen(k->name) + 1;
			char* tmp = new char[len];
			snprintf(tmp, len, "%s%s", type, k->name);
			findTrigger(tmp, 0)->exec();
			delete[] tmp;
		}
	}
}