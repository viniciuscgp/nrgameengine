#pragma once
#include <string>
#include <vector>

struct Alarm {
    std::string name;         // Ex: "alarm0"
    int counter = 0;          // ticks até ativar
    std::string on_activate;  // nome do script a ser executado
};

class Entity {
public:
    std::string name;             // nome do objeto (ex: "player")

    // eventos → guardam o NOME do script
    std::string on_create;
    std::string on_destroy;
    std::string on_step;
    std::string on_collision;
    std::string on_keypress;
    std::string on_joystick;

    // animação padrão desse objeto
    std::string animation_name;

    // alarms associados à entidade
    std::vector<Alarm> alarms;
};
