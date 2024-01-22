#pragma once

const int CommonBoxNum = 20;
const int UncommonBoxNum = 10;
const int RareBoxNum = 1;
const int ItemNum = CommonBoxNum + UncommonBoxNum + RareBoxNum;

//���A�x
enum rarity
{
	Common,		//����
	Uncommon,	//���ʂ���Ȃ�
	Rare		//��
};

//�R�����A�C�e��
enum commonItem
{
	gasoline,				//�K�\����
	//sylinge,				//���ˊ�
	armorPlate,				//�A�[�}�[�v���[�g
	//triDagger,				//�O�p�̒Z��
	Crowber,				//���ȂĂ�
	//topazBrooch,			//�g�p�[�Y�̃u���[�`
	//armorPiercingRounds,	//���b�ђʒe
	tougherTimes,			//�^�t�@�[�^�C���X
	lensMakerGlasses,		//�����Y���[�J�[�̊ዾ
	//roketFireWorks,			//���P�b�g�ԉ�
	//bisonSteak,				//�o�C�\���̃X�e�[�L
	//cautiousSlug,			//�T�d�ȃi���N�W
	goatHoof,				//���M�̂ЂÂ�
	//medkit,					//�~�}�L�b�g
	//bustlingFungus,			//���͂̃L�m�R
	//focusCrystal,			//�œ_�N���X�^��
	//shieldGenerator,		//�V�[���h������
	//backupMagazine,			//�o�b�N�A�b�v�}�K�W��
	//energyDrink,			//�G�i�W�[�h�����N
	//stickyBomb,				//�S�����e
	//stunGranade,			//�X�^���O���l�[�h
	//monsterTooth,			//�����X�^�[�̎�
	//warBanner,				//���
	CommonNum
};
//�A���R�����A�C�e��
enum uncommonItem
{
	//predatoryInstincts,		//�ߐH�{�\
	//bandolier,				//�e���
	//ghorTome,				//�S�[�A�̖{
	//ukulele,				//�E�N����
	//deathMark,				//���̈�
	//warHorn,				//��̊p�J
	//fuelCell,				//�R���d�r
	//oldGuillotine,			//�Â��M���`��
	Dynamite,				//�_�C�i�}�C�g(�E�B�X�v)
	//hopooFeather,			//�z�b�|�̉H��
	//kjaroBand,				//�N�W�����̃o���h
	//runaldBand,				//���i���h�̃o���h
	//harvesterScythe,		//���n�҂̑劙
	infusion,				//�����t
	//waxQuail,				//�X�̃E�Y��
	//atGMissile_Mk1,			//�ΐ�ԃ~�T�C��Mk1
	//oldWarStealthkit,		//��펞�̃X�e���X�L�b�g
	//leechingSeed,			//�z����q
	//chronobauble,			//�N���m�{�[�u��
	roseBuckler,			//�o���̃o�b�N���[
	//redWhip,				//�Ԃ����`
	//leptonDaisy,			//���v�g���f�C�W�[
	//razorwire,				//�n�̓S��
	//berzerkerPauldron,		//�o�[�T�[�J�[�̌��b
	//squidPolyp,				//�C�J�̃|���v
	UncommonNum
};
//���A�A�C�e��
enum rareItem
{
	//alienHead,				//�G�C���A���̓�
	//shatteringJustice,		//���`�̓S��
	//aegis,					//�C�[�W�X
	//brilliantBehemoth,		//�u�����A���g�x�q�[���X
	//sentientMeatHook,		//�s�q�ȃt�b�N
	//cloverOf57Leafs,		//57���t�̃N���[�o�[
	//ceremonialDagger,		//�V���p�̒Z��
	//dioBestFriend,			//�f�B�I�̐e�F
	//H3AD_ST_v2,				//H3AD-ST v2
	//wakeOfVultures,			//�n�Q���V�̖ڊo��
	frostRelic,				//�X�̈╨
	//rejuvenationRack,		//��Ԃ�̊p
	//brainstalks,			//�u���C���X�g�[�N
	//resonanceDisc,			//���̉~��
	//nkuhanaOpinion,			//���N�n���̈ӌ�
	//interstellarDeskPlant,	//�f���ԃf�X�N�v�����g
	//unstableTeslaCoil,		//�s����ȃe�X���R�C��
	//soulboundCatalyst,		//�����̐G�}
	//hardlightAfterburner,	//�n�[�h���C�g�A�t�^�[�o�[�i�[
	//happiestMask,			//�����̉���
	RareNum
};

enum itemJudge
{
	//�A�C�e���̏����󋵂̗v�f
	havingItem,
	//�A�C�e���̏������̗v�f
	havingItemNum,
	//�z���`�p
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
