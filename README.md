# Introduction

Here's a generic math library for scientific computation as base layer. 
It tends to use advance algebra/geometry concept to build up the data structure, and as a sequence, making variables and dimensions as flexible as possible. 

# What included

Signature: 
- [x] Done and Passed Tests
- [ ] On-going

Basic Structures:
- [x] Complex
- [x] Vector
- [x] Matrix
- [x] Index
- [x] IndexD
- [x] Array
- [ ] Tensor

Generic Geometry:
- [x] Coordinate System
- [x] Point
- [x] Plane
- [ ] Curve
- [ ] Quadratic

NonGeneric Geometry:
- [x] Segment
- [x] Line
- [ ] Circle
- [ ] Surface

Parametric Functions:
- [ ] Generic Parametric Function
- [ ] Polygon Function
  
# Features

## NumTrait

This library contains an automatic type promotion from integer to float, and from 32 byte number to 64 byte number.
```
class TraitPromoter;
```
Example:
```
Vector3<int> v1(0,0,0);
Vector3<float> v2(0,0,0);

auto v3 = v1 + v2; // v3 is Vector3<double>
```

# Use this Library

Download the code and include "Math.hpp" in your code. This header would include most type alias for easy use. 

```
#include <Math/Math.hpp>

var x = Vector2d(0,0);
```

# Feedbacks

Welcome to raise up an issue or send email with me. 
Mail: hmev@outlook.com

