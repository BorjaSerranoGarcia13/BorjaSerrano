using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DetectCageTrap : MonoBehaviour
{

    GameObject player;
    public Rigidbody cage;

    void Start()
    {
        player = GameObject.FindWithTag("Player");
    }

    void OnTriggerEnter(Collider other)
    {
        if (other.tag == "Player")
        {
            cage.useGravity = true;
        }
    }

}
