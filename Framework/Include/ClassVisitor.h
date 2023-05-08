#pragma once

#include <cstdint>

namespace TinyReflect
{
	class Type;
	class Field;
	class Class;

	class ClassVisitor
	{
	public:

		ClassVisitor() = default;
		virtual ~ClassVisitor() = default;

		virtual void classBegin(const Class* c, int32_t depth) = 0;
		virtual void classEnd(const Class* c, int32_t depth) = 0;
		virtual void classMember(const Field* f, int32_t depth) = 0;

		virtual void arrayBegin(const Type* t, int32_t depth, int32_t length) = 0;
		virtual void arrayEnd(const Type* t, int32_t depth) = 0;
		virtual void arrayElement(const Type* t, int32_t depth, int32_t elem) = 0;

		virtual void mapBegin(const Type* t, int32_t depth, int32_t count) = 0;
		virtual void mapEnd(const Type* t, int32_t depth) = 0;
		virtual void mapElement(const Type* kt, const Type* vt, int32_t depth, const void* key) = 0;

		virtual void primitive(const Type* t, const void* instance) = 0;
		virtual void stringPrimitive(const Type* t, const void* instance) = 0;
	};
}