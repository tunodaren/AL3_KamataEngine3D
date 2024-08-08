#pragma once

#include <vector>

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Player.h"
#include "Enemy.h"
#include "DebugCamera.h"
#include "Skydome.h"
#include "MapChipField.h"
#include "CameraController.h"
#include "DeathParticles.h"




/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();


	//　全ての当たり判定を行う
	void CheckAllCollisions();

	
	     

private: // メンバ変数

	//ゲームのフェイズ(型)
	enum class Phase {
		kplay, //ゲームプレイ
		kDeath,
	};

	//ゲームの現在フェイズ
	Phase phase_;

	DeathParticles*deathParticles_ = nullptr;

	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	// テクスチャハンドル
	uint32_t textureHandle_ = 0;
	uint32_t playertextureHandle_ = 0;
	// 3Dモデル
	Model* model_ = nullptr;
	Model* modelPlayer_ = nullptr;
	Model* modelBlock_ = nullptr;
	Model* modelSkydom_ = nullptr;
	Model* modelEnemy_ = nullptr;
	Model* modelDeathParticle_ = nullptr;
	
	// ワールドトランスフォーム
	/*WorldTransform worldTransformSkydome_;*/
	WorldTransform worldTransform_;
	// ビュープロジェクション
	ViewProjection viewProjection_;

	// 自キャラ
	Player* player_ = nullptr;

	//敵キャラ
	Enemy* newEnemy_ = nullptr;
	/*Enemy* enemy_ = nullptr;*/
	std::list<Enemy*> enemies_;

	// 縦横ブロック配列
	std::vector<std::vector<WorldTransform*>> worldTransformBlocks_;

	// デバッグカメラ有効
	bool isDebugCameraActive_ = false;
	// デバッグカメラ
	DebugCamera* debugCamera_ = nullptr;

	// スカイドーム
	Skydome* skydom_ =nullptr;

	//マップチップフィールド
	MapChipField* mapChipField_ = nullptr;

	CameraController* cameraController = nullptr;

	DeathParticles* dethParticles_ = nullptr;

	void ChangePhase();

	void GenerateBlocks();
	
	void UpdateCamera();

	void UpdateBlocks();
	
	/*void GenerateBlocks();*/
};