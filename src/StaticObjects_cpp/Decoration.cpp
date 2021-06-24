//-------------------------- Include section  ----------------------------
#include "StaticObjects_Headers/Decoration.h"
#include "Macros.h"
#include "Resources.h"


// C-tor
Decoration::Decoration(const sf::Vector2f& pos,
	const char type, const int stageNum)
	: StaticObject({ 0,0 }, pos)
{
	m_shape.setTexture(Resources::instance().
		getStaticObjectTexture(Resources::DECORATIONS));

	if (stageNum == STAGE_ONE)
		setStageOneDecoration(type);
	else if (stageNum == STAGE_TWO)
		setStageTwoDecoration(type);
	else if (stageNum == STAGE_THREE)
		setStageThreeDecoration(type);

	m_shape.setTextureRect(m_rect);
}


//------------------------ setStageOneDecoration -------------------------
// Sets the firsts stage decoration.
//------------------------------------------------------------------------
void Decoration::setStageOneDecoration(const char type)
{
	if (type == STAGE1_TREE) {
		m_shape.setSize({ BLOCK_SIZE, BLOCK_SIZE * 3 });
		m_shape.setPosition(m_shape.getPosition().x,
			m_shape.getPosition().y - BLOCK_SIZE*2.5f );
		m_rect = STAGE1_TREE_INTRECT;
	}
	if (type == STAGE1_LOG) {
		m_shape.setSize({ BLOCK_SIZE*2, BLOCK_SIZE*0.5 });
		m_shape.setPosition(m_shape.getPosition().x,
			m_shape.getPosition().y);
		m_rect = STAGE1_BUSH_INTRECT;
	}
}


//------------------------- setStageTwoDecoration ------------------------
// Sets the seconds stage decoration.
//------------------------------------------------------------------------
void Decoration::setStageTwoDecoration(const char type)
{
	if (type == STAGE2_CRYSTAL1) {
		m_shape.setSize({ BLOCK_SIZE, BLOCK_SIZE});
		m_shape.setPosition(m_shape.getPosition().x - BLOCK_SIZE*0.5f,
			m_shape.getPosition().y - BLOCK_SIZE*0.4f);
		m_rect = STAGE2_CRYSTAL1_INTRECT;
	}
	if (type == STAGE2_CRYSTAL2) {
		m_shape.setSize({ BLOCK_SIZE, BLOCK_SIZE });
		m_shape.setPosition(m_shape.getPosition().x - BLOCK_SIZE * 0.5f,
			m_shape.getPosition().y - BLOCK_SIZE * 0.4f);
		m_rect = STAGE2_CRYSTAL2_INTRECT;
	}
}


//------------------------- setStageThreeDecoration ----------------------
// Sets the thirds stage decoration.
//------------------------------------------------------------------------
void Decoration::setStageThreeDecoration(const char type)
{
	if (type == STAGE3_BUSH) {
		m_shape.setSize({ BLOCK_SIZE, BLOCK_SIZE });
		m_shape.setPosition(m_shape.getPosition().x - BLOCK_SIZE * 0.5f,
			m_shape.getPosition().y - BLOCK_SIZE * 0.4f);
		m_rect = STAGE3_BUSH_INTRECT;
	}
	if (type == STAGE3_TREE) {
		m_shape.setSize({ BLOCK_SIZE*1.5f, BLOCK_SIZE*2 });
		m_shape.setPosition(m_shape.getPosition().x - BLOCK_SIZE * 0.5f,
			m_shape.getPosition().y - BLOCK_SIZE * 1.5f);
		m_rect = STAGE3_TREE_INTRECT;
	}
}