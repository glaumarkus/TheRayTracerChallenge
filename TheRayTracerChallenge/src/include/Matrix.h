#ifndef INCLUDE_MATRIX_H
#define INCLUDE_MATRIX_H

#include "Vec4.h"

namespace RayTracer {

// Mat2
class Mat2 {
public:

    Mat2() {
        f[0][0] = 1.0f;
        f[0][1] = 0.0f;

        f[1][1] = 1.0f;
        f[1][0] = 0.0f;
    }

	Mat2(float fi[2][2]) {
        std::memcpy(f, fi, sizeof f);
	}

    Mat2(const Mat2& m2) {
        for (int r = 0; r < 2; ++r) {
            for (int c = 0; c < 2; ++c) {
                f[r][c] = m2.f[r][c];
            }
        }
    }

	Mat2(Mat2&& m2) noexcept {
        std::memcpy(&f, &m2.f, sizeof f);
	}

    ~Mat2() {}

    void transpose() {

        float tmp;

        // swapping 1 cells
        tmp = f[0][1];
        f[0][1] = f[1][0];
        f[1][0] = tmp;
    }

    inline Mat2& operator =(const Mat2& m2) {
        for (int r = 0; r < 2; ++r) {
            for (int c = 0; c < 2; ++c) {
                f[r][c] = m2.f[r][c];
            }
        }
        return *this;
    }

	inline Mat2& operator =(Mat2&& m2) noexcept {
        std::memcpy(&f, &m2.f, sizeof m2.f);
		return *this;
	}

    float f[2][2];
};

// determinante
inline float determinant(const Mat2& m2) {
    return m2.f[0][0] * m2.f[1][1] - m2.f[1][0] * m2.f[0][1];
}


// Mat3
class Mat3 {
public:

    Mat3() {
        f[0][0] = 1.0f;
        f[0][1] = 0.0f;
        f[0][1] = 0.0f;

        f[1][0] = 0.0f;
        f[1][1] = 1.0f;
        f[1][2] = 0.0f;

        f[2][0] = 0.0f;
        f[2][1] = 0.0f;
        f[2][2] = 1.0f;
    }

    Mat3(float fi[3][3]) {
        std::memcpy(f, fi, sizeof f);
    }

    Mat3(const Mat3& m3) {
        for (int r = 0; r < 3; ++r) {
            for (int c = 0; c < 3; ++c) {
                f[r][c] = m3.f[r][c];
            }
        }
    }

	Mat3(Mat3&& m3) noexcept {
		std::memcpy(&f, &m3.f, sizeof f);
	}

    ~Mat3() {}

    inline Mat3& operator =(const Mat3& m3) {
        for (int r = 0; r < 3; ++r) {
            for (int c = 0; c < 3; ++c) {
                f[r][c] = m3.f[r][c];
            }
        }
        return *this;
    }
	inline Mat3& operator =(Mat3&& m3) noexcept {
        std::memcpy(&f, &m3.f, sizeof f);
		return *this;
	}

	float f[3][3];
};

// Mat3 submatrix
Mat2 submatrix(const Mat3& m3, const int& ri, const int& ci) {

    float f[2][2];

    int nr = 0;

    for (int r = 0; r < 3; ++r) {
        if (r == ri)
            continue;

        int nc = 0;
        for (int c = 0; c < 3; ++c) {
            if (c == ci)
                continue;

            f[nr][nc] = m3.f[r][c];
            nc++;
        }
        nr++;
    }

    return Mat2(f);
}

float minor(const Mat3& m3, const int& ri, const int& ci) {
    return determinant(Mat2(submatrix(m3, ri, ci)));
}

float cofactor(const Mat3& m3, const int& ri, const int& ci) {
    return minor(m3, ri, ci) * ((ri + ci) % 2 > 0 ? -1 : 1);
}

float determinant(const Mat3& m3) {
    float det = 0.0f;
    for (int c = 0; c < 3; ++c) {
        det += m3.f[0][c] * cofactor(m3, 0, c);
    }
    return det;
}


// Mat4
class Mat4 {
public:
    Mat4() {
        f[0][0] = 1.0f;
        f[0][1] = 0.0f;
        f[0][2] = 0.0f;
        f[0][3] = 0.0f;

        f[1][0] = 0.0f;
        f[1][1] = 1.0f;
        f[1][2] = 0.0f;
        f[1][3] = 0.0f;

        f[2][0] = 0.0f;
        f[2][1] = 0.0f;
        f[2][2] = 1.0f;
        f[2][3] = 0.0f;

        f[3][0] = 0.0f;
        f[3][1] = 0.0f;
        f[3][2] = 0.0f;
        f[3][3] = 1.0f;
    }


	Mat4(float fi[4][4]) {
		memcpy(f, fi, sizeof(f));
	}

    Mat4(const Mat4& m4) {
        for (int r = 0; r < 4; ++r) {
            for (int c = 0; c < 4; ++c) {
                f[r][c] = m4.f[r][c];
            }
        }
    }

	Mat4(Mat4&& m4) noexcept {
        std::memcpy(&f, &m4.f, sizeof f);
	}

    ~Mat4() {}

    void transpose() {

        float tmp;

        // swapping 6 cells
        tmp = f[0][1];
        f[0][1] = f[1][0];
        f[1][0] = tmp;

        tmp = f[0][2];
        f[0][2] = f[2][0];
        f[2][0] = tmp;

        tmp = f[0][3];
        f[0][3] = f[3][0];
        f[3][0] = tmp;

        tmp = f[1][2];
        f[1][2] = f[2][1];
        f[2][1] = tmp;

        tmp = f[1][3];
        f[1][3] = f[3][1];
        f[3][1] = tmp;

        tmp = f[2][3];
        f[2][3] = f[3][2];
        f[3][2] = tmp;

    }

    // copy constructor
    inline Mat4& operator =(const Mat4& m4) {
        for (int r = 0; r < 4; ++r) {
            for (int c = 0; c < 4; ++c) {
                f[r][c] = m4.f[r][c];
            }
        }
        return *this;
    }

    // move constructor
	inline Mat4& operator =(Mat4&& m4) noexcept {
        std::memcpy(&f, &m4.f, sizeof f);
		return *this;
	}

    void print() {
        printf("(%f, %f, %f, %f)\n", f[0][0], f[0][1], f[0][2], f[0][3]);
        printf("(%f, %f, %f, %f)\n", f[1][0], f[1][1], f[1][2], f[1][3]);
        printf("(%f, %f, %f, %f)\n", f[2][0], f[2][1], f[2][2], f[2][3]);
        printf("(%f, %f, %f, %f)\n", f[3][0], f[3][1], f[3][2], f[3][3]);
    }

    float f[4][4];
};

// Mat4 submatrix
Mat3 submatrix(const Mat4& m4, const int& ri, const int& ci) {

    float f[3][3];

    int nr = 0;

    for (int r = 0; r < 4; ++r) {
        if (r == ri)
            continue;
        int nc = 0;
        for (int c = 0; c < 4; ++c) {
            if (c == ci)
                continue;

            f[nr][nc] = m4.f[r][c];
            nc++;
        }
        nr++;
    }

    return Mat3(f);
}

float determinant(const Mat4& m4) {
    float det = 0.0f;
    for (int c = 0; c < 4; ++c) {
        Mat3 sub(submatrix(m4, 0, c));
        float tmp = 0.0f;
        for (int c2 = 0; c2 < 3; ++c2) {
            tmp += sub.f[0][c2] * cofactor(sub, 0, c2);
        }
        det += tmp * (c % 2 > 0 ? -1 : 1) * m4.f[0][c];
    }
    return det;
}

bool inverse(Mat4& m4) {
    float det = determinant(m4);
    if (det < EPSILON && det > -EPSILON)
        return false;

    float m4_new[4][4];
    for (int r = 0; r < 4; ++r) {
        for (int c = 0; c < 4; ++c) {
            float tmp = determinant(submatrix(m4, r, c)) * ((r + c) % 2 > 0 ? -1 : 1);
            m4_new[c][r] = tmp / det;
        }
    }
    m4 = Mat4(m4_new);
    return true;
}


// equal
bool equal(const Mat2& m1, const Mat2& m2) {
    for (int r = 0; r < 2; ++r) {
        for (int c = 0; c < 2; ++c) {
            if (m1.f[r][c] != m2.f[r][c])
                return false;
        }
    }
    return true;
}

bool equal(const Mat3& m1, const Mat3& m2) {
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            if (m1.f[r][c] != m2.f[r][c])
                return false;
        }
    }
    return true;
}

bool equal(const Mat4& m1, const Mat4& m2) {
    for (int r = 0; r < 4; ++r) {
        for (int c = 0; c < 4; ++c) {
            if (m1.f[r][c] != m2.f[r][c])
                return false;
        }
    }
    return true;
}


// addition
inline Mat2 operator +(const Mat2& m1, const Mat2& m2) noexcept {
    float f[2][2];
    for (int r = 0; r < 2; ++r) {
        for (int c = 0; c < 2; ++c) {
            f[r][c] = m1.f[r][c] + m2.f[r][c];
        }
    }
    return Mat2(f);
}

inline Mat3 operator +(const Mat3& m1, const Mat3& m2) noexcept {
    float f[3][3];
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            f[r][c] = m1.f[r][c] + m2.f[r][c];
        }
    }
    return Mat3(f);
}

inline Mat4 operator +(const Mat4& m1, const Mat4& m2) noexcept {
    float f[4][4];
    for (int r = 0; r < 4; ++r) {
        for (int c = 0; c < 4; ++c) {
            f[r][c] = m1.f[r][c] + m2.f[r][c];
        }
    }
    return Mat4(f);
}

// substraction
inline Mat2 operator -(const Mat2& m1, const Mat2& m2) noexcept {
    float f[2][2];
    for (int r = 0; r < 2; ++r) {
        for (int c = 0; c < 2; ++c) {
            f[r][c] = m1.f[r][c] - m2.f[r][c];
        }
    }
    return Mat2(f);
}

inline Mat3 operator -(const Mat3& m1, const Mat3& m2) noexcept {
    float f[3][3];
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            f[r][c] = m1.f[r][c] - m2.f[r][c];
        }
    }
    return Mat3(f);
}

inline Mat4 operator -(const Mat4& m1, const Mat4& m2) noexcept {
    float f[4][4];
    for (int r = 0; r < 4; ++r) {
        for (int c = 0; c < 4; ++c) {
            f[r][c] = m1.f[r][c] - m2.f[r][c];
        }
    }
    return Mat4(f);
}

// multiplication
inline Mat2 operator *(const Mat2& m1, const Mat2& m2) noexcept {
    float f[2][2];
    for (int r = 0; r < 2; ++r) {
        for (int c = 0; c < 2; ++c) {
            float tmp = 0.0f;
            for (int i = 0; i < 2; ++i) {
                tmp += m1.f[r][i] * m2.f[i][c];
            }
            f[r][c] = tmp;
        }
    }
    return Mat2(f);
}

inline Mat3 operator *(const Mat3& m1, const Mat3& m2) noexcept {
    float f[3][3];
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            float tmp = 0.0f;
            for (int i = 0; i < 3; ++i) {
                tmp += m1.f[r][i] * m2.f[i][c];
            }
            f[r][c] = tmp;
        }
    }
    return Mat3(f);
}

inline Mat4 operator *(const Mat4& m1, const Mat4& m2) noexcept {
    float f[4][4];
    for (int r = 0; r < 4; ++r) {
        for (int c = 0; c < 4; ++c) {
            float tmp = 0.0f;
            for (int i = 0; i < 4; ++i) {
                tmp += m1.f[r][i] * m2.f[i][c];
            }
            f[r][c] = tmp;
        }
    }
    return Mat4(f);
}

// multiplication vector
inline Vec4 operator *(const Mat4& m, const Vec4& v) {
    float f[4];
    for (int r = 0; r < 4; ++r) {
        float tmp = 0.0f;
        for (int c = 0; c < 4; ++c) {
            tmp += m.f[r][c] * v[c];
        }
        f[r] = tmp;
    }
    return Vec4(f[0], f[1], f[2], f[3]);
}


// move pt
Mat4 translate(const float& x, const float& y, const float& z) {
    float f[4][4] = {
        {1.0f, 0.0f, 0.0f, x   },
        {0.0f, 1.0f, 0.0f, y   },
        {0.0f, 0.0f, 1.0f, z   },
        {0.0f, 0.0f, 0.0f, 1.0f}
    };
    return Mat4(f);
}

// increase pt
Mat4 scale(const float& x, const float& y, const float& z) {
    float f[4][4] = {
        {x,    0.0f, 0.0f, 0.0f},
        {0.0f, y,    0.0f, 0.0f},
        {0.0f, 0.0f, z,    0.0f},
        {0.0f, 0.0f, 0.0f, 1.0f}
    };
    return Mat4(f);
}

// rotate pt on x
Mat4 rotate_x(const float& rad) {
    float f[4][4] = {
        {1.0f, 0.0f,      0.0f,     0.0f},
        {0.0f, cos(rad), -sin(rad), 0.0f},
        {0.0f, sin(rad),  cos(rad), 0.0f},
        {0.0f, 0.0f,      0.0f,     1.0f}
    };
    return Mat4(f);
}

// rotate pt on y
Mat4 rotate_y(const float& rad) {
    float f[4][4] = {
        {cos(rad),  0.0f, sin(rad), 0.0f},
        {0.0f,      1.0f, 0.0f,     0.0f},
        {-sin(rad), 0.0f, cos(rad), 0.0f},
        {0.0f,      0.0f, 0.0f,     1.0f}
    };
    return Mat4(f);
}

// rotate pt on z
Mat4 rotate_z(const float& rad) {
    float f[4][4] = {
        {cos(rad), -sin(rad),  0.0f, 0.0f},
        {sin(rad),  cos(rad),  0.0f, 0.0f},
        {0.0f,      0.0f,      1.0f, 0.0f},
        {0.0f,      0.0f,      0.0f, 1.0f}
    };
    return Mat4(f);
}

// influence of params on others
Mat4 shear(const float& xy, const float& xz, const float& yx, const float& yz, const float& zx, const float& zy) {
    float f[4][4] = {
        {1.0f, xy,   xz,   0.0f},
        {yx,   1.0f, yz,   0.0f},
        {zx,   zy,   1.0f, 0.0f},
        {0.0f, 0.0f, 0.0f, 1.0f}
    };
    return Mat4(f);
}

// chain all transformations
Mat4 transform(
    const float& x_translate = 0.0f,
    const float& y_translate = 0.0f,
    const float& z_translate = 0.0f,
    const float& x_scale = 1.0f,
    const float& y_scale = 1.0f,
    const float& z_scale = 1.0f,
    const float& x_rotate = 0.0f,
    const float& y_rotate = 0.0f,
    const float& z_rotate = 0.0f,
    const float& xy = 0.0f,
    const float& xz = 0.0f,
    const float& yx = 0.0f,
    const float& yz = 0.0f,
    const float& zx = 0.0f,
    const float& zy = 0.0f
) {
    Mat4 translation, scaling, rotation_x, rotation_y, rotation_z, shearing;

    if (x_translate != 0.0f || y_translate != 0.0f || y_translate == 0.0f)
        translation = translate(x_translate, y_translate, z_translate);

    if (x_scale != 1.0f || y_scale != 1.0f || z_scale != 1.0f)
        scaling = scale(x_scale, y_scale, z_scale);

    if (x_rotate != 0.0f)
        rotation_x = rotate_x(x_rotate);

    if (y_rotate != 0.0f)
        rotation_y = rotate_y(y_rotate);

    if (z_rotate != 0.0f)
        rotation_z = rotate_z(z_rotate);

    if (xy != 0.0f || xz != 0.0f || yx != 0.0f || yz != 0.0f || zx != 0.0f || zy != 0.0f)
        shearing = shear(xy, xz, yx, yz, zx, zy);

    return Mat4(translation * scaling * rotation_x * rotation_y * rotation_z * shearing);
}


}

#endif 