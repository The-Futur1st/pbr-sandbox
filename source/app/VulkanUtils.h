#pragma once

#define NOMINMAX
#define VK_USE_PLATFORM_WIN32_KHR
#include <vulkan/vulkan.h>

struct VulkanRendererContext;

/*
 */
class VulkanUtils
{
public:
	static uint32_t findMemoryType(
		const VulkanRendererContext &context,
		uint32_t typeFilter,
		VkMemoryPropertyFlags properties
	);

	static void createBuffer(
		const VulkanRendererContext &context,
		VkDeviceSize size,
		VkBufferUsageFlags usage,
		VkMemoryPropertyFlags memoryProperties,
		VkBuffer &buffer,
		VkDeviceMemory &memory
	);

	static void createImage2D(
		const VulkanRendererContext &context,
		uint32_t width,
		uint32_t height,
		VkFormat format,
		VkImageTiling tiling,
		VkImageUsageFlags usage,
		VkMemoryPropertyFlags memoryProperties,
		VkImage &image,
		VkDeviceMemory &memory
	);

	static VkImageView createImage2DView(
		const VulkanRendererContext &context,
		VkImage image,
		VkFormat format,
		VkImageAspectFlags aspectFlags
	);

	static VkSampler createSampler(
		const VulkanRendererContext &context
	);

	static void copyBuffer(
		const VulkanRendererContext &context,
		VkBuffer src,
		VkBuffer dst,
		VkDeviceSize size
	);

	static void copyBufferToImage(
		const VulkanRendererContext &context,
		VkBuffer src,
		VkImage dst,
		uint32_t width,
		uint32_t height
	);

	static void transitionImageLayout(
		const VulkanRendererContext &context,
		VkImage image,
		VkFormat format,
		VkImageLayout oldLayout,
		VkImageLayout newLayout
	);

private:
	static bool hasStencilComponent(VkFormat format);
	static VkCommandBuffer beginSingleTimeCommands(const VulkanRendererContext &context);
	static void endSingleTimeCommands(const VulkanRendererContext &context, VkCommandBuffer commandBuffer);
};