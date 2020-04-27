#pragma once

// Config.h
// Gather basic definitions for high precision calculation

#define NameSpace_Math_Begin \
	namespace math {

#define NameSpace_Math_End \
	};

NameSpace_Math_Begin

#define DIFF 1e-5												// Do not suggest to use this directly.
#define PI   3.14159265

#define Equal(x, y)		(std::fabs((x) - (y)) < DIFF)
#define _Zero(x)			(std::fabs(x) < DIFF)
#define Positive(x)		((x) >= DIFF)
#define Negative(x)		((x) <= -DIFF)
#define Less(x, y)		((y) - (x) >= DIFF)
#define More(x, y)		((x) - (y) >= DIFF)
#define Inside(m,x,y)	((m) - (x) >  DIFF && (y) - (m) >  DIFF)
#define Between(m,x,y)	((m) - (x) > -DIFF && (y) - (m) > -DIFF)

#define DEG2RAD(deg)	(deg / 180.0 * PI)
#define RAD2DEG(rad)	(rad * 180.0 / PI)

NameSpace_Math_End