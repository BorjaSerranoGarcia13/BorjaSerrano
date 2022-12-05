using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LifeController : MonoBehaviour {

    public delegate void DamageTaken(int life, int damage);
    public event DamageTaken OnDamageTaken;

    [SerializeField]
    private int life;
    [SerializeField]
    private float timeBetweenDamage = 3.0f;
    private float lastDamagedTime;

    private void Start() {
        lastDamagedTime = Time.time - timeBetweenDamage;
    }

    public void TakeDamage(int damage) {
        if (Time.time >= lastDamagedTime + timeBetweenDamage) {
            life = Mathf.Clamp(life - damage, 0, life);
            lastDamagedTime = Time.time;
            if (OnDamageTaken != null) {
                OnDamageTaken(life, damage);
            }

            if (life <= 0) {
                gameObject.SetActive(false);
            }
        }
    }

    public int GetLife() {
        return life;
    }
}
