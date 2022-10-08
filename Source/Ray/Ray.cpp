#include "Ray/Ray.h"

std::ostream& operator<<(std::ostream& os, const linalg::aliases::float3& R) {
    os << R.x << ", " << R.y << ", " << R.z;
    return os;
}

std::ostream& operator<<(std::ostream& os, const Raytracer::Ray& R) {
    os << "Origin: " << R.Origin << " Direction: " << R.Direction;
    return os;
}
