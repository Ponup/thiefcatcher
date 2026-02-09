#include "Surface.h"

#include <stdexcept>
using std::runtime_error;

#include <SDL_image.h>

#include "StringUtil.h"

#include "Window.h"

Surface::Surface()
{
    surface = nullptr;
}

Surface::Surface(SDL_Surface *surface)
{
    if (nullptr == surface)
    {
        throw std::runtime_error("surface is null");
    }
    SDL_Surface *convertedSurface = SDL_ConvertSurface(surface, surface->format, SDL_SWSURFACE);
    this->surface = (nullptr == convertedSurface ? surface : convertedSurface);
}

Surface::Surface(Surface *surface, const Dimension &dimension)
{
    SDL_Surface *x = surface->toSDL();
    this->surface = SDL_CreateRGBSurface((x)->flags /*| SDL_SRCALPHA*/, dimension.w,
                                         dimension.h, (x)->format->BitsPerPixel, (x)->format->Rmask, (x)->format->Gmask, (x)->format->Bmask, (x)->format->Amask);
}

Surface::Surface(const string &path, bool hasAlphaChannel)
{
    load(path, hasAlphaChannel);
}

void Surface::load(const string &path, bool hasAlphaChannel)
{
    SDL_Surface *normal = IMG_Load(path.c_str());
    if (nullptr == normal)
        throw runtime_error(IMG_GetError());

    surface = normal;
}

Surface::~Surface()
{
    if (surface != nullptr)
    {
        SDL_FreeSurface(surface);
        surface = nullptr;
    }
}

void Surface::optimize()
{
}

Dimension Surface::getDimension() const
{
    return Dimension(surface->w, surface->h);
}

void Surface::clean()
{
    Uint32 a = SDL_MapRGB(surface->format, 200, 200, 200);
    SDL_FillRect(surface, nullptr, a);
}

void Surface::clean(const Color &color)
{
    Uint32 a = SDL_MapRGB(surface->format, color.r, color.g, color.b);
    SDL_FillRect(surface, nullptr, a);
}

void Surface::setTransparentColor(const Color &color)
{
    // Uint32 key = SDL_MapRGB( surface->format, color.r, color.g, color.b );
    // SDL_SetColorKey(surface, SDL_SRCCOLORKEY | SDL_RLEACCEL, key);
}

void Surface::drawSurface(Surface *image, const Point &point)
{
    if (nullptr == image)
        return;
    SDL_Surface *imageSurf = image->toSDL();

    SDL_Rect rectDst = {point.x, point.y, 0, 0};
    SDL_Rect rectSrc;

    rectSrc.x = rectSrc.y = 0;
    rectSrc.w = imageSurf->w;
    rectSrc.h = imageSurf->h;

    SDL_BlitSurface(imageSurf, &rectSrc, surface, &rectDst);
}

void Surface::drawTexture(Texture *texture, const Point &point)
{
}

void Surface::updateArea(const Point &point, const Dimension &dimension)
{
    // SDL_UpdateRect(surface, point.x, point.y, dimension.w, dimension.h);
}

void Surface::updateArea(const Area &area)
{
    updateArea(area.getPoint(), area.getDimension());
}

Surface *Surface::getArea(const Point &point, const Dimension &dimension)
{
    SDL_Surface *area = SDL_CreateRGBSurface((surface)->flags /*| SDL_SRCALPHA*/, (dimension.w),
                                             (dimension.h), (surface)->format->BitsPerPixel, (surface)->format->Rmask, (surface)->format->Gmask, (surface)->format->Bmask, (surface)->format->Amask);
    SDL_Rect rect = {point.x, point.y, dimension.w, dimension.h};
    SDL_BlitSurface(surface, &rect, area, nullptr);

    return new Surface(area);
}

Surface *Surface::getArea(const Area &areap)
{
    SDL_Surface *area = SDL_CreateRGBSurface((surface)->flags /*| SDL_SRCALPHA*/, (areap.w),
                                             (areap.h), (surface)->format->BitsPerPixel, (surface)->format->Rmask, (surface)->format->Gmask, (surface)->format->Bmask, (surface)->format->Amask);
    SDL_Rect rect = areap;
    SDL_BlitSurface(surface, &rect, area, nullptr);

    return new Surface(area);
}

void Surface::setOpacity(Uint8 opacity)
{
    // SDL_SetAlpha(surface, SDL_RLEACCEL | SDL_SRCALPHA, opacity);
}

void Surface::transform(SDL_Renderer *renderer, double angle, double zoom, int smooth)
{
    (void)zoom;
    (void)smooth;
    // @todo implement when migrating to SDL3
    SDL_Surface *rotatedSurface = nullptr; // SDL_RenderTextureRotated(renderer, surface, nullptr, nullptr, angle, zoom, SDL_FLIP_NONE);
    if (nullptr != rotatedSurface)
    {
        SDL_FreeSurface(surface);
        surface = rotatedSurface;
    }
}

SDL_Surface *Surface::toSDL()
{
    return surface;
}

SDL_Texture *Surface::toTexture(SDL_Renderer *renderer)
{
    return SDL_CreateTextureFromSurface(renderer, surface);
}
