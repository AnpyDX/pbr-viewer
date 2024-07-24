#include "Model.h"

#include <stdexcept>

#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

namespace {
    struct Vertex {
        mas::vec3 position;
        mas::vec3 normal;
        mas::vec2 texCoord;
    };
}

namespace PBRV {
    Model::Builder& Model::Builder::operator()() {
        static Builder builder;
        return builder;
    }

    Model::Builder& Model::Builder::from_file(const std::string& path) {
        build_path = path;
        return *this;
    }

    std::unique_ptr<Model> Model::Builder::build() {
        Assimp::Importer importer;
        const aiScene *scene = importer.ReadFile(build_path.c_str(), aiProcess_Triangulate | aiProcess_GenNormals);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            throw std::runtime_error("error occurred while calling <Model::Builder::from_file>: failed to load model " + build_path + " !");
        }

        current_dir = build_path.substr(0, build_path.find_last_of('/'));

        auto result = std::make_unique<Model>();

        process_node(scene->mRootNode, scene, result.get());

        return result;
    }

    void Model::Builder::process_node(aiNode *node, const aiScene *scene, Model *model) {
        // process meshes under current node
        for (uint32_t i = 0; i < node->mNumMeshes; i++) {
            aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
            model->meshes.push_back(process_mesh(mesh, scene, model));
        }

        // process nodes inside
        for (uint32_t i = 0; i < node->mNumChildren; i++) {
            process_node(node->mChildren[i], scene, model);
        }
    }

    Mesh Model::Builder::process_mesh(aiMesh *mesh, const aiScene *scene, Model *model) {
        Mesh result {};
        std::vector<Vertex> vertices(mesh->mNumVertices);
        std::vector<unsigned int> indices {};

        for (uint32_t i = 0; i < mesh->mNumVertices; i++) {
            Vertex vertex;

            vertex.position.x = mesh->mVertices[i].x;
            vertex.position.y = mesh->mVertices[i].y;
            vertex.position.z = mesh->mVertices[i].z;

            vertex.normal.x = mesh->mNormals[i].x;
            vertex.normal.y = mesh->mNormals[i].y;
            vertex.normal.z = mesh->mNormals[i].z;

            if (mesh->mTextureCoords[0]) {
                vertex.texCoord.x = mesh->mTextureCoords[0][i].x;
                vertex.texCoord.y = mesh->mTextureCoords[0][i].y;
            }
            else {
                vertex.texCoord.x = 0;
                vertex.texCoord.y = 0;
            }

            vertices[i] = vertex;
        }
        Core::VertexBufferInfo vbInfo{};
        int stride_size = sizeof(float) * 8;
        vbInfo.set_buffer(vertices.data(), vertices.size() * sizeof(Vertex))
                .add_attribute(0, 3, GL_FLOAT, GL_FALSE, stride_size, 0)
                .add_attribute(1, 3, GL_FLOAT, GL_FALSE, stride_size, sizeof(mas::vec3))
                .add_attribute(2, 2, GL_FLOAT, GL_FALSE, stride_size, sizeof(mas::vec3) * 2);
        result.vb = std::make_unique<Core::VertexBuffer>(vbInfo);

        for (uint32_t i = 0; i < mesh->mNumFaces; i++) {
            aiFace face = mesh->mFaces[i];
            /** @note: can be optimized */
            for (uint32_t j = 0; j < face.mNumIndices; j++) {
                indices.push_back(face.mIndices[j]);
            }
        }
        result.ib = std::make_unique<Core::IndexBuffer>(indices.data(), indices.size() * sizeof(unsigned int), indices.size());

        if (mesh->mMaterialIndex >= 0) {
            aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
            result.mat.albdo = load_texture(material, aiTextureType_BASE_COLOR, model);
            result.mat.normal = load_texture(material, aiTextureType_NORMALS, model);
            result.mat.metallic = load_texture(material, aiTextureType_METALNESS, model);
            result.mat.roughness = load_texture(material, aiTextureType_DIFFUSE_ROUGHNESS, model);
            result.mat.ao = load_texture(material, aiTextureType_AMBIENT_OCCLUSION, model);
        }

        return result;
    }

    Core::Texture* Model::Builder::load_texture(aiMaterial *mat, aiTextureType type, Model *model) {
        if (mat->GetTextureCount(type) == 0) return nullptr;

        aiString textureName;
        mat->GetTexture(type, 0, &textureName);
        std::string fullPath = current_dir + "/" + std::string(textureName.C_Str());

        if (model->textures.find(fullPath) == model->textures.end()) {
            Core::TextureInfo texInfo {};
            texInfo.min_filter = GL_LINEAR_MIPMAP_LINEAR; // FIXME: restrict mipmap max_level and base_level
            model->textures[fullPath] = std::make_unique<Core::Texture>(fullPath, texInfo);
        }

        return model->textures[fullPath].get();
    }

    void Model::draw(Core::Shader* shader) {
        for (auto& mesh : meshes) {
            shader->use();

            bind_sampler(shader, mesh.mat.albdo, 0, "PBRV_Texture0");
            bind_sampler(shader, mesh.mat.normal, 1, "PBRV_Texture1");
            bind_sampler(shader, mesh.mat.metallic, 2, "PBRV_Texture2");
            bind_sampler(shader, mesh.mat.roughness, 3, "PBRV_Texture3");
            bind_sampler(shader, mesh.mat.ao, 4, "PBRV_Texture4");

            mesh.vb->bind();
            mesh.ib->bind();
            glDrawElements(GL_TRIANGLES, static_cast<int>(mesh.ib->get_count()), GL_UNSIGNED_INT, nullptr);
        }
    }

    void Model::bind_sampler(Core::Shader const * shader, Core::Texture const* texture, uint8_t offset, const std::string& uniform_name) {
        if (!texture) return;

        texture->bind_sampler(GL_TEXTURE0 + offset);
        shader->set_int(uniform_name, offset);
    }
}