#pragma once
#include "Renderable.h"
#include "Resources.h"
constexpr auto CHUNK_SIDE = 32u;
constexpr auto TILE_SIZE = 64u;
constexpr auto TEX_TILES = 8;

enum TileType: std::uint8_t {
	grass = 0,
	stone = 15,
};

struct Tile
{
	TileType type;
};

struct Chunk {
	Tile tiles[CHUNK_SIDE * CHUNK_SIDE];
	sf::Vector2i root;
};

struct ChunkRenderData {
	sf::VertexArray vertices;
};

class World :
	public RenderComponent
{
public:
	World(){
		this->texture = RTX::get("test");
	}

	virtual void update(float delta) override;
	virtual void onInit() override;

	virtual void onDestroy() override {
		for (auto it = chunks.begin(); it != chunks.end(); it++)
		{
			delete it->second;
			it->second = nullptr;
		}
		for (auto it = renderData.begin(); it != renderData.end(); it++)
		{
			delete it->second;
			it->second = nullptr;
		}
	};

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states, sf::Transform t) const {
		states.texture = texture;
		for (auto it = renderData.begin(); it != renderData.end(); it++)
		{
			states.transform *= t;
			target.draw(it->second->vertices, states);
		}
	}

	Chunk* getChunk(sf::Vector2i position);
	Chunk* generateChunk(sf::Vector2i position);
	ChunkRenderData* generateChunkRenderData(Chunk* chunk, ChunkRenderData* olddata);

	std::map<std::pair<int,int>, Chunk*> chunks;
	std::map<std::pair<int, int>, ChunkRenderData* > renderData;
	sf::Texture* texture;
};

