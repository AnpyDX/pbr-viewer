#include "SceneManager.h"
#include <stdexcept>
#include <fstream>


namespace PBRV {

    void SceneManager::new_shader(const std::string& name, const std::string& path) {
        if (shaders.find(name) != shaders.end()) {
            throw std::runtime_error("error occurred while calling <SceneManager::new_shader>: shader \"" + name + "\" is existed!");
        }

        std::fstream shader_file(path);
        if (!shader_file.is_open()) {
            throw std::runtime_error("error occurred while calling <SceneManager::new_shader>: failed to open shader \"" + name + "\" !");
        }

        shaders[name] = std::make_unique<Shader>(shader_file);
        shader_file.close();
    }

    void SceneManager::new_model(const std::string& name, std::unique_ptr<Model> &&model, const std::string& shader_name) {
        if (models.find(name) != models.end()) {
            throw std::runtime_error("error occurred while calling <SceneManager::add_model>: model \"" + name + "\" is existed!");
        }

        if (shaders.find(shader_name) == shaders.end()) {
            throw std::runtime_error("error occurred while calling <SceneManager::add_model>: shader \"" + shader_name + "\" is not existed!");
        }

        models[name] = std::move(model);
        models[name]->shader = shaders[shader_name].get();
    }

    void SceneManager::new_pointlight() {}

    void SceneManager::new_sunlight() {}

    void SceneManager::remove_shader(const std::string& name) {
        if (shaders.find(name) == shaders.end()) {
            throw std::runtime_error("error occurred while calling <SceneManager::remove_shader>: shader \"" + name + "\" is not existed!");
        }
        
        shaders[name].reset();
        shaders.erase(name);
    }

    void SceneManager::remove_model(const std::string& name) {
        if (models.find(name) == models.end()) {
            throw std::runtime_error("error occurred while calling <SceneManager::remove_model>: model \"" + name + "\" is not existed!");
        }

        models[name].reset();
        models.erase(name);
    }

    void SceneManager::remove_pointlight(const std::string& name) {}

    void SceneManager::remove_sunlight(const std::string& name) {}

    void SceneManager::render(Camera *camera, Framebuffer *target) {
        target->bind();

        // draw models
        for (auto& model : models) {
            Shader *shader = model.second->shader;
            shader->use();
            shader->set_mat4("PBRV_Transform_View", camera->get_lookat());
            shader->set_mat4("PBRV_Transform_Projection", camera->get_perspective());
            model.second->draw();
        }

        // draw light

        // draw skybox


        PBRV::Framebuffer::bind_default();
    }
}