using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Compacter : MonoBehaviour
{

    public float speed;

    public delegate void EnvairomentCompacted(GameObject envairoment);
    public event EnvairomentCompacted OnEnvairomentCompacted;

    void FixedUpdate() {
        GetComponent<Rigidbody>().MovePosition(gameObject.transform.position + gameObject.transform.forward * speed * Time.fixedDeltaTime);
    }

    void OnTriggerEnter(Collider other) {
        if (other.gameObject.CompareTag("Player")) {
            other.gameObject.GetComponent<LifeController>().TakeDamage(9999);
        }
    }

    void OnTriggerExit(Collider other) {
        // if (other.gameObject.CompareTag("Enviroment") || other.gameObject.CompareTag("Respawn")) {
            if (OnEnvairomentCompacted != null) {
                OnEnvairomentCompacted(other.gameObject);
            }
        // }
    }

    void OnTriggerStay(Collider other) {
        if (other.gameObject.CompareTag("Left Curve") || other.gameObject.CompareTag("Right Curve")) {
            if ((gameObject.transform.position - other.bounds.center).magnitude <= 4.3f) {
                Vector3 rotation = Vector3.up * (other.gameObject.CompareTag("Left Curve") ? -90 : 90);
                gameObject.transform.Rotate(rotation);
                gameObject.transform.position = new Vector3(other.bounds.center.x, gameObject.transform.position.y, other.bounds.center.z);
                Debug.Log(rotation);

                if (OnEnvairomentCompacted != null) {
                    OnEnvairomentCompacted(other.gameObject);
                }

            }

        }
    }
}
