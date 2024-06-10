--SCENE:

  -controls:
  (up down etc as the axes you see with the initial orientation, from the original position)
  *key pressed -> action 
  light position:
     o = up
     p = down
     k = away from camera 
     l = towards camera 
     n = towards the right side of the screen
     m = towards the left side of the screen

  light color:
     1 = +Red
     2 = -Red
     3 = +Green
     4 = -Green
     5 = +Blue
     6 = -Red


--ORBIT:

--GAME:
   object-object and plane-object collisions are detected, only linear translations supported
    
    -controls: 
      *wasd as usual
      *jump with spacebar 

   -things to try: 
     *try to push the boxes around. 
     *jump while keeping the spacebar and see what happens.
     *try to land on a box. why can you not stay on top of it?



PREREQUISITES:
assimp
glad
glfw
glm

