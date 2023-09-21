// ////////////////////////
// File: AssetRegistry.h
// Created at: 09 19, 2023
// Description:
// Modified by: Daniel Henrique
// 09 19, 2023
// ////////////////////////

#ifndef ASSET_REGISTRY_H
#define ASSET_REGISTRY_H

#include "../Utils/CommonStuff.h"

#include "Asset.h"
#include "../Core/TypeId.h"

namespace abyss2d
{
	struct AssetRegistry
	{
	private:
		std::unordered_map<assetTypeId, std::vector<Asset*>> _data;

	public:
		ABYSS_INLINE void Clear()
		{
			for(auto&[_, list] : _data)
			{
				for(auto a : list)
				{
					ABYSS_DELETE(a)
				}
			}

			_data.clear();
		}
		
		template <typename T>
		assetId GetId(const std::string& name)
		{
			ABYSS_STATIC_ASSERT(std::is_base_of_v<Asset, T>);
			const auto type = TypeId<T>();
			if(!_data.count(type))
			{
				return INVALID_ID;
			}

			for(auto& a : _data.at(type))
			{
				if(!a->name.compare(name))
				{
					return a->id;
				}
			}

			return INVALID_ID;
		}

		template <typename T>
		T* Get(assetId id)
		{
			ABYSS_STATIC_ASSERT(std::is_base_of_v<Asset, T>);
			const auto type = TypeId<T>();
			if(!_data.count(type))
			{
				return nullptr;
			}

			for(auto& a : _data.at(type))
			{
				if(a->id == id)
				{
					return static_cast<T*>(a);
				}
			}

			return nullptr;
		}

		template <typename T>
		T* Get(const std::string name)
		{
			assetId id = GetId<T>(name);
			ABYSS_STATIC_ASSERT(std::is_base_of_v<Asset, T>);
			const auto type = TypeId<T>();
			if(!_data.count(type))
			{
				return nullptr;
			}

			for(auto& a : _data.at(type))
			{
				if(a->id == id)
				{
					return static_cast<T*>(a);
				}
			}

			return nullptr;
		}
		
		template <typename T>
		T* Add(const std::string& name)
		{
			auto asset = new T();
			asset->name = name;
			_data[TypeId<T>()].push_back(asset);
			return asset;
		}
	};
}

#endif
