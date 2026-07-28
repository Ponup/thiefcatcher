#include "Renderer.h"

Kangaroo::Renderer::Renderer(SDL_Renderer* renderer) : internal(renderer) {

}

void Kangaroo::Renderer::drawTexture(Texture* texture, const Point& pos) {
	SDL_FRect srcRect = { 0.0f, 0.0f, static_cast<float>(texture->getWidth()), static_cast<float>(texture->getHeight()) };
	SDL_FRect dstRect = { static_cast<float>(pos.x), static_cast<float>(pos.y), static_cast<float>(texture->getWidth()), static_cast<float>(texture->getHeight()) };
	SDL_RenderTexture(internal, texture->getInternal(), &srcRect, &dstRect);
}

void Kangaroo::Renderer::drawText(Text* text, const Point& pos) {
	SDL_Surface* surface = text->toSDL();
	Texture texture(internal, surface);
	SDL_DestroySurface(surface);
	drawTexture(&texture, pos);
}

void Kangaroo::Renderer::present() {
	SDL_RenderPresent(internal);
}
