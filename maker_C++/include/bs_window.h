
/**
 * Author: Borja Serrano <serranoga@esat-alumni.com>
 * Filename: bs_backgorund.cc
 *
 * Implementation: background class
 */

 #ifndef __BS_WINDOW_H__
 #define __BS_WINDOW_H__ 1

/**
/* Class window 
/* Used to open a window
*/
class bsWindow {

 public:
 //* Init the window
    /*
    \*param a int for the width od window
    \*param a int for the height od window
*/
  void init(unsigned int width, unsigned int height);
  void frame(); /**<  Constructor used to initilizate the class  */
  void destroy(); /**<  Destroy the window  */
  bool isOpened(); /**<  return if window is opened  */

  /* Set the mouse visibility
    /*
    \*param a bool argument to set it
*/
  void setMouseVisibility(bool visible);

  unsigned int height(); /**<  variable to set the hegiht  */
  unsigned int width(); /**<  variable to set the width  */

};

#endif // __BS_WINDOW_H__
