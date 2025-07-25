#pragma once
#include <string>

class HealItem {
public:
    HealItem(const std::string& name, int healAmount)
        : name(name), healAmount(healAmount) {}

    std::string GetName() const { return name; }
    int GetHealAmount() const { return healAmount; }

private:
    std::string name;
    int healAmount;
};