#include "render/backend/vulkan/PipelineLayoutCache.h"
#include "render/backend/vulkan/PipelineLayoutBuilder.h"
#include "render/backend/vulkan/DescriptorSetLayoutCache.h"

#include "render/backend/vulkan/Driver.h"
#include "render/backend/vulkan/Device.h"
#include "render/backend/vulkan/Context.h"

#include <array>
#include <vector>
#include <cassert>

namespace render::backend::vulkan
{
	template <class T>
	static void hashCombine(uint64_t &s, const T &v)
	{
		std::hash<T> h;
		s^= h(v) + 0x9e3779b9 + (s<< 6) + (s>> 2);
	}

	PipelineLayoutCache::~PipelineLayoutCache()
	{
		clear();
	}

	VkPipelineLayout PipelineLayoutCache::fetch(const Context *context)
	{
		uint8_t push_constants_size = context->getPushConstantsSize();
		uint8_t num_bind_sets = context->getNumBindSets();

		std::array<VkDescriptorSetLayout, Context::MAX_SETS> layouts;
		for (uint8_t i = 0; i < num_bind_sets; ++i)
		{
			const BindSet *bind_set = context->getBindSet(i);
			layouts[i] = (bind_set) ? bind_set->set_layout : VK_NULL_HANDLE;
		}

		uint64_t hash = getHash(num_bind_sets, layouts.data(), push_constants_size);

		auto it = cache.find(hash);
		if (it != cache.end())
			return it->second;

		PipelineLayoutBuilder builder;

		for (uint8_t i = 0; i < num_bind_sets; ++i)
			builder.addDescriptorSetLayout(layouts[i]);

		if (push_constants_size > 0)
			builder.addPushConstantRange(VK_SHADER_STAGE_ALL, 0, push_constants_size);

		VkPipelineLayout result = builder.build(device->getDevice());

		cache[hash] = result;
		return result;
	}

	void PipelineLayoutCache::clear()
	{
		for (auto it = cache.begin(); it != cache.end(); ++it)
			vkDestroyPipelineLayout(device->getDevice(), it->second, nullptr);

		cache.clear();
	}

	uint64_t PipelineLayoutCache::getHash(uint8_t num_layouts, const VkDescriptorSetLayout *layouts, uint8_t push_constants_size) const
	{
		assert(num_layouts == 0 || layouts != nullptr);

		uint64_t hash = 0;
		hashCombine(hash, push_constants_size);
		hashCombine(hash, num_layouts);
		
		for (uint8_t i = 0; i < num_layouts; ++i)
			hashCombine(hash, layouts[i]);

		return hash;
	}
}
