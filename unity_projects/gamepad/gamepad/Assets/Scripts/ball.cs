using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ball : MonoBehaviour
{
    public int playerBall = 0;

    // Start is called before the first frame update
    void Start()
    {
      playerBall = 0;
    }

    void Update()
    {
    }

    private void OnCollisionEnter(Collision other)
    {
      if (other.gameObject.CompareTag("Player1") || other.gameObject.CompareTag("Player2"))
      {
        GetComponent<Rigidbody>().velocity = Vector3.zero;
        GetComponent<Rigidbody>().angularVelocity = Vector3.zero;
      }
    }

    private void OnTriggerEnter(Collider other)
    {
      if (other.gameObject.CompareTag("Player1") && playerBall!= 1)
      {
        playerBall = 1;
        GetComponent<Rigidbody>().velocity = Vector3.zero;
        GetComponent<Rigidbody>().angularVelocity = Vector3.zero;
        transform.parent = transform.parent = other.transform;
      }
      if (other.gameObject.CompareTag("Player2") && playerBall!= 2)
      {
        playerBall = 2;
        GetComponent<Rigidbody>().velocity = Vector3.zero;
        GetComponent<Rigidbody>().angularVelocity = Vector3.zero;
        transform.parent = other.transform;
      }
    }
}
