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

struct Vec3;

float dot(const Vec3& a, const Vec3& b);

struct Vec3 {
    float x;
    float y;
    float z;

    Vec3() : x(0.0), y(0.0), z(0.0) {};
    
    Vec3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {};


    Vec3 operator+(const Vec3& v) const {
        return Vec3(x + v.x, y + v.y, z + v.z);
    }
    
    Vec3 operator-(const Vec3& v) const {
        return Vec3(x - v.x, y - v.y, z - v.z);
    }

    Vec3 operator-() const {
        return Vec3(-x, -y, -z);
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

    Mat33() {};
    
    Mat33(const Vec3& col0, const Vec3& col1, const Vec3& col2) {
        _cols[0] = col0;
        _cols[1] = col1;
        _cols[2] = col2;
    }
    
    Vec3& operator[](size_t n) {
        return _cols[n];
    }

    Vec3 operator[](size_t n) const {
        return _cols[n];
    }

    Mat33 operator*(float r) const {
        Mat33 result;
        for (size_t i = 0; i < 3; ++i) {
            for (size_t j = 0; j < 3; ++j) {
                result[i][j] = _cols[i][j] * r;
            }
        }

        return result;
    }


    Vec3 operator*(const Vec3& r) const {
        Vec3 result;
        for (size_t i = 0; i < 3; ++i) {
            Vec3 row(_cols[0][i], _cols[1][i], _cols[2][i]);
            result[i] = dot(row, r);
        }

        return result;
    }
    
    float det() const {
        return _cols[0][0] * minor(0, 0)
            + _cols[1][0] * minor(1, 0)
            + _cols[2][0] * minor(2, 0);
    }

    Mat33 adj() const {
        Mat33 cofactor;
        for (size_t i = 0; i < 3; ++i) {
            for (size_t j = 0; j < 3; ++j) {
                cofactor[i][j] = minor(i, j);
            }
        }

        return cofactor.t();
    }

    Mat33 t() const {
        Mat33 t;
        for (size_t i = 0; i < 3; ++i) {
            for (size_t j = 0; j < 3; ++j) {
                t[i][j] = _cols[j][i];
            }
        }

        return t;
    }
    
    Mat33 inv() const {
        return this->adj() * (1 / (this->det()));
    }

    // Not exactly minor. Sign implicitly included. More like element of cofactor matrix
    float minor(size_t col, size_t row) const {
        size_t c0 = (col + 1) % 3;
        size_t c1 = (col + 2) % 3;
        size_t r0 = (row + 1) % 3;
        size_t r1 = (row + 2) % 3;

        return _cols[c0][r0] * _cols[c1][r1] - _cols[c1][r0] * _cols[c0][r1];
    }

    friend std::ostream& operator<<(std::ostream& os, const Mat33& m) {
        os << "[" << m[0][0] << ", " << m[1][0] << ", " << m[2][0] << "; "
           << m[0][1] << ", " << m[1][1] << ", " << m[2][1] << "; "
           << m[0][2] << ", " << m[1][2] << ", " << m[2][2] << "]";
        return os;
    }
    
private:
    Vec3 _cols[3];
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
