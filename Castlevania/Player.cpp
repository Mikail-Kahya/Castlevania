#include "pch.h"
#include "Player.h"
#include "InCrouchState.h"
#include "InAttackState.h"
#include "Level.h"
#include "Confodore.h"
#include "SpecialAttack.h"
#include "Game.h"
#include "RigidBody.h"
#include "myUtils.h"

Player::Player()
{
	Setup();
}

#pragma region MainFunctions
void Player::Setup()
{
	SetupSpawn();
	SetupSprite();
	Entity::SetState(new IdleState{ this });

	m_Equipment.AddWeapon("left", new Confodore{ "left" });
	m_Equipment.AddWeapon("right", new Confodore{ "right" });
	m_Equipment.AddWeapon("special", new SpecialAttack{ this });

	m_LevelCalculator = LevelCalculator(m_Stats.exp);
	UpdateLevel();
}

void Player::SetupSpawn()
{
	nlohmann::json data{};
	myUtils::ParseJson("./Player/Player.json", data);
	SetupStats(data);
	SetupRigidBody(data);

	data = Game::GetSavedData();

	SetupStats(data);
	SetupRigidBody(data);
}

void Player::Update(float deltaTime)
{
	Entity::Update(deltaTime);
	m_Equipment.Update(this, deltaTime);
	if (Level::RoomChanged())
		m_AllowControl = true;
}

void Player::Draw() const
{
	if (IsFlickering()) return;

	m_Equipment.Draw();
	Entity::Draw();
}
#pragma endregion MainFunctions


#pragma region Create
void Player::SetupStats(const nlohmann::json& data)
{
	if (data.contains("maxHp"))
	{
		const int maxHp{ data["maxHp"] };
		m_MaxStats.hp = maxHp;
		m_DefaultStats.hp = maxHp;
	}

	if (data.contains("maxStam"))
	{
		const float maxStam{ data["maxStam"] };
		m_MaxStats.stamina = maxStam;
		m_DefaultStats.stamina = maxStam;
	}

	if (data.contains("maxMana"))
		m_MaxStats.mana = data["maxMana"];

	if (data.contains("mana"))
		m_Stats.mana = data["mana"];

	if(data.contains("exp"))
		m_Stats.exp = data["exp"];

	if (data.contains("defense"))
		m_Stats.defense = data["defense"];

	m_Stats.hp = m_MaxStats.hp;
	m_Stats.stamina = m_MaxStats.stamina;
}

void Player::SetupRigidBody(const nlohmann::json& data)
{
	if (!data.contains("spawn")) return;
	const Point2f pivot{ data["spawn"]["x"], data["spawn"]["y"] };
	const float width{ 20 }, height{ 70 };
	m_RigidBody = RigidBody{ pivot, width, height, Vector2f() };
}

void Player::SetupSprite()
{
	m_pSprite = dynamic_cast<Avatar*> (GetTextureManager().CreateSprite("player"));
	m_pSprite->SetPivot(m_RigidBody.GetPivot());
}
#pragma endregion Create

void Player::UpdateSprite(float deltaTime)
{
	m_pSprite->SetPivot(m_RigidBody.GetPivot());
	m_pSprite->Update(deltaTime);
}

void Player::UpdateRigidBody(float deltaTime)
{
	const Uint8* pKeyStates{ SDL_GetKeyboardState(nullptr) };
	if (pKeyStates[SDL_SCANCODE_S])
		m_AvoidPlatforms = true;

	m_RigidBody.ResetCollision();
	m_RigidBody.UpdatePhysics(deltaTime);
	m_IsCollidingHard = m_RigidBody.CollideHard();
	if (!m_AvoidPlatforms)
		m_RigidBody.CollideSoft();
	m_AvoidPlatforms = false;
}

void Player::UpdateLevel()
{
	const float damageMultiplier{ 0.5f };
	const int healthMultiplier{ 8 };
	const int staminaMultiplier{ 2 };
	const float defenseMultiplier{ 0.25f };

	const int level{ m_LevelCalculator() };

	m_Stats.damage = int(damageMultiplier * level);
	m_MaxStats.hp = m_DefaultStats.hp + healthMultiplier * level;
	m_MaxStats.stamina = m_DefaultStats.stamina + staminaMultiplier * level;
	m_Stats.defense = int(defenseMultiplier * level);
	Reset();
	GetSoundManager().PlaySound("LevelUp");
}

void Player::GetDefaultData(nlohmann::json& data)
{
	myUtils::ParseJson("./Player/Player.json", data);
}

bool Player::IsDodging() const
{
	return dynamic_cast<Dodge*>(GetState());
}

#pragma region Behaviour

bool Player::Hurt(const Rectf& hitBox, int damage)
{
	if (Entity::Hurt(hitBox, damage))
	{
		SprayBlood(hitBox);
		SpawnDamage(damage - m_Stats.defense, Color4f{ 0.8f, 0.3f, 0.3f, 1 });
		Entity::SetState(new HurtState{ this });
		return true;
	}
	return false;
}
#pragma endregion Behaviour

#pragma region Getters/Setters

bool Player::IsCrouched() const
{
	return dynamic_cast<InCrouchState*>(GetState()) || dynamic_cast<CrouchAttackState*>(GetState());
}

bool Player::IsGrounded() const
{
	return m_RigidBody.IsGrounded();
}

Weapon* Player::GetActiveWeapon() const
{
	return m_Equipment.GetActiveWeapon();
}

const Stats& Player::GetMaxStats() const
{
	return m_MaxStats;
}

const Stats& Player::GetStats() const
{
	return m_Stats;
}

const Vector2f& Player::GetVelocity() const
{
	return m_RigidBody.GetVelocity();
}

void Player::AllowControl(bool allowControl)
{
	m_AllowControl = allowControl;
}

void Player::AddMana(int mana)
{
	m_Stats.mana += mana;
}

void Player::AddExp(int exp)
{
	m_Stats.exp += exp;
	if (m_LevelCalculator(exp))
	{
		UpdateLevel();
		GetSoundManager().PlaySound("ShanoaVictory");
	}
}

void Player::Respawn()
{
	SetupSpawn();
	Entity::SetState(new IdleState{ this });
	Level::Reset();
}

void Player::Reset()
{
	m_Stats.hp = m_MaxStats.hp;
	m_Stats.stamina = m_MaxStats.stamina;
}

void Player::HardReset()
{
	nlohmann::json data{};
	GetDefaultData(data);

	SetupStats(data);
	SetupRigidBody(data);
}
#pragma endregion Getters/Setters