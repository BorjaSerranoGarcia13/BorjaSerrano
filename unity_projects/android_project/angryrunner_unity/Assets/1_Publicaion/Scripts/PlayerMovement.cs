using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerMovement : MonoBehaviour {

  public float mov_speed_;
  public float jmp_speed_;
  public float jmp_boost_;
  public float gravity_;
  public float backwards_speed_mult_;
  public AudioSource sound_;

    public CharacterController controller_;
  private Animator animator_;
  public Vector3 movement_;

  public bool jumping = false;

  void Start() {
    controller_ = gameObject.GetComponent<CharacterController>();
    animator_ = gameObject.GetComponent<Animator>();
  }

  void Update() {
    movement_.x = Input.GetAxis("Horizontal") * mov_speed_;
    animator_.SetFloat("Speed", Mathf.Abs(movement_.x));

    // Determing the look direction in relation to the mouse position
    float look_direction_ = -1.0f;
    float walk_direction_ = -1.0f;

    Vector3 mouse_position = Input.mousePosition;
    mouse_position.z = 10.0f;
    mouse_position = Camera.main.ScreenToWorldPoint(mouse_position);

    if ((mouse_position.x - transform.position.x) > 0.0f) {
      look_direction_ = 1.0f;
    }
    if (movement_.x > 0.0f) {
      walk_direction_ = 1.0f;
    }

    if (look_direction_ != walk_direction_) {
      movement_.x *= backwards_speed_mult_;
    }

    if (controller_.isGrounded) {
      if (Input.GetButton("Jump")) {
        jumping = true;
        if (jumping)
        {
          movement_.y = jmp_speed_;
          animator_.SetBool("isJumping",true);
          sound_.Play();
        }
      }
      else {
        movement_.y = 0.0f;
        animator_.SetBool("isJumping",false);
        jumping = false;
      }
    }
    else {
      if ((controller_.collisionFlags & CollisionFlags.Above) != 0) {
        movement_.y = -gravity_ * Time.deltaTime;
        animator_.SetBool("isJumping",false);
      }
      movement_.y -= (gravity_ - jmp_boost_ * Input.GetAxis("Jump")) * Time.deltaTime;
    }
    controller_.Move(movement_ * Time.deltaTime);
  }
}
