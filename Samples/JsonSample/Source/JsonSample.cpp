#include "TestObject.h"
#include "TestObject.generated.h"
#include "JsonWriter.h"
#include "JsonReader.h"
#include <iostream>

using namespace TinyReflect;

int main(int argc, char* argv[])
{
	TestObject testObject;
	testObject.mValue = 1;
	testObject.mStruct.mValue = 2;
	testObject.mArray[0] = 1;
	testObject.mArray[1] = 2;
	testObject.mArray[2] = 3;
	testObject.mArray[3] = 4;
	testObject.mVec = { 0, 1, 2, 3 };
	testObject.mString = "This is a test string";
	testObject.mMap = {
		{ "First Value", {} },
		{ "Second Value", {} }
	};

	JsonWriter writer;
	const Class* cls = GetClass<TestObject>();
	if (!cls)
	{
		std::cerr << "TestObject class not reflected!!" << std::endl;
		return -1;
	}

	cls->visit(&testObject, &writer);

	std::string jsonStr = writer.toString(4);
	std::cout << "Json: " << jsonStr << std::endl;

	TestObject testObject2;
	JsonReader reader;

	reader.fromString(jsonStr);
	cls->visit(&testObject2, &reader);

	std::cout << std::endl;
	std::cout << "Object after reading: " << std::endl;
	testObject2.dump(0);

	return 0;
}