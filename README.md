# OfflineRayTracer
An offline ray tracer written in C++

See [here](https://creativerecurrence.wordpress.com/portfolio/offline-ray-tracing/) for examples of this program being used and some more information.

Details of the scene are written in a .txt file and the program generates a .ppm file of the image. 
Run it in the terminal with the input text file as an argument.

RayTracer.cpp is the driver of the program. It reads the input file and creates the scene. It then creates a camera (see Camera.cpp) that does the output to the file.

Camera creates rays for each pixel of the screen and calls the scene's ShadeRay function to get the color for that pixel.

Input files are formatted with multiple lines defining properties of the image and the objects it shows. Each line starts with the name of a property or object followed by values that define it.
See Skybox.txt for an example

"eye" followed by x y z positions of the location of the eye/camera
"viewdir" followed by x y z for a vector defining the direction the eye/camera is pointed at
"updir" followed by x y z for a vector defining the up direction within camera space. Changing this will rotate the camera.
"vfov" followed by a value for the vertical field of view
"imsize" followed by the width and height (in pixels) of the final image
"bkcolor" followed by r g b that defines the color that is drawn when a ray doesnt hit any object

"light" creates a light in the scene. It takes an x y z for the position of the light, followed by a w. Setting w to 0 gives a directional light and setting it to 1 gives a point light. 
  After x y z w there are three parameters for the r g b color of the light.
 
"attlight" creates an attenuated light. This acts the same but gets dimmer the farther from the source your are.
  It takes the same arguments as light ( x y z w r g b ) but adds three parameters for the constant, linear and exponential decay of the light over distance.
  Note that attenuated lights are always point lights so setting w to 0 has no effect.
 
"spotlight" creates a spot light, a directional light that only shines within a specific cone. It takes 10 arguments.
  x y z for the position of the light, dirX dirY dirZ for the direction the light points at, theta for the max angle that the light shines at, and then an r g b for the color of the light.

"attspotlight" likewise adds a constant linear and exponential argument to the normal spotlight arguments

"texture" defines a texture that subsequent objects will use (currently only supported for sphere and triangle).
  It takes one argument that is the file name of the texture.

"mtlcolor" defines the color and material properties of all subsequent objects. Lighting is calculated using a standard blinn phong shading equation.
  It takes 12 arguments, diffR diffG diffB specR specG specB kA kD kS n opacity refraction
  diffR diffG diffB defines the color of the diffuse component while specR specG specB is the specular color.
  kA kD and kS define the strength of the ambient, diffuse and spectular components of the lighting respectively
  n defines how sharp the specular highlight it
  opacity defines how transparent the material is and refraction defines how reflective it is
 
"sphere" has arguments x y z r which define the position and radius of a sphere in the scene
"ellipsoid" has arguments x y z xr yr zr which define the position and axis lengths of an ellipsoid

triangle meshes can be defined using a simplified version of the .obj file format.
