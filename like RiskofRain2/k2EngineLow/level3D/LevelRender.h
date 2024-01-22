#pragma once

#include "TklFile.h"

namespace nsK2EngineLow {
	class MapChipRender;

	//オブジェクト名
	struct LevelRenderObjectData
	{
		//座標
		Vector3 position;
		//回転
		Quaternion rotation;
		//拡大率
		Vector3 scale;
		//名前
		const wchar_t* name;
		int number = 0;

		//引数で渡したオブジェクト名のオブジェクトか調べる
		bool EqualObjectName(const wchar_t* objName)
		{
			return wcscmp(objName, name) == 0;
		}

		//名前が前方一致するか調べる
		bool ForwardMatchName(const wchar_t* n)
		{
			auto len = wcslen(n);
			auto namelen = wcslen(name);

			//名前が長い時falseを返す
			if (len > namelen)
			{
				return false;
			}

			return wcsncmp(n, name, len) == 0;
		}

	};


	class LevelRender :public Noncopyable
	{
	private:
		using MapChipRenderPtr = std::shared_ptr<MapChipRender>;
	public:
		//レベルを初期化
		void Init(
			//tklファイルパス
			const char* filepath, 
			//オブジェクト作成時の処理をフックするための関数オブジェクト
			std::function<bool(LevelRenderObjectData& objData)> hookFunc
		);

		//更新処理
		void Update();

		//モデルを描画
		void Draw(RenderContext& rc);

	private:
		//マップチップを作成
		void CreateMapChipRender(const LevelRenderObjectData& objData, const char* filePath);

		//tklファイルの行列を変換する
		void MatrixTklToLevel();

	private:
		//ボーンPtr
		using BonePtr = std::unique_ptr<Bone>;
		//ボーンのリスト
		std::vector<BonePtr> m_bonelist;
		//行列のリスト
		std::unique_ptr<Matrix[]> m_matrixlist;
		//マップチップの可変長配列
		std::map < std::string, MapChipRenderPtr > m_mapChipRenderPtrs;
		//tklファイル
		TklFile m_tklFile;
	};

}