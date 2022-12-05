using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class JumpPlatform : MonoBehaviour
{
    GameObject player;
    public float jumpForce = 10.0f;

    void Start()
    {
      player = GameObject.FindWithTag("Player");
    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.tag == "Player")
        {
            player.GetComponent<Rigidbody>().velocity = new Vector3(0, jumpForce, 0);
        }
    }

}
