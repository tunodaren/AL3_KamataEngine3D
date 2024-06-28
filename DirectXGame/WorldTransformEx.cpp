#include "WorldTransform.h"
#include "myMath.h"

void WorldTransform::UpdateMatrix() {

//スケール、回転、平行移動、
matWorld_ = MakeAffineMatrix(scale_, rotation_, translation_);

TransferMatrix();


}

