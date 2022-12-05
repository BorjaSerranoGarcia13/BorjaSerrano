using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DetectCageTrap : MonoBehaviour
{
    CharacterController player;
    public Rigidbody cage;

    void Start()
    {
        player = GameObject.Find("Player").GetComponent<CharacterController>();
    }

    void OnTriggerEnter(Collider other)
    {
        if (other == player)
        {
            cage.useGravity = true;
        }
    }
}
