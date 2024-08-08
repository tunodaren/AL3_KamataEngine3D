#include "GameScene.h"
#include "TextureManager.h"
#include "myMath.h"
#include "CameraController.h"
#include <cassert>


GameScene::GameScene() {}

GameScene::~GameScene() {

	delete model_;

	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			delete worldTransformBlock;
			worldTransformBlock = nullptr;
		}
	}

	worldTransformBlocks_.clear();
	/*delete modelPlayer_;*/

	delete debugCamera_;

	delete modelSkydom_;
    
	delete mapChipField_;
    
	delete cameraController;
	
	delete player_;	

	/*delete enemy_;*/
	/*for (Enemy* enemy : enemies_) {
		delete enemy;
	}*/
	delete newEnemy_;

	delete modelDeathParticle_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	// ビュープロジェクションの初期化
	viewProjection_.Initialize();

	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("cube/cube.jpg");
	playertextureHandle_ = TextureManager::Load("mario.jpg");

	// 3Dモデルの生成 
	/*modelPlayer_ = Model::CreateFromOBJ("player",true);*/
	model_ = Model::Create();
	modelBlock_ = Model::CreateFromOBJ("block",true);
	modelSkydom_ = Model::CreateFromOBJ("sphere",true);
	modelDeathParticle_ = Model::CreateFromOBJ("deathParticle", true);

	mapChipField_ = new MapChipField;
	mapChipField_->LoadMapChipCsv("Resources/map.csv");

	// 自キャラの生成
	player_ = new Player();

	//敵キャラの生成
	/*enemy_ = new Enemy();*/
	/*for(int32_t i = 0; i < 3; ++i){
		Enemy* newEnemy = new Enemy();
		Vector3 enemyPosition = mapChipField_->GetMapChipPositionByIndex(30, 16+i);
		newEnemy->Initialize(modelEnemy_,&viewProjection_,enemyPosition);
		enemies_.push_back(newEnemy);
	}*/

	newEnemy_ = new Enemy();
	Vector3 enemyPosition = mapChipField_->GetMapChipPositionByIndex(30, 18);
	newEnemy_->Initialize(modelEnemy_, &viewProjection_, enemyPosition);

	enemies_.push_back(newEnemy_);



	//座標をマップチップ番号で指定(プレイヤー)
	Vector3 playerPosition = mapChipField_ ->GetMapChipPositionByIndex(2,18);

	//座標をマップチップ番号で指定(敵)
	/*Vector3 enemyPosition = mapChipField_ ->GetMapChipPositionByIndex(30,18);*/

	// 自キャラの初期化
	player_->Initialize(playerPosition,&viewProjection_);
	player_->SetMapChipField(mapChipField_);

	// 敵キャラの初期化
	/*enemy_->Initialize(enemyPosition,&viewProjection_);*/
	/*enemy_->SetMapChipField(mapChipField_);*/



	viewProjection_.Initialize();

	//
	skydom_ = new Skydome();
	skydom_->Initialize(modelSkydom_,&viewProjection_);


	//仮の生成処理.後で消す.
	dethParticles_ = new DeathParticles;
	dethParticles_ ->Initialize(modelDeathParticle_,&viewProjection_,playerPosition);

	// デバッグカメラの生成
	debugCamera_ = new DebugCamera(1280,720);

	GenerateBlocks();
  /*GenerateBlocks();*/



	cameraController = new CameraController();
	cameraController->Initialize();
	cameraController->SetTarget(player_);
	cameraController->Reset();

	CameraController::Rect cameraArea = {12.0f,100-12.0f,6.0f,6.0f};
	cameraController->SetMovableArea(cameraArea);




	// デバッグカメラの生成
	debugCamera_ = new DebugCamera(1280,720);

}

void GameScene::GenerateBlocks() {

	// 要素数
	 uint32_t kNumBlockVirtical = mapChipField_->GetNumBlockVirtical();
	 uint32_t kNumBlockHorizontal = mapChipField_->GetNumBlockHorizontal();
	// ブロック1個分の横幅
	/*const float kBlockWidth = 2.0f;
	const float kBlockHeight = 2.0f;*/
	// 要素数を変更する
	worldTransformBlocks_.resize(kNumBlockVirtical);

	// キューブの生成
	for (uint32_t i = 0; i < kNumBlockVirtical; ++i) {
		worldTransformBlocks_[i].resize(kNumBlockHorizontal);
	}

	/*for (uint32_t i = 0; i < kNumBlockVirtical; ++i) {
			for (uint32_t j = 0; j < kNumBlockHorizontal; ++j) {
				if (j % 2 == (i%2)) {
					worldTransformBlocks_[i][j] = new WorldTransform();
					worldTransformBlocks_[i][j]->Initialize();
					worldTransformBlocks_[i][j]->translation_.x = kBlockWidth * j;
					worldTransformBlocks_[i][j]->translation_.y = kBlockHeight * i;
				} else {
					worldTransformBlocks_[i][j] = nullptr;
				}
			}
	}*/

	for (uint32_t i = 0; i < kNumBlockVirtical; ++i) {
			for (uint32_t j = 0; j < kNumBlockHorizontal; ++j) {
				if (mapChipField_->GetMapChipTypeByIndex(j,i) == MapChipType::kBlock) {
					WorldTransform* worldTransform = new WorldTransform();
					worldTransform->Initialize();
					worldTransformBlocks_[i][j] = worldTransform;
					worldTransformBlocks_[i][j]->translation_ = mapChipField_->GetMapChipPositionByIndex(j,i);
				} /*else {
					worldTransformBlocks_[i][j] = nullptr;
				}*/
			}
	}


	}

void GameScene::Update() {



#ifdef _DEBUG


	if (input_->TriggerKey(DIK_SPACE)) {
		isDebugCameraActive_ = !isDebugCameraActive_;
		/*if (isDebugCameraActive_ == true)
			isDebugCameraActive_ = false;
		else
			isDebugCameraActive_ = true;*/
	}
#endif

	cameraController->Update();
	// カメラ処理
	if (isDebugCameraActive_) {
		// デバッグカメラの更新
		debugCamera_->Update();
		cameraController->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		// ビュープロジェクション行列の転送
		viewProjection_.TransferMatrix();
	} else {

		viewProjection_.matView = cameraController->GetViewProjection().matView;
		viewProjection_.matProjection = cameraController->GetViewProjection().matProjection;
		// ビュープロジェクション行列の更新と転送
		viewProjection_.TransferMatrix();
		/*viewProjection_.UpdateMatrix();*/
	}


	// 自キャラの更新
	player_->Update();

	//天球の更新
	skydom_->Update();

	// 敵キャラの更新
	/*enemy_->Update();*/

	for (Enemy* enemy : enemies_) {
		enemy->Update();
	}
	newEnemy_->Update();

	//デスパーティクルが存在するなら
	if (dethParticles_) {
		dethParticles_->Update();
	}

	// 縦横ブロック更新
	for (std::vector<WorldTransform*> worldTransformBlockTate : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlockYoko : worldTransformBlockTate) {
			if (!worldTransformBlockYoko)
				continue;

            // アフィン変換行列の作成
			worldTransformBlockYoko->matWorld_ = 
			MakeAffineMatrix(worldTransformBlockYoko->scale_,
		    worldTransformBlockYoko->rotation_,
			worldTransformBlockYoko->translation_);

			//定数バッファに転送
			worldTransformBlockYoko->TransferMatrix();
			/*worldTransformBlockYoko->UpdateMatrix();
			worldTransformBlockYoko->TransferMatrix();*/
		}
	}

	//　全ての当たり判定を行う
	CheckAllCollisions();

	//// 縦横ブロック更新
	//for (std::vector<WorldTransform*> worldTransformBlockTate : worldTransformBlocks_) {
	//	for (WorldTransform* worldTransformBlockYoko : worldTransformBlockTate) {
	//		if (!worldTransformBlockYoko)
	//			continue;

	//		// アフィン変換行列の作成
	//		worldTransformBlockYoko->UpdateMatrix();
	//	}
	//}
}


void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	// 3Dモデル描画
	/*model_->Draw(worldTransform_, viewProjection_, textureHandle_);*/
	modelSkydom_->Draw(worldTransform_,viewProjection_);
	// 自キャラの描画
	player_->Draw();

	//敵の描画
	/*enemy_->Draw();*/
	newEnemy_->Draw();
	newEnemy_->Draw();


	//デスパーティクルが存在するなら
	if (dethParticles_) {
		dethParticles_->Draw();
	}

	//
	/*skydom_->Draw();*/

	//
	/*mapChipField_->Draw();*/

	// 縦横ブロック描画
	for (std::vector<WorldTransform*> worldTransformBlockTate : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlockYoko : worldTransformBlockTate) {
			if (!worldTransformBlockYoko)
				continue;

			modelBlock_->Draw(*worldTransformBlockYoko, viewProjection_);
		}
	}


	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

//#pragma endregion

}


void GameScene::CheckAllCollisions() {

	//判定対象1と2の座標
	AABB aabb1, aabb2;

	//自キャラ
	aabb1 = player_->GetAABB();

	for (Enemy* enemy : enemies_) {
		aabb2 = enemy->GetAABB();

		if(IsCollision(aabb1,aabb2)){

			player_->OnCollision(enemy);

			enemy->OnCollision(player_);

		}

	}


}
