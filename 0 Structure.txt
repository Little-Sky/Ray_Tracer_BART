Design briefing:
    - All function applied on a specific structure are implemented inside their struct file.
    - BFS search is used for tracking the rays in the hope that the pixel's light intensity is increased faster, so that the remaining ray contributes less and hit the terminate threshold faster than DFS.



Step1: build a ray tracer for one frame (given all objects positions)
struct:
    1 Point:
        - Basic 3D geometry operations
        - Vector & Color:    
    2 Ray:        position, direction, light color, next intersection
        - Light source is a special ray (all directions / v = {0,0,0})
    3 Material:   ...
    4 Polygon:
        - Polygon and its intersection with ray

    5 BVH_Node:       bbox and BVH tree construction
    6 Camera:
        - Jittered samples as viewed from camera

Step2: Figure out how to read from .aff ... 
       AND use transformation to create all scenes.

