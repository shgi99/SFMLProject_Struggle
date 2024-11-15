#include "stdafx.h"
#include "rapidcsv.h"
#include "AnimationClip.h"
AnimationLoopTypes AnimationClip::parseLoopType(const std::string& loopTypeStr) {
	if (loopTypeStr == "Single") return AnimationLoopTypes::Single;
	if (loopTypeStr == "Loop") return AnimationLoopTypes::Loop;
	if (loopTypeStr == "PingPong") return AnimationLoopTypes::PingPong;
	return AnimationLoopTypes::Single; // ±âº»°ª
}

bool AnimationClip::loadFromFile(const std::string& filePath)
{
	std::ifstream f(filePath);
	json j = json::parse(f);

	id = j["name"].get<std::string>();
	loopType = parseLoopType(j["loopType"].get<std::string>());
	fps = j["fps"].get<int>();


    frames.clear();
    for (const auto& frame : j["frames"]) {
        frames.push_back({
            frame["texId"].get<std::string>(),
            sf::IntRect(
                frame["texCoord"][0].get<int>(),
                frame["texCoord"][1].get<int>(),
                frame["texCoord"][2].get<int>(),
                frame["texCoord"][3].get<int>()
            )
            });
    }

	return true;
}

