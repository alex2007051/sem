#include <iostream>


class Fighter{
private:
    const char* name;
    int health;
    int maxHealth;
    int damage;
public:
    Fighter(const char* name, int health, int damage) : name(name), health(health), maxHealth(health), damage(damage){
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
};
void PrintFighter(const Fighter& fighter) {
    fighter.PrintStatus();
}


class Game {
private:
    Fighter player;
    Fighter enemy;
public:
    Game() : player("player", 30, 8), enemy("enemy", 12, 3){
    };

    void Run() {
        while (true) {
            PrintFighter(player);
            PrintFighter(enemy);
            int com;
            std::cin >> com;
            if (com == 0) {
                break;
            }
            if (com == 1) {
                player.Attack(enemy);
                if (!enemy.IsAlive()) {
                    std::cout <<"Win";
                    break;
                }
                enemy.Attack(player);
                if (!player.IsAlive()) {
                    std::cout << "Lose";
                    break;
                }
            }

        }
    }

};

int main()
{
    Game game;
    game.Run();
    return 0;
};





