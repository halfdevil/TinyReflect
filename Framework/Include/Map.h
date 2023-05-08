#pragma once

#include <unordered_map>

namespace TinyReflect
{
	class MapBase
	{
	public:

		virtual void InsertDefault(const std::string& key) = 0;
	};

	template <typename T>
	class Map : public std::unordered_map<std::string, T>, public MapBase
	{
	public:

		using MapT = std::unordered_map<std::string, T>;
		using MapT::MapT;

		virtual void InsertDefault(const std::string& key) override
		{
			MapT::insert(std::pair(key, T()));
		}
	};
}