#include "SceneManager.h"
#include <stdexcept>
#include <fstream>


namespace PBRV {

    void SceneManager::new_shader(const std::string& name, const std::string& path, bool allow_override) {
        if (shaders.find(name) != shaders.end() && !allow_override) {
            throw std::runtime_error("error occurred while calling <SceneManager::new_shader>: shader \"" + name + "\" is existed!");
        }

        std::fstream shader_file(path);
        if (!shader_file.is_open()) {
            throw std::runtime_error("error occurred while calling <SceneManager::new_shader>: failed to open shader \"" + name + "\" !");
        }

        shaders[name].object = std::make_unique<Core::Shader>(shader_file);
        shaders[name].path = path;
        shader_file.close();
    }

    void SceneManager::new_model(const std::string& name, std::unique_ptr<Model> &&model, const std::string& shader_name, const Transform& transform) {
        if (models.find(name) != models.end()) {
            throw std::runtime_error("error occurred while calling <SceneManager::add_model>: model \"" + name + "\" is existed!");
        }

        if (shaders.find(shader_name) == shaders.end()) {
            throw std::runtime_error("error occurred while calling <SceneManager::add_model>: shader \"" + shader_name + "\" is not existed!");
        }

        models[name].object = std::move(model);
        models[name].transform = transform;
        models[name].shader = shader_name;
    }

    void SceneManager::new_pointlight() {}

    void SceneManager::new_sunlight() {}

    void SceneManager::remove_shader(const std::string& name) {
        if (shaders.find(name) == shaders.end()) {
            throw std::runtime_error("error occurred while calling <SceneManager::remove_shader>: shader \"" + name + "\" is not existed!");
        }
        
        shaders[name].object.reset();
        shaders.erase(name);
    }

    void SceneManager::remove_model(const std::string& name) {
        if (models.find(name) == models.end()) {
            throw std::runtime_error("error occurred while calling <SceneManager::remove_model>: model \"" + name + "\" is not existed!");
        }

        models[name].object.reset();
        models.erase(name);
    }

    void SceneManager::remove_pointlight(const std::string& name) {}

    void SceneManager::remove_sunlight(const std::string& name) {}

    void SceneManager::render(Camera *camera, Core::Framebuffer *target) {
        target->bind();

        // draw models
        for (auto& model : models) {
            Core::Shader *shader = shaders[model.second.shader].object.get();
            shader->use();

            mas::mat4 T_model(1.0f);
            T_model = mas::translate(T_model, model.second.transform.translate);
            T_model = mas::scale(T_model, model.second.transform.scale);
            T_model = mas::rotate(T_model, mas::vec3(1.0, 0.0, 0.0), model.second.transform.rotate.x);
            T_model = mas::rotate(T_model, mas::vec3(0.0, 1.0, 0.0), model.second.transform.rotate.y);
            T_model = mas::rotate(T_model, mas::vec3(0.0, 0.0, 1.0), model.second.transform.rotate.z);

            shader->set_mat4("PBRV_Transform_Model", T_model);
            shader->set_mat4("PBRV_Transform_View", camera->get_lookat());
            shader->set_mat4("PBRV_Transform_Projection", camera->get_perspective());
            model.second.object->draw(shader);
        }

        // draw light

        // draw skybox


        PBRV::Core::Framebuffer::bind_default();
    }
}