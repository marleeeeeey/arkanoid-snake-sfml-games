#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

int main()
{
    glm::vec2 vector( 1.0f, 0.0f ); // Initial vector (horizontal)
    float angleDegrees = 45.0f; // Rotation angle in degrees

    // Convert angle from degrees to radians
    float angleRadians = glm::radians( angleDegrees );

    // Create a rotation matrix
    glm::mat4 rotationMatrix = glm::rotate( glm::mat4( 1.0f ), angleRadians, glm::vec3( 0.0f, 0.0f, 1.0f ) );

    // Rotate the vector using the rotation matrix
    glm::vec4 rotatedVector = rotationMatrix * glm::vec4( vector, 0.0f, 1.0f );

    // Extract the rotated 2D vector from the result
    glm::vec2 rotated2DVector( rotatedVector );

    std::cout << "Original Vector: (" << vector.x << ", " << vector.y << ")" << std::endl;
    std::cout << "Rotated Vector: (" << rotated2DVector.x << ", " << rotated2DVector.y << ")" << std::endl;
}
