#pragma once
#include "PlayerWeapon.h"

class Confodore : public PlayerWeapon
{
public:
	Confodore(const std::string& hand);
	virtual ~Confodore() = default;

	Confodore(const Confodore& other) = delete;
	Confodore& operator=(const Confodore& other) = delete;
	Confodore(Confodore&& other) noexcept = delete;
	Confodore& operator=(Confodore&& other) noexcept = delete;

private:
	void Setup(const std::string& hand);
};