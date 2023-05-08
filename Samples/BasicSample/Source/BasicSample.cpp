#include "TestObject.h"
#include "TestObject.generated.h"
#include "DumpVisitor.h"
#include <iostream>

using namespace TinyReflect;

int main(int argc, char* argv[])
{
	TestObject testObject;
	testObject.mObjectName = "Test Object";
	testObject.mEnum = TinyReflect::TestEnum::Enum1;
	testObject.mStruct.value1 = 1.0f;
	testObject.mStruct.value2 = 2;
	testObject.mStruct.value3 = 3;

	DumpVisitor visitor;

	const Class* cls = GetClass<TestObject>();
	if (!cls)
	{
		std::cerr << "TestObject class not reflected!!" << std::endl;
		return -1;
	}

	cls->visit(&testObject, &visitor);

	return 0;
}