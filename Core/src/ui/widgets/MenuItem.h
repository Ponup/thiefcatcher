#ifndef MENUITEM_H
#define MENUITEM_H

#include <Point.h>
#include <Dimension.h>
#include <Area.h>
#include <Text.h>

class MenuItem {
	private:
		Point position;
		Area area;
		Text *text;
	
	public:
		MenuItem() {}
		void setArea(const Area &area);
		Area getArea() const;
		
		void setText(Text *text);
		Text *getText() const;
		
		void setPosition(Point position);
		const Point &getPosition() const;
};

#endif

