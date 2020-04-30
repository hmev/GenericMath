#pragma once

// Config.h
// Gather basic definitions for high precision calculation

#define NameSpace_Math_Begin \
	namespace math {

#define NameSpace_Math_End \
	};

NameSpace_Math_Begin

/// 
/// \brief An "infinite" small quantity, as infinite as the precision allows.
/// Please don't use this quantity directly. Instead, use macros below.
///  
#define DIFF 1e-5

/// 
/// \brief Check by an open interval, i.e., |x-y| < DIFF
/// 
#define Equal(x, y)		(std::fabs((x) - (y)) < DIFF)
#define Zero(x)			(std::fabs(x) < DIFF)
#define Positive(x)		((x) >= DIFF)
#define Negative(x)		((x) <= -DIFF)
#define Less(x, y)		((y) - (x) >= DIFF)
#define More(x, y)		((x) - (y) >= DIFF)

/// 
/// \brief An open interval, i.e., m in (x, y).
/// 
#define Inside(m,x,y)	((m) - (x) >  DIFF && (y) - (m) >  DIFF)

/// 
/// \brief An closed interval, i.e., m in [x, y].
/// 
#define Between(m,x,y)	((m) - (x) > -DIFF && (y) - (m) > -DIFF)

#define PI   3.14159265
#define DEG2RAD(deg)	(deg / 180.0 * PI)
#define RAD2DEG(rad)	(rad * 180.0 / PI)

NameSpace_Math_End