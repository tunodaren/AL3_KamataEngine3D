#define NOMINMAX

#include "Enemy.h"
#include "Input.h"
#include "DirectxCommon.h"
#include "MapChipField.h"
#include "myMath.h"
#include "Easing.h"
#include <algorithm>
#include <cassert>
#include <numbers>


void Enemy::Initialize(const Vector3& position, ViewProjection* viewProjection) {

// ワールド変換の初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;

	viewProjection_ = viewProjection;

	// 左を向かせる(πとか数値情報が定義されてる)
	worldTransform_.rotation_.y -= std::numbers::pi_v<float> / 2.0f;

// 引数の内容をメンバ変数に記録
	model_ = Model::CreateFromOBJ("enemy", true);


    velocity_ = {-kWalkSpeed,0,0};
	walkTimer_ = 0.0f;

}


void Enemy::Draw() {

// 3Dモデルを描画
	model_->Draw(worldTransform_, *viewProjection_);

}


void Enemy::Update() {

//タイマーを加算
	walkTimer_ += 1.0f / 60.0f;

// 行列計算
	worldTransform_.UpdateMatrix();
// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();

	//移動
	worldTransform_.translation_+= velocity_;

	//X軸周り角度 = std::sin(2π*経過時間/アニメーションの周期となる時間); 
	worldTransform_.rotation_.x = std::sin(std::numbers::pi_v<float> * 2.0f * walkTimer_ / kWalkMotionTime);

}