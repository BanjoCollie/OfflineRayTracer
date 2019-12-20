# CMakeList.txt : CMake project for RayTracer, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (RayTracer 
	"Camera.cpp"
	"Camera.h"
	"Color.h"
	"Ellipsoid.cpp"
	"Ellipsoid.h"
	"Light.h"
	"Material.h"
	"Ray.h"
	"RayCollision.h"
	"RayTracer.cpp"
	"RayTracer.h"
	"Scene.cpp"
	"Scene.h"
	"Shape.h"
	"Sphere.cpp"
	"Sphere.h"
	"SpotLight.h"
	"Texture.h"
	"Triangle.cpp"
	"Triangle.h"
	"Vector2.h"
	"Vector3.cpp"
	"Vector3.h"
	"Vector4.cpp"
	"Vector4.h"
)
