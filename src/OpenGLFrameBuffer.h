#ifndef OPENGL_FRAME_BUFFER_H_
#define OPENGL_FRAME_BUFFER_H_

#include <memory>
#include <cstdint>

namespace GL
{
    struct FramebufferSpecification
	{
		uint32_t Width, Height;
		// FramebufferFormat Format = 
		uint32_t Samples = 1;

		bool SwapChainTarget = false;
	};

    class OpenGLFramebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferSpecification& spec);
		virtual ~OpenGLFramebuffer();

		void Invalidate();

		virtual void Bind();
		virtual void Unbind();
		virtual void Resize(uint32_t width, uint32_t height);

		virtual uint32_t GetColorAttachmentRendererID() const { return m_ColorAttachment; }

		virtual const FramebufferSpecification& GetSpecification() const { return m_Specification; }
	private:
		uint32_t m_RendererID;
		uint32_t m_ColorAttachment, m_DepthAttachment;
		FramebufferSpecification m_Specification;
	};
}

#endif //OPENGL_FRAME_BUFFER_H_