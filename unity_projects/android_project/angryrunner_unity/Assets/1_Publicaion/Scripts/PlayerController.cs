using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController : MonoBehaviour {

  public float fire_rate_;
  public float mana_cost_;
  public float melee_range_;
  public float fireball_damage_;
  public float melee_damage_;
  public AudioSource sound_;

  public Texture2D cursor_;
  public CursorMode cursorMode_ = CursorMode.Auto;
   public Vector2 hotSpot_ = Vector2.zero;

  private float cooldown_;
  private HealthScript health_;
  private Animator animator_;
  private GameObject fireball_;
  private float look_direction_;


  void Start() {
    health_ = gameObject.GetComponent<HealthScript>();
    animator_ = gameObject.GetComponent<Animator>();
    cooldown_ = fire_rate_* 0.99f;
    fireball_ = (GameObject)Resources.Load("Prefabs/Fireball", typeof(GameObject));
    Cursor.SetCursor(cursor_, hotSpot_, cursorMode_);

  }

  void Update() {
    // Determing the look direction in relation to the mouse position
    Vector3 mouse_position = Input.mousePosition;
    mouse_position.z = 10.0f;
    mouse_position = Camera.main.ScreenToWorldPoint(mouse_position);

    if ((mouse_position.x - transform.position.x) > 0.0f) {
      look_direction_ = 1.0f;
    }
    else {
      look_direction_ = -1.0f;
    }

    // Pivot to face the mouse position
    Vector3 rotation = Vector3.zero;
    rotation.y = look_direction_ * 90.0f + 269.99f;
    transform.rotation = Quaternion.Euler(Vector3.Lerp(transform.rotation.eulerAngles,rotation, 5.0f * Time.deltaTime));
    }
}
