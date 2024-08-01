#pragma once

#include <stdint.h>
#include <vector>
#include "Vector3.h"

	// 伝統的な列挙と比べてenum classには次の利点があります。
// enum classの列挙値は暗黙的に整数型に変換されず、
// 明示的に型変換を指定する必要があります。
// enum classのenum値はそのenum型内で一意であり、
// 他のスコープの識別子とは衝突しません
enum class MapChipType {
	kBlank, // 空白
	kBlock, // ブロック
};

struct MapChipData {
	std::vector<std::vector<MapChipType>> data;
};


/// <summary>
/// マップチップフィールド
/// </summary>
class MapChipField {
public:

	struct IndexSet {
		uint32_t xIndex;
		uint32_t yIndex;
	};


    struct Rect {
		float left;       // 左端
		float right;      // 右端
		float bottom;     // 下端
		float top;        // 上端
	};


	void ResetMapChipData();
	void LoadMapChipCsv(const std::string& filePath);
	MapChipType GetMapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex);
	Vector3 GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex);
	IndexSet GetMapChipIndexSetByPosition(const Vector3& position);
	Rect GetRectByIndex(uint32_t xIndex, uint32_t yIndex);

	uint32_t GetNumBlockVirtical();
	uint32_t GetNumBlockHorizontal();
	
	/*MapChipType GetMapChipTypeByPosition(const Vector3& position);*/
	
    
	/*IndexSet GetMapChipIndexSetByPosition(const Vector3& position);*/

	

private:
	// 1ブロックのサイズ
	static inline const float kBlockWidth = 1.0f;
	static inline const float kBlockHeight = 1.0f;
	// ブロックの個数
	static inline const uint32_t kNumBlockVirtical = 20;
	static inline const uint32_t kNumBlockHorizontal = 100;

	MapChipData mapChipData_;

	

};



//#include<stdint.h>
//#include<vector>
//#include <cassert>
//#include"Vector3.h"
//#include"Model.h"
//#include"WorldTransform.h"
//#include "Viewprojection.h"
//
//// 伝統的な列挙と比べてenum classには次の利点があります。
//// enum classの列挙値は暗黙的に整数型に変換されず、
//// 明示的に型変換を指定する必要があります。
//// enum classのenum値はそのenum型内で一意であり、
//// 他のスコープの識別子とは衝突しません
//enum class MapChipType {
//	kBlank, // 空白
//	kBlock, // ブロック
//};
//
//
//struct MapChipData {
//	std::vector<std::vector<MapChipType>> data;
//};
//
///// <summary>
///// マップチップフィールド
///// </summary>
//class MapChipField {
//public:
//	void ResetMapChipData();
//	void LoadMapChipCsv(const std::string& filePath);
//	MapChipType GetMapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex);
//	Vector3 GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex);
//	uint32_t GetNumBlockVirtical();
//	uint32_t GetNumBlockHorizontal();
//
//	/*void Initialize(Model* model, ViewProjection* viewProjection); 
//
//	void Update();
//
//	void Draw();*/
//
//    static inline const float kBlockWidth = 1.0f;
//	static inline const float kBlockHeight = 1.0f;
//
//	private:
//	// 1ブロックのサイズ
//	
//	// ブロックの個数
//	static inline const uint32_t kNumBlockVirtical = 20;
//	static inline const uint32_t kNumBlockHorizontal = 100;
//
//	MapChipData mapChipData_;
//
//	//// ワールド変換データ
//	//WorldTransform worldTransform_;
//	//ViewProjection* viewProjection_ = nullptr;
//	//// モデル
//	//Model* model_ = nullptr;
//};