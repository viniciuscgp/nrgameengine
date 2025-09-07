# NRGameEngine

## O que é
* O NRGameEngine (NRGE) será uma engine de criação de jogos simples (2D).

## Componentes

* Engine e disposições gerais:

    * Feita em **C++ e SDL**. Ela é o runner do jogo. Ela vai carregar um JSON que representa 
      o jogo em si e vai executar.

    * Cada recurso carregado vai ser representado por um **nome único (string)** dentro da 
      estrutura e esse nome poderá ser referenciado na linguagem de script e em 
      outras classes/estruturas.  

    * Se algum campo de evento (ex: `on_step`) estiver vazio, significa que nenhum script está associado.  

    * Scripts são escritos em **Lua** e recebem acesso a variáveis da instância (`self.x`, `self.y`, etc) 
      e funções expostas pela engine (`print`, `quit`, `mouse_button_pressed`, `sound_play`, `scene_goto_next`).  

* Editor (GUI):
    * GUI para a criação desse JSON de uma forma simples para o usuário.  
        - A GUI será capaz de definir as informações dos objetos descritos 
          abaixo na forma de JSON.  
    * A GUI vai possibilitar posicionar `Instance` dentro de `Scene`, que serão
          as instâncias definidas via editor. Durante o jogo poderemos criar 
          novas instâncias via scripts.  
    * A GUI vai ser da seguinte forma: 
        - Do lado esquerdo teremos uma lista de botões; 
          quando esse botão for pressionado, ele abre logo abaixo dele a lista de
          recurso que ele representa, empurrando os outros botões para baixo.  
        - A parte central da tela será onde poderemos  posicionar objetos caso 
          estejamos editando uma `Scene`.  
        - A parte direita será uma janela global de propriedades da instância selecionada
          na cena ou algum outro objeto que tenha propriedades.  
        - A parte superior terá um menu, para salvar, about e coisas do tipo, e terá
          uma barra de ferramentas com botões para executar o jogo, exportar etc.  
        - A parte inferior será um rodapé com informações diversas.  
        - Logo acima do rodapé haverá um **console de debug** que exibirá logs, prints e erros Lua.  

 
## Elementos internos da engine

* **Image** – define uma imagem
    - name          -> nome da imagem (usado como chave)  
    - file_name     -> arquivo da imagem  
    - width         -> largura da imagem  
    - height        -> altura da imagem  
    No JSON ficará dentro do array `images`.  

* **Animation** – estrutura que define uma lista de imagens que juntas formam uma animação
    - name           -> nome da animação  
    - frames         -> lista de nomes de `Image`  

* **Sound** – estrutura que define um som
    - name          -> nome do som  
    - file_name     -> arquivo de áudio  
    - volume        -> volume do som  

* **Alarm** – define um alarme
    - name          -> nome do alarme  
    - counter       -> >0 decresce até 0, quando chega a 0 executa o script e volta para -1  
    - on_activate   -> nome do script a ser executado quando o counter chega a zero  

* **Entity** – define um objeto do jogo  
    - name             -> nome do objeto  
    - on_create        -> nome do script executado ao criar  
    - on_destroy       -> nome do script executado ao ser destruído  
    - on_step          -> nome do script executado a cada frame  
    - on_collision     -> script executado ao ocorrer uma colisão (recebe duas instâncias)  
    - on_keypress      -> script executado quando uma tecla é pressionada  
    - on_joystick      -> script executado quando um botão do joystick é pressionado/movido  
    - animation_name   -> nome da animação associada  
    - alarms           -> lista de `Alarm`  

    * Methods:
        - **doDestroy()** -> chamado imediatamente antes da remoção da instância, dispara `on_destroy`.  
        - **doCreate()**  -> chamado na criação de cada instância, dispara `on_create`.  
        - **doStep()**    -> chamado pela engine em cada frame: atualiza posição/forças/atrito e dispara `on_step`.  

* **Instance** – uma instância de uma `Entity`.  
    - depth         -> profundidade: menor valor = renderizado por último (fica na frente)  
    - x             -> posição x (float)  
    - y             -> posição y (float)  
    - force_x       -> força adicionada ao x a cada ciclo (float)  
    - force_y       -> força adicionada ao y a cada ciclo (float)  
    - friction      -> diminui das forças x e y (float)  
    - entity_name   -> nome da `Entity` associada  
    - image_index   -> índice do frame inicial dentro da animação  

* **Scene** – armazena instâncias  
    - name      -> nome da cena  
    - instances -> lista de `Instance`  

* **Script** – estrutura que armazena um script Lua  
    - name          -> nome do script  
    - code          -> texto do script  

* **Game** – armazena os dados do jogo  
    - name          -> nome do jogo  
    - description   -> título (usado como nome da janela)  
    - version       -> versão do jogo  
    - width         -> largura da tela  
    - height        -> altura da tela  
    - type          -> tipo do jogo  

    - images        -> lista de `Image`  
    - sounds        -> lista de `Sound`  
    - scenes        -> lista de `Scene`  
    - scripts       -> lista de `Script`  
    - entities      -> lista de `Entity`  
    - animations    -> lista de `Animation`  

    * Methods disponíveis via script:
        - `print(msg)`  
        - `sound_play("nome")` -> executa som pelo nome  
        - `quit()` -> finaliza o jogo  
        - `instance_create(x, y, "entity_name")` -> cria uma instância  
        - `instance_remove("entity_name")` -> remove uma instância  
        - `scene_goto_next()` -> remove as instâncias atuais, carrega a próxima cena  
        - `mouse_button_pressed([button])` -> true/false se botão do mouse está pressionado  

# Estrutura do JSON que define o jogo

{
  "game": {
    "name": "test",
    "description": "",
    "version": "1.0",
    "width": 800,
    "height": 600,
    "type": "adventure",

    "images": [
      {
        "name": "game_title",
        "file_name": "game_title.png",
        "width": 300,
        "height": 128
      },
      {
        "name": "ship_1",
        "file_name": "ship_1.png",
        "width": 128,
        "height": 128
      },
      {
        "name": "ship_2",
        "file_name": "ship_2.png",
        "width": 128,
        "height": 128
      }
    ],

    "animations": [
      {
        "name": "title",
        "frames": ["game_title"]
      },
      {
        "name": "ship",
        "frames": ["ship_1", "ship_2"]
      }
    ],

    "sounds": [
      {
        "name": "explosion",
        "file_name": "explosion.wav",
        "volume": 100
      },
      {
        "name": "tiro",
        "file_name": "laser.wav",
        "volume": 50
      }
    ],

    "scripts": [
      {
        "name": "initialize",
        "code": "x = 320; y = 100; sound_play(\"explosion\")"
      },
      {
        "name": "move_x",
        "code": "x = x + 1"
      },
      {
        "name": "handle_menu_keys",
        "code": "if (key == KEY_ESC) quit(); else scene_goto_next()"
      },
      {
        "name": "increase_y",
        "code": "y = y + 1"
      }
    ],

    "entities": [
      {
        "name": "title",
        "on_create": "",
        "on_destroy": "",
        "on_step": "move_x",
        "on_collision": "",
        "on_keypress": "handle_menu_keys",
        "on_joystick": "",
        "animation_name": "title",
        "alarms": [
          {
            "name": "alarm0",
            "counter": 1000,
            "on_activate": "increase_y"
          }
        ]
      },
      {
        "name": "nave",
        "on_create": "initialize",
        "on_destroy": "",
        "on_step": "move_x",
        "on_collision": "",
        "on_keypress": "",
        "on_joystick": "",
        "animation_name": "ship",
        "alarms": []
      }
    ],

    "scenes": [
      {
        "name": "menu",
        "instances": [
          {
            "entity_name": "title",
            "depth": 0,
            "x": 0,
            "y": 0,
            "force_x": 0,
            "force_y": 0,
            "friction": 0,
            "image_index": 0
          }
        ]
      },
      {
        "name": "play",
        "instances": [
          {
            "entity_name": "nave",
            "depth": 100,
            "x": 0,
            "y": 0,
            "force_x": 0,
            "force_y": 0,
            "friction": 0,
            "image_index": 0
          },
          {
            "entity_name": "nave",
            "depth": 100,
            "x": 100,
            "y": 50,
            "force_x": 0,
            "force_y": 0,
            "friction": 0,
            "image_index": 1
          }
        ]
      }
    ]
  }
}

Estrutura de pastas com interfaces:
-----------------------------------

NRGameEngine/
 ├── CMakeLists.txt              # Configuração de build (CMake)
 ├── README.md                   # Documentação principal do projeto
 │
 ├── src/
 │   ├── core/
 │   │   ├── engine/             # Motor de execução
 │   │   │   ├── Engine.h
 │   │   │   ├── Engine.cpp
 │   │   │   ├── GameLoader.h
 │   │   │   ├── GameLoader.cpp
 │   │   │   ├── ScriptManager.h
 │   │   │   ├── ScriptManager.cpp
 │   │   │   ├── LuaApi.h
 │   │   │   ├── LuaApi.cpp
 │   │   │   ├── ResourceManager.h
 │   │   │   └── ResourceManager.cpp
 │   │   │
 │   │   ├── model/              # Estruturas de dados do jogo
 │   │   │   ├── Game.h
 │   │   │   ├── Scene.h
 │   │   │   ├── Entity.h
 │   │   │   ├── Instance.h
 │   │   │   ├── Alarm.h
 │   │   │   └── Collision.h
 │   │   │
 │   │   ├── resources/          # Recursos carregáveis
 │   │   │   ├── Image.h
 │   │   │   ├── Animation.h
 │   │   │   ├── Sound.h
 │   │   │   └── Script.h
 │   │   │
 │   │   └── utils/              # Utilitários auxiliares
 │   │       ├── Logger.h
 │   │       └── Logger.cpp
 │   │
 │   ├── ports/                  # Interfaces (Ports)
 │   │   ├── IGraphics.h
 │   │   ├── IAudio.h
 │   │   ├── IInput.h
 │   │   ├── ITimer.h
 │   │   └── KeyCode.h
 │   │
 │   ├── adapters/               # Implementações (Adapters)
 │   │   ├── sdl/
 │   │   │   ├── SDLGraphics.h
 │   │   │   ├── SDLGraphics.cpp
 │   │   │   ├── SDLSurface.h
 │   │   │   ├── SDLSurface.cpp
 │   │   │   ├── SDLAudio.h
 │   │   │   ├── SDLAudio.cpp
 │   │   │   ├── SDLInput.h
 │   │   │   ├── SDLInput.cpp
 │   │   │   ├── SDLTimer.h
 │   │   │   └── SDLTimer.cpp
 │   │   │
 │   │   └── (outros backends futuramente, ex: sfml/, glfw/, etc.)
 │   │
 │   ├── assets/                 # Arquivos de jogo de exemplo
 │   │   ├── game.json
 │   │   ├── hello.png
 │   │   ├── explosion.wav
 │   │   └── music.ogg
 │   │
 │   └── main.cpp                # Ponto de entrada
 │
 └── tests/                      # (futuro) testes unitários e de integração
     └── CMakeLists.txt

Pacotes pro adapter com SDL:
----------------------------

sudo apt update
sudo apt install build-essential cmake pkg-config \
                 libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev \
                 liblua5.3-dev

sudo apt install nlohmann-json3-dev

Compilacao com cmake:
---------------------
cd build
cmake ..
make


-------------------------------------------
|                 Prompt
-------------------------------------------
Quero que você memorize e use como referência o seguinte projeto chamado **NRGameEngine (NRGE)**:

# NRGameEngine (NRGE)

## Objetivo
Uma engine simples para jogos 2D, composta por:
- Runner (C++ + SDL + Lua): executa o jogo descrito em JSON.
- Editor (GUI): cria o JSON visualmente.

## Arquitetura
- Engine escrita em C++ com SDL2.
- Scripts em **Lua**, integrados com a engine via `ScriptManager` e `LuaApi`.
- Recursos identificados por **nome (string)**, não por índice.
- Se um evento não tiver script, o campo fica vazio.
- Instâncias expõem `self.x`, `self.y`, `self.force_x`, etc. para os scripts.
- Funções expostas ao Lua: `print`, `quit`, `sound_play`, `mouse_button_pressed`, `scene_goto_next`, `instance_create`, `instance_remove`.

## Estruturas internas
- **Image**: `{ name, file_name, width, height }`
- **Animation**: `{ name, frames: [image_names] }`
- **Sound**: `{ name, file_name, volume }`
- **Script**: `{ name, code }`
- **Alarm**: `{ name, counter, on_activate }`
- **Entity**: `{ name, on_create, on_destroy, on_step, on_collision, on_keypress, on_joystick, animation_name, alarms[] }`
- **Instance**: `{ entity_name, x, y, depth, force_x, force_y, friction, image_index }`
- **Scene**: `{ name, instances[] }`
- **Game**: `{ name, description, version, width, height, type, images, animations, sounds, scripts, entities, scenes }`

## Engine
- `Engine` inicializa gráficos, carrega JSON, cria `ScriptManager`, chama `scene->triggerOnCreate`.
- `GameLoader` carrega o JSON, cria mapas (`unordered_map`) para `images`, `animations`, `sounds`, `scripts`, `entities`.
- `Game` guarda o estado atual e executa `step()` chamando `scene->stepAll`.
- `Scene` executa `stepAll` para todas as instâncias e dispara scripts `on_step`.
- `Instance::step` aplica força, atrito e atualização de posição.
- `ScriptManager` cria contexto Lua, expõe API com funções C++ → Lua, roda scripts de instâncias com sincronização de variáveis.
- Funções Lua com `userdata` são registradas usando upvalues (ex: `mouse_button_pressed` usa `lua_upvalueindex(1)` para acessar `IInput*`).

## Editor (planejado)
- Layout: esquerda (lista de recursos), centro (edição da cena), direita (propriedades), topo (menu e toolbar), rodapé (status) e console de debug acima do rodapé.
- Exporta JSON que é consumido pelo runner.

## Sistema de colisão
- Bounding box (retângulos).

## Exportação
- Runner renomeado com nome do jogo + JSON + recursos.

## Estrutura de pastas

NRGameEngine/
├── CMakeLists.txt
├── README.md
├── src/
│ ├── core/
│ │ ├── engine/ (Engine.cpp/h, GameLoader, ScriptManager, LuaApi, ResourceManager)
│ │ ├── model/ (Game, Scene, Entity, Instance, Alarm, Collision)
│ │ ├── resources/ (Image, Animation, Sound, Script)
│ │ └── utils/ (Logger)
│ ├── ports/ (IGraphics, IAudio, IInput, ITimer, KeyCode)
│ ├── adapters/ (sdl/: SDLGraphics, SDLSurface, SDLAudio, SDLInput, SDLTimer)
│ ├── assets/ (game.json, imagens, sons)
│ └── main.cpp
└── tests/


## Dependências
- SDL2 (`libsdl2-dev`, `libsdl2-image-dev`, `libsdl2-mixer-dev`, `libsdl2-ttf-dev`)
- Lua (`liblua5.3-dev`)
- JSON (`nlohmann-json3-dev`)

## Exemplo mínimo de JSON
```json
{
  "game": {
    "name": "test",
    "description": "My Game",
    "version": "1.0",
    "width": 800,
    "height": 600,
    "type": "adventure",
    "images": [
      { "name": "square", "file_name": "square.png", "width": 50, "height": 50 }
    ],
    "animations": [
      { "name": "square_anim", "frames": ["square"] }
    ],
    "sounds": [],
    "scripts": [
      { "name": "on_click", "code": "if mouse_button_pressed() then self.x = self.x + 5 end" }
    ],
    "entities": [
      { "name": "square_entity", "on_create": "", "on_destroy": "", "on_step": "on_click", "on_collision": "", "on_keypress": "", "on_joystick": "", "animation_name": "square_anim", "alarms": [] }
    ],
    "scenes": [
      { "name": "main", "instances": [ { "entity_name": "square_entity", "x": 400, "y": 300, "depth": 0, "force_x": 0, "force_y": 0, "friction": 0, "image_index": 0 } ] }
    ]
  }
}


