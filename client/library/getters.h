#ifndef GETTERS_H 
#define GETTERS_H
#include "structures.h"

#ifdef _WIN32
#define DLLEXPORT extern "C" __declspec(dllexport)
#else
#define DLLEXPORT
#endif

#ifdef __cplusplus
extern "C" {
#endif

DLLEXPORT int creatureGetId(_Creature* ptr);
DLLEXPORT int creatureGetOwner(_Creature* ptr);
DLLEXPORT int creatureGetX(_Creature* ptr);
DLLEXPORT int creatureGetY(_Creature* ptr);
DLLEXPORT int creatureGetHealth(_Creature* ptr);
DLLEXPORT int creatureGetHunger(_Creature* ptr);
DLLEXPORT int creatureGetCarnivorism(_Creature* ptr);
DLLEXPORT int creatureGetHerbivorism(_Creature* ptr);
DLLEXPORT int creatureGetSpeed(_Creature* ptr);
DLLEXPORT int creatureGetMaxStamina(_Creature* ptr);
DLLEXPORT int creatureGetDefense(_Creature* ptr);
DLLEXPORT int creatureGetAge(_Creature* ptr);


DLLEXPORT int plantGetId(_Plant* ptr);
DLLEXPORT int plantGetX(_Plant* ptr);
DLLEXPORT int plantGetY(_Plant* ptr);
DLLEXPORT int plantGetSize(_Plant* ptr);
DLLEXPORT int plantGetAge(_Plant* ptr);


DLLEXPORT int playerGetId(_Player* ptr);
DLLEXPORT char* playerGetPlayerName(_Player* ptr);
DLLEXPORT float playerGetTime(_Player* ptr);



#ifdef __cplusplus
}
#endif

#endif
