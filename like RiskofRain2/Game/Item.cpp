#include "stdafx.h"
#include "Item.h"
#include "Number.h"

void Item::Create(Vector3 pos, int boxtype)
{
	m_itemPos = pos;
	int rarityJudge = rand() % 100;

	//デバッグ
	//rarityJudge = 50;

	switch (boxtype)
	{
	case 0:
		if (rarityJudge < 80)
		{
			//白
			m_itemRarity = m_common;
		}
		else if (rarityJudge < 99)
		{
			//緑
			m_itemRarity = m_uncommon;
		}
		else
		{
			//赤
			m_itemRarity = m_rare;
		}
		break;
	case 1:
		if (rarityJudge < 80)
		{
			//緑
			m_itemRarity = m_uncommon;
		}
		else
		{
			//赤
			m_itemRarity = m_rare;
		}
		break;
	case 2:
		m_itemRarity = m_rare;
		break;
	default:
		break;
	}

	switch (m_itemRarity)
	{
	case 0:
		ItemJudge_common();
		
		//デバッグ
		m_itemNum = rand() % 6;

		switch (m_itemNum)
		{
		/*case sylinge:
			m_itemRender.Init("Assets/modelData/item/sylinge.tkm");
			break;*/
		case armorPlate:
			m_itemRender.Init("Assets/modelData/item/armorPlate.tkm");
			break;
		/*case triDagger:
			m_itemRender.Init("Assets/modelData/item/triDagger.tkm");
			break;*/
		case Crowber:
			m_itemRender.Init("Assets/modelData/item/crowber.tkm");
			break;
		/*case topazBrooch:
			m_itemRender.Init("Assets/modelData/item/topazBrooch.tkm");
			break;*/
		case tougherTimes:
			m_itemRender.Init("Assets/modelData/item/tougherTimes.tkm");
			break;
		/*case armorPiercingRounds:
			m_itemRender.Init("Assets/modelData/item/armorPiercingRounds.tkm");
			break;*/
		case lensMakerGlasses:
			m_itemRender.Init("Assets/modelData/item/lensMakerGlasses.tkm");
			break;
		/*case roketFireWorks:
			m_itemRender.Init("Assets/modelData/item/roketFireWorks.tkm");
			break;*/
		/*case bisonSteak:

			break;*/
		/*case cautiousSlug:

			break;*/
		case goatHoof:
			m_itemRender.Init("Assets/modelData/item/goatHoof.tkm");
			break;
		case gasoline:
			m_itemRender.Init("Assets/modelData/item/gasoline.tkm");
			break;
		/*case medkit:

			break;*/
		/*case bustlingFungus:

			break;*/
		/*case focusCrystal:

			break;*/
		/*case shieldGenerator:

			break;*/
		/*case backupMagazine:

			break;*/
		/*case energyDrink:

			break;*/
		/*case stickyBomb:

			break;*/
		/*case stunGranade:

			break;*/
		/*case monsterTooth:

			break;*/
		/*case warBanner:

			break;*/
		default:
			break;
		}

		break;
	case 1:
		ItemJudge_uncommon();

		switch (m_itemNum)
		{
		/*case predatoryInstincts:

			break;*/
		/*case bandolier:

			break;*/
		/*case ghorTome:

			break;*/
		/*case ukulele:

			break;*/
		/*case deathMark:

			break;*/
		/*case warHorn:

			break;*/
		/*case fuelCell:

			break;*/
		/*case oldGuillotine:

			break;*/
		case Dynamite:
			m_itemRender.Init("Assets/modelData/item/dynamite.tkm");
			break;
		/*case hopooFeather:

			break;*/
		/*case kjaroBand:

			break;*/
		/*case runaldBand:

			break;*/
		/*case harvesterScythe:

			break;*/
		case infusion:
			m_itemRender.Init("Assets/modelData/item/infusion.tkm");
			break;
		/*case waxQuail:

			break;*/
		/*case atGMissile_Mk1:

			break;*/
		/*case oldWarStealthkit:

			break;*/
		/*case leechingSeed:

			break;*/
		/*case chronobauble:

			break;*/
		case roseBuckler:
			m_itemRender.Init("Assets/modelData/item/buckler.tkm");
			break;
		/*case redWhip:

			break;*/
		/*case leptonDaisy:

			break;*/
		/*case razorwire:

			break;*/
		/*case berzerkerPauldron:

			break;*/
		/*case squidPolyp:

			break;*/
		default:
			break;
		}
		break;
	case 2:
		ItemJudge_rare();

		switch (m_itemNum)
		{
		//case alienHead:
		//	//m_itemRender.Init();
		//	break;
		//case shatteringJustice:
		//	//m_itemRender.Init();
		//	break;
		//case aegis:
		//	//m_itemRender.Init();
		//	break;
		//case brilliantBehemoth:
		//	//m_itemRender.Init();
		//	break;
		//case sentientMeatHook:
		//	//m_itemRender.Init();
		//	break;
		//case cloverOf57Leafs:
		//	//m_itemRender.Init();
		//	break;
		//case ceremonialDagger:
		//	//m_itemRender.Init();
		//	break;
		//case dioBestFriend:
		//	//m_itemRender.Init();
		//	break;
		//case H3AD_ST_v2:
		//	//m_itemRender.Init();
		//	break;
		//case wakeOfVultures:
		//	//m_itemRender.Init();
		//	break;
		case frostRelic:
			m_itemRender.Init("Assets/modelData/item/frostRelic.tkm");
			break;
		//case rejuvenationRack:
		//	//m_itemRender.Init();
		//	break;
		//case brainstalks:
		//	//m_itemRender.Init();
		//	break;
		//case resonanceDisc:
		//	//m_itemRender.Init();
		//	break;
		//case nkuhanaOpinion:
		//	//m_itemRender.Init();
		//	break;
		//case interstellarDeskPlant:
		//	//m_itemRender.Init();
		//	break;
		//case unstableTeslaCoil:
		//	//m_itemRender.Init();
		//	break;
		//case soulboundCatalyst:
		//	//m_itemRender.Init();
		//	break;
		//case hardlightAfterburner:
		//	//m_itemRender.Init();
		//	break;
		//case happiestMask:
		//	//m_itemRender.Init();
		//	break;

		default:
			break;
		}
		break;
	default:
		break;
	}

	m_itemRender.SetPosition(m_itemPos);
}

void Item::ItemJudge_common()
{
	srand((unsigned int)time(NULL));
	m_itemNum = rand() % CommonNum;
}

void Item::ItemJudge_uncommon()
{
	srand((unsigned int)time(NULL));
	m_itemNum = rand() % UncommonNum;
}

void Item::ItemJudge_rare()
{
	srand((unsigned int)time(NULL));
	m_itemNum = rand() % RareNum;
}

void Item::Update()
{
	//回る
	m_itemRotation.AddRotationDegY(1.0f);
	m_itemRender.SetRotation(m_itemRotation);

	m_itemRender.Update();
}

void Item::Render(RenderContext& rc)
{
	//描画
	m_itemRender.Draw(rc);
}