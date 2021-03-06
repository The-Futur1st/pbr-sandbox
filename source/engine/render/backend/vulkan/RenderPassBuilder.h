#pragma once

#include <vector>
#include <volk.h>

namespace render::backend::vulkan
{
	/*
	 */
	class RenderPassBuilder
	{
	public:
		RenderPassBuilder() { }
		~RenderPassBuilder();

		RenderPassBuilder &RenderPassBuilder::addColorAttachment(
			VkFormat format,
			VkSampleCountFlagBits num_samples,
			VkImageLayout final_layout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
			VkAttachmentLoadOp load_op = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
			VkAttachmentStoreOp store_op = VK_ATTACHMENT_STORE_OP_DONT_CARE,
			VkAttachmentLoadOp stencil_load_op = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
			VkAttachmentStoreOp stencil_store_op = VK_ATTACHMENT_STORE_OP_DONT_CARE
		);

		RenderPassBuilder &RenderPassBuilder::addColorResolveAttachment(
			VkFormat format,
			VkImageLayout final_layout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
			VkAttachmentLoadOp load_op = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
			VkAttachmentStoreOp store_op = VK_ATTACHMENT_STORE_OP_DONT_CARE,
			VkAttachmentLoadOp stencil_load_op = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
			VkAttachmentStoreOp stencil_store_op = VK_ATTACHMENT_STORE_OP_DONT_CARE
		);

		RenderPassBuilder &addDepthStencilAttachment(
			VkFormat format,
			VkSampleCountFlagBits num_samples,
			VkImageLayout final_layout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
			VkAttachmentLoadOp load_op = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
			VkAttachmentStoreOp store_op = VK_ATTACHMENT_STORE_OP_DONT_CARE,
			VkAttachmentLoadOp stencil_load_op = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
			VkAttachmentStoreOp stencil_store_op = VK_ATTACHMENT_STORE_OP_DONT_CARE
		);

		RenderPassBuilder &addSubpass(
			VkPipelineBindPoint bind_point
		);

		RenderPassBuilder &addColorAttachmentReference(
			int subpass,
			int attachment
		);

		RenderPassBuilder &addColorResolveAttachmentReference(
			int subpass,
			int attachment
		);

		RenderPassBuilder &setDepthStencilAttachmentReference(
			int subpass,
			int attachment
		);

		VkRenderPass build(VkDevice device);

	private:
		struct SubpassData
		{
			std::vector<VkAttachmentReference> color_attachment_references;
			std::vector<VkAttachmentReference> color_attachment_resolve_references;
			VkAttachmentReference *depth_stencil_attachment_reference {nullptr};
		};

		std::vector<VkAttachmentDescription> attachments;
		std::vector<VkSubpassDescription> subpass_infos;
		std::vector<SubpassData> subpass_datas;
	};
}
