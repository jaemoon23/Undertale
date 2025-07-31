#pragma once
#include "GameObject.h"
#include "Animator.h"
#include "HitBox.h"

class TemMie :
    public GameObject
{
protected:
   // std::string texId = "Sprites/temmie/spr_temmie_lt_0.png";
    std::string texId = "Sprites/Temmie_sheet.png";
    sf::Sprite temMie;
    Animator animator;

    HitBox hitBox;
public:
    TemMie(const std::string& name);
    ~TemMie() override = default;

    void SetPosition(const sf::Vector2f& pos) override;
    void SetRotation(float rot) override;
    void SetScale(const sf::Vector2f& s) override;
    void SetOrigin(const sf::Vector2f& o) override;
    void SetOrigin(Origins preset) override;

    void Init() override;
    void Release() override;
    void Reset() override;
    void Update(float dt) override;
    void Draw(sf::RenderWindow& window) override;

    const sf::RectangleShape& GetHitBox() const;
};

