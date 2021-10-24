#ifndef ALGE_H
#define ALGE_H

#include <iostream>
#include <cmath>

const float small = 0.005f;

bool as_zero(float n) {
    return n >= -small && n <= small;
}

bool as_negative(float n) {
    return n < -small;
}

bool as_positive(float n) {
    return n > small;
}

struct Vec3 {
    float x;
    float y;
    float z;

    Vec3() : x(0.0), y(0.0), z(0.0) {};
    
    Vec3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {};

    Vec3 operator-(const Vec3& v) const {
        return Vec3(x - v.x, y - v.y, z - v.z);
    }

    float& operator[](size_t n) {
        return *(reinterpret_cast<float*>(this) + n);
    }

    float operator[](size_t n) const {
        return *(reinterpret_cast<const float*>(this) + n);
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Vec3& v) {
        os << "[" << v.x << ", " << v.y << ", " << v.z << "]";
        return os;
    }
};

struct Mat33 {
    Vec3 cols[3];

    Vec3& operator[](size_t n) {
        return cols[n];
    }

    Vec3 operator[](size_t n) const {
        return cols[n];
    }

    Mat33 inv() {
        // TODO
    }
};

Vec3 cross(const Vec3& a, const Vec3& b) {
    return Vec3(
        a.y * b.z - b.y * a.z,
        b.x * a.z - a.x * b.z,
        a.x * b.y - b.x * a.y
        );
}

float dot(const Vec3& a, const Vec3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

float length2(const Vec3& v) {
    return v.x * v.x + v.y * v.y + v.z * v.z;
}

float length(const Vec3& v) {
    return sqrt(length2(v));
}


#endif
