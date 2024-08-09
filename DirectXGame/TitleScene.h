#pragma once

#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class TitleScene {
public:

~TitleScene();

void Initialize();

void Update();

void Draw();

bool IsFinished()const{return finished_;}

private:

// ビュープロジェクション
	ViewProjection viewProjection_;
// ワールド変換データ
	/*WorldTransform worldTransform_;*/
	WorldTransform worldTransformTitle_;
	WorldTransform worldTransformPlayer_;
	Model* modelTitle_ = nullptr;
	Model* modelPlayer_ = nullptr;

	bool finished_ = false;
	float counter_ = 0.0f;
	static inline const float kTimeTitleMove = 2.0f;
};