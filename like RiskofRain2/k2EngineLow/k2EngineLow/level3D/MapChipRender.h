#pragma once

namespace nsK2EngineLow {
	struct LevelRenderObjectData;

	struct MapChipData
	{
		//座標
		Vector3 position;
		//大きさ
		Vector3 scale;
		//回転
		Quaternion rotation;

	};

	class MapChipRender :public Noncopyable
	{
	public:
		MapChipRender(const LevelRenderObjectData& objData,const char* filepath);

		//マップチップデータを追加
		void AddMapChipData(const LevelRenderObjectData& objData);

		//初期化
		void Init();

		//モデルの更新
		void Update();

		//描画処理
		void Draw(RenderContext& rc);

	private:
		//モデルレンダー
		ModelRender m_modelRender;
		//マップチップデータのリスト
		std::vector<MapChipData> m_mapChipDataVector;
		//tkmファイルパス
		std::unique_ptr<const char*> m_filepath;
		//静的物理オブジェクトのスマートポインタの配列
		std::vector<std::unique_ptr<PhysicsStaticObject>> m_physicsStaticObjectPtrVector;
		//マップチップデータの数
		int m_mapChipDataNum;
	};

}