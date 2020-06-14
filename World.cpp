#include "World.h"

void World::update(float delta)
{
}

void World::onInit() {
	Chunk* chunk = generateChunk(sf::Vector2i(0,0));
	ChunkRenderData* data = generateChunkRenderData(chunk, nullptr);

	auto key = std::make_pair(chunk->root.x, chunk->root.y);
	chunks[key] = chunk;
	renderData[key] = data;

}
Chunk* World::getChunk(sf::Vector2i position)
{
	return chunks[std::make_pair(position.x, position.y)];
}
Chunk* World::generateChunk(sf::Vector2i position = sf::Vector2i(0, 0))
{
	Chunk* chunk = new Chunk();
	for (auto i = 0; i < CHUNK_SIDE * CHUNK_SIDE; i++) {
		chunk->tiles[i].type = grass;
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

	auto root = chunk->root;

	for (unsigned int i = 0; i < CHUNK_SIDE; ++i)
		for (unsigned int j = 0; j < CHUNK_SIDE; ++j)
		{
			auto tileType = chunk->tiles[i + j * CHUNK_SIDE].type;
			std::uint8_t tileTypeNumber = tileType;
			// auto tileTypeNumber = rand() % 16;
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