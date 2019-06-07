#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <string>
template <typename R, typename I>
class ResourceHolder {
public:
	bool load(I id, std::string filename) {
		R* res = new R();
		if (!res->loadFromFile(filename)) {
			return false;
		}
		if (mResources.size() > 0 && mResources.find(id) != mResources.end()) {
			return false;
		}

		mResources[id] = res;
		return true;
	};

	R* get(I id) {
		return mResources.find(id)->second;
	}

private:
	std::map<I, R*> mResources;

};


template <typename R, typename I>
class Resource
{
public:
	static bool load(I id, std::string filename) { if (rh == nullptr) rh = new ResourceHolder<R, I>(); return rh->load(id, filename); };
	static R* get(I id) { return rh->get(id); };
private:
	static ResourceHolder<R, I>* rh;
};

template <typename R, typename I>
ResourceHolder<R, I>* Resource<R, I>::rh;
typedef Resource<sf::Texture, std::string> RTX;

