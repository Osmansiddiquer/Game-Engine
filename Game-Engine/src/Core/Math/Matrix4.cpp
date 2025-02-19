#include "Engine_pch.h"
#include "Core/Math/Matrix4.h"
#include "Math.h"
#include "Core/Math/Matrix3.h"
#include "Core/Math/Quaternion.h"
#include "Core/Math/Vector3.h"
#include "Core/Math/Vector4.h"

namespace Engine::Math
{
    const Matrix4 Matrix4::zero = Matrix4{};
    const Matrix4 Matrix4::identity =
        Matrix4{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
    const Matrix4 Matrix4::xRot45 =
        Math::Matrix4::RotateX(0.5f * PI_HALF);
    const Matrix4 Matrix4::xRot90 =
        Matrix4{ 1, 0, 0, 0, 0, 0, 1, 0, 0, -1, 0, 0, 0, 0, 0, 1 };
    const Matrix4 Matrix4::yRot45 =
        Math::Matrix4::RotateY(0.5f * PI_HALF);
    const Matrix4 Matrix4::yRot90 =
        Matrix4{ 0, 0, -1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1 };
    const Matrix4 Matrix4::zRot45 =
        Math::Matrix4::RotateZ(0.5f * PI_HALF);
    const Matrix4 Matrix4::zRot90 =
        Matrix4{ 0, 1, 0, 0, -1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };

    Matrix4::Matrix4() { memset(data, 0, sizeof(data)); }

    Matrix4::Matrix4(float value) {
        for (float& item : data) {
            item = value;
        }
    }

    // Matrix4::Matrix4(const float* inMat) {
    //  for (int i = 0; i < ELEMENT_COUNT; i++) {
    //    data[i] = inMat[i];
    //  }
    //}

    Matrix4::Matrix4(const float inMat[]) {
        for (int i = 0; i < ELEMENT_COUNT; ++i) {
            data[i] = inMat[i];
        }
    }

    Matrix4::Matrix4(float m11, float m12, float m13, float m14, float m21,
        float m22, float m23, float m24, float m31, float m32,
        float m33, float m34, float m41, float m42, float m43,
        float m44) {
        data[0] = m11;
        data[1] = m12;
        data[2] = m13;
        data[3] = m14;
        data[4] = m21;
        data[5] = m22;
        data[6] = m23;
        data[7] = m24;
        data[8] = m31;
        data[9] = m32;
        data[10] = m33;
        data[11] = m34;
        data[12] = m41;
        data[13] = m42;
        data[14] = m43;
        data[15] = m44;
    }

    Matrix4::Matrix4(const Math::Quaternion& quat) {
        SetRow(ROW_COUNT - 1, Math::Vector4{ 0 });
        SetCol(ROW_COUNT - 1, Math::Vector4{ 0 });
        SetTopLeftMatrix3(quat.GetMatrix3());
        row_col[ROW_COUNT - 1][ROW_COUNT - 1] = 1;
    }

    Matrix4::Matrix4(const Matrix4& inMatrix) {
        for (int i = 0; i < ELEMENT_COUNT; ++i) {
            data[i] = inMatrix.data[i];
        }
    }

    Matrix4::Matrix4(Matrix4&& inMatrix) noexcept {
        for (int i = 0; i < ELEMENT_COUNT; ++i) {
            data[i] = inMatrix.data[i];
        }
    }

    Matrix4& Matrix4::operator=(const Matrix4& inMatrix) {
        for (int i = 0; i < ELEMENT_COUNT; ++i) {
            data[i] = inMatrix.data[i];
        }
        return *this;
    }

    Matrix4& Matrix4::operator=(Matrix4&& inMatrix) noexcept {
        for (int i = 0; i < ELEMENT_COUNT; ++i) {
            data[i] = inMatrix.data[i];
        }
        return *this;
    }

    Matrix4::Matrix4(const Vector4& aVector, const Vector4& bVector) {
        data[0] = aVector.x * bVector.x;
        data[1] = aVector.x * bVector.y;
        data[2] = aVector.x * bVector.z;
        data[3] = aVector.x * bVector.w;
        data[4] = aVector.y * bVector.x;
        data[5] = aVector.y * bVector.y;
        data[6] = aVector.y * bVector.z;
        data[7] = aVector.y * bVector.w;
        data[8] = aVector.z * bVector.x;
        data[9] = aVector.z * bVector.y;
        data[10] = aVector.z * bVector.z;
        data[11] = aVector.z * bVector.w;
        data[12] = aVector.w * bVector.x;
        data[13] = aVector.w * bVector.y;
        data[14] = aVector.w * bVector.z;
        data[15] = aVector.w * bVector.w;
    }

    // float Matrix4::operator[](int i) const {
    //  if (i < 0 || i > ELEMENT_COUNT - 1)
    //    throw std::out_of_range{"Matrix4::[] => Index access out of range."};
    //  return data[i];
    //}
    float* Matrix4::operator[](int i) const {
        if (i < 0 || i > ROW_COUNT - 1)
            throw std::out_of_range{ "Matrix4::[] => Index access out of range." };
        return (float*)(row_col[i]);
    }
    bool Matrix4::operator==(const Matrix4& rhs) const {
        for (int i = 0; i < ELEMENT_COUNT; ++i) {
            if (data[i] != rhs.data[i]) {
                return false;
            }
        }
        return true;
    }

    bool Matrix4::operator!=(const Matrix4& rhs) const {
        for (int i = 0; i < ELEMENT_COUNT; ++i) {
            if (data[i] != rhs.data[i]) {
                return true;
            }
        }
        return false;
    }

    Matrix4 Matrix4::operator+(const Matrix4& rhs) const {
        Matrix4 ret{};
        for (int i = 0; i < ELEMENT_COUNT; ++i) {
            ret.data[i] += rhs.data[i];
        }
        return ret;
    }

    Matrix4& Matrix4::operator+=(const Matrix4& rhs) {
        for (int i = 0; i < ELEMENT_COUNT; ++i) {
            data[i] += rhs.data[i];
        }
        return *this;
    }

    Matrix4 Matrix4::operator-(const Matrix4& rhs) const {
        Matrix4 ret{};
        for (int i = 0; i < ELEMENT_COUNT; ++i) {
            ret.data[i] -= rhs.data[i];
        }
        return ret;
    }

    Matrix4 Matrix4::operator-=(const Matrix4& rhs) {
        for (int i = 0; i < ELEMENT_COUNT; ++i) {
            data[i] += rhs.data[i];
        }
        return *this;
    }

    Matrix4 Matrix4::operator*(const Matrix4& rhs) const {
        Matrix4 ret{};
        for (int i = 0; i < ROW_COUNT; ++i) {
            for (int j = 0; j < ROW_COUNT; ++j) {
                for (int k = 0; k < ROW_COUNT; ++k) {
                    ret.row_col[i][j] += row_col[i][k] * rhs.row_col[k][j];
                }
            }
        }
        return ret;
    }

    Matrix4 Matrix4::operator*=(const Matrix4& rhs) {
        float newData[ROW_COUNT][ROW_COUNT];
        for (int i = 0; i < ROW_COUNT; ++i) {
            for (int j = 0; j < ROW_COUNT; ++j) {
                newData[i][j] = 0;
                for (int k = 0; k < ROW_COUNT; ++k) {
                    newData[i][j] += row_col[i][k] * rhs.row_col[k][j];
                }
            }
        }
        for (int i = 0; i < ROW_COUNT; ++i) {
            for (int j = 0; j < ROW_COUNT; ++j) {
                row_col[i][j] = newData[i][j];
            }
        }
        return *this;
    }

    Matrix4 Matrix4::operator*(const float scalar) const {
        Matrix4 ret{};
        for (int i = 0; i < ELEMENT_COUNT; ++i) {
            ret.data[i] = data[i] * scalar;
        }
        return ret;
    }

    Matrix4 Matrix4::operator*=(const float scalar) {
        for (int i = 0; i < ELEMENT_COUNT; ++i) {
            data[i] *= scalar;
        }
        return *this;
    }

    Vector4 Matrix4::operator*(const Vector4& rhs) const {
        return Vector4{
            data[0] * rhs.x + data[1] * rhs.y + data[2] * rhs.z + data[3] * rhs.w,
            data[4] * rhs.x + data[5] * rhs.y + data[6] * rhs.z + data[7] * rhs.w,
            data[8] * rhs.x + data[9] * rhs.y + data[10] * rhs.z + data[11] * rhs.w,
            data[12] * rhs.x + data[13] * rhs.y + data[14] * rhs.z +
                data[15] * rhs.w };
    }

    float Matrix4::Determinant() const {
        float m11 = data[5] * data[10] * data[15] - data[5] * data[11] * data[14] -
            data[9] * data[6] * data[15] + data[9] * data[7] * data[14] +
            data[13] * data[6] * data[11] - data[13] * data[7] * data[10];
        float m21 = -data[4] * data[10] * data[15] + data[4] * data[11] * data[14] +
            data[8] * data[6] * data[15] - data[8] * data[7] * data[14] -
            data[12] * data[6] * data[11] + data[12] * data[7] * data[10];
        float m31 = data[4] * data[9] * data[15] - data[4] * data[11] * data[13] -
            data[8] * data[5] * data[15] + data[8] * data[7] * data[13] +
            data[12] * data[5] * data[11] - data[12] * data[7] * data[9];
        float m41 = -data[4] * data[9] * data[14] + data[4] * data[10] * data[13] +
            data[8] * data[5] * data[14] - data[8] * data[6] * data[13] -
            data[12] * data[5] * data[10] + data[12] * data[6] * data[9];
        return data[0] * m11 + data[1] * m21 + data[2] * m31 + data[3] * m41;
    }

    float Matrix4::Get(int x, int y) const {
        if (x > ELEMENT_COUNT - 1 || x < 0 || y > ELEMENT_COUNT - 1 || y < 0) {
            throw std::out_of_range{ "Matrix4::Get => Matrix index out of range." };
        }
        return row_col[x][y];
    }

    void Matrix4::Set(int x, int y, float number) {
        if (x > ELEMENT_COUNT - 1 || x < 0 || y > ELEMENT_COUNT - 1 || y < 0) {
            throw std::out_of_range{ "Matrix4::Set => Matrix index out of range." };
        }
        row_col[x][y] = number;
    }

    Matrix4 Matrix4::Inverse() const {
        float m11 = data[5] * data[10] * data[15] - data[5] * data[11] * data[14] -
            data[9] * data[6] * data[15] + data[9] * data[7] * data[14] +
            data[13] * data[6] * data[11] - data[13] * data[7] * data[10];
        float m21 = -data[4] * data[10] * data[15] + data[4] * data[11] * data[14] +
            data[8] * data[6] * data[15] - data[8] * data[7] * data[14] -
            data[12] * data[6] * data[11] + data[12] * data[7] * data[10];
        float m31 = data[4] * data[9] * data[15] - data[4] * data[11] * data[13] -
            data[8] * data[5] * data[15] + data[8] * data[7] * data[13] +
            data[12] * data[5] * data[11] - data[12] * data[7] * data[9];
        float m41 = -data[4] * data[9] * data[14] + data[4] * data[10] * data[13] +
            data[8] * data[5] * data[14] - data[8] * data[6] * data[13] -
            data[12] * data[5] * data[10] + data[12] * data[6] * data[9];
        float m12 = -data[1] * data[10] * data[15] + data[1] * data[11] * data[14] +
            data[9] * data[2] * data[15] - data[9] * data[3] * data[14] -
            data[13] * data[2] * data[11] + data[13] * data[3] * data[10];
        float m22 = data[0] * data[10] * data[15] - data[0] * data[11] * data[14] -
            data[8] * data[2] * data[15] + data[8] * data[3] * data[14] +
            data[12] * data[2] * data[11] - data[12] * data[3] * data[10];
        float m32 = -data[0] * data[9] * data[15] + data[0] * data[11] * data[13] +
            data[8] * data[1] * data[15] - data[8] * data[3] * data[13] -
            data[12] * data[1] * data[11] + data[12] * data[3] * data[9];
        float m42 = data[0] * data[9] * data[14] - data[0] * data[10] * data[13] -
            data[8] * data[1] * data[14] + data[8] * data[2] * data[13] +
            data[12] * data[1] * data[10] - data[12] * data[2] * data[9];
        float m13 = data[1] * data[6] * data[15] - data[1] * data[7] * data[14] -
            data[5] * data[2] * data[15] + data[5] * data[3] * data[14] +
            data[13] * data[2] * data[7] - data[13] * data[3] * data[6];
        float m23 = -data[0] * data[6] * data[15] + data[0] * data[7] * data[14] +
            data[4] * data[2] * data[15] - data[4] * data[3] * data[14] -
            data[12] * data[2] * data[7] + data[12] * data[3] * data[6];
        float m33 = data[0] * data[5] * data[15] - data[0] * data[7] * data[13] -
            data[4] * data[1] * data[15] + data[4] * data[3] * data[13] +
            data[12] * data[1] * data[7] - data[12] * data[3] * data[5];
        float m43 = -data[0] * data[5] * data[14] + data[0] * data[6] * data[13] +
            data[4] * data[1] * data[14] - data[4] * data[2] * data[13] -
            data[12] * data[1] * data[6] + data[12] * data[2] * data[5];
        float m14 = -data[1] * data[6] * data[11] + data[1] * data[7] * data[10] +
            data[5] * data[2] * data[11] - data[5] * data[3] * data[10] -
            data[9] * data[2] * data[7] + data[9] * data[3] * data[6];
        float m24 = data[0] * data[6] * data[11] - data[0] * data[7] * data[10] -
            data[4] * data[2] * data[11] + data[4] * data[3] * data[10] +
            data[8] * data[2] * data[7] - data[8] * data[3] * data[6];
        float m34 = -data[0] * data[5] * data[11] + data[0] * data[7] * data[9] +
            data[4] * data[1] * data[11] - data[4] * data[3] * data[9] -
            data[8] * data[1] * data[7] + data[8] * data[3] * data[5];
        float m44 = data[0] * data[5] * data[10] - data[0] * data[6] * data[9] -
            data[4] * data[1] * data[10] + data[4] * data[2] * data[9] +
            data[8] * data[1] * data[6] - data[8] * data[2] * data[5];

        float det = data[0] * m11 + data[1] * m21 + data[2] * m31 + data[3] * m41;

        if (det == 0) {
            throw std::out_of_range{
                "Matrix4::Inverse => Cannot do inverse when the determinant is zero." };
        }

        Matrix4 ret{ m11, m12, m13, m14, m21, m22, m23, m24,
                    m31, m32, m33, m34, m41, m42, m43, m44 };
        return ret * (1.f / det);
    }

    Matrix4 Matrix4::Transpose() const {
        Matrix4 ret{ *this };
        std::swap(ret.data[1], ret.data[4]);
        std::swap(ret.data[2], ret.data[8]);
        std::swap(ret.data[3], ret.data[12]);
        std::swap(ret.data[6], ret.data[9]);
        std::swap(ret.data[7], ret.data[13]);
        std::swap(ret.data[11], ret.data[14]);
        return ret;
    }

    bool Matrix4::IsIdentity() const {
        for (int i = 0; i < ROW_COUNT; ++i) {
            for (int j = 0; j < ROW_COUNT; ++j) {
                if (data[(i << 2) + j] != static_cast<float>(i == j) ||
                    data[(j << 2) + i] != static_cast<float>(i == j)) {
                    return false;
                }
            }
        }
        return true;
    }

    bool Matrix4::IsZero() const {
        for (int i = 0; i < ELEMENT_COUNT; ++i) {
            if (data[i] != 0) return false;
        }
        return true;
    }

    Vector4 Matrix4::GetRow(const int row) const {
        if (row < 0 || row > ROW_COUNT - 1)
            throw std::out_of_range{ "Matrix4::GetRow => Row index out of range." };
        return Vector4(data[row << 2], data[(row << 2) + 1], data[(row << 2) + 2],
            data[(row << 2) + 3]);
    }

    void Matrix4::SetRow(const int row, const Vector4& rowData) {
        if (row < 0 || row > ROW_COUNT)
            throw std::out_of_range{ "Matrix4::SetRow => Row index out of range." };
        for (int i = 0; i < ROW_COUNT; ++i) {
            row_col[row][i] = rowData[i];
        }
    }

    void Matrix4::SetRow(const int row, const Vector3& rowData,
        const float rowVal) {
        if (row < 0 || row > ROW_COUNT - 1)
            throw std::out_of_range{ "Matrix4::SetRow => Row index out of range." };
        for (int i = 0; i < Vector3::ELEMENT_COUNT; ++i) {
            row_col[row][i] = rowData[i];
        }
        row_col[row][ROW_COUNT - 1] = rowVal;
    }

    Vector4 Matrix4::GetCol(const int col) const {
        if (col < 0 || col > ROW_COUNT - 1)
            throw std::out_of_range{ "Matrix4:GetCol => Column index out of range." };
        return Vector4{ row_col[0][col], row_col[1][col], row_col[2][col],
                       row_col[3][col] };
    }

    Matrix3 Matrix4::GetTopLeftMatrix3() const {
        Matrix3 mat3;
        for (int i = 0; i < Vector3::ELEMENT_COUNT; ++i) {
            mat3.SetCol(i, static_cast<Vector3>(GetCol(i)));
        }
        return mat3;
    }

    void Matrix4::SetCol(const int col, const Vector4& colData) {
        if (col < 0 || col > ROW_COUNT)
            throw std::out_of_range{ "Matrix4:SetCol => Column index out of range." };
        for (int i = 0; i < ROW_COUNT; ++i) {
            row_col[i][col] = colData[i];
        }
    }

    void Matrix4::SetCol(const int col, const Vector3& colData,
        const float colVal) {
        if (col < 0 || col > ROW_COUNT - 1)
            throw std::out_of_range{ "Matrix4:SetCol => Column index out of range." };
        for (int i = 0; i < Vector3::ELEMENT_COUNT; ++i) {
            row_col[i][col] = colData[i];
        }
        row_col[ROW_COUNT - 1][col] = colVal;
    }

    void Matrix4::SetTopLeftMatrix3(const Matrix3& matrix3) {
        for (int i = 0; i < Vector3::ELEMENT_COUNT; ++i) {
            SetCol(i, matrix3.GetCol(i), Get(3, i));
        }
    }

    void Matrix4::SetDiagonal(const Vector4& diagonal) {
        SetDiagonal(diagonal.x, diagonal.y, diagonal.z, diagonal.w);
    }

    void Matrix4::SetDiagonal(float r0c0, float r1c1, float r2c2, float r3c3) {
        row_col[0][0] = r0c0;
        row_col[1][1] = r1c1;
        row_col[2][2] = r2c2;
        row_col[3][3] = r3c3;
    }

    Matrix4 Matrix4::Translate(const Vector3& translation) {
        return Matrix4{ 1, 0, 0, translation.x,  //
                       0, 1, 0, translation.y,  //
                       0, 0, 1, translation.z,  //
                       0, 0, 0, 1 };
    }

    Matrix4 Matrix4::Scale(const Vector3& scale) {
        return Matrix4{ scale.x, 0,       0,       0,  //
                       0,       scale.y, 0,       0,  //
                       0,       0,       scale.z, 0,  //
                       0,       0,       0,       1 };
    }

    Matrix4 Matrix4::RotateX(float radians) {
        float Cos = cos(radians);
        float Sin = sin(radians);
        return Matrix4{ 1, 0,    0,   0,  //
                       0,Cos,  Sin, 0,  //
                       0, -Sin, Cos, 0,  //
                       0, 0,    0,   1 };
    }
    Matrix4 Matrix4::RotateY(float radians) {
        float Cos = cos(radians);
        float Sin = sin(radians);
        return Matrix4{ Cos, 0, -Sin, 0,  //
                       0,   1, 0,    0,  //
                       Sin, 0, Cos,  0,  //
                       0,   0, 0,    1 };
    }
    Matrix4 Matrix4::RotateZ(float radians) {
        float Cos = cos(radians);
        float Sin = sin(radians);
        return Matrix4{ Cos,  Sin, 0, 0,  //
                       -Sin, Cos, 0, 0,  //
                       0,    0,   1, 0,  //
                       0,    0,   0, 1 };
    }

    Matrix4 Matrix4::Rotate(const Vector3& rotation) {
        return RotateX(rotation.x) * RotateY(rotation.y) * RotateZ(rotation.z);
    }

    Matrix4 Matrix4::Transform(const Vector3& translation, const Vector3& rotation,
        const Vector3& scale) {
        return Translate(translation) * Rotate(rotation) * Scale(scale);
    }

    bool Matrix4::FuzzyEqual(const Matrix4& lhs, const Matrix4& rhs) {
        for (int i = 0; i < ELEMENT_COUNT; ++i) {
            if (abs(lhs.data[i] - rhs.data[i]) > FLT_EPSILON) {
                return false;
            }
        }
        return true;
    }
}
