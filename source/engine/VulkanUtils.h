#pragma once

#include <vector>
#include <volk.h>

class VulkanContext;

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

	static uint32_t fetchGraphicsQueueFamily(
		VkPhysicalDevice physicalDevice
	);

	static uint32_t fetchPresentQueueFamily(
		VkPhysicalDevice physicalDevice,
		VkSurfaceKHR surface,
		uint32_t graphicsQueueFamily
	);

	static void createBuffer(
		const VulkanContext *context,
		VkDeviceSize size,
		VkBufferUsageFlags usage,
		VkMemoryPropertyFlags memoryProperties,
		VkBuffer &buffer,
		VkDeviceMemory &memory
	);

	static void createImageCube(
		const VulkanContext *context,
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
		const VulkanContext *context,
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

	static VkImageView createImageView(
		const VulkanContext *context,
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
		const VulkanContext *context,
		uint32_t minMipLevel,
		uint32_t maxMipLevel 
	);

	static VkShaderModule createShaderModule(
		const VulkanContext *context,
		const uint32_t *bytecode,
		size_t bytecodeSize
	);

	static void VulkanUtils::bindUniformBuffer(
		const VulkanContext *context,
		VkDescriptorSet descriptorSet,
		int binding,
		VkBuffer buffer,
		VkDeviceSize offset,
		VkDeviceSize size
	);

	static void bindCombinedImageSampler(
		const VulkanContext *context,
		VkDescriptorSet descriptorSet,
		int binding,
		VkImageView imageView,
		VkSampler sampler
	);

	static void copyBuffer(
		const VulkanContext *context,
		VkBuffer src,
		VkBuffer dst,
		VkDeviceSize size
	);

	static void copyBufferToImage(
		const VulkanContext *context,
		VkBuffer src,
		VkImage dst,
		uint32_t width,
		uint32_t height
	);

	static void transitionImageLayout(
		const VulkanContext *context,
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
		const VulkanContext *context,
		VkImage image,
		uint32_t width,
		uint32_t height,
		uint32_t mipLevels,
		VkFormat format,
		VkFilter filter
	);

	static VkCommandBuffer beginSingleTimeCommands(
		const VulkanContext *context
	);

	static void endSingleTimeCommands(
		const VulkanContext *context,
		VkCommandBuffer commandBuffer
	);

private:
	static bool hasStencilComponent(VkFormat format);
};