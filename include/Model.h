/** PBRV Project (https://github.com/anpydx/pbr-viewer)
 * @brief model object
 */
#pragma once
#include <map>
#include <vector>
#include <memory>
#include <string>

#include <assimp/scene.h>

#include "core/texture.h"
#include "core/shader.h"
#include "core/vertexbuffer.h"
#include "core/indexbuffer.h"

namespace PBRV {

    /* Material Resources Object */
    struct MaterialRes {
        Texture* albdo     = nullptr;
        Texture* normal    = nullptr;
        Texture* metallic  = nullptr;
        Texture* roughness = nullptr;
        Texture* ao        = nullptr;
    };

    /* Mesh Object */
    struct Mesh {
        std::unique_ptr<VertexBuffer> vb {};
        std::unique_ptr<IndexBuffer> ib {};
        MaterialRes mat {};
    };

    /* Transform Object */
    struct Transform {
        mas::vec3 translate { 0.0f };
        mas::vec3 scale { 1.0f };
        mas::vec3 rotate { 0.0f };
    };

    /* Model Node Object */
    class Model {
    public:
        /* Model Node Builder */
        class Builder {
        public:
            Builder& operator()();
            
            // load model from file
            Builder& from_file(const std::string& path);

            // set model's transform
            Builder& set_transform(Transform& transform);

            // set model's material shader
            Builder& set_shader(Shader *shader);

            // build model object
            std::unique_ptr<Model> build();

        private:
            std::string build_path {};
            Transform build_transform {};
            Shader *build_shader { nullptr };

            std::string current_dir {};

        private:
            /** @note: can be optimized */
            void process_node(aiNode *node, const aiScene *scene, Model *model);
            Mesh process_mesh(aiMesh *mesh, const aiScene *scene, Model *model);
            Texture* load_texture(aiMaterial *mat, aiTextureType type, Model *model);
        };

        // model drawing interface
        void draw();

    private:
        static void bind_sampler(Shader const * shader, Texture const* texture, uint8_t offset, const std::string& uniform_name); 
    
    public:
        // model's transform attribute
        Transform transform {};

        // model's meshes collection
        std::vector<Mesh> meshes {};

        // loaded textures collection
        std::map<std::string, std::unique_ptr<Texture>> textures {};

        // model's material shader
        Shader* shader = nullptr;
    };
}