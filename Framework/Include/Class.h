#pragma once

#include "Type.h"
#include "Field.h"
#include "Iterator.h"
#include <string>
#include <vector>

namespace TinyReflect
{
	class ClassVisitor;

	template <typename T>
	class ClassTag
	{
	};

	class Class : public Type
	{
	public:

		Class() = default;
		Class(const Class* parent, const char* name, uint32_t size, Field* fields, Field* lastField);

		Iterator<Field> getFields() const;
		const Field* getField(const char* name) const;

		virtual void visitField(const void* ptr, const Field* field, ClassVisitor* visitor,
			int32_t depth, int32_t arrayElem = -1) const;

		virtual void visitArray(const void* ptr, const Field* field, ClassVisitor* visitor,
			int32_t depth) const;

		virtual void visit(const void* instance, ClassVisitor* visitor,
			int32_t depth = 0) const;

		virtual bool isRecord() const override;
		virtual bool isSubclassOf(const Class* cls) const;
		virtual bool hasChild(const Class* cls) const;
		virtual bool hasChild(uint64_t type) const;
		virtual void addChild(const Class* cls) const;

	protected:

		const Class* mParent{ nullptr };
		std::vector<const Class*> mChildren;

		Field* mFields{ nullptr };
		Field* mLastField{ nullptr };
	};

	template <typename T>
	const Class* GetClassImpl(ClassTag<T>);

	template <typename T>
	const Class* GetClass()
	{
		return GetClassImpl(ClassTag<T>());
	}
}