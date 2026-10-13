#include <iostream>


class Fighter{
private:
    const char* name;
    int health;
    int maxHealth;
    int damage;
public:
    Fighter(const char* name, int health, int damage, int maxHealth = 20) : name(name), health(health), maxHealth(health), damage(damage){
    };
    void TakeDamage(int amount) {
        health -= amount;
        if (health < 0) {
            health = 0;
        }
    }

    void Attack(Fighter& target) const {
        target.TakeDamage(damage);
    }

    bool IsAlive() const {
        return (health > 0);
    }

    void PrintStatus() const {
        std::cout << name << " " << health << " " << "\n";
    }

    void Heal(int amount) {
        if (health + amount > maxHealth) {
            health = maxHealth;
        }
        else {
            health += amount;
        }
    }
};
void PrintFighter(const Fighter& fighter) {
    fighter.PrintStatus();
}


class Game {
private:
    Fighter player;
    Fighter enemies[3];
    Fighter* currentTarget;
    int medkits = 1;
public:
    Game() : player("player", 20, 8), currentTarget(nullptr),enemies{Fighter("Enemy 1", 12, 3), Fighter("Enemy 2", 18, 4), Fighter("Enemy 3", 24, 5)}
    {
    }
    bool TrySelectTarget(int number, Fighter*& outTarget) {
        outTarget = nullptr;
        if (number < 1 || number > 3) {
            return false;
        }
        if (!enemies[number - 1].IsAlive()) {
            return false;
        }
        outTarget = &enemies[number - 1];
        return true;
    }

    bool AllEnemiesDefeated() const {
        for (int i = 0; i < 3; ++i) {
            if (enemies[i].IsAlive()) {
                return false;
            }
        }
        return true;
    }

    void Run() {
        while (true) {
            std::cout << "\nPlayer: ";
            player.PrintStatus();

            for (int i = 0; i < 3; ++i) {
                if (&enemies[i] == currentTarget) {
                    std::cout << "+ ";
                } else {
                    std::cout << "   ";
                }
                enemies[i].PrintStatus();
            }

            int com;
            std::cin >> com;

            if (com == 0) {
                break;
            }

            if (com == 1) {
                int targetNum;
                std::cin >> targetNum;
                if (!TrySelectTarget(targetNum, currentTarget))
                {
                    std::cout << "Nothing \n";
                }
            }
            else if (com == 2) {
                if (currentTarget == nullptr)
                {
                    std::cout << "Nothing \n";
                }
                else
                {
                    Fighter& target = *currentTarget;
                    player.Attack(target);


                    if (!target.IsAlive()) {
                        currentTarget = nullptr;

                        if (AllEnemiesDefeated()) {
                            std::cout << "Win\n";
                            break;
                        }
                    } else {
                        target.Attack(player);
                        if (!player.IsAlive()) {
                            std::cout << "Lose\n";
                            break;
                        }
                    }
                }
            }
            else if (com == 3) {
                if (currentTarget == nullptr)
                {
                    std::cout << "Nothing \n";
                }
                else if (medkits == 0){
                    std::cout << "No kits \n";
                }
                else {
                    player.Heal(8);
                    medkits -= 1;
                    Fighter& target = *currentTarget;
                    target.Attack(player);
                    if (!player.IsAlive()) {
                        std::cout << "Lose\n";
                        break;
                    }
                }
            }
        }
    }
};

int main(){
    Game game;
    game.Run();
    return 0;
};
