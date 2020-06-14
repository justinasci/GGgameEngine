#include "World.h"
#include <iostream>
#include <iostream>
#include <vector>
#include <algorithm>
#include "PerlinNoise.hpp"

sf::Vector2i getNearestChunkRoot(sf::Vector2i point, int chunkSideLenght) {
	return sf::Vector2i(point.x - point.x % chunkSideLenght, point.y - point.y % chunkSideLenght);
}

void World::update(float delta)
{
	auto view = this->window->getView();
	auto center = view.getCenter();
	auto getSize = view.getSize();

	auto sideLenght = TILE_SIZE * CHUNK_SIDE;
	auto topLeft = sf::Vector2i(center.x - getSize.x - sideLenght, center.y - getSize.y - sideLenght);
	auto bottomRight = sf::Vector2i(center.x + getSize.x + sideLenght, center.y + getSize.y + sideLenght);

	auto nTopLeft = getNearestChunkRoot(bottomRight, sideLenght);
	auto nBottomRight = getNearestChunkRoot(topLeft, sideLenght);

	std::vector<std::pair<int, int>> keys;

	for (auto x = nBottomRight.x; x < nTopLeft.x; x += sideLenght) {
		for (auto y = nBottomRight.y; y < nTopLeft.y; y += sideLenght) {
			auto key = std::make_pair(x, y);
			keys.push_back(key);
			if (renderData.count(key) > 0) {
				continue;
			}
			else {
				Chunk* chunk = generateChunk(sf::Vector2i(x, y));
				ChunkRenderData* data = generateChunkRenderData(chunk, nullptr);
				chunks[key] = chunk;
				renderData[key] = data;
			}
		}
	}

	for (auto it = renderData.begin(); it != renderData.end();)
	{	
		if (std::find(keys.begin(), keys.end(), it->first) != keys.end()) {
			++it;
			continue;
		}
		else {
			std::cout << it->first.first << " " << it->first.second;
			delete it->second;
			renderData.erase(it++);
		}
	}

}

void World::onInit() {
}

Chunk* World::getChunk(sf::Vector2i position)
{
	return chunks[std::make_pair(position.x, position.y)];
}
Chunk* World::generateChunk(sf::Vector2i position = sf::Vector2i(0, 0))
{
	Chunk* chunk = new Chunk();
	float f = 8.0f;
	float px = (float)position.x / (float)(CHUNK_SIDE * CHUNK_SIDE);
	float py = (float)position.y / (float)(CHUNK_SIDE * CHUNK_SIDE);
	const siv::PerlinNoise perlin(88888);
	for (auto i = 0; i < CHUNK_SIDE * CHUNK_SIDE; i++) {

		double xzz = (double)((double)(i % CHUNK_SIDE) / CHUNK_SIDE + px) / f;
		double x = (double)((double)(i % CHUNK_SIDE) / CHUNK_SIDE + px) / f;
		double y = (double)((double)((double)(i / CHUNK_SIDE) / CHUNK_SIDE) + py ) / f;
		auto p = perlin.accumulatedOctaveNoise2D_0_1(x, y , 8);
		auto type = static_cast<TileType>(
			static_cast<int>(roundf((p * TileType::lastTile - 0.5f)))
			);
		chunk->tiles[i].type = type;
	}
	chunk->root = position;
	return chunk;
}
ChunkRenderData* World::generateChunkRenderData(Chunk* chunk, ChunkRenderData* olddata)
{
	if (chunk == nullptr) {
		throw "generateChunkRenderData: chunk  nullptr";
	}
	ChunkRenderData* data = nullptr;
	if (olddata != nullptr) {
		data = olddata;
	}
	else {
		data = new ChunkRenderData;
	}

	// resize the vertex array to fit the level size
	data->vertices.setPrimitiveType(sf::Quads);
	data->vertices.resize(CHUNK_SIDE * CHUNK_SIDE * 4);

	auto root = sf::Vector2f(chunk->root.x, chunk->root.y);

	for (unsigned int i = 0; i < CHUNK_SIDE; ++i)
		for (unsigned int j = 0; j < CHUNK_SIDE; ++j)
		{
			auto tileType = chunk->tiles[i + j * CHUNK_SIDE].type;
			std::uint8_t tileTypeNumber = tileType;
			int step = texture->getSize().x / TEX_TILES;

			float tu = (float)(tileTypeNumber * step % (texture->getSize().x));
			float tv = (float)(tileTypeNumber * step / texture->getSize().x);

			sf::Vertex* quad = &data->vertices[(i + j * CHUNK_SIDE) * 4];
			quad[0].position = sf::Vector2f(i * TILE_SIZE + root.x, j * TILE_SIZE + root.y);
			quad[1].position = sf::Vector2f((i + 1) * TILE_SIZE + root.x, j * TILE_SIZE + root.y);
			quad[2].position = sf::Vector2f((i + 1) * TILE_SIZE + root.x, (j + 1) * TILE_SIZE + root.y);
			quad[3].position = sf::Vector2f(i * TILE_SIZE + root.x, (j + 1) * TILE_SIZE + root.y);

			quad[0].texCoords = sf::Vector2f(tu, tv);
			quad[1].texCoords = sf::Vector2f((tu + step), tv);
			quad[2].texCoords = sf::Vector2f((tu + step), tv + step);
			quad[3].texCoords = sf::Vector2f(tu, tv + step);
		}
	return data;
}
;