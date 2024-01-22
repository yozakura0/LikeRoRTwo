#include "k2EngineLowPreCompile.h"
#include "MapChipRender.h"
#include "LevelRender.h"

namespace nsK2EngineLow {

	MapChipRender::MapChipRender(const LevelRenderObjectData& objData, const char* filepath)
	{
		//モデルのファイルパスを取得
		m_filepath = std::make_unique<const char*>(filepath);

		//マップチップデータを追加
		AddMapChipData(objData);
	}

	void MapChipRender::AddMapChipData(const LevelRenderObjectData& objData)
	{
		MapChipData mapChipData;
		mapChipData.position = objData.position;
		mapChipData.rotation = objData.rotation;
		mapChipData.scale = objData.scale;
		m_mapChipDataVector.push_back(mapChipData);
	}

	void MapChipRender::Init()
	{
		m_mapChipDataNum = static_cast<int>(m_mapChipDataVector.size());

		if (m_mapChipDataNum == 1)
		{
			m_modelRender.Init(*m_filepath.get());
			auto& mapChipData = m_mapChipDataVector[0];
			m_modelRender.SetTRS(mapChipData.position, mapChipData.rotation, mapChipData.scale);
			m_modelRender.Update();
		}
	}

	void MapChipRender::Update()
	{
		if (m_mapChipDataNum == 1)
		{
			m_modelRender.Update();
		}
	}

	void MapChipRender::Draw(RenderContext& rc)
	{
		m_modelRender.Draw(rc);
	}
}