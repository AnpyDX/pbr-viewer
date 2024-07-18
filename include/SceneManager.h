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

    class SceneManager {
    public:
        // create shader resource
        void new_shader(const std::string& name, const std::string& path);

        // add new model to scene
        void new_model(const std::string& name, std::unique_ptr<Model> &&model, const std::string& shader_name);

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
        void render(Camera* camera, Framebuffer* target);

    private:
        std::map<std::string, std::unique_ptr<Model>> models {};
        std::map<std::string, PointLight>             pointlights {};
        std::map<std::string, SunLight>               sunlights {};
        
        std::unique_ptr<SkyBox> skybox {};

        std::map<std::string, std::unique_ptr<Shader>> shaders {};
    };
}