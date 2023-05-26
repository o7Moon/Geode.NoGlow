#include <Geode/Geode.hpp>
#include <Geode/modify/LevelEditorLayer.hpp>
#include <Geode/loader/SettingEvent.hpp>

using namespace geode::prelude;

bool noglow = false;
bool dontfade = false;
bool dontenter = false;

// for some reason calling getSettingValue in the hook messes up the object position,
// so this is the workaround.

$execute {
	Mod* mod = Mod::get();
	noglow = mod->getSettingValue<bool>("no-glow");
	dontfade = mod->getSettingValue<bool>("dont-fade");
	dontenter = mod->getSettingValue<bool>("dont-enter");

	listenForSettingChanges("no-glow", +[](bool value){
		noglow = value;
	});
	listenForSettingChanges("dont-fade", +[](bool value){
		dontfade = value;
	});
	listenForSettingChanges("dont-enter", +[](bool value){
		dontenter = value;
	});
}

class $modify(LevelEditorLayer) {
	GameObject* createObject(int a, cocos2d::CCPoint b, bool c){
		GameObject* obj = LevelEditorLayer::createObject(a,b,c);
		obj->m_isGlowDisabled = noglow;
		obj->m_isDontFade = dontfade;
		obj->m_isDontEnter = dontenter;
		return obj;
	}
};
