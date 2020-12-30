#include "./../include/Water.hpp"
#include "./../include/AssetsManager.hpp"
#include <chrono>
#include <random>

Water::Water():GameObject(
                glm::vec3(0.f,-15.f,0.f),
                1.f,
                glm::vec3(0.f, 0.f, 0.f),
                *new Model(AssetManager::Get()->appPath().dirPath() + "Assets/models" + "/water.obj"),
                0,
                glm::vec3(0, 0, 0))
                {}

void Water::move() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_real_distribution<double> uniformRealDistribution(-0.5,0.5);

    double x = uniformRealDistribution(generator);
//    std::cout<<"Random : "<< x<<std::endl;
    for(auto & vertex : _model->_meshes[0]._vertices){
        auto* height = new float(uniformRealDistribution(generator));
        vertex.position.y += *height;
//        std::cout<<" " << vertex.position.y << " : "<< x;

    }
//    std::cout<<" Random position : " << _model->_meshes[0]._vertices[0].position.y << std::endl;
}
//

void Water::displayWater() {
    glUniformMatrix4fv(AssetManager::Get()->_waterProgram.M_Location(), 1, GL_FALSE, glm::value_ptr(_M));
    glUniformMatrix4fv(AssetManager::Get()->_waterProgram.MV_Location(), 1, GL_FALSE, glm::value_ptr(_MV));
    glUniformMatrix4fv(AssetManager::Get()->_waterProgram.MVP_Location(), 1, GL_FALSE, glm::value_ptr(_MVP));
    glUniformMatrix4fv(AssetManager::Get()->_waterProgram.N_Location(), 1, GL_FALSE, glm::value_ptr(_N));

    GLuint diffuseNr = 1;
    GLuint specularNr = 1;


    // draw mesh
    glBindVertexArray(_model->_meshes[0]._vao);
    glBindBufferRange(GL_UNIFORM_BUFFER, 0 , _model->_meshes[0]._ubo, 0, sizeof(Material));
    glDrawElements(GL_TRIANGLES, _model->_meshes[0]._indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // Unbind
    for (size_t i = 0; i < _model->_meshes[0]._textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}


