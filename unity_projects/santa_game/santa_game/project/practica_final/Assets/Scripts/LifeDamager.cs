using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LifeDamager : MonoBehaviour {

    public List<string> targets;
    public int damage;

    private void OnCollisionEnter(Collision other) {
        bool targeted = false;
        for (int i = 0; i < targets.Count && !targeted; ++i) {
            if (other.gameObject.CompareTag(targets[i])) {
                LifeController controller = other.gameObject.GetComponent<LifeController>();
                if (controller != null) {
                    controller.TakeDamage(damage);
                }
            }
        }
    }

    private void OnTriggerEnter(Collider other) {
        bool targeted = false;
        for (int i = 0; i < targets.Count && !targeted; ++i) {
            if (other.gameObject.CompareTag(targets[i])) {
                LifeController controller = other.gameObject.GetComponent<LifeController>();
                if (controller != null) {
                    controller.TakeDamage(damage);
                }
            }
        }
    }

}
