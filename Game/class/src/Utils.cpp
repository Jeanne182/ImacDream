#include "../include/Utils.h"
#include <cmath>


double dot(glm::vec3 v1, glm::vec3 v2) {
    double result = 0.0;
    for(size_t i=0; i<3; ++i)
        result += v1[i]*v2[i];

    return result;
}

void normalize(glm::vec3 vector) {
    double vec_norm = std::sqrt(dot(vector, vector));
    for (size_t i =0; i<3; i++)
        vector[i] /= vec_norm;
}