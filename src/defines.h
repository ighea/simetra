//-DDEBUG for debug messages
#ifdef DEBUG
#define DEBUG_OUT(s) ( printf(s) )
#define DEBUG_OUT2(s,i) ( printf(s,i) ) 
#define DEBUG_OUT3(s,i,j) ( printf(s,i,j) ) 
#else
#define DEBUG_OUT(s)
#define DEBUG_OUT2(s,i)
#define DEBUG_OUT3(s,i,j)
#endif

#define OTUS_SPAWNING_TYPE_COUNT 2
#define OTUS_SPAWNING_TYPE_KILL 0
#define OTUS_SPAWNING_TYPE_TIMED 1

#define GUN_TYPE_GENERAL 0;
#define GUN_TYPE_SHOTGUN 1

#define BONUSBOX_HEALKIT 0
#define BONUSBOX_SHOTGUN 1

#define VERSION "Simetra v0.06 - \"Bloatness\" © ighea"

