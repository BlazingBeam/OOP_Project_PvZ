#pragma once
class Health {
    protected:
        double health;
        double armor;
    public:
        Health(double health = 3, double armor = 0);
        double getHealth();
        double getArmor();

        void setHealth(double health);
        void setArmor(double armor);

        void takeDamage(double damage);
};

