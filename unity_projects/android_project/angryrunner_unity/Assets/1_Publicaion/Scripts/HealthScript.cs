using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class HealthScript : MonoBehaviour {

  public float cur_health_;
  public float max_health_;

  void Start () {
    cur_health_ = max_health_;
  }

  public void Heal(float amount) {
    cur_health_ += amount;
    if(cur_health_ > max_health_) {
      cur_health_ = max_health_;
    }
  }

  public void Damage(float amount) {
    cur_health_ -= amount;
    if(cur_health_ <= 0) {
      if(gameObject.CompareTag("Enemy"))
      {
        DieEnemy();
      }
      else
      {
        Die();
      }

    }
  }

  public void Die() {
    SceneManager.LoadScene("DeathScene");
    gameObject.SetActive(false);
  }

  void DieEnemy() {
    Animator animator = GetComponent<Animator>();
    animator.SetBool("dead", true);
  }
}
