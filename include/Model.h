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
        Core::Texture* albdo     = nullptr;
        Core::Texture* normal    = nullptr;
        Core::Texture* metallic  = nullptr;
        Core::Texture* roughness = nullptr;
        Core::Texture* ao        = nullptr;
    };

    /* Mesh Object */
    struct Mesh {
        std::unique_ptr<Core::VertexBuffer> vb {};
        std::unique_ptr<Core::IndexBuffer> ib {};
        MaterialRes mat {};
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

            // build model object
            std::unique_ptr<Model> build();

        private:
            std::string build_path {};
            std::string current_dir {};

        private:
            /** @note: can be optimized */
            void process_node(aiNode *node, const aiScene *scene, Model *model);
            Mesh process_mesh(aiMesh *mesh, const aiScene *scene, Model *model);
            Core::Texture* load_texture(aiMaterial *mat, aiTextureType type, Model *model);
        };

        // model drawing interface
        void draw(Core::Shader *shader);

    private:
        static void bind_sampler(Core::Shader const *shader, Core::Texture const* texture, uint8_t offset, const std::string& uniform_name); 
    
    public:
        // model's meshes collection
        std::vector<Mesh> meshes {};

        // loaded textures collection
        std::map<std::string, std::unique_ptr<Core::Texture>> textures {};
    };
}