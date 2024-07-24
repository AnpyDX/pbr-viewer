/** PBRV Project (https://github.com/anpydx/pbr-viewer)
 * @brief scene manager
 */
#pragma once
#include <map>
#include <string>
#include <memory>

#include "core/shader.h"
#include "core/framebuffer.h"

#include "Camera.h"
#include "Model.h"
#include "Light.h"
#include "SkyBox.h"

namespace PBRV {
    struct Transform {
        mas::vec3 translate { 0.0f };
        mas::vec3 scale { 1.0f };
        mas::vec3 rotate { 0.0f };
    };

    struct ShaderObject {
        std::unique_ptr<PBRV::Core::Shader> object {};
        std::string path {};
    };

    struct ModelObject {
        std::unique_ptr<PBRV::Model> object {};
        PBRV::Transform transform {};
        std::string shader {};
    };
}

namespace PBRV {

    class SceneManager {
    public:
        // create shader resource
        void new_shader(const std::string& name, const std::string& path, bool allow_override = false);

        // add new model to scene
        void new_model(const std::string& name, std::unique_ptr<Model> &&model, const std::string& shader_name, const Transform& transform);

        // add new pointlight to scene
        void new_pointlight();

        // add new sunlight to scene
        void new_sunlight();

        // remove shader
        void remove_shader(const std::string& name);

        // remove model
        void remove_model(const std::string& name);

        // remove pointlight
        void remove_pointlight(const std::string& name);

        // remove sunlight
        void remove_sunlight(const std::string& name);

        // render scene to target Frambuffer
        void render(Camera* camera, Core::Framebuffer* target);

    public:
        std::map<std::string, ModelObject> models {};
        std::map<std::string, PointLight>  pointlights {};
        std::map<std::string, SunLight>    sunlights {};
        
        std::unique_ptr<SkyBox> skybox {};

        std::map<std::string, ShaderObject> shaders {};
    };
}