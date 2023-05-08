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

	void DumpVisitor::classBegin(const Class* c, int32_t depth, const void* instance)
	{
		printf("%s {\n", c->getName());
	}

	void DumpVisitor::classEnd(const Class* c, int32_t depth)
	{
		printf("%.*s}\n", depth * 4, spaces);
	}

	void DumpVisitor::classMember(const Field* f, int32_t depth)
	{
		printf("%.*s.%s = ", depth * 4, spaces, f->getName());
	}

	void DumpVisitor::arrayBegin(const Type* t, int32_t depth, int32_t length, const void* instance)
	{
		printf("[\n");
	}

	void DumpVisitor::arrayEnd(const Type* t, int32_t depth)
	{
		printf("%.*s]\n", depth * 4, spaces);
	}

	void DumpVisitor::arrayElement(const Type* t, int32_t depth, int32_t elem)
	{
		printf("%.*s[%d] = ", depth * 4, spaces, elem);
	}

	void DumpVisitor::vectorBegin(const Type* t, int32_t depth, int32_t length, const void* instance)
	{
		printf("[\n");
	}

	void DumpVisitor::vectorEnd(const Type* t, int32_t depth)
	{
		printf("%.*s]\n", depth * 4, spaces);
	}

	void DumpVisitor::vectorElement(const Type* t, int32_t depth, int32_t elem)
	{
		printf("%.*s[%d] = ", depth * 4, spaces, elem);
	}

	void DumpVisitor::mapBegin(const Type* t, int32_t depth, int32_t count, const void* instance)
	{
		printf("{\n");
	}

	void DumpVisitor::mapEnd(const Type* t, int32_t depth)
	{
		printf("%.*s}\n", depth * 4, spaces);
	}

	void DumpVisitor::mapElement(const Type* kt, const Type* vt, int32_t depth, const void* key)
	{
		printf("%.*s[%s] = ", depth * 4, spaces, getValue(kt, key).c_str());
	}

	void DumpVisitor::enumElement(const Type* t, const void* instance)
	{
		if (!instance)
		{
			printf("nullptr\n");
			return;
		}

		printf("%s{ %s }\n", t->getName(), std::to_string(*((uint32_t*)instance)).c_str());
	}

	void DumpVisitor::primitive(const Type* t, const void* instance)
	{
		if (!instance)
		{
			printf("nullptr\n");
			return;
		}

		printf("%s{ %s }\n", t->getName(), getValue(t, instance).c_str());
	}

	void DumpVisitor::stringPrimitive(const Type* t, const void* instance)
	{
		if (!instance)
		{
			printf("nullptr\n");
			return;
		}

		const char** str = (const char**)instance;
		printf("%s{ %s }\n", t->getName(), *str);
	}

	void DumpVisitor::stringElement(const Type* t, const void* instance)
	{
		if (!instance)
		{
			printf("nullptr\n");
			return;
		}

		const std::string* str = (const std::string*)instance;
		printf("%s{ %s }\n", t->getName(), str->c_str());
	}

	std::string DumpVisitor::getValue(const Type* t, const void* instance)
	{
		if (t->getHash() == GetType<bool>()->getHash())
		{
			return std::to_string(*((bool*)instance));
		}
		else if (t->getHash() == GetType<float>()->getHash())
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