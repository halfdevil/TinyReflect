#include "Class.h"
#include "ClassVisitor.h"

namespace TinyReflect
{
	Class::Class(const Class* parent, const char* name, uint32_t size, Field* fields, Field* lastField)	: 
		Type(name, size), 
		mParent(parent), 
		mFields(fields), 
		mLastField(lastField)
	{
	}

	Iterator<Field> Class::getFields() const
	{
		return Iterator<Field>(mFields, mLastField);
	}

	const Field* Class::getField(const char* name) const
	{
		for (auto& field : getFields())
		{
			if (strcmp(field.getName(), name) == 0)
			{
				return &field;
			}
		}

		return nullptr;
	}

	void Class::visitField(const void* ptr, const Field* field, ClassVisitor* visitor,
		int32_t depth, int32_t arrayElem) const
	{
		const Type* type = field->getType();
		const FieldQualifier& qualifier = field->getQualifier();

		if (qualifier.isArray)
		{
			visitor->arrayElement(type, depth, arrayElem);
		}
		else
		{
			visitor->classMember(field, depth);
		}

		if (type->isRecord())
		{
			const Class* cls = (const Class*)type;

			if (qualifier.isPointer)
			{
				const void* p = *(const void**)ptr;
				cls->visit(p, visitor, depth);
			}
			else
			{
				cls->visit(ptr, visitor, depth);
			}
		}
		else
		{
			if (field->getFlags() & (uint8_t)FieldFlags::CString)
			{
				visitor->stringPrimitive(type, ptr);
			}
			else
			{
				visitor->primitive(type, ptr);
			}
		}
	}

	void Class::visitArray(const void* ptr, const Field* field, ClassVisitor* visitor, int32_t depth) const
	{
		const Type* type = field->getType();
		const FieldQualifier& qualifier = field->getQualifier();

		visitor->classMember(field, depth);
		visitor->arrayBegin(type, depth, (int32_t)qualifier.arrayLen);

		const char* p = (const char*)ptr;
		for (uint32_t i = 0; i < qualifier.arrayLen; i++)
		{
			visitField(p, field, visitor, depth + 1, i);
			p += type->getSize();
		}

		visitor->arrayEnd(type, depth);
	}

	void Class::visit(const void* instance, ClassVisitor* visitor, int32_t depth) const
	{
		if (!instance)
		{
			visitor->primitive(this, instance);
			return;
		}

		visitor->classBegin(this, depth);

		for (auto& field : getFields())
		{
			const void* ptr = field.getVoidPointer(instance);
			const FieldQualifier& qualifier = field.getQualifier();

			if (qualifier.isArray)
			{
				visitArray(ptr, &field, visitor, depth + 1);
			}
			else
			{
				visitField(ptr, &field, visitor, depth + 1);
			}
		}

		visitor->classEnd(this, depth);
	}

	bool Class::isRecord() const
	{
		return true;
	}

	bool Class::isSubclassOf(const Class* cls) const
	{
		const Class* parent = mParent;
		while (parent != nullptr)
		{
			if (parent == cls)
			{
				return true;
			}

			parent = parent->mParent;
		}

		return false;
	}

	bool Class::hasChild(const Class* cls) const
	{
		for (const Class* c : mChildren)
		{
			if (c == cls)
			{
				return true;
			}

			if (hasChild(c))
			{
				return true;
			}
		}

		return false;
	}

	bool Class::hasChild(uint64_t type) const
	{
		for (const Class* c : mChildren)
		{
			if (c->getHash() == type)
			{
				return true;
			}

			if (hasChild(c))
			{
				return true;
			}
		}

		return false;
	}

	void Class::addChild(const Class* cls) const
	{
		if (cls)
		{
			const_cast<Class*>(this)->mChildren.push_back(cls);
		}
	}
}