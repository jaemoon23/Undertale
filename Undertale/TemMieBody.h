#pragma once
#include "GameObject.h"
#include "Animator.h"

class TemMieBody :  public GameObject
{
protected:
    std::string texId = "Sprites/temmie/spr_5_tembody.png";
    sf::Sprite temMieBody;
    sf::Sprite smiling_face;
    Animator animator;

    bool isSmiling = false;
    bool isIdle = false;

    float timer = 0.f;
public:
    TemMieBody(const std::string& name);
    ~TemMieBody() override = default;

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

    void SetSmiling(bool bo) { isSmiling = bo; }
};

