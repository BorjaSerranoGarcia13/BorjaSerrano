using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SmoothCameraFollow : MonoBehaviour {

  public float horizontal_threshold_;
  public float horizontal_offset_;
  public float vertical_threshold_;
  public float vertical_offset_;

  public Transform target_;

  void Start() {
    if (target_ == null) {
      target_ = GameObject.Find("Player").GetComponent<Transform>();
    }
  }

  void Update() {
    Vector3 viewPos = Camera.main.WorldToViewportPoint(target_.position);

    bool dirty = false;

    if (viewPos.x > (1.0f - horizontal_threshold_)) {
        viewPos.x = (1.0f - horizontal_threshold_);
        dirty = true;
    }

    if (viewPos.x < horizontal_threshold_) {
        viewPos.x = horizontal_threshold_;
        dirty = true;
    }

    if (viewPos.y < vertical_threshold_) {
        viewPos.y = vertical_threshold_;
        dirty = true;
    }

    if (viewPos.y > (1.0f - vertical_threshold_)) {
        viewPos.y = (1.0f - vertical_threshold_);
        dirty = true;
    }

    if (dirty) {
        // figure out how much the camera needs to move so that the player will be at the updated viewport location
        Vector3 offset = target_.position - Camera.main.ViewportToWorldPoint(viewPos);
        offset.x += horizontal_offset_;
        offset.y += vertical_offset_;
        Camera.main.transform.position += offset;
    }
  }
}
