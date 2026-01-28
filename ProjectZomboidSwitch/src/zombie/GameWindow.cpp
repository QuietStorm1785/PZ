#include <iostream>
#ifdef __SWITCH__
#include <switch.h>
#endif
// Integrate SDL2 input system
#include "zombie/input/Mouse.h"
#include "zombie/input/GameKeyboard.h"
#include "zombie/input/JoypadManager.h"
#include <SDL2/SDL.h>

// Global SDL2 input instances
Mouse g_mouse;
GameKeyboard g_keyboard;
JoypadManager g_joypads;

void GameWindow::MainLoop() {
    mainThreadInit();
    enter();

#ifdef __SWITCH__
    PadState pad;
    padInitializeDefault(&pad);
    std::cout << "[Switch] Entering main game loop. Press + to exit." << std::endl;
    while (appletMainLoop()) {
        padUpdate(&pad);
        u64 kDown = padGetButtonsDown(&pad);
        if (kDown & HidNpadButton_Plus) {
            break;
        }
        // SDL2 input update
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            g_keyboard.handleEvent(event);
            g_joypads.handleEvent(event);
        }
        g_mouse.update();
        g_keyboard.update();
        g_joypads.update();
        frameStep();
        logic();
        consoleUpdate(NULL);
    }
#else
    std::cout << "[Desktop] Entering main game loop. Press Ctrl+C to exit." << std::endl;
    while (true) {
        // SDL2 input update
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            g_keyboard.handleEvent(event);
            g_joypads.handleEvent(event);
        }
        g_mouse.update();
        g_keyboard.update();
        g_joypads.update();
        frameStep();
        logic();
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
#endif
    exit();
    std::cout << "Exiting main game loop." << std::endl;
}
#include <string>
#include "zombie/GameWindow.h"

namespace zombie {
int GameWindow::StringUTF::encode(const std::string& var1) {
    // Simple UTF-8 encoding: return length in bytes
    return static_cast<int>(var1.size());
}

std::string GameWindow::StringUTF::decode(int var1) {
    // Not enough context for a real decode; return empty string
    return std::string();
}

void GameWindow::StringUTF::save(ByteBuffer var1, const std::string& var2) {
    // Save string as UTF-8 bytes to ByteBuffer
    // (Assume ByteBuffer has put and position methods)
    int len = static_cast<int>(var2.size());
    var1.putInt(len);
    for (char c : var2) {
        var1.put(static_cast<uint8_t>(c));
    }
}

std::string GameWindow::StringUTF::load(ByteBuffer var1) {
    // Load string from ByteBuffer (UTF-8)
    int len = var1.getInt();
    std::string result;
    result.reserve(len);
    for (int i = 0; i < len; ++i) {
        result.push_back(static_cast<char>(var1.get()));
    }
    return result;
}


bool GameWindow::OSValidator::isWindows() {
    #ifdef _WIN32
    return true;
    #else
    return false;
    #endif
}

bool GameWindow::OSValidator::isMac() {
    #ifdef __APPLE__
    return true;
    #else
    return false;
    #endif
}

bool GameWindow::OSValidator::isUnix() {
    #if defined(__unix__) || defined(__unix) || defined(unix) || defined(__linux__)
    return true;
    #else
    return false;
    #endif
}

bool GameWindow::OSValidator::isSolaris() {
    #ifdef __sun
    return true;
    #else
    return false;
    #endif
}


void GameWindow::initShared() {
    // Ported from Java/C++ legacy
    std::string cacheDir = ZomboidFileSystem::instance.getCacheDir() + "/";
    std::filesystem::create_directories(cacheDir);
    TexturePackPage::bIgnoreWorldItemTextures = true;
    int var2 = 2;
    LoadTexturePack("UI", var2);
    LoadTexturePack("UI2", var2);
    LoadTexturePack("IconsMoveables", var2);
    LoadTexturePack("RadioIcons", var2);
    LoadTexturePack("ApComUI", var2);
    LoadTexturePack("Mechanics", var2);
    LoadTexturePack("WeatherFx", var2);
    setTexturePackLookup();
    PerkFactory::init();
    CustomPerks::instance.init();
    DoLoadingText(Translator::getText("UI_Loading_Scripts"));
    ScriptManager::instance.Load();
    DoLoadingText(Translator::getText("UI_Loading_Clothing"));
    ClothingDecals::init();
    BeardStyles::init();
    HairStyles::init();
    OutfitManager::init();
    DoLoadingText("");
    TraitFactory::init();
    ProfessionFactory::init();
    Rand::init();
    TexturePackPage::bIgnoreWorldItemTextures = false;
    TextureID::bUseCompression = TextureID::bUseCompressionOption;
    MuzzleFlash::init();
    Mouse::initCustomCursor();
    if (!Core::bDebug) {
        states.States.push_back(new TISLogoState());
    }
    states.States.push_back(new TermsOfServiceState());
    states.States.push_back(new MainScreenState());
    if (!Core::bDebug) {
        states.LoopToState = 1;
    }
    GameInput::initControllers();
    if (Core::getInstance().isDefaultOptions() && SteamUtils::isSteamModeEnabled() && SteamUtils::isRunningOnSteamDeck()) {
        Core::getInstance().setOptionActiveController(0, true);
    }
    int controllerCount = GameInput::getControllerCount();
    for (int i = 0; i < controllerCount; ++i) {
        Controller* ctrl = GameInput::getController(i);
        if (ctrl) {
            int axisCount = ctrl->getAxisCount();
            for (int j = 0; j < axisCount; ++j) {
                // Log axis names if needed
            }
            int buttonCount = ctrl->getButtonCount();
            for (int j = 0; j < buttonCount; ++j) {
                // Log button names if needed
            }
        }
    }
}

void GameWindow::logic() {
    // Ported from Java GameWindow.logic()
    // 1. Update network client if enabled
    if (GameClient::bClient) {
        try {
            GameClient::instance.update();
        } catch (const std::exception& ex) {
            ExceptionLogger::logException(ex);
        }
    }

    // 2. Update single player server/client
    try {
        SinglePlayerServer::update();
        SinglePlayerClient::update();
    } catch (const std::exception& ex) {
        std::cerr << "[GameWindow::logic] Exception in SinglePlayerServer/Client update: " << ex.what() << std::endl;
        ExceptionLogger::logException(ex);
    }

    // 3. Steam loop
    // Java: SteamUtils.runLoop();
    try {
        SteamUtils::runLoop();
    } catch (const std::exception& ex) {
        std::cerr << "[GameWindow::logic] Exception in SteamUtils::runLoop: " << ex.what() << std::endl;
    }

    // 4. Input updates
    try {
        Mouse::update();
    } catch (const std::exception& ex) {
        std::cerr << "[GameWindow::logic] Exception in Mouse::update: " << ex.what() << std::endl;
    }
    try {
        GameKeyboard::update();
    } catch (const std::exception& ex) {
        std::cerr << "[GameWindow::logic] Exception in GameKeyboard::update: " << ex.what() << std::endl;
    }
    try {
        GameInput::updateGameThread();
    } catch (const std::exception& ex) {
        std::cerr << "[GameWindow::logic] Exception in GameInput::updateGameThread: " << ex.what() << std::endl;
    }

    // 5. CoopMaster update
    try {
        if (CoopMaster::instance != nullptr) {
            CoopMaster::instance->update();
        }
    } catch (const std::exception& ex) {
        std::cerr << "[GameWindow::logic] Exception in CoopMaster::update: " << ex.what() << std::endl;
    }

    // 6. IsoPlayer/IsoCamera update
    try {
        if (IsoPlayer::players[0] != nullptr) {
            IsoPlayer::setInstance(IsoPlayer::players[0]);
            IsoCamera::CamCharacter = IsoPlayer::players[0];
        }
    } catch (const std::exception& ex) {
        std::cerr << "[GameWindow::logic] Exception in IsoPlayer/IsoCamera update: " << ex.what() << std::endl;
    }

    // 7. UI update
    try {
        UIManager::update();
    } catch (const std::exception& ex) {
        std::cerr << "[GameWindow::logic] Exception in UIManager::update: " << ex.what() << std::endl;
    }

    // 8. Voice update
    try {
        if (VoiceManager::instance != nullptr) {
            VoiceManager::instance->update();
        }
    } catch (const std::exception& ex) {
        std::cerr << "[GameWindow::logic] Exception in VoiceManager::update: " << ex.what() << std::endl;
    }

    // 9. LineDrawer clear
    try {
        LineDrawer::clear();
    } catch (const std::exception& ex) {
        std::cerr << "[GameWindow::logic] Exception in LineDrawer::clear: " << ex.what() << std::endl;
    }

    // 10. Joypad activation event

    try {
        if (JoypadManager::isAPressed(-1)) {
            for (int i = 0; i < JoypadManager::JoypadList.size(); ++i) {
                Joypad* joypad = JoypadManager::JoypadList[i];
                if (joypad && joypad->isAPressed()) {
                    if (ActivatedJoyPad == nullptr) {
                        ActivatedJoyPad = joypad;
                    }
                    if (IsoPlayer::getInstance() != nullptr) {
                        LuaEventManager::triggerEvent("OnJoypadActivate", joypad->getID());
                    } else {
                        LuaEventManager::triggerEvent("OnJoypadActivateUI", joypad->getID());
                    }
                    break;
                }
            }
        }
    } catch (const std::exception& ex) {
        std::cerr << "[GameWindow::logic] Exception in JoypadManager/LuaEventManager: " << ex.what() << std::endl;
    }

    // 11. Sound update
    try {
        if (SoundManager::instance != nullptr) {
            SoundManager::instance->Update();
        }
    } catch (const std::exception& ex) {
        std::cerr << "[GameWindow::logic] Exception in SoundManager::Update: " << ex.what() << std::endl;
    }

    // 12. Game pause logic
    bool doGameLogic = true;
    try {
        if (GameTime::isGamePaused()) doGameLogic = false;
    } catch (const std::exception& ex) {
        std::cerr << "[GameWindow::logic] Exception in GameTime::isGamePaused: " << ex.what() << std::endl;
    }

    try {
        MapCollisionData::updateGameState();
    } catch (const std::exception& ex) {
        std::cerr << "[GameWindow::logic] Exception in MapCollisionData::updateGameState: " << ex.what() << std::endl;
    }
    // TODO: Mouse::setCursorVisible(true);
        Mouse::setCursorVisible(true);
    if (doGameLogic) {
        states.update();
    } else {
        IsoCamera::updateAll();
        if (IngameState::instance != nullptr && (states.current == IngameState::instance || std::find(states.States.begin(), states.States.end(), IngameState::instance) != states.States.end())) {
            LuaEventManager::triggerEvent("OnTickEvenPaused", 0.0);
        }
    }

    try {
        UIManager::resize();
    } catch (const std::exception& ex) {
        std::cerr << "[GameWindow::logic] Exception in UIManager::resize: " << ex.what() << std::endl;
    }
    // File system async
    try {
        fileSystem.updateAsyncTransactions();
    } catch (const std::exception& ex) {
        std::cerr << "[GameWindow::logic] Exception in fileSystem::updateAsyncTransactions: " << ex.what() << std::endl;
    }

    // Screenshot key
    try {
        int screenshotKey = Core::getInstance().getKey("Take screenshot");
        if (GameKeyboard::isKeyPressed(screenshotKey)) {
            Core::getInstance().TakeFullScreenshot(nullptr);
        }
    } catch (const std::exception& ex) {
        std::cerr << "[GameWindow::logic] Exception in screenshot key logic: " << ex.what() << std::endl;
    }
}

void GameWindow::render() {
    // Java: IsoCamera.frameState.frameCount++;
    //        renderInternal();
    try {
        IsoCamera::frameState.frameCount++;
    } catch (const std::exception& ex) {
        std::cerr << "[GameWindow::render] Exception incrementing frameCount: " << ex.what() << std::endl;
    }
    try {
        renderInternal();
    } catch (const std::exception& ex) {
        std::cerr << "[GameWindow::render] Exception in renderInternal: " << ex.what() << std::endl;
    }
}

void GameWindow::renderInternal() {
    // Ported from Java GameWindow.renderInternal()
    // if (!PerformanceSettings.LightingThread && LightingJNI.init && !LightingJNI.WaitingForMain()) {
    //     LightingJNI.DoLightingUpdateNew(System.nanoTime());
    // }
    try {
        if (!zombie::core::PerformanceSettings::LightingThread &&
            zombie::iso::LightingJNI::init &&
            !zombie::iso::LightingJNI::WaitingForMain()) {
            // Use high-resolution clock for timing
            auto now = std::chrono::high_resolution_clock::now();
            auto nanos = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()).count();
            zombie::iso::LightingJNI::DoLightingUpdateNew(nanos);
        }
    } catch (const std::exception& ex) {
        std::cerr << "[GameWindow::renderInternal] Exception in LightingJNI update: " << ex.what() << std::endl;
    }

    try {
        zombie::iso::IsoObjectPicker::getInstance().StartRender();
    } catch (const std::exception& ex) {
        std::cerr << "[GameWindow::renderInternal] Exception in IsoObjectPicker::StartRender: " << ex.what() << std::endl;
    }

    try {
        // s_performance.statesRender.invokeAndMeasure(states, GameStateMachine::render);
        // If s_performance is available, wrap with timing; otherwise, call directly
        zombie::gameStates::GameStateMachine::render();
    } catch (const std::exception& ex) {
        std::cerr << "[GameWindow::renderInternal] Exception in GameStateMachine::render: " << ex.what() << std::endl;
    }
}

void GameWindow::InitDisplay() {
    // SDL2-based display initialization
    SDL_SetWindowTitle(SDL_GL_GetCurrentWindow(), "Project Zomboid");
    // Load options, set fullscreen, set resolution, etc. (platform-specific)
    // This is a placeholder; actual implementation should match engine config
    // For now, just print info
    std::cout << "[InitDisplay] Display initialized (SDL2 stub)" << std::endl;
}

void GameWindow::InitGameThread() {
    // Set up main game thread and exception handlers
    // In C++, use std::thread and set up try/catch in main loop
    // For now, just call mainThread() directly
    mainThread();
}

void GameWindow::uncaughtExceptionMainThread(Thread var0, std::exception var1) {
    // Log and handle uncaught exceptions in main thread
    try {
        uncaughtException(var0, var1);
    } catch (...) {
        onGameThreadExited();
    }
}

void GameWindow::uncaughtGlobalException(Thread var0, std::exception var1) {
    // Log and handle uncaught exceptions in global threads
    uncaughtException(var0, var1);
}

void GameWindow::uncaughtException(Thread var0, std::exception var1) {
    // Log and handle uncaught exceptions
    std::cerr << "[uncaughtException] Exception in thread: " << var0.get_id() << std::endl;
    try {
        throw;
    } catch (const std::exception& ex) {
        ExceptionLogger::logException(ex);
    } catch (...) {
        std::cerr << "[uncaughtException] Unknown exception" << std::endl;
    }
}

void GameWindow::mainThread() {
    // TODO: Implement mainThread
}

void GameWindow::mainThreadInit() {
    // Set up debug, sound, and other core flags
    // (Replace with your actual config/engine calls)
    bool debug = false;
    bool soundDisabled = false;
    // TODO: Parse command-line or config for debug/soundDisabled
    // TODO: Set up logging, profiler, and any global state
    if (!soundDisabled) {
        // TODO: Initialize sound system (OpenAL)
    }
    // TODO: Initialize debug options, profiler, etc.
    // TODO: Initialize file system, mods, and any global managers
    // TODO: Call renameSaveFolders() and init() as needed
}

void GameWindow::renameSaveFolders() {
    // Ported from Java: rename legacy save folders if needed
    std::string saveDir = ZomboidFileSystem::instance.getSaveDir();
    std::filesystem::path savePath(saveDir);
    if (std::filesystem::exists(savePath) && std::filesystem::is_directory(savePath)) {
        auto fighter = savePath / "Fighter";
        auto survivor = savePath / "Survivor";
        if (std::filesystem::exists(fighter) && std::filesystem::is_directory(fighter) &&
            std::filesystem::exists(survivor) && std::filesystem::is_directory(survivor)) {
            std::cout << "RENAMING Saves/Survivor to Saves/Apocalypse" << std::endl;
            std::cout << "RENAMING Saves/Fighter to Saves/Survivor" << std::endl;
            std::filesystem::rename(survivor, savePath / "Apocalypse");
            std::filesystem::rename(fighter, savePath / "Survivor");
            auto latestSave = ZomboidFileSystem::instance.getCacheDir() + "/latestSave.ini";
            if (std::filesystem::exists(latestSave)) {
                std::filesystem::remove(latestSave);
            }
        }
    }
}

long GameWindow::readLong(DataInputStream var0) {
    // Read 8 bytes as little-endian long
    uint8_t b[8];
    var0.read(reinterpret_cast<char*>(b), 8);
    long result = 0;
    for (int i = 0; i < 8; ++i) {
        result |= static_cast<long>(b[i]) << (8 * i);
    }
    return result;
}

int GameWindow::readInt(DataInputStream var0) {
    // Read 4 bytes as little-endian int
    uint8_t b[4];
    var0.read(reinterpret_cast<char*>(b), 4);
    int result = 0;
    for (int i = 0; i < 4; ++i) {
        result |= static_cast<int>(b[i]) << (8 * i);
    }
    return result;
}

void GameWindow::run_ez() {
    // Ported from Java: main game loop with frame timing
    using namespace std::chrono;
    auto last = high_resolution_clock::now();
    long accumulator = 0;
    while (!RenderThread::isCloseRequested() && !closeRequested) {
        auto now = high_resolution_clock::now();
        auto delta = duration_cast<nanoseconds>(now - last).count();
        last = now;
        if (PerformanceSettings::isUncappedFPS()) {
            frameStep();
        } else {
            accumulator += delta;
            long frameNanos = 1000000000L / PerformanceSettings::getLockFPS();
            if (accumulator >= frameNanos) {
                frameStep();
                accumulator %= frameNanos;
            }
        }
        std::this_thread::yield();
    }
    exit();
}

void GameWindow::enter() {
    // Ported from Java: set up graphics, load textures, initialize world
    Core::TileScale = Core::getInstance().getOptionTexture2x() ? 2 : 1;
    if (Core::SafeModeForced) Core::TileScale = 1;
    IsoCamera::init();
    int flags = TextureID::bUseCompression ? 4 : 0;
    flags |= 64;
    if (Core::TileScale == 1) {
        LoadTexturePack("Tiles1x", flags);
        LoadTexturePack("Overlays1x", flags);
        LoadTexturePack("JumboTrees1x", flags);
        LoadTexturePack("Tiles1x.floor", flags & ~4);
    }
    if (Core::TileScale == 2) {
        LoadTexturePack("Tiles2x", flags);
        LoadTexturePack("Overlays2x", flags);
        LoadTexturePack("JumboTrees2x", flags);
        LoadTexturePack("Tiles2x.floor", flags & ~4);
    }
    setTexturePackLookup();
    if (Texture::getSharedTexture("TileIndieStoneTentFrontLeft") == nullptr) {
        throw std::runtime_error("Rebuild Tiles.pack with '1 Include This in .pack' as individual images not tilesheets");
    }
    s_fpsTracking.init();
    DoLoadingText(Translator::getText("UI_Loading_ModelsAnimations"));
    ModelManager::instance.create();
    if (!SteamUtils::isSteamModeEnabled()) {
        DoLoadingText(Translator::getText("UI_Loading_InitPublicServers"));
        PublicServerUtil::init();
    }
    VoiceManager::instance.InitVMClient();
    DoLoadingText(Translator::getText("UI_Loading_OnGameBoot"));
    LuaEventManager::triggerEvent("OnGameBoot");
}

void GameWindow::frameStep() {
    // Ported from Java: per-frame logic
    try {
        IsoCamera::frameState.frameCount++;
        s_performance.frameStep.start();
        s_fpsTracking.frameStep();
        s_performance.logic.invokeAndMeasure([](){ logic(); });
        Core::getInstance().setScreenSize(RenderThread::getDisplayWidth(), RenderThread::getDisplayHeight());
        renderInternal();
        if (doRenderEvent) {
            LuaEventManager::triggerEvent("OnRenderTick");
        }
        Core::getInstance().DoFrameReady();
        LightingThread::instance.update();
        // Lua debugger and console toggles omitted for brevity
    } catch (const OpenGLException& ex) {
        RenderThread::logGLException(ex);
    } catch (const std::exception& ex) {
        ExceptionLogger::logException(ex);
    } catch (...) {
        s_performance.frameStep.end();
        throw;
    }
    s_performance.frameStep.end();
}

void GameWindow::exit() {
    // Ported from Java: shutdown and cleanup
    std::cout << "EXITDEBUG: GameWindow.exit 1" << std::endl;
    if (GameClient::bClient) {
        for (int i = 0; i < IsoPlayer::numPlayers; ++i) {
            IsoPlayer* p = IsoPlayer::players[i];
            if (p) {
                ClientPlayerDB::getInstance().clientSendNetworkPlayerInt(p);
            }
        }
        WorldStreamer::instance.stop();
        GameClient::instance.doDisconnect("exit");
        VoiceManager::instance.DeinitVMClient();
    }
    if (OkToSaveOnExit) {
        try {
            WorldStreamer::instance.quit();
        } catch (...) {}
        if (PlayerDB::isAllow()) {
            PlayerDB::getInstance().saveLocalPlayersForce();
            PlayerDB::getInstance().m_canSavePlayers = false;
        }
        if (ClientPlayerDB::isAllow()) {
            ClientPlayerDB::getInstance().canSavePlayers = false;
        }
        try {
            if (GameClient::bClient && GameClient::connection != nullptr) {
                GameClient::connection->username = "";
            }
            save(true);
        } catch (...) {}
        try {
            if (IsoWorld::instance.CurrentCell != nullptr) {
                LuaEventManager::triggerEvent("OnPostSave");
            }
        } catch (...) {}
        try {
            LightingThread::instance.stop();
            MapCollisionData::instance.stop();
            ZombiePopulationManager::instance.stop();
            PolygonalMap2::instance.stop();
            ZombieSpawnRecorder::instance.quit();
        } catch (...) {}
    }
    std::cout << "EXITDEBUG: GameWindow.exit 2" << std::endl;
    if (GameClient::bClient) {
        WorldStreamer::instance.stop();
        GameClient::instance.doDisconnect("exit-saving");
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    std::cout << "EXITDEBUG: GameWindow.exit 3" << std::endl;
    if (PlayerDB::isAvailable()) PlayerDB::getInstance().close();
    if (ClientPlayerDB::isAvailable()) ClientPlayerDB::getInstance().close();
    std::cout << "EXITDEBUG: GameWindow.exit 4" << std::endl;
    GameClient::instance.Shutdown();
    SteamUtils::shutdown();
    ZipLogs::addZipFile(true);
    onGameThreadExited();
    std::cout << "EXITDEBUG: GameWindow.exit 5" << std::endl;
}

void GameWindow::onGameThreadExited() {
    bGameThreadExited = true;
    RenderThread::onGameThreadExited();
}

void GameWindow::setTexturePackLookup() {
    // Ported from Java: update texture pack lookup
    texturePackTextures.clear();
    for (int i = texturePacks.size() - 1; i >= 0; --i) {
        TexturePack& tp = texturePacks[i];
        if (tp.modID.empty()) {
            texturePackTextures.insert(tp.textures.begin(), tp.textures.end());
        }
    }
    auto modIDs = ZomboidFileSystem::instance.getModIDs();
    for (int i = texturePacks.size() - 1; i >= 0; --i) {
        TexturePack& tp = texturePacks[i];
        if (!tp.modID.empty() && std::find(modIDs.begin(), modIDs.end(), tp.modID) != modIDs.end()) {
            texturePackTextures.insert(tp.textures.begin(), tp.textures.end());
        }
    }
    Texture::onTexturePacksChanged();
}

void GameWindow::LoadTexturePack(const std::string& var0, int var1) {
    // Ported from Java: load texture pack
    LoadTexturePack(var0, var1, "");
}

void GameWindow::LoadTexturePack(const std::string& var0, int var1, const std::string& var2) {
    // Ported from Java: load texture pack with mod id
    std::cout << "texturepack: loading " << var0 << std::endl;
    DoLoadingText(Translator::getText("UI_Loading_Texturepack", var0));
    std::string fileName = ZomboidFileSystem::instance.getString("media/texturepacks/" + var0 + ".pack");
    TexturePack tp;
    tp.packName = var0;
    tp.fileName = fileName;
    tp.modID = var2;
    fileSystem.mountTexturePack(var0, tp.textures, var1);
    texturePacks.push_back(tp);
}

void GameWindow::LoadTexturePackDDS(const std::string& var0) {
    // Ported from Java: load DDS texture pack (deprecated)
    std::cout << "texturepack: loading " << var0 << std::endl;
    // Not implemented: UI feedback and DDS parsing
    Texture::nullTextures.clear();
}

void GameWindow::installRequiredLibrary(const std::string& var0, const std::string& var1) {
    // Ported from Java: install required library if missing
    if (std::filesystem::exists(var0)) {
        std::cout << "Attempting to install " << var1 << std::endl;
        std::cout << "Running " << var0 << "." << std::endl;
        // Not implemented: process execution
    } else {
        std::cout << "Please install " << var1 << std::endl;
    }
}

void GameWindow::checkRequiredLibraries() {
    // Ported from Java: check for required DLLs on Windows
    #ifdef _WIN32
    std::string var0, var1, var2, var3;
    if (sizeof(void*) == 8) {
        var0 = "Lighting64";
        var1 = "_CommonRedist/vcredist/2010/vcredist_x64.exe";
        var2 = "_CommonRedist/vcredist/2012/vcredist_x64.exe";
        var3 = "_CommonRedist/vcredist/2013/vcredist_x64.exe";
    } else {
        var0 = "Lighting32";
        var1 = "_CommonRedist/vcredist/2010/vcredist_x86.exe";
        var2 = "_CommonRedist/vcredist/2012/vcredist_x86.exe";
        var3 = "_CommonRedist/vcredist/2013/vcredist_x86.exe";
    }
    try {
        // Not implemented: dynamic library loading
    } catch (...) {
        installRequiredLibrary(var1, "the Microsoft Visual C++ 2010 Redistributable.");
        installRequiredLibrary(var2, "the Microsoft Visual C++ 2012 Redistributable.");
        installRequiredLibrary(var3, "the Microsoft Visual C++ 2013 Redistributable.");
    }
    #endif
}

void GameWindow::init() {
    // Ported from Java: initialize core systems
    initFonts();
    checkRequiredLibraries();
    SteamUtils::init();
    ServerBrowser::init();
    SteamFriends::init();
    SteamWorkshop::init();
    RakNetPeerInterface::init();
    LightingJNI::init();
    ZombiePopulationManager::init();
    PZSQLUtils::init();
    Clipper::init();
    WorldMapJNI::init();
    Bullet::init();
    std::filesystem::create_directories(ZomboidFileSystem::instance.getCacheDir());
    DoLoadingText("Loading Mods");
    ZomboidFileSystem::instance.resetDefaultModsForNewRelease("41_51");
    ZomboidFileSystem::instance.loadMods("default");
    ZomboidFileSystem::instance.loadModPackFiles();
    DoLoadingText("Loading Translations");
    Languages::instance.init();
    Translator::language = "";
    initFonts();
    Translator::loadFiles();
    initShared();
    DoLoadingText(Translator::getText("UI_Loading_Lua"));
    LuaManager::init();
    CustomPerks::instance.initLua();
    CustomSandboxOptions::instance.init();
    CustomSandboxOptions::instance.initInstance(SandboxOptions::instance);
    LuaManager::LoadDirBase();
    ZomboidGlobals::Load();
    LuaEventManager::triggerEvent("OnLoadSoundBanks");
}

void GameWindow::initFonts() {
    // Ported from Java: initialize fonts
    TextManager::instance.Init();
    while (TextManager::instance.font.empty()) {
        fileSystem.updateAsyncTransactions();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void GameWindow::save(bool var0) {
    // Ported from Java: save world state
    if (!Core::getInstance().isNoSave()) {
        if (IsoWorld::instance.CurrentCell != nullptr &&
            Core::getInstance().getGameMode() != "LastStand" &&
            Core::getInstance().getGameMode() != "Tutorial") {
            // Not implemented: file IO for map_ver.bin, map_sand.bin, map.bin
            LuaEventManager::triggerEvent("OnSave");
            // Not implemented: SavefileThumbnail, MapCollisionData, SGlobalObjects, ZomboidRadio, GlobalModData, MapItem, WorldMapVisited
        }
    }
}

std::string GameWindow::getCoopServerHome() {
    // Ported from Java: get coop server home directory
    std::filesystem::path cacheDir(ZomboidFileSystem::instance.getCacheDir());
    return cacheDir.parent_path().string();
}

void GameWindow::WriteString(ByteBuffer var0, const std::string& var1) {
    // Ported from Java: write string to ByteBuffer
    WriteStringUTF(var0, var1);
}

void GameWindow::WriteStringUTF(ByteBuffer var0, const std::string& var1) {
    // Ported from Java: write string as UTF to ByteBuffer
    StringUTF::save(var0, var1);
}

void GameWindow::WriteString(DataOutputStream var0, const std::string& var1) {
    // Ported from Java: write string to DataOutputStream
    if (var1.empty()) {
        var0.writeInt(0);
    } else {
        var0.writeInt(static_cast<int>(var1.length()));
        var0.write(var1.c_str(), var1.length());
    }
}

std::string GameWindow::ReadStringUTF(ByteBuffer var0) {
    // Ported from Java: read string from ByteBuffer
    return StringUTF::load(var0);
}

std::string GameWindow::ReadString(ByteBuffer var0) {
    // Ported from Java: read string from ByteBuffer
    return ReadStringUTF(var0);
}

return GameWindow::ReadStringUTF() {
    // Ported from Java: read string from ByteBuffer (alias)
    return ReadStringUTF();
}

std::string GameWindow::ReadString(DataInputStream var0) {
    // Ported from Java: read string from DataInputStream
    int len = var0.readInt();
    if (len == 0) return "";
    if (len > 65536) throw std::runtime_error("GameWindow::ReadString: string is too long, corrupted save?");
    std::string result(len, '\0');
    var0.read(&result[0], len * sizeof(char));
    return result;
}

void GameWindow::doRenderEvent(bool var0) {
    // Ported from Java: set doRenderEvent flag
    doRenderEvent = var0;
}

void GameWindow::DoLoadingText(const std::string& var0) {
    // Ported from Java: show loading text (stub)
    std::cout << "[Loading] " << var0 << std::endl;
}

} // namespace zombie
