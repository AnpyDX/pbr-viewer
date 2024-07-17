/** PBRV Project (https://github.com/anpydx/pbr-viewer)
 * @brief scene manager
 */
#pragma once
#define MAS_UTYPE_FLOAT
#include <vector>
#include <map>
#include <memory>
#include <string>
#include <mas/mas.hpp>
#include <assimp/scene.h>

#include "core/shader.h"
#include "core/texture.h"
#include "core/framebuffer.h"
#include "core/vertexbuffer.h"
#include "core/indexbuffer.h"

namespace PBRV {

    struct Material {
        Texture* albdo     = nullptr;
        Texture* normal    = nullptr;
        Texture* metallic  = nullptr;
        Texture* roughness = nullptr;
        Texture* ao        = nullptr;
    };

    struct Mesh {
        std::unique_ptr<VertexBuffer> vb {};
        std::unique_ptr<IndexBuffer> ib {};
        Material mat {};
    };

    class Model {
    public:
        class Builder {
        public:
            Builder& operator()();
            
            // create mesh from model
            std::unique_ptr<Model> from_file(const std::string& path);

        private:
            std::string current_dir {};

        private:
            /** @note: can be optimized */
            void process_node(aiNode *node, const aiScene *scene, Model *model);
            Mesh process_mesh(aiMesh *mesh, const aiScene *scene, Model *model);
            Texture* load_texture(aiMaterial *mat, aiTextureType type, Model *model);
        };

        // draw mesh_set
        void draw(Shader const *shader, Framebuffer *target);

    private:
        static void bind_sampler(Shader const * shader, Texture const* texture, uint8_t offset, const std::string& uniform_name); 
    
    private:
        std::vector<Mesh> mesh_set {};
        std::map<std::string, std::unique_ptr<Texture>> texture_set {};
    };


    class SceneManager {
    public:
        void add_mesh(std::unique_ptr<Model>&& model);
        void add_light();
        void set_skybox();

        /** @note: can be optimized */
        // render scene on target framebuffer
        void render(Shader const *shader, Framebuffer *target);

    private:
        std::vector<std::unique_ptr<Model>> m_models {};
    };
}