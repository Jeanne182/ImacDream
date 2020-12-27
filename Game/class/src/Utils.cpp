#include "../include/Utils.hpp"
#include <cmath>


double dotProduct(const glm::vec3 &v1, const glm::vec3 &v2) {
    assert(v1.length()==v2.length() && "dot product:error:not the same size");
    double result = 0.0;
    for(size_t i=0; i<3; ++i)
        result += v1[i]*v2[i];

    return result;
}

void normalize(glm::vec3 &vector) {
    double vec_norm = std::sqrt(dotProduct(vector, vector));
    for (size_t i =0; i<3; i++)
        vector[i] /= vec_norm;
}

/*
template<typename Type>
Type crossProduct(const Type &a, const Type &b){

}
*/