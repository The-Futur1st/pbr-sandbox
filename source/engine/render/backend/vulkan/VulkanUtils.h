#pragma once

#include <vector>
#include <volk.h>

namespace render::backend::vulkan
{
	class Device;
}

/*
 */
class VulkanUtils
{
public:
	static bool checkInstanceValidationLayers(
		const std::vector<const char *> &requiredLayers,
		bool verbose = false
	);

	static bool checkInstanceExtensions(
		const std::vector<const char *> &requiredExtensions,
		bool verbose = false
	);

	static bool checkPhysicalDeviceExtensions(
		VkPhysicalDevice physicalDevice,
		const std::vector<const char *> &requiredExtensions,
		bool verbose = false
	);

	static VkSampleCountFlagBits getMaxUsableSampleCount(
		VkPhysicalDevice physicalDevice
	);

	static VkFormat VulkanUtils::selectOptimalImageFormat(
		VkPhysicalDevice physicalDevice,
		const std::vector<VkFormat> &candidates,
		VkImageTiling tiling,
		VkFormatFeatureFlags features
	);

	static VkFormat VulkanUtils::selectOptimalDepthFormat(
		VkPhysicalDevice physicalDevice
	);

	static uint32_t findMemoryType(
		VkPhysicalDevice physicalDevice,
		uint32_t typeFilter,
		VkMemoryPropertyFlags properties
	);

	static uint32_t getGraphicsQueueFamily(
		VkPhysicalDevice physicalDevice
	);

	static uint32_t getPresentQueueFamily(
		VkPhysicalDevice physicalDevice,
		VkSurfaceKHR surface,
		uint32_t graphicsQueueFamily
	);

	static void createBuffer(
		const render::backend::vulkan::Device *device,
		VkDeviceSize size,
		VkBufferUsageFlags usage,
		VkMemoryPropertyFlags memoryProperties,
		VkBuffer &buffer,
		VkDeviceMemory &memory
	);

	static void createDeviceLocalBuffer(
		const render::backend::vulkan::Device *device,
		VkDeviceSize size,
		const void *data,
		VkBufferUsageFlags usage,
		VkBuffer &buffer,
		VkDeviceMemory &memory
	);

	static void createImage(
		const render::backend::vulkan::Device *device,
		VkImageType type,
		uint32_t width,
		uint32_t height,
		uint32_t depth,
		uint32_t mipLevels,
		uint32_t arrayLayers,
		VkSampleCountFlagBits numSamples,
		VkFormat format,
		VkImageTiling tiling,
		VkImageUsageFlags usage,
		VkMemoryPropertyFlags memoryProperties,
		VkImageCreateFlags flags,
		VkImage &image,
		VkDeviceMemory &memory
	);

	static void fillImage(
		const render::backend::vulkan::Device *device,
		VkImage image,
		uint32_t width,
		uint32_t height,
		uint32_t depth,
		uint32_t mipLevels,
		uint32_t arrayLayers,
		uint32_t pixelSize,
		VkFormat format,
		const void *data,
		uint32_t dataMipLevels,
		uint32_t dataArrayLayers
	);

	static void createImageCube(
		const render::backend::vulkan::Device *device,
		uint32_t width,
		uint32_t height,
		uint32_t mipLevels,
		VkSampleCountFlagBits numSamples,
		VkFormat format,
		VkImageTiling tiling,
		VkImageUsageFlags usage,
		VkMemoryPropertyFlags memoryProperties,
		VkImage &image,
		VkDeviceMemory &memory
	);

	static void createImage2D(
		const render::backend::vulkan::Device *device,
		uint32_t width,
		uint32_t height,
		uint32_t mipLevels,
		VkSampleCountFlagBits numSamples,
		VkFormat format,
		VkImageTiling tiling,
		VkImageUsageFlags usage,
		VkMemoryPropertyFlags memoryProperties,
		VkImage &image,
		VkDeviceMemory &memory
	);

	static void createImage2D(
		const render::backend::vulkan::Device *device,
		uint32_t width,
		uint32_t height,
		uint32_t mipLevels,
		uint32_t pixelSize,
		const void *data,
		uint32_t dataMipLevels,
		VkSampleCountFlagBits numSamples,
		VkFormat format,
		VkImageTiling tiling,
		VkImage &image,
		VkDeviceMemory &memory
	);

	static VkImageView createImageView(
		const render::backend::vulkan::Device *device,
		VkImage image,
		VkFormat format,
		VkImageAspectFlags aspectFlags,
		VkImageViewType viewType,
		uint32_t baseMipLevel = 0,
		uint32_t numMipLevels = 1,
		uint32_t baseLayer = 0,
		uint32_t numLayers = 1
	);

	static VkSampler createSampler(
		const render::backend::vulkan::Device *device,
		uint32_t minMipLevel,
		uint32_t maxMipLevel 
	);

	static VkShaderModule createShaderModule(
		const render::backend::vulkan::Device *device,
		const uint32_t *bytecode,
		size_t bytecodeSize
	);

	static void VulkanUtils::bindUniformBuffer(
		const render::backend::vulkan::Device *device,
		VkDescriptorSet descriptorSet,
		int binding,
		VkBuffer buffer,
		VkDeviceSize offset,
		VkDeviceSize size
	);

	static void bindCombinedImageSampler(
		const render::backend::vulkan::Device *device,
		VkDescriptorSet descriptorSet,
		int binding,
		VkImageView imageView,
		VkSampler sampler
	);

	static void copyBuffer(
		const render::backend::vulkan::Device *device,
		VkBuffer src,
		VkBuffer dst,
		VkDeviceSize size
	);

	static void copyBufferToImage(
		const render::backend::vulkan::Device *device,
		VkBuffer src,
		VkImage dst,
		uint32_t width,
		uint32_t height,
		uint32_t depth = 1,
		uint32_t mipLevel = 0,
		uint32_t layer = 0,
		VkDeviceSize bufferOffset = 0
	);

	static void transitionImageLayout(
		const render::backend::vulkan::Device *device,
		VkImage image,
		VkFormat format,
		VkImageLayout oldLayout,
		VkImageLayout newLayout,
		uint32_t baseMipLevel = 0,
		uint32_t numMipLevels = 1,
		uint32_t baseLayer = 0,
		uint32_t numLayers = 1
	);

	static void generateImage2DMipmaps(
		const render::backend::vulkan::Device *device,
		VkImage image,
		VkFormat imageFormat,
		uint32_t width,
		uint32_t height,
		uint32_t mipLevels,
		VkFormat format,
		VkFilter filter
	);

	static VkCommandBuffer beginSingleTimeCommands(
		const render::backend::vulkan::Device *context
	);

	static void endSingleTimeCommands(
		const render::backend::vulkan::Device *device,
		VkCommandBuffer commandBuffer
	);

private:
	static bool hasStencilComponent(VkFormat format);
	static bool isDepthFormat(VkFormat format);
};