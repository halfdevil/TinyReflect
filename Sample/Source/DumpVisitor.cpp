#include "DumpVisitor.h"
#include "DefaultTypes.h"
#include "Class.h"
#include <stdio.h>

namespace TinyReflect
{
	char const* spaces =
		"                                                                             "
		"                                                                             "
		"                                                                             ";

	void DumpVisitor::classBegin(const Class* c, int32_t depth)
	{
		printf("%s {", c->getName());
	}

	void DumpVisitor::classEnd(const Class* c, int32_t depth)
	{
		printf("%.*s}", depth * 2, spaces);
	}

	void DumpVisitor::classMember(const Field* f, int32_t depth)
	{
		printf("%.*s.%s = ", depth * 2, spaces, f->getName());
	}

	void DumpVisitor::arrayBegin(const Type* t, int32_t depth, int32_t length)
	{
		printf("[");
	}

	void DumpVisitor::arrayEnd(const Type* t, int32_t depth)
	{
		printf("%.*s]", depth * 2, spaces);
	}

	void DumpVisitor::arrayElement(const Type* t, int32_t depth, int32_t elem)
	{
		printf("%.*s[%d] = ", depth * 2, spaces, elem);
	}

	void DumpVisitor::mapBegin(const Type* t, int32_t depth, int32_t count)
	{
		printf("{");
	}

	void DumpVisitor::mapEnd(const Type* t, int32_t depth)
	{
		printf("%.*s}", depth * 2, spaces);
	}

	void DumpVisitor::mapElement(const Type* kt, const Type* vt, int32_t depth, const void* key)
	{
		printf("%.*s[%s] = ", depth * 2, spaces, getValue(kt, key).c_str());
	}

	void DumpVisitor::primitive(const Type* t, const void* instance)
	{
		if (!instance)
		{
			printf("nullptr");
			return;
		}

		printf("%s{ %s }", t->getName(), getValue(t, instance).c_str());
	}

	void DumpVisitor::stringPrimitive(const Type* t, const void* instance)
	{
		if (!instance)
		{
			printf("nullptr");
			return;
		}

		const char** str = (const char**)instance;
		printf("%s{ %s }", t->getName(), *str);
	}

	std::string DumpVisitor::getValue(const Type* t, const void* instance)
	{
		if (t->getHash() == GetType<float>()->getHash())
		{
			return std::to_string(*((float*)instance));
		}
		else if (t->getHash() == GetType<int8_t>()->getHash())
		{
			return std::to_string(*((int8_t*)instance));
		}
		else if (t->getHash() == GetType<uint8_t>()->getHash())
		{
			return std::to_string(*((uint8_t*)instance));
		}
		else if (t->getHash() == GetType<int16_t>()->getHash())
		{
			return std::to_string(*((int16_t*)instance));
		}
		else if (t->getHash() == GetType<uint16_t>()->getHash())
		{
			return std::to_string(*((uint16_t*)instance));
		}
		else if (t->getHash() == GetType<int32_t>()->getHash())
		{
			return std::to_string(*((int32_t*)instance));
		}
		else if (t->getHash() == GetType<uint32_t>()->getHash())
		{
			return std::to_string(*((uint32_t*)instance));
		}
		else if (t->getHash() == GetType<int64_t>()->getHash())
		{
			return std::to_string(*((int64_t*)instance));
		}
		else if (t->getHash() == GetType<uint64_t>()->getHash())
		{
			return std::to_string(*((uint64_t*)instance));
		}

		return {};
	}
}