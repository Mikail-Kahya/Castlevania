#pragma once
#include <string>
#include <iostream>

struct Window
{
	explicit Window( const std::string& title = "Title", float width = 320.0f, 
		float height = 180.0f, bool isVSyncOn = true );

	std::string title;
	float width;
	float height;
	bool isVSyncOn;
};

struct Point2f
{
	Point2f( );
	explicit Point2f( float x, float y );

	friend bool operator>(const Point2f& p1, const Point2f& p2);
	friend bool operator<(const Point2f& p1, const Point2f& p2);
	friend bool operator==(const Point2f& p1, const Point2f& p2);
	friend std::ostream& operator<<(std::ostream& out, const Point2f& point);

	float x;
	float y;
};

bool operator>(const Point2f& p1, const Point2f& p2);
bool operator<(const Point2f& p1, const Point2f& p2);
bool operator==(const Point2f& p1, const Point2f& p2);
std::ostream& operator<<(std::ostream& out, const Point2f& point);

struct Rectf
{
	Rectf( );
	explicit Rectf( float left, float bottom, float width, float height );
	explicit Rectf(const Point2f& bottomLeft, float width, float height);
	
	friend std::ostream& operator<<(std::ostream& out, const Rectf& r);

	Rectf& operator=(const Point2f& bottomLeft);

	float left;
	float bottom;
	float width;
	float height;

};
std::ostream& operator<<(std::ostream& out, const Rectf& r);

struct Color4f
{
	Color4f( );
	explicit Color4f( float r, float g, float b, float a );
	
	float r;
	float g;
	float b;
	float a;
};

struct Circlef
{
	Circlef( );
	explicit Circlef( const Point2f& center, float radius );
	explicit Circlef( float centerX, float centerY, float radius );

	Point2f center;
	float radius;
};


struct Ellipsef
{
	Ellipsef( );
	explicit Ellipsef( const Point2f& center, float radiusX, float radiusY );
	explicit Ellipsef( float centerX, float centerY, float radiusX, float radiusY );

	Point2f center;
	float radiusX;
	float radiusY;
};



