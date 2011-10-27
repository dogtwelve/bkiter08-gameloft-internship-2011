#ifndef __MACROS_H__
#define __MACROS_H__

#include "Header.h"

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

#define DEG_2_RAD (3.14159f/180.0f)
#define RAD_2_DEG (180.0f/3.14159f)

// compile - runtime helper
#if CONFIG_PLATFORM==PLATFORM_WIN32_VS
#	include <stdlib.h>
#	define TODO(x) __pragma(message("[TODO]:" __FILE__ "("TOSTRING(__LINE__)") " TOSTRING(x))); Log(x);
#	define BREAK_IF(cond, _message) if (cond) {Log(_message); _asm int 3}
#	define BREAK(_message) BREAK_IF(true, _message)
#	define EXEC(command)	system(command)
#else
#	define TODO(x) ;
#	define WARNING(x) ;
#	define ERR(x) ;
#	define BREAK_IF(cond, _message) ;
#	define BREAK(cond, _message) ;
#	define EXEC(command)	;
#endif

// log helper
#if CONFIG_PLATFORM==PLATFORM_WIN32_VS
extern void SetCommandTextColor(WORD);
#	define Log(...)			printf(__VA_ARGS__);printf("\n")
#	define LogError(...)	printf(__VA_ARGS__);printf("\n")
#	define LogWarning(...)	printf(__VA_ARGS__);printf("\n")
#elif CONFIG_PLATFORM==PLATFORM_ANDROID
#	include <android/log.h>
#	define Log(...)  __android_log_print(ANDROID_LOG_INFO, "NativeLib" ,__VA_ARGS__)
#	define LogError(...)  __android_log_print(ANDROID_LOG_ERROR, "NativeLib" ,__VA_ARGS__)
#endif





// struct alignment
#if CONFIG_PLATFORM==PLATFORM_WIN32_VS
#	define __PACK__
#else
#	define __PACK__		
#endif


#define SAFE_DEL(a)					{if(a){delete (a);(a) = NULL;}}
#define SAFE_DEL_ARRAY(a)			{if(a){delete[] (a);(a) = NULL;}}
#define SAFE_DEL_ARRAY_TYPE(a, t)	{if((t)a){delete[] ((t)(a));(a) = NULL;}}
#define SAFE_DEL_ARRAY_OBJ(p, n)	{if ((p)!=NULL) {for (int __i = 0; __i < (n); __i++) SAFE_DEL((p)[__i]); SAFE_DEL_ARRAY(p);}}
#define SAFE_DEL_ARRAY_ARRAY(p, n)	{if ((p)!=NULL) {for (int __i = 0; __i < (n); __i++) SAFE_DEL_ARRAY((p)[__i]); SAFE_DEL_ARRAY(p);}}

#endif