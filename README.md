# miniRT

## 🔆 Project Overview

miniRT is an introduction to the fascinating world of ray tracing, a rendering technique that produces highly realistic computer-generated images by simulating the physical behavior of light. Unlike traditional rasterization methods used in most real-time graphic engines, ray tracing calculates the path of individual light rays as they interact with objects in a 3D scene.

This project implements a basic ray tracer from scratch using C and the miniLibX library, demonstrating fundamental 3D graphics concepts and mathematical principles. Despite its "mini" designation, it creates impressive visual results by accurately calculating shadows, lighting, and object intersections.

![Ray Tracing Example](images/5.8.png)

## 🎯 Features

### Core Rendering Capabilities
- **Ray Tracing Engine**: Models light paths and calculates intersections with geometric objects
- **Scene Parsing**: Reads and processes scene descriptions from .rt files
- **Window Management**: Fluid window interaction using miniLibX
- **Image Export**: Rendered scenes can be displayed in a window

### Geometric Objects
- **Spheres**: Perfect spherical objects with configurable position and diameter
- **Planes**: Infinite flat surfaces with defined orientation
- **Cylinders**: Cylindrical objects with configurable position, orientation, diameter, and height

### Lighting System
- **Ambient Lighting**: Basic scene illumination to prevent complete darkness
- **Diffuse Reflection**: Light reflection based on surface orientation
- **Hard Shadows**: Objects block light, creating realistic shadow areas

### Transformations
- **Translation**: Move objects, lights, and cameras in 3D space
- **Rotation**: Rotate objects and cameras to change orientation

## 💻 Technical Implementation

### Ray Tracing Algorithm

The ray tracing process follows these steps:
1. For each pixel in the output image, cast a ray from the camera
2. Calculate intersections with all objects in the scene
3. Find the closest intersection point
4. Calculate lighting at the intersection point considering:
   - Ambient light contribution
   - Direct light contribution with shadow checks
5. Determine the final color based on object color and lighting

### Mathematical Foundations

The implementation involves several key mathematical concepts:
- **Vector Operations**: Dot product, cross product, normalization
- **Line-Object Intersections**: Analytical solutions for rays intersecting with:
  - Spheres (quadratic equation)
  - Planes (algebraic solution)
  - Cylinders (quadratic equation with constraints)
- **Color Calculation**: RGB color manipulation and light intensity factors

### Scene Description Format

Scenes are defined in .rt files with a specific format:
- **A**: Ambient lighting (ratio and color)
- **C**: Camera (position, orientation, field of view)
- **L**: Light source (position, brightness)
- **sp**: Sphere (center coordinates, diameter, color)
- **pl**: Plane (point, normal vector, color)
- **cy**: Cylinder (center, axis, diameter, height, color)

## 🚀 Usage

### Prerequisites

- GCC/Clang compiler
- Make
- X11 development libraries (for miniLibX)

### Installation

```bash
# Clone the repository
git clone https://github.com/Melis-Pablo/minirt.git
cd minirt

# Compile the program
make
```

### Running the Program

```bash
# Run with a specific scene file
./miniRT scenes/example.rt
```

### Controls

| Key/Action | Function |
|------------|----------|
| ESC | Exit program |
| Click window's red cross | Exit program |

### Example Scene File

```
# Simple scene with basic shapes
A 0.2 255,255,255        # Ambient light
C -50,0,20 0,0,1 70      # Camera
L -40,0,30 0.7 255,255,255  # Light source
pl 0,0,0 0,1.0,0 255,0,225  # Floor plane
sp 0,0,20 20 255,0,0     # Red sphere
cy 50.0,0.0,20.6 0,0,1.0 14.2 21.42 10,0,255  # Blue cylinder
```

## 🧠 Technical Challenges and Solutions

### Ray-Object Intersection

The most complex part of the implementation was calculating ray intersections with various geometric shapes:

- **Spheres**: Used the quadratic formula to find intersection points between a ray and a sphere, checking if the discriminant is positive (indicating a hit)
- **Planes**: Calculated the dot product between the ray direction and plane normal to determine intersections
- **Cylinders**: Implemented a more complex quadratic equation solution that accounts for the limited height of cylinders

### Performance Optimization

Several optimizations were implemented to improve rendering speed:
- **Early Ray Termination**: Stop calculations once an opaque object is hit
- **Bounding Box Checks**: Quick rejection tests before detailed intersection calculations
- **Vector Normalization Caching**: Pre-compute normalized vectors when possible

### Memory Management

Careful memory management practices were followed throughout the implementation:
- **Dynamic Memory Allocation**: Proper allocation and freeing of memory for scene objects
- **Error Handling**: Graceful error detection and cleanup to prevent memory leaks

## 📝 Learning Outcomes

This project provided in-depth experience with:

- **3D Mathematics**: Practical application of vectors, matrices, and geometric principles
- **Ray Tracing Algorithm**: Implementation of a fundamental computer graphics technique
- **Memory Management**: Proper handling of complex data structures in C
- **File Parsing**: Creating a robust scene description parser
- **Computer Graphics**: Understanding how images are synthesized from 3D scene data
- **Optimization Techniques**: Balancing quality and performance in rendering

## 🎨 Gallery

![Sphere Example](images/5.1.png)
*A sphere with diffuse lighting*

![Cylinder Example](images/5.2.png)
*A cylinder with proper lighting and shading*

![Multiple Objects Scene](images/5.4.png)
*A scene with multiple objects demonstrating ray tracing capabilities*

![Shadows Example](images/5.6.png)
*Hard shadows demonstrating light obstruction*

## ⚠️ Note

For detailed project requirements, see the [minirt.md](minirt.md) file.

---

*This project is part of the 42 School Common Core curriculum.*