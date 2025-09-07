# NRGameEngine (NRGE)

## 🎮 O que é
O **NRGameEngine (NRGE)** é uma engine simples para criação de jogos **2D**.  
Ela é composta por duas partes principais:
- **Runner (engine)**: escrito em **C++ + SDL**, responsável por executar os jogos.
- **Editor (GUI)**: interface visual para criação dos jogos, que gera o **JSON** com todos os recursos.

---

## 🧩 Componentes

### Engine
- Desenvolvida em **C++ + SDL**.
- Executa jogos definidos em um arquivo **JSON**.
- Cada recurso é identificado por um **nome único** (`string`), não por índices.
- Scripts escritos em **Lua**.
- Exposição de funções C++ para Lua via **API customizada** (`ScriptManager` + `LuaAPI`).

### Editor (GUI)
- Interface para criar e manipular jogos sem editar JSON manualmente.
- Layout planejado:
  - **Esquerda** → lista de recursos com botões expansíveis.
  - **Centro** → área de edição da `Scene` (posicionamento de instâncias).
  - **Direita** → painel de propriedades do item selecionado.
  - **Topo** → menu e barra de ferramentas (Salvar, Exportar, Executar, About...).
  - **Rodapé** → status geral.
  - **Acima do rodapé** → **console de debug** (logs, prints de scripts, erros).

---

## 🏗️ Estruturas principais

### Recursos básicos
- **Image**
  - `name`
  - `file_name`
  - `width`, `height`
- **Animation**
  - `name`
  - `frames`: lista de nomes de imagens
  - `speed` (opcional)
- **Sound**
  - `name`
  - `file_name`
  - `volume`
- **Script**
  - `name`
  - `code` (código em Lua)

### Controle
- **Alarm**
  - `name`
  - `counter`
  - `on_activate` (script disparado quando chega a `0`)

### Objetos e Instâncias
- **Entity**
  - `name`
  - Eventos:  
    - `on_create`  
    - `on_destroy`  
    - `on_step`  
    - `on_collision`  
    - `on_keypress`  
    - `on_joystick`  
  - `animation_name`
  - `alarms`
- **Instance**
  - `entity_name`
  - `x`, `y`
  - `depth`
  - `force_x`, `force_y`
  - `friction`
  - `image_index`

### Cena e Jogo
- **Scene**
  - `name`
  - `instances`: lista de instâncias
- **Game**
  - Metadados: `name`, `description` (título da janela), `version`, `author`, `width`, `height`, `type`.
  - Recursos: mapas (`images`, `animations`, `sounds`, `scripts`, `entities`).
  - `scenes`: lista de cenas.
  - `start_scene`: cena inicial.

---

## ⚙️ Métodos disponíveis em scripts (Lua)

Expostos pela **engine** via `ScriptManager` + `LuaAPI`:

- `print(msg)` → loga no console.
- `quit()` → encerra o jogo.
- `mouse_button_pressed([button])` → retorna `true` se botão do mouse estiver pressionado (`1=esquerdo`, `2=meio`, `3=direito`).
- `scene_goto_next()` → troca para a próxima cena.
- `sound_play("nome")` → reproduz um som.
- (futuro) `instance_create`, `instance_remove`.

---

## 🔲 Sistema de colisão
- Usa **bounding box** (retângulos delimitadores).  

---

## 📦 Exportação
O jogo final é distribuído como:  
- O **runner** (engine) renomeado com o nome do jogo.  
- O arquivo **JSON** que descreve o jogo.  
- Recursos apontados no JSON (imagens, sons, etc.).  

---

## 🐞 Debug
- O editor possui um **console de debug**:
  - Logs da execução.
  - Saídas de `print` dos scripts Lua.
  - Mensagens de erro.

---

## 🚀 Status
📌 Projeto em fase inicial, já com:  
- Estrutura em **C++ + SDL**.  
- Integração Lua funcionando (`ScriptManager`, `LuaAPI`).  
- Registro de funções básicas (`print`, `quit`, `mouse_button_pressed`, `sound_play`, `scene_goto_next`).  
- JSON reorganizado para usar **nomes como chaves** em vez de índices.  

Próximos passos:  
- Expansão da API Lua (`instance_create`, `instance_remove`).  
- Sistema de colisão.  
- Prototipagem do editor GUI.  

---

## 📝 Exemplo mínimo de JSON ("Hello World")

```json
{
  "game": {
    "name": "HelloWorld",
    "description": "Exemplo básico",
    "version": "1.0",
    "width": 800,
    "height": 600,

    "images": [
      { "name": "square", "file_name": "square.png", "width": 64, "height": 64 }
    ],

    "animations": [
      { "name": "square_anim", "frames": ["square"] }
    ],

    "sounds": [],

    "scripts": [
      { "name": "move_right", "code": "if mouse_button_pressed() then self.x = self.x + 5 end" }
    ],

    "entities": [
      {
        "name": "square_entity",
        "on_create": "",
        "on_destroy": "",
        "on_step": "move_right",
        "on_collision": "",
        "on_keypress": "",
        "on_joystick": "",
        "animation_name": "square_anim",
        "alarms": []
      }
    ],

    "scenes": [
      {
        "name": "main",
        "instances": [
          { "entity_name": "square_entity", "x": 368, "y": 268, "depth": 0, "force_x": 0, "force_y": 0, "friction": 0, "image_index": 0 }
        ]
      }
    ],

    "start_scene": 0
  }
}
