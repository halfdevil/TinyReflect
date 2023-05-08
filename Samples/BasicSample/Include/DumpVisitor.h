#pragma once

#include "ClassVisitor.h"
#include <string>

namespace TinyReflect
{
	class DumpVisitor : public ClassVisitor
	{
	public:

		virtual void classBegin(const Class* c, int32_t depth, const void* instance) override;
		virtual void classEnd(const Class* c, int32_t depth) override;
		virtual void classMember(const Field* f, int32_t depth) override;

		virtual void arrayBegin(const Type* t, int32_t depth, int32_t length, const void* instance) override;
		virtual void arrayEnd(const Type* t, int32_t depth) override;
		virtual void arrayElement(const Type* t, int32_t depth, int32_t elem) override;

		virtual void vectorBegin(const Type* t, int32_t depth, int32_t length, const void* instance) override;
		virtual void vectorEnd(const Type* t, int32_t depth) override;
		virtual void vectorElement(const Type* t, int32_t depth, int32_t elem) override;

		virtual void mapBegin(const Type* t, int32_t depth, int32_t count, const void* instance) override;
		virtual void mapEnd(const Type* t, int32_t depth) override;
		virtual void mapElement(const Type* kt, const Type* vt, int32_t depth, const void* key) override;

		virtual void enumElement(const Type* t, const void* instance) override;
		virtual void primitive(const Type* t, const void* instance) override;
		virtual void stringPrimitive(const Type* t, const void* instance) override;
		virtual void stringElement(const Type* t, const void* instance) override;

	private:

		std::string getValue(const Type* t, const void* instance);
	};
}