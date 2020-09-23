#ifndef _MACROS_H_
#define _MACROS_H_

#define ARR_LEN(arr)		(sizeof(arr) / sizeof(*arr))
#define _STR(a)				#a
#define STR(a)				_STR(a)
#define _JOIN(a, b)			a##b
#define JOIN(a, b)			_JOIN(a, b)

#endif
