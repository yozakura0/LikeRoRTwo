#pragma once

const int CommonBoxNum = 20;
const int UncommonBoxNum = 10;
const int RareBoxNum = 1;
const int ItemNum = CommonBoxNum + UncommonBoxNum + RareBoxNum;

//レア度
enum rarity
{
	Common,		//普通
	Uncommon,	//普通じゃない
	Rare		//希少
};

//コモンアイテム
enum commonItem
{
	gasoline,				//ガソリン
	//sylinge,				//注射器
	armorPlate,				//アーマープレート
	//triDagger,				//三角の短剣
	Crowber,				//かなてこ
	//topazBrooch,			//トパーズのブローチ
	//armorPiercingRounds,	//装甲貫通弾
	tougherTimes,			//タファータイムス
	lensMakerGlasses,		//レンズメーカーの眼鏡
	//roketFireWorks,			//ロケット花火
	//bisonSteak,				//バイソンのステーキ
	//cautiousSlug,			//慎重なナメクジ
	goatHoof,				//ヤギのひづめ
	//medkit,					//救急キット
	//bustlingFungus,			//活力のキノコ
	//focusCrystal,			//焦点クリスタル
	//shieldGenerator,		//シールド発生器
	//backupMagazine,			//バックアップマガジン
	//energyDrink,			//エナジードリンク
	//stickyBomb,				//粘着爆弾
	//stunGranade,			//スタングレネード
	//monsterTooth,			//モンスターの歯
	//warBanner,				//戦旗
	CommonNum
};
//アンコモンアイテム
enum uncommonItem
{
	//predatoryInstincts,		//捕食本能
	//bandolier,				//弾薬帯
	//ghorTome,				//ゴーアの本
	//ukulele,				//ウクレレ
	//deathMark,				//死の印
	//warHorn,				//戦の角笛
	//fuelCell,				//燃料電池
	//oldGuillotine,			//古いギロチン
	Dynamite,				//ダイナマイト(ウィスプ)
	//hopooFeather,			//ホッポの羽根
	//kjaroBand,				//クジャロのバンド
	//runaldBand,				//ルナルドのバンド
	//harvesterScythe,		//収穫者の大鎌
	infusion,				//注入液
	//waxQuail,				//蝋のウズラ
	//atGMissile_Mk1,			//対戦車ミサイルMk1
	//oldWarStealthkit,		//大戦時のステルスキット
	//leechingSeed,			//吸血種子
	//chronobauble,			//クロノボーブル
	roseBuckler,			//バラのバックラー
	//redWhip,				//赤いムチ
	//leptonDaisy,			//レプトンデイジー
	//razorwire,				//刃の鉄線
	//berzerkerPauldron,		//バーサーカーの肩甲
	//squidPolyp,				//イカのポリプ
	UncommonNum
};
//レアアイテム
enum rareItem
{
	//alienHead,				//エイリアンの頭
	//shatteringJustice,		//正義の鉄槌
	//aegis,					//イージス
	//brilliantBehemoth,		//ブリリアントベヒーモス
	//sentientMeatHook,		//鋭敏なフック
	//cloverOf57Leafs,		//57枚葉のクローバー
	//ceremonialDagger,		//儀式用の短剣
	//dioBestFriend,			//ディオの親友
	//H3AD_ST_v2,				//H3AD-ST v2
	//wakeOfVultures,			//ハゲワシの目覚め
	frostRelic,				//氷の遺物
	//rejuvenationRack,		//若返りの角
	//brainstalks,			//ブレインストーク
	//resonanceDisc,			//共鳴の円盤
	//nkuhanaOpinion,			//ンクハラの意見
	//interstellarDeskPlant,	//惑星間デスクプラント
	//unstableTeslaCoil,		//不安定なテスラコイル
	//soulboundCatalyst,		//結魂の触媒
	//hardlightAfterburner,	//ハードライトアフターバーナー
	//happiestMask,			//至福の仮面
	RareNum
};

enum itemJudge
{
	//アイテムの所持状況の要素
	havingItem,
	//アイテムの所持個数の要素
	havingItemNum,
	//配列定義用
	ItemJudgeNum
};

enum EnemyCost
{
	beetle = 2,
	wisp = 5,
	imp = 7,
	golem = 10,
	g_wisp = 20
};
