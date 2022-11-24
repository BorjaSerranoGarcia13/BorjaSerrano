#ifndef __BS_PATH_H__
#define __BS_PATH_H__ 1

#include "bs_entity.h"
#include "adt_vector.h"
#include "abgs_memory_manager.h"
#include "vector_2.h"
#include "vector_3.h"
#include "vector_4.h"

#include "matrix_2.h"
#include "matrix_4.h"


const u16 kMaxShapes = 8;
const u16 kCapacityVector = 10;

struct BufferVector {
    u16 head_; /**< head of vector*/
    u16 tail_; /**< tail of vector*/
    u16 capacity_;  /**< number of total capacity*/
    Vector2 vector_[kCapacityVector];
};

class BsPath : public BsEntity {

 public:
   BsPath();
   BsPath(const BsPath& o);
   virtual ~BsPath();

   void init() override;

   void initBuffer();

   void addVertex(const Vector2* vertex);

   /**
 * @brief set the scale
 * @param position value to position
 */
   sf::Vector2f position() override;

   /**
  * @brief set the rotation
  * @param rotation value to rotation
  */
   float rotation() override;

   /**
  * @brief set the scale
  * @param rot value to scale
  */
   sf::Vector2f scale() override; /**<   get the scale*/

    /**
  * @brief set the pos
  * @param rot value to pos
  */
   void set_position(sf::Vector2f pos) override;

   /**
  * @brief set the rot
  * @param rot value to set
  */
   void set_rotation(float rot) override;

   /**
  * @brief set the scale
  * @param rot value to scale
  */
   void set_scale(sf::Vector2f scale) override;

   /**
  * @brief draw the shape
  * @param window to draw
  */
   void draw(sf::RenderWindow& window) override;

   sf::Vector2f position_;
   sf::Vector2f scale_;
   float rotation_;

   Vector3 speed_;
   Vector4 stroke_color_;
   Vector4 fill_color_;
   float solid_color_;

   BufferVector* buffer_vector_ = nullptr;
   sf::ConvexShape convex_;

   // Counter for the factory
   static uint32_t s_total_shapes_; /**<   static counter of all shapes*/

 //private:

};

#endif // __BS_PATH_H__
