#pragma once

#include"AABB.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"


class MapChipField;
class Player;

/// <summary>
/// 自キャラ
/// </summary>
class Enemy {
public:
	

    void Initialize(Model*model, ViewProjection* viewProjection,const Vector3& position);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();


	void SetMapChipField(MapChipField* mapChipField){mapChipField_ = mapChipField;}

	void OnCollision(const Player* player);

	//ワールド座標を取得
	Vector3 GetWorldPosition();

	AABB GetAABB();

private:

// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	ViewProjection* viewProjection_ = nullptr;

	//マップチップによるフィールド
	MapChipField* mapChipField_ = nullptr;


	//歩行の速さ
	static inline const float kWalkSpeed = 0.03f;
	//速度
	Vector3 velocity_ = {};

	//最初の角度[度]
	static inline const float kWalkMotionAngleStart = 0.0f;
	//最後の角度[度]
	static inline const float kWalkMotionAngleEnd = 30.0f;
	//アニメーションの周期となる時間[秒]
	static inline const float kWalkMotionTime = 1.0f;

	//経過
	float walkTimer_ = 0.0f;

	static inline const float kWidth = 0.8f;
	static inline const float kHeight = 0.8f;

};