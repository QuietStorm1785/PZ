#include "zombie/iso/IsoObject.h"

namespace zombie {
namespace iso {

// IsoObject constructors
IsoObject::IsoObject() {
	for (int i = 0; i < 4; ++i) {
		setAlphaAndTarget(i, 1.0f);
		outlineHighlightCol[i] = -1;
	}
}

IsoObject::IsoObject(IsoCell* cell) : IsoObject() {}
IsoObject::IsoObject(IsoCell* cell, IsoGridSquare* square, IsoSprite* sprite) : IsoObject() {
	this->sprite = sprite;
	this->square = square;
}
IsoObject::IsoObject(IsoCell* cell, IsoGridSquare* square, const std::string& spriteName) : IsoObject() {
	// Set sprite using IsoSpriteManager, matching Java logic
	if (!spriteName.empty()) {
		// IsoSpriteManager singleton assumed to have getInstance() and getSprite()
		this->sprite = IsoSpriteManager::getInstance()->getSprite(spriteName);
	}
	this->square = square;
	this->tile = spriteName;
}
IsoObject::IsoObject(IsoGridSquare* square, const std::string& spriteName, const std::string& objectName) : IsoObject() {
	if (!spriteName.empty()) {
		this->sprite = IsoSpriteManager::getInstance()->getSprite(spriteName);
	}
	this->square = square;
	this->tile = spriteName;
	this->spriteName = spriteName;
	this->name = objectName;
}
IsoObject::IsoObject(IsoGridSquare* square, const std::string& spriteName, const std::string& objectName, bool someFlag) : IsoObject() {
	if (someFlag && !spriteName.empty()) {
		// Create a new sprite and load frames, matching Java logic
		this->sprite = IsoSprite::CreateSprite(IsoSpriteManager::getInstance());
		this->sprite->LoadFramesNoDirPageSimple(spriteName);
	} else if (!spriteName.empty()) {
		this->sprite = IsoSpriteManager::getInstance()->getSprite(spriteName);
	}
	this->tile = spriteName;
	this->square = square;
	this->name = objectName;
}
IsoObject::IsoObject(IsoGridSquare* square, const std::string& spriteName, bool someFlag) : IsoObject() {
	if (someFlag && !spriteName.empty()) {
		this->sprite = IsoSprite::CreateSprite(IsoSpriteManager::getInstance());
		this->sprite->LoadFramesNoDirPageSimple(spriteName);
	} else if (!spriteName.empty()) {
		this->sprite = IsoSpriteManager::getInstance()->getSprite(spriteName);
	}
	this->tile = spriteName;
	this->square = square;
}
IsoObject::IsoObject(IsoGridSquare* square, const std::string& spriteName) : IsoObject() {
	if (!spriteName.empty()) {
		this->sprite = IsoSprite::CreateSprite(IsoSpriteManager::getInstance());
		this->sprite->LoadFramesNoDirPageSimple(spriteName);
	}
	this->square = square;
}

bool IsoObject::isFloor() const {
	if (this->sprite && this->sprite->getProperties() && this->sprite->getProperties()->Is(IsoFlagType::solidfloor)) {
		return true;
	}
	return false;
}

std::shared_ptr<IsoObject> IsoObject::getNew(IsoGridSquare* square, const std::string& spriteName, const std::string& objectName, bool someFlag) {
	// Ported from Java: Use a static cache to reuse IsoObject instances for the same parameters
	// Key is a tuple of (square pointer, spriteName, objectName, someFlag)
	using CacheKey = std::tuple<IsoGridSquare*, std::string, std::string, bool>;
	static std::unordered_map<CacheKey, std::weak_ptr<IsoObject>> cache;

	CacheKey key = std::make_tuple(square, spriteName, objectName, someFlag);
	auto it = cache.find(key);
	if (it != cache.end()) {
		if (auto obj = it->second.lock()) {
			return obj;
		}
	}
	auto newObj = std::make_shared<IsoObject>(square, spriteName, objectName, someFlag);
	cache[key] = newObj;
	return newObj;
}

std::shared_ptr<IsoObject> IsoObject::getLastRendered() {
	return lastRendered;
}

void IsoObject::setLastRendered(std::shared_ptr<IsoObject> obj) {
	lastRendered = obj;
}

// IsoObjectFactory methods
IsoObject::IsoObjectFactory::IsoObjectFactory(uint8_t id, const std::string& name)
	: classID(id), objectName(name), hashCode(std::hash<std::string>{}(name)) {}

std::shared_ptr<IsoObject> IsoObject::IsoObjectFactory::InstantiateObject(IsoCell* cell) {
	return std::make_shared<IsoObject>(cell);
}

uint8_t IsoObject::IsoObjectFactory::getClassID() const { return classID; }
std::string IsoObject::IsoObjectFactory::getObjectName() const { return objectName; }

// IsoObjectPicker::ClickObject methods
int IsoObject::IsoObjectPicker::ClickObject::calculateScore() {
	// Ported from IsoObjectPicker$ClickObject.java
	// The actual Java logic checks for object type and properties to assign a score
	// C++ version assumes IsoObject* object is a member of ClickObject
	int score = 0;
	if (!object) return score;

	// Prioritize IsoDoor, IsoThumpable, IsoWindow, IsoCurtain, IsoLightSwitch
	// (Assume dynamic_cast is available and these types are defined)
	if (dynamic_cast<IsoDoor*>(object)) {
		score = 100;
	} else if (dynamic_cast<IsoThumpable*>(object)) {
		score = 90;
	} else if (dynamic_cast<IsoWindow*>(object)) {
		score = 80;
	} else if (dynamic_cast<IsoCurtain*>(object)) {
		score = 70;
	} else if (dynamic_cast<IsoLightSwitch*>(object)) {
		score = 60;
	} else if (object->sprite && object->sprite->getProperties()) {
		// Check for special sprite flags (e.g., solidfloor, solidtrans, etc.)
		if (object->sprite->getProperties()->Is(IsoFlagType::solidfloor)) {
			score = 50;
		} else if (object->sprite->getProperties()->Is(IsoFlagType::solidtrans)) {
			score = 40;
		} else if (object->sprite->getProperties()->Is(IsoFlagType::collideW)) {
			score = 30;
		} else {
			score = 10;
		}
	} else {
		score = 1;
	}
	return score;
}
int IsoObject::IsoObjectPicker::ClickObject::getScore() const { return score; }

int IsoObject::IsoObjectPicker::compare(const ClickObject& var1, const ClickObject& var2) {
	int var3 = var1.getScore();
	int var4 = var2.getScore();
	if (var3 > var4) return 1;
	else if (var3 < var4) return -1;

	// Tie-breaker: compare IsoObject pointers (lowest address wins, as a proxy for Java's hashCode/identity)
	if (var1.object < var2.object) return -1;
	if (var1.object > var2.object) return 1;

	// Further tie-breaker: compare IsoGridSquare pointers if available
	if (var1.square && var2.square) {
		if (var1.square < var2.square) return -1;
		if (var1.square > var2.square) return 1;
	}

	// If still equal, return 0
	return 0;
}

// IsoObjectSyncRequests methods
void IsoObject::IsoObjectSyncRequests::putRequest(void* /*IsoGridSquare*/ var1, void* /*IsoObject*/ var2) {
	// Ported from IsoObjectSyncRequests.java: queue the request for later processing
	// Use a static vector as the request queue
	using Request = std::pair<void*, void*>;
	static std::vector<Request> requestQueue;
	requestQueue.emplace_back(var1, var2);
}
void IsoObject::IsoObjectSyncRequests::putRequestLoad(void* /*IsoGridSquare*/ var1) {
	// Ported from IsoObjectSyncRequests.java: queue the load request for later processing
	static std::vector<void*> loadRequestQueue;
	loadRequestQueue.push_back(var1);
}
void IsoObject::IsoObjectSyncRequests::putRequest(int, int, int, uint8_t) {
	// Ported from IsoObjectSyncRequests.java: queue the coordinate-based request for later processing
	using CoordRequest = std::tuple<int, int, int, uint8_t>;
	static std::vector<CoordRequest> coordRequestQueue;
	coordRequestQueue.emplace_back(std::make_tuple(
        std::forward<int>(std::get<0>(std::forward_as_tuple(__builtin_va_arg_pack()))),
        std::forward<int>(std::get<1>(std::forward_as_tuple(__builtin_va_arg_pack()))),
        std::forward<int>(std::get<2>(std::forward_as_tuple(__builtin_va_arg_pack()))),
        std::forward<uint8_t>(std::get<3>(std::forward_as_tuple(__builtin_va_arg_pack())))
    ));
}
}
void IsoObject::IsoObjectSyncRequests::sendRequests(void* /*UdpConnection*/ var1) {
	// Ported from IsoObjectSyncRequests.java: send all queued requests (placeholder logic)
	// In a real implementation, this would serialize and send requests over the network
	// For now, just clear the queues
	{
		using Request = std::pair<void*, void*>;
		static std::vector<Request> requestQueue;
		requestQueue.clear();
	}
	{
		static std::vector<void*> loadRequestQueue;
		loadRequestQueue.clear();
	}
	{
		using CoordRequest = std::tuple<int, int, int, uint8_t>;
		static std::vector<CoordRequest> coordRequestQueue;
		coordRequestQueue.clear();
	}
}
void IsoObject::IsoObjectSyncRequests::receiveIsoSync(int, int, int, uint8_t) {
	// Ported from IsoObjectSyncRequests.java: handle received sync request (placeholder)
	// In a real implementation, this would update the game state based on received data
	// For now, do nothing
}

// IsoObject$OutlineShader methods
void IsoObject::OutlineShader::initShader() {
	// Ported from IsoObject$OutlineShader.java: initialize the outline shader
	// This version compiles a simple outline shader using OpenGL, and ensures SDL2 context is active (for Switch)

#ifdef __SWITCH__
	// For Nintendo Switch, ensure SDL2 context is initialized
	if (SDL_WasInit(SDL_INIT_VIDEO) == 0) {
		SDL_Init(SDL_INIT_VIDEO);
	}
#endif

	const char* vertexShaderSource =
		"#version 330 core\n"
		"layout(location = 0) in vec3 aPos;\n"
		"void main() {\n"
		"    gl_Position = vec4(aPos, 1.0);\n"
		"}";

	const char* fragmentShaderSource =
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"uniform vec4 outlineColor;\n"
		"void main() {\n"
		"    FragColor = outlineColor;\n"
		"}";

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);

	GLint success;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		fprintf(stderr, "Vertex shader compilation failed: %s\n", infoLog);
	}

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		fprintf(stderr, "Fragment shader compilation failed: %s\n", infoLog);
	}

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
		fprintf(stderr, "Shader program linking failed: %s\n", infoLog);
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Store shaderProgram in a member variable if needed
}
}
void IsoObject::OutlineShader::setOutlineColor(float, float, float, float) {
	// Ported from IsoObject$OutlineShader.java: set the outline color uniform in the shader
	// Assumes shaderProgram is stored as a member variable (e.g., this->shaderProgram)

	// If shaderProgram is not a member, this should be adapted accordingly
	GLint outlineColorLoc = glGetUniformLocation(this->shaderProgram, "outlineColor");
	if (outlineColorLoc != -1) {
		glUseProgram(this->shaderProgram);
		glUniform4f(outlineColorLoc, r, g, b, a);
	}
}
void IsoObject::OutlineShader::setStepSize(float, int, int) {
	// Ported from IsoObject$OutlineShader.java: set the step size uniform in the shader
	// Assumes shaderProgram is stored as a member variable (e.g., this->shaderProgram)

	// In a real shader, step size may be used for outline thickness or screen scaling
	GLint stepSizeLoc = glGetUniformLocation(this->shaderProgram, "stepSize");
	if (stepSizeLoc != -1) {
		glUseProgram(this->shaderProgram);
		// Pass as vec3: (step, width, height)
		glUniform3f(stepSizeLoc, step, static_cast<float>(width), static_cast<float>(height));
	}
}
bool IsoObject::OutlineShader::StartShader() {
	// Ported from IsoObject$OutlineShader.java: activate the outline shader
	// Assumes shaderProgram is stored as a member variable (e.g., this->shaderProgram)
	if (this->shaderProgram) {
		glUseProgram(this->shaderProgram);
		return true;
	}
	return false;
}

} // namespace iso
} // namespace zombie
