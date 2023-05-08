#pragma once

#include "DefaultTypes.h"
#include "Class.h"
#include "Enum.h"
#include "StringClass.h"
#include "VectorClass.h"
#include "MapClass.h"

namespace TinyReflect
{
#ifdef __REFLECT__
	#define CLASS(...)			__attribute__((annotate("reflect-class," #__VA_ARGS__)))
	#define STRUCT(...)			__attribute__((annotate("reflect-struct," #__VA_ARGS__)))
	#define ENUM(...)			__attribute__((annotate("reflect-enum," #__VA_ARGS__)))
	#define PROPERTY(...)		__attribute__((annotate("reflect-field," #__VA_ARGS__)))
	#define BODY()
#else
	#define CLASS(...)			
	#define STRUCT(...)		
	#define ENUM(...)			
	#define PROPERTY(...)
	#define BODY()                                                                               \
			template <typename T>                                                                \
			friend const TinyReflect::Class* GetClassImpl(TinyReflect::ClassTag<T>);             
																	                             
#endif
}