#include "myMath.h"
#include "Vector3.h"
#include "GameScene.h"
#include <Easing.h>

// 行列の掛け算
Matrix4x4 MatrixMultiply(Matrix4x4& m1, Matrix4x4& m2) {

    Matrix4x4 result;
    result.m[0][0] = m1.m[0][0] * m2.m[0][0] + m1.m[0][1] * m2.m[1][0] + m1.m[0][2] * m2.m[2][0] + m1.m[0][3] * m2.m[3][0];
    result.m[0][1] = m1.m[0][0] * m2.m[0][1] + m1.m[0][1] * m2.m[1][1] + m1.m[0][2] * m2.m[2][1] + m1.m[0][3] * m2.m[3][1];
    result.m[0][2] = m1.m[0][0] * m2.m[0][2] + m1.m[0][1] * m2.m[1][2] + m1.m[0][2] * m2.m[2][2] + m1.m[0][3] * m2.m[3][2];
    result.m[0][3] = m1.m[0][0] * m2.m[0][3] + m1.m[0][1] * m2.m[1][3] + m1.m[0][2] * m2.m[2][3] + m1.m[0][3] * m2.m[3][3];
    result.m[1][0] = m1.m[1][0] * m2.m[0][0] + m1.m[1][1] * m2.m[1][0] + m1.m[1][2] * m2.m[2][0] + m1.m[1][3] * m2.m[3][0];
    result.m[1][1] = m1.m[1][0] * m2.m[0][1] + m1.m[1][1] * m2.m[1][1] + m1.m[1][2] * m2.m[2][1] + m1.m[1][3] * m2.m[3][1];
    result.m[1][2] = m1.m[1][0] * m2.m[0][2] + m1.m[1][1] * m2.m[1][2] + m1.m[1][2] * m2.m[2][2] + m1.m[1][3] * m2.m[3][2];
    result.m[1][3] = m1.m[1][0] * m2.m[0][3] + m1.m[1][1] * m2.m[1][3] + m1.m[1][2] * m2.m[2][3] + m1.m[1][3] * m2.m[3][3];
    result.m[2][0] = m1.m[2][0] * m2.m[0][0] + m1.m[2][1] * m2.m[1][0] + m1.m[2][2] * m2.m[2][0] + m1.m[2][3] * m2.m[3][0];
    result.m[2][1] = m1.m[2][0] * m2.m[0][1] + m1.m[2][1] * m2.m[1][1] + m1.m[2][2] * m2.m[2][1] + m1.m[2][3] * m2.m[3][1];
    result.m[2][2] = m1.m[2][0] * m2.m[0][2] + m1.m[2][1] * m2.m[1][2] + m1.m[2][2] * m2.m[2][2] + m1.m[2][3] * m2.m[3][2];
    result.m[2][3] = m1.m[2][0] * m2.m[0][3] + m1.m[2][1] * m2.m[1][3] + m1.m[2][2] * m2.m[2][3] + m1.m[2][3] * m2.m[3][3];
    result.m[3][0] = m1.m[3][0] * m2.m[0][0] + m1.m[3][1] * m2.m[1][0] + m1.m[3][2] * m2.m[2][0] + m1.m[3][3] * m2.m[3][0];
    result.m[3][1] = m1.m[3][0] * m2.m[0][1] + m1.m[3][1] * m2.m[1][1] + m1.m[3][2] * m2.m[2][1] + m1.m[3][3] * m2.m[3][1];
    result.m[3][2] = m1.m[3][0] * m2.m[0][2] + m1.m[3][1] * m2.m[1][2] + m1.m[3][2] * m2.m[2][2] + m1.m[3][3] * m2.m[3][2];
    result.m[3][3] = m1.m[3][0] * m2.m[0][3] + m1.m[3][1] * m2.m[1][3] + m1.m[3][2] * m2.m[2][3] + m1.m[3][3] * m2.m[3][3];

    return result;
}

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rot, const Vector3& translate){

    Matrix4x4 ScallMat,
              RotateMat,RotateMatX,RotateMatY,RotateMatZ,
              TranslateMat,
              returnMat
              /*,RotateMatAll , ansMat*/;

    // スケール行列作成
    ScallMat = {scale.x, 0, 0, 0,
                0, scale.y, 0, 0,
                0, 0, scale.z, 0,
                0, 0, 0, 1};

    // XYZ回転行列作成
    RotateMatX = {1, 0, 0, 0,
                  0, cosf(rot.x), sinf(rot.x), 0,
                  0,-sinf(rot.x), cosf(rot.x), 0,
                  0, 0, 0, 1};

    RotateMatY = {cosf(rot.y), 0,-sinf(rot.y), 0,
                  0, 1, 0, 0,
                  sinf(rot.y), 0, cosf(rot.y), 0,
                  0, 0, 0, 1};

    RotateMatZ = {cosf(rot.z), sinf(rot.z), 0, 0,
                 -sinf(rot.z), cosf(rot.z), 0, 0,
                  0, 0, 1, 0,
                  0, 0, 0, 1};

    // XYZ回転行列の合成(Z*X*Y)
    RotateMat = MatrixMultiply(RotateMatZ, RotateMatX);
    // ↑の結果＊Y軸回転
    RotateMat = MatrixMultiply(RotateMat, RotateMatY);

    // 平行移動行列作成
    TranslateMat = {1, 0, 0, 0,
                    0, 1, 0, 0,
                    0, 0, 1, 0,
                    translate.x, translate.y, translate.z, 1};

    // スケール＊回転＊平行移動をワールド変換行列に
    returnMat = MatrixMultiply(ScallMat, RotateMat);
    returnMat = MatrixMultiply(returnMat, TranslateMat);

    //X軸回転*Y軸回転で回転行列を合成
    Matrix4x4 RotateMatAll = MatrixMultiply(RotateMatX,RotateMatY);

    //回転*平行で回転行列だけをワールド変換行列に
    Matrix4x4 ansMat = MatrixMultiply(RotateMatAll,TranslateMat);

    return returnMat;
}



Vector3& operator+=(Vector3& lhv, const Vector3& rhv) {
	lhv.x += rhv.x;
	lhv.y += rhv.y;
	lhv.z += rhv.z;
	return lhv;
}

float EaseInOut(float x1, float x2, float t) {
	float easedT = -(std::cosf(std::numbers::pi_v<float> * t) - 1.0f) / 2.0f;
	return Lerp(x1, x2, easedT);
}

float Lerp(float x1, float x2, float t) { return (1.0f - t) * x1 + t * x2; }

Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t) { return Vector3(Lerp(v1.x, v2.x, t), Lerp(v1.y, v2.y, t), Lerp(v1.z, v2.z, t)); }

const Vector3 operator+(const Vector3& v1, const Vector3& v2) { 
    Vector3 temp(v1);
	return temp += v2;
}

Vector3& operator*=(Vector3& v, float s) { 
    v.x *= s;
	v.y *= s;
	v.z *= s;
	return v;
}

const Vector3 operator*(const Vector3& v, float s) {
	Vector3 temp(v);
	return temp *= s;
}




//Vector3 operator+(const Vector3& v) { return v; }
//Vector3 operator-(const Vector3& v) { return Vector3(-v.x, -v.y, -v.z); }
//
//const Vector3 operator+(const Vector3& v1, const Vector3& v2) { 
//    Vector3 temp(v1);
//	return temp += v2;
//}
//
//Vector3& operator+=(Vector3& lhv, const Vector3& rhv) {
//	lhv.x += rhv.x;
//	lhv.y += rhv.y;
//	lhv.z += rhv.z;
//	return lhv;
//}
//
//Vector3& operator*=(Vector3& v, float s) { 
//    v.x *= s;
//	v.y *= s;
//	v.z *= s;
//	return v;
//}
//
//const Vector3 operator*(const Vector3& v, float s) {
//	Vector3 temp(v);
//	return temp *= s;
//}
//
//float EaseInOut(float x1, float x2, float t) {
//	float easedT = -(std::cosf(std::numbers::pi_v<float> * t) - 1.0f) / 2.0f;
//	return Lerp(x1, x2, easedT);
//}
//
//float Lerp(float x1, float x2, float t) { return (1.0f - t) * x1 + t * x2; }
//
//Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t) { return Vector3(Lerp(v1.x, v2.x, t), Lerp(v1.y, v2.y, t), Lerp(v1.z, v2.z, t)); }



//Vector3& operator-=(Vector3& lhv, const Vector3& rhv) {
//	lhv.x -= rhv.x;
//	lhv.y -= rhv.y;
//	lhv.z -= rhv.z;
//	return lhv;
//}
//Vector3& operator*=(Vector3& v, float s) {
//	v.x *= s;
//	v.y *= s;
//	v.z *= s;
//	return v;
//}
//Vector3& operator/=(Vector3& v, float s) {
//	v.x /= s;
//	v.y /= s;
//	v.z /= s;
//	return v;
//}
//// 2項演算子オーバーロード
//const Vector3 operator+(const Vector3& v1, const Vector3& v2) {
//	Vector3 temp(v1);
//	return temp += v2;
//}
//const Vector3 operator-(const Vector3& v1, const Vector3& v2) {
//	Vector3 temp(v1);
//	return temp -= v2;
//}
//const Vector3 operator*(const Vector3& v, float s) {
//	Vector3 temp(v);
//	return temp *= s;
//}
//const Vector3 operator*(float s, const Vector3& v) { return v * s; }
//const Vector3 operator/(const Vector3& v, float s) {
//	Vector3 temp(v);
//	return temp /= s;
//}
////数学関数のｈ
//// 単項演算子オーバーロード
//Vector3 operator+(const Vector3& v);
//Vector3 operator-(const Vector3& v);
//// 代入演算子オーバーロード
//Vector3& operator+=(Vector3& lhs, const Vector3& rhv);
//Vector3& operator-=(Vector3& lhs, const Vector3& rhv);
//Vector3& operator*=(Vector3& v, float s);
//Vector3& operator/=(Vector3& v, float s);
//// 2項演算子オーバーロード
//const Vector3 operator+(const Vector3& v1, const Vector3& v2);
//const Vector3 operator-(const Vector3& v1, const Vector3& v2);
//const Vector3 operator*(const Vector3& v, float s);
//const Vector3 operator*(float s, const Vector3& v);
//const Vector3 operator/(const Vector3& v, float s);

