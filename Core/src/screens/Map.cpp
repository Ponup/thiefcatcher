#include "Map.h"

#include "MathUtil.h"
#include "MediaSound.h"
#include "Text.h"
#include "FrameRegulator.h"
#include "utilities/Translator.h"
#include "entities/CountriesManager.h"

Point latlong2point( pair<double, double> latlong )
{
        // y = ((-1 * lat) + 90) * (MAP_HEIGHT / 180);
        // x = ( lon + 180) * (MAP_WIDTH / 360);
	Point point;
	point.y = (int)( ( ( -1 * latlong.first ) + 90 ) * 2.6 );
	point.x = (int)( ( latlong.second + 180 ) * ( 720 / 360 ) );
	printf("%f, %f => %s\n", latlong.first, latlong.second, point.toString().c_str() );
	return point;
}

Map::Map(Window *window_, Country *sourceCountry_, Country *targetCountry_) : selected(0), quit(false), updatePending( true ) {
	window = window_;
	
	sourceCountry = sourceCountry_;
	targetCountry = targetCountry_;

	bgSurface = NULL;

	mapOffset = Point( 50, 80 );
	// This point fixes the position of the bullets on the map.
	offsetFix = Point::Origin;
	
	bulletRadius = Point( 10, 10 );

	airplane.load("resources/images/map/airplane-30.png", true);

	font.load( "resources/fonts/FreeSansBold.ttf", 15 );
	font.setColor( Color( 0x8e, 0x60, 0x3e ) );

	addSensibleAreas();
	createStaticBackground();
	drawAllCountries();

	updateScreen( true );

	while( !quit ) {
		captureEvents();

		if( updatePending ) updateScreen( true );

		SDL_Delay( 30 );
	}

	if( -1 != selected )
		gotoTarget();
}

Map::~Map() {
}

void Map::drawAllCountries()
{
	vector<Country> countries = CountriesManager::findAll();
	for( unsigned int i = 0; i < countries.size(); i++ ) 
	{
		Text text( countries[ i ].getIsoCode(), &font );
		text.draw( latlong2point( countries[ i ].getLatitudeLongitude() ) + mapOffset - bulletRadius, bgSurface );
	}
}

void Map::addSensibleAreas()
{
	Dimension bulletDimension( 20, 20 );

	for( int i = 0; i < 3; i++ )
	{
		Point p = latlong2point( targetCountry[ i ].getLatitudeLongitude() );
		points[ i ] = p + mapOffset - bulletRadius + offsetFix;
		sensAreas.addArea( Area( points[ i ], bulletDimension ) );
	}
}

void Map::updateScreen( bool update ) {

	drawOptions();
	drawDirectedAirplane();

	if( update ) {
		window->drawSurface( canvas );
		window->flip();
	}

	updatePending = false;
}

void Map::drawOptions()
{
	font.setColor(Color(0x8e, 0x60, 0x3e));

	Color colorNormal(0, 0, 0);
	Color colorHighlight(0x8e, 0x60, 0x3e);

	unsigned int lineHeight = font.getLineSkip();

	unsigned char posx = 230;
	unsigned int posy = 505;

	Surface tickSurf( "resources/images/game/tick.png" );

	for (int i = 0; i < 3; i++) {
		Point countryNamePosition(posx, posy);

		if (i == selected) {
			canvas->drawSurface(&tickSurf, Point(210, posy));
			font.setColor(colorNormal);
			canvas->drawSurface(&bulletOverSurface, points[i]);
		} else {
			font.setColor(colorHighlight);
			canvas->drawSurface( &bulletSurface, points[i]);
		}

		Text text( targetCountry[i].getName(), &font );
		text.draw( countryNamePosition, canvas );

		posy += lineHeight;
	}
}

void Map::createStaticBackground()
{
	if( NULL != bgSurface )
		return;

	bgSurface = new Surface( "resources/images/empty_background.jpg" );

	Surface mapSurface( "resources/images/map/mercator-map-small.png" );
	bgSurface->drawSurface( &mapSurface, mapOffset );

	bulletSurface.load("resources/images/map/flight_target.gif");
	bulletOverSurface.load("resources/images/map/flight_target_over.gif");

	Font currentLocationFont( "resources/fonts/FreeSansBold.ttf", 30 );
	currentLocationFont.setColor( Color(255, 220, 220) );

	char temp[200];
	memset(temp, '\0', 200);
	sprintf( temp, _("You are in %s.").c_str(), sourceCountry->getName().c_str() );
	Text currentLocationText( temp, &currentLocationFont );
	currentLocationText.draw( Point( 50, 20 ), bgSurface );

	Text text( _("Choose your destination:"), &font );
	text.draw( Point( 50, 505 ), bgSurface );

	canvas = new Surface( bgSurface->toSDL() );
}

void Map::drawDirectedAirplane()
{
	double deltay = latlong2point( sourceCountry->getLatitudeLongitude() ).y - latlong2point( targetCountry[ selected ].getLatitudeLongitude() ).y;
	double deltax = latlong2point( sourceCountry->getLatitudeLongitude() ).x - latlong2point( targetCountry[ selected ].getLatitudeLongitude() ).x;
	double angle = MathUtil::radian2degree( atan2( deltax, deltay ) );
	angle += 45; // because the airplane is rotated already.

	airplane.load("resources/images/map/airplane-30.png", true);
	directedAirplane = airplane;
	directedAirplane.transform( angle );

	airplanePosition = latlong2point( sourceCountry->getLatitudeLongitude() ) - Point( 15, 15 ) + mapOffset - bulletRadius + offsetFix;
	canvas->drawSurface( &directedAirplane, airplanePosition );
}

void Map::gotoTarget() {
	quit = true;

	MediaSound sound("resources/sounds/airplane.wav");

	Point sourcePoint = airplanePosition;
	Point targetPoint = points[ selected ] - bulletRadius;
	vector<Point> path = MathUtil::calculatePath( sourcePoint, targetPoint );

	FrameRegulator fr( 50 );
	fr.setUp();

	sound.play();
	vector<Point>::iterator it;
	for( it = path.begin(); it != path.end(); it++ )
	{
		Point point = airplanePosition + (*it);
		Surface *canvas = new Surface( bgSurface->toSDL() );

		drawOptions();
		canvas->drawSurface( &directedAirplane, point );
		window->drawSurface( canvas );
		window->flip();
		delete canvas;
		fr.regulate();
	}

	SDL_Delay( 800 );
}

char Map::getSelection() {
	return selected;
}

void Map::onKeyDown(SDL_KeyboardEvent key) {
	updatePending = true;
	switch (key.keysym.sym) {
	case SDLK_ESCAPE:
		cancelScene();
		break;
	case SDLK_RETURN:
		quit = true;
		break;
	case SDLK_UP:
		selected--;
		if (selected == -1)
			selected = 2;
		break;
	case SDLK_DOWN:
		selected++;
		if (selected > 2)
			selected = 0;
		break;
	default:
		break;
	}
}

void Map::onKeyUp(SDL_KeyboardEvent e) {
}

void Map::onMouseButtonDown(SDL_MouseButtonEvent e) {
	switch (e.button) {
	case SDL_BUTTON_RIGHT:
		cancelScene();
		break;
	case SDL_BUTTON_LEFT:
		int resolved = sensAreas.resolve(e.x, e.y);
		if (resolved != -1) {
			selected = resolved;
			gotoTarget();
		}
		break;
	}
}

void Map::onMouseButtonUp(SDL_MouseButtonEvent e) {
}

void Map::onMouseMotion(SDL_MouseMotionEvent motion) {
	int resolved = sensAreas.resolve( motion.x, motion.y );
	if( resolved != -1 ) {
		updatePending = true;
		selected = resolved;
	}
}

void Map::cancelScene() {
	selected = -1;
	quit = true;
}

