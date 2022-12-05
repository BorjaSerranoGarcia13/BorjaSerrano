using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LanceTrap : MonoBehaviour
{
    CharacterController player;

    void Start()
    {
        player = GameObject.Find("Player").GetComponent<CharacterController>();
    }

    void OnTriggerEnter(Collider other)
    {
        if (other == player)
        {
            
        }
    }
}
