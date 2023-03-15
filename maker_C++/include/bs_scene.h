/**
 * Author: Borja Serrano <serranoga@esat-alumni.com>
 * Filename: bs_backgorund.cc
 *
 * Implementation: background class
 */

 #ifndef __BS_SCENE_H__
 #define __BS_SCENE_H__ 1

 #include <esat/window.h>
 #include <esat/draw.h>
 #include <esat/input.h>
 #include <esat/time.h>
 #include <esat/sprite.h>
 #include <ESAT_extra/imgui.h>

 #include <iostream>
 #include <fstream>

 #include "bs_game_manager.h"

/**
/* Class scene 
/* manage evrything from the scene, gameplay
*/
class bsScene {
 public:
   bsScene(); /**<  Constructor used to initilizate the class  */

   void IMGUI(); /**<  Cfunction to use imgui */
   void playGame(); /**<  function that allows the logical of the gameplay  */

   void controls(); /**<  function that allows the controls of the gameplay  */

   void addCube(); /**<  function to enabled_ the cubes  */
   void deleteCube(); /**<  function to desabled_ the cubes  */

   void drawAllCubes(); /**<  function to draw all the cubes  */

   void editionMode(); /**<  function to enter in the edition mode  */
   void initEditionMode(); /**<  function to init the edition mode, its called after change size of game  */

   //* checks the colissions
    /*
    \*param the x, y height and width of 2 quads
    \*param return true if there is a colission
    \*param the size of label
*/
   bool CheckRectangleColision(float x, float y, float width, float height, float x2, float y2, float width2, float height2);

   void playMode(); /**<  function to enter in the play mode  */

   void allElements(); /**<  function to take the direction of all objetcs and give them to pointer of pointer  */

   float mouse_pos_x_; /**<  var to keep the mouse position  */
   float mouse_pos_y_; /**<  var to keep the mouse position  */
   bool create_cube_; /**<  used to enabled cubes */
   bool delete_cube_; /**<  used to disabled cubes */

   bool player_fall_; /**<  used to know logical of game */
   bool player_mov_right_; /**<  used to know logical of game */
   bool player_mov_left_; /**<  used to know logical of game */
   bool player_jump_; /**<  used to know logical of game */
   float player_jump_distance_; /**<  used to know logical of game */

   float color_draw_[4]; /**<  used to change iin real time the color of objects */

   void drawModePlay(); /**<  draw the mode play */

   void addBackground(); /**<  add the background to the game */
   void drawBackground(); /**<  draw the background to the game */


   bool order_by_tag_; /**<  var to know if its neccesary to order by tag the objects in IMGUI */

 };

#endif // __BS_SCENE_H__
