#pragma once

#include "ClassVisitor.h"
#include <stack>

#include "nlohmann/json.hpp"
using json = nlohmann::json;

namespace TinyReflect
{
	class JsonWriter : public ClassVisitor
	{
	public:

		JsonWriter();

		const json& getRoot() const
		{
			return mRoot;
		}

		std::string toString(uint32_t numSpaces = 0) const;
		void write(const std::string& fileName) const;

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

		void pushCurrent(const char* name);
		void popCurrent();

	private:

		json mRoot;
		json* mCurrent{ nullptr };
		std::stack<json*> mJsonStack;
	};
}