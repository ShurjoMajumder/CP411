# A4 Report

Author: Shurjo Majumder  
Date: 2024-11-05 

Check [readme.txt](readme.txt) for course work statement and self-evaluation. 
  
## Q1 Culling, Lighting, Shading (description)


### Q1.1 Concepts of culling

1. What is the difference between culling and clipping?

: Culling is a process where geometry that's not visible from the camera is discarded to save processing time. Clipping is a process that removes parts of primitives that are outside the camera's view volume (clipping against the six faces of the view volume).

: Culling is also applied to fragments that fall outside the view space.

2. What is the difference between object precision and image precision hidden surface removal methods? Give an example of each method.

: Object Precision: Decides visibility based on entire objects' positions in 3D space. Example: BSP Tree (Binary Space Partitioning), which splits and sorts objects to determine what’s in front.

: Image Precision: Decides visibility at each pixel on the screen by checking depth. Example: Z-buffer, which keeps track of the closest depth at each pixel and only renders that pixel.

### Q1.2 Culling computing

Given:
* Eye position at E(3, 2, 2), and
* Reference (look at) point at R(0, 0, 0).

1. Compute to determine if triangle P1(1,0,0)P2(0,1,0)P3(0, 0, 1) is a back face.
: Assuming Counter-clockwise winding, then the triangle is a back face. However, if one assumes clockwise vertex winding, then it is a front face.
: If using the normals of the face to determine the direction the face is facing, then there is not enough information.

2. Compute the depth (z-value) of the above triangle.
: Z-up co-ordinates: P1: 0, P2: 1, P3: 0
: Y-up co-ordinates: P1: 0, P2: 0, P3: 1

### Q1.3 Concepts of lighting and shading

1. What does a color model do? Give the names of three color models.
: A colour model is a mathematical representation of colour.
: Examples: RGBA, RGBA, ARGB, BGR, HSV, CMYK

2. What does a light source model determine? Give the names of three light source models.
: A light source model determines how light interacts with a 3D scene to create realistic shading.
: Examples: Ambient Light, Point Light, Directional Light

3. What does a reflection model determine? Give the names of three reflection models.
: A reflection model simulates how various materials reflect light.
: Examples: Phong Reflection, Lambertian Reflection, Blinn-Phong Reflection.

4. What does a shading model determine? Give the names of three shading models.
: A shading model determines how colours and lighting are applied across the surfaces of 3D scenes to create depth/texture. It's similar to a reflection model, however also considers the object's innate colour.
: Examples: Flat Shading, Gouraud Shading, Phong Shading

### Q1.4 Lighting computing

Given:

* Eye position at E(3, 2, 2), point light position at L(1, 2, 4) with light intensity 0.8,
* Triangle P1(1,0,0)P2(0,1,0)P3(0, 0, 1), and surface diffusion rate 0.4 for red color.

Compute the simple diffusion reflection intensity of red color at the center of the triangle. (Use the simple diffusion reflection formula in slide 10 of lecture 13 (lighting).

Write your solution on paper, and take a photo, save it as a4q1.4.png to the images folder and link to the a4_report.md

Centre of triangle.

$$
\begin{aligned}
C &= \left( \frac{x_1+x_2+x_3}{3},\frac{y_1+y_2+y_3}{3},\frac{z_1+z_2+z_3}{3} \right) \\
C &= \left( \frac{1}{3},\frac{1}{3},\frac{1}{3} \right)
\end{aligned}
$$

Normal of the triangle.

$$
\begin{aligned}
\vec{P_1P_2} &= (-1, 1, 0) \\
\vec{P_1P_3} &= (-1, 0, 1) \\
\vec{N} &= |\vec{P_1P_2} \times \vec{P_1P_3}| \\
\vec{N} &= \left( \frac{1}{\sqrt{3}}, \frac{1}{\sqrt{3}}, \frac{1}{\sqrt{3}} \right)
\end{aligned}
$$

Light direction.

$$
\vec{L} = |L - C| = \left( \frac{2}{5\sqrt{6}}, \frac{5}{5\sqrt{6}}, \frac{11}{5\sqrt{6}} \right)
$$

Diffuse reflection intensity.

$$
\begin{aligned}
I_{\text{diffuse}} &= I_L k_d ( \vec{L} \cdot \vec{N} ) \\
I_{\text{diffuse}} &= 0.8 \cdot 0.4 \cdot \frac{3\sqrt{2}}{5} \\
I_{\text{diffuse}} &= 0.192\sqrt{2}
\end{aligned}
$$

## Q2 OpenGL Culling, Lighting, Shading (lab practice)

### Q2.1 Hidden surface removal 

Complete? Yes or No 

<!--If you answer Yes, insert one or more screenshot images to show the completion.-->

![Image caption](images/demo.png)

<!-- If No, add a short description to describe the issues encountered.-->

### Q2.2 Lighting and shading 

Complete? Yes or No 

<!--If you answer Yes, insert one or more screenshot images to show the completion.-->

![Image caption](images/demo.png)

<!-- If No, add a short description to describe the issues encountered.-->

### Q2.3 Animation 

Complete? Yes or No 

<!--If you answer Yes, insert one or more screenshot images to show the completion.-->

![Image caption](images/demo.png)

<!-- If No, add a short description to describe the issues encountered.-->


## Q3 SimpleView2 Culling, Lighting, Shading (programming)

### Q3.1 Culling

Complete? Yes or No 

<!--If you answer Yes, insert one or more screenshot images to show the completion. -->

![Image caption](images/demo.png)

<!--If No, add a short description to describe the issues encountered.-->


### Q3.2 Lighting

Complete? Yes or No 

<!--If you answer Yes, insert one or more screenshot images to show the completion. -->

![Image caption](images/demo.png)

<!--If No, add a short description to describe the issues encountered.-->


### Q3.3 Shading

Complete? Yes or No 

<!--If you answer Yes, insert one or more screenshot images to show the completion. -->

![Image caption](images/demo.png)

<!--If No, add a short description to describe the issues encountered.-->


### Q3.4 Animations

Complete? Yes or No 

<!--If you answer Yes, insert one or more screenshot images to show the completion. -->

![Image caption](images/demo.png)

<!--If No, add a short description to describe the issues encountered.-->

**References**

1. CP411 a4
2. Add your references if you used any. 
