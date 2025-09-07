#include "core/engine/Engine.h"
#include "adapters/sdl/SDLGraphics.h"
#include "adapters/sdl/SDLAudio.h"
#include "adapters/sdl/SDLInput.h"
#include "adapters/sdl/SDLTimer.h"
#include <string>

int main(int argc, char* argv[]) {
    std::string gamePath = "./game.json";

    if (argc > 1) {
        gamePath = argv[1];
    }

    Engine engine(
        std::make_unique<SDLGraphics>(),
        std::make_unique<SDLAudio>(),
        std::make_unique<SDLInput>(),
        std::make_unique<SDLTimer>()
    );

    if (!engine.init(800, 600, "NRGameEngine 0.1", gamePath)) {
        return 1;
    }

    engine.run();
    return 0;
}
