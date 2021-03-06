#pragma once

#include <render/Mesh.h>
#include <render/backend/driver.h>

namespace render
{
	class Shader;
	class Texture;
}

/*
 */
class Texture2DRenderer
{
public:
	Texture2DRenderer(render::backend::Driver *driver);

	void init(const render::backend::Texture *target_texture);
	void shutdown();
	void render(const render::backend::Shader *vertex_shader, const render::backend::Shader *fragment_shader);

private:
	render::backend::Driver *driver {nullptr};
	render::backend::CommandBuffer *command_buffer {nullptr};
	render::backend::FrameBuffer *framebuffer {nullptr};

	render::Mesh quad;
};
