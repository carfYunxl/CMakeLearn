#ifndef COMPONENTS_H_
#define COMPONENTS_H_

#include <string>
#include "glm/glm.hpp"

namespace GL {

	struct TagComponent
	{
		std::string Tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag)
			: Tag(tag) {}
	};

	struct TransformComponent
	{
		glm::mat4 Transform{ 1.0f };
		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::mat4 & transform)
			: Transform(transform) {}
		// glm::mat4& operator() { return Transform; }
		// const glm::mat4& operator() const { return Transform; }
	};


	struct ColorComponent
	{
		glm::vec4 Color{ 1.0f, 0.0f, 0.0f, 1.0f };
		ColorComponent() = default;
		ColorComponent(const ColorComponent&) = default;
		ColorComponent(const glm::vec4& color)
			: Color(color) {}
	};
}

#endif //COMPONENTS_H_