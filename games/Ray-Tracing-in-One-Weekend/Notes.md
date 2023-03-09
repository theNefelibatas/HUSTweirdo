# Notes

[Ray Tracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html)

[RayTracing/raytracing.github.io: Main Web Site (Online Books)](https://github.com/RayTracing/raytracing.github.io)

## Intro by chatGPT

here is a more detailed breakdown of each step involved in building a ray tracer:
  
1. **Set up the environment:** You'll need to create a new project in your preferred programming language and IDE. You may need to add any necessary libraries and dependencies for vector and matrix calculations. Initialize an image buffer of a specified resolution (e.g., 800 x 600) and set up a camera position, which includes the camera's position, orientation, and field of view.
  
2. **Create ray class:** A ray is a fundamental component of ray tracing. It represents a line that starts at an origin point and extends in a specific direction. You'll need to define a ray class that stores the origin and direction of a ray.
  
3. **Create vector class:** A vector is a mathematical object that represents a point in 3D space with x, y, and z coordinates. You'll need to define a vector class that can perform basic vector operations, such as addition, subtraction, dot product, cross product, and normalization. This class will be used for calculating intersection points, direction vectors, and more.
  
4. **Create a simple sphere:** A sphere is a basic geometric object that is commonly used in ray tracing. You'll need to define a sphere class that stores the center point and radius of a sphere. You'll also need to implement a method that tests whether a ray intersects with the sphere.
  
5. **Render a simple image:** Using the camera and sphere classes, render a simple image of a sphere. This step involves casting rays from the camera position and testing whether they intersect with the sphere. For each intersection point, calculate the color of the pixel by applying shading based on the angle of incidence of the light source.
  
6. **Add surface normals:** A surface normal is a vector that is perpendicular to the surface of an object at a specific point. You'll need to calculate the surface normal of the sphere at each intersection point with the ray. This information will be used for shading calculations and other operations.
  
7. **Add shading:** Shading is the process of determining the color of a pixel based on the object's surface normal and the angle of incidence of the light source. You'll need to implement a shading algorithm that takes into account the surface normal of the sphere, the direction of the light source, and any other relevant factors.
  
8. **Add multiple objects:** To create more complex scenes, you'll need to add multiple objects to the scene. This can include planes, boxes, or additional spheres. You'll need to implement intersection tests and shading calculations for each object.
  
9. **Add anti-aliasing:** Anti-aliasing is a technique used to reduce jagged edges and improve image quality. You'll need to implement anti-aliasing by casting multiple rays for each pixel and averaging the colors of the resulting intersections.
  
10. **Add diffuse materials:** A diffuse material is a type of material that scatters light in all directions, resulting in a matte appearance. You'll need to implement a diffuse material for each object in the scene.
  
11. **Add reflections:** Reflections are a fundamental component of ray tracing. They occur when a ray intersects with a reflective surface and bounces off at an angle equal to the angle of incidence. You'll need to implement reflection calculations for each object in the scene.
  
12. **Add refraction:** Refraction is the bending of light as it passes through a material with a different refractive index. You'll need to implement refraction calculations for each object in the scene that has a transparent or translucent material.
  
13. **Add indirect lighting:** Indirect lighting is the light that bounces off objects and affects the color of other objects in the scene. This is a complex process that involves casting rays from each point on the surface of an object and tracing them until they hit another object, which then affects the color of the original point. This step involves implementing a technique called path tracing, which is a Monte Carlo method for approximating the solution to a problem by using random sampling.
  
14. **Optimize the ray tracer:** As the scene becomes more complex and the number of objects and rays increase, the rendering time can become prohibitively slow. You'll need to optimize the ray tracer by implementing techniques such as spatial partitioning, where the scene is divided into smaller sub-regions to reduce the number of intersection tests needed.
  
15. **Add textures:** Textures are patterns or images applied to an object's surface to give it a more realistic appearance. You'll need to implement texture mapping, which involves mapping a texture onto the surface of an object based on its UV coordinates.
  
16. **Implement motion blur:** Motion blur is a technique used to simulate the effect of motion in a scene by blurring the image in the direction of motion. This step involves calculating the position of each object at different times and using that information to create a blur effect in the rendered image.
  
17. **Add global illumination:** Global illumination is a technique used to simulate the effect of light bouncing multiple times around a scene, creating complex lighting effects such as color bleeding and ambient occlusion. This step involves implementing a technique called photon mapping, which is a global illumination algorithm that uses a precomputed map of photons to calculate the lighting in the scene.
  
18. **Implement depth of field:** Depth of field is a technique used to simulate the effect of a camera's focus, where objects in the foreground or background of the scene are blurred. This step involves calculating the distance from the camera to each object in the scene and using that information to simulate the depth of field effect in the rendered image.
  
19. **Add volumetric effects:** Volumetric effects are used to simulate the interaction of light with particles in a medium such as smoke or fog. This step involves implementing a technique called ray marching, which is a method for tracing rays through a volume of particles and calculating the color and opacity of the resulting intersections.
  
20. **Add motion graphics:** Motion graphics are animated graphics that use visual effects and motion to communicate a message or tell a story. This step involves animating the objects in the scene over time, using techniques such as keyframe animation or procedural animation.
  
These are just some of the steps involved in building a ray tracer, and the complexity of each step can vary depending on the desired level of realism and functionality. However, following the steps outlined in the how-to guide mentioned earlier should give you a good foundation for building a simple but effective ray tracer.

## PPM

GIMP - a free open-source image editing software that can open and edit PPM format files.

[GIMP - Downloads](https://www.gimp.org/downloads/)



```
P3
# P3 colors are in ASCII
3 2
# 3 columns and 2 rows
255
# max color
255 0 0
0 255 0
0 0 255
255 255 0
255 255 255
0 0 0
# RGB triplets
```
## RGB

RGB is a commonly used color representation format, which refers to three primary colors: red (R), green (G), and blue (B). By combining different intensities of these three colors, various colors can be produced. In the RGB color space, each color's value range is 0-255 (8-bit unsigned integer), representing the intensity of the color.

For example, pure red can be represented as RGB(255, 0, 0), pure green can be represented as RGB(0, 255, 0), pure blue can be represented as RGB(0, 0, 255), while white can be represented as RGB(255, 255, 255), and black can be represented as RGB(0, 0, 0).

In computer graphics, the RGB format is one of the most commonly used image formats, and it is often used for storing, transmitting, and displaying images. When generating images using computer programs, the RGB format can be used to describe the color value of each pixel. For example, when generating PPM format image files, RGB format can be used to represent the color value of each pixel.

## Vector3

向量库包含一个 vec3 结构体，表示一个三维向量，包含三个 double 类型的成员变量 x、y、z，分别表示向量在三个方向上的分量。

在这个向量库中，我们使用了一些函数来操作向量，这些函数包括：

vec3_init，用于初始化向量的值；

vec3_negate，用于求向量的负值；

vec3_add，用于将两个向量相加；

vec3_multiply，用于将向量数乘一个标量；

vec3_divide，用于将向量除以一个标量；

vec3_length_squared，用于计算向量的长度的平方；

vec3_length，用于计算向量的长度。


