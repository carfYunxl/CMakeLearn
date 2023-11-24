#ifndef SCENE_SERIALIZER_H_
#define SCENE_SERIALIZER_H_

#include "Scene.h"

namespace GL
{
    class SceneSerializer
	{
	public:
		SceneSerializer(Scene* scene);

		void Serialize(const std::string& filepath);
		void SerializeRuntime(const std::string& filepath);

		bool Deserialize(const std::string& filepath);
		bool DeserializeRuntime(const std::string& filepath);
	private:
		Scene* m_Scene{nullptr};
	};

}

#endif //SCENE_SERIALIZER_H_