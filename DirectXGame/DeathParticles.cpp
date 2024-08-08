//#pragma once
#define NOMINMAX

#include "DeathParticles.h"
#include "Input.h"
#include "DirectxCommon.h"
#include "MapChipField.h"
#include "myMath.h"
#include "Easing.h"
#include <algorithm>
#include <cassert>
#include <numbers>


void DeathParticles::Initialize(Model*model, ViewProjection* viewProjection,const Vector3& position) {

	for(auto& worldTransforms : worldTransforms_)
	{

	worldTransforms.Initialize();
	worldTransforms.translation_ = position;

	}
	model_ = model;
	viewProjection_ = viewProjection;
	
	/*objectColor_.Initialize();
	color_ = {1,1,1,1};*/
}


void DeathParticles::Update() {

	//終了なら何もしない
	if (isFinished_) {
		return;
	}


	for (auto& worldTransform : worldTransforms_) {
	    worldTransform.UpdateMatrix();
	}

	for (uint32_t i = 0; i < worldTransforms_.size(); ++i) {
		//基本となる速さベクトル
		Vector3 velocity = {kSpeed, 0, 0};
		//回転角を計算する
		float angle = kAngleUnit * i;
		//Z軸まわり回転行列
		Matrix4x4 matrixRotation = MakeRotateZMatrix(angle);
		//基本ベクトルを回転させて速度ベクトルを得る
		velocity = Transform(velocity, matrixRotation);
		//移動処理
		worldTransforms_[i].translation_ += velocity;
	}

	//カウンターを1フレーム分の秒数進める
	counter_ += 1.0f / 60.0f;

	//残存時間の上限に達したら
	if (counter_ >= kDuration) {
		counter_ = kDuration;
		//終了扱いにする
		isFinished_ = true;
	}
	/*color_.w = std::clamp(counter_,0.0f,1.0f);*/
	/*color_.w = std::clamp(counter_,0.0f,1.0f);*/
    //色変更オブジェクトに色の数値を設定する
	/*objectColor_.SetColor(color_);*/
	//色変更オブジェクトをVRAMに転送
	/*objectColor_.TransferMatrix();*/
}

void DeathParticles::Draw() {

	//終了なら何もしない
	if (isFinished_) {
		return;
	}

	for (auto& worldTransform : worldTransforms_) {
		model_->Draw(worldTransform,*viewProjection_/*,&objectColor_*/);
	
	}

}