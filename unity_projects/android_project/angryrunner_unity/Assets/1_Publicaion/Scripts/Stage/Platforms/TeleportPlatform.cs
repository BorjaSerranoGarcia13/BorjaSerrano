using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TeleportPlatform : MonoBehaviour
{
    CharacterController player;
    public GameObject teleport;
    Vector3 new_place;

    void Start()
    {
        player = GameObject.Find("Player").GetComponent<CharacterController>();
        new_place = teleport.transform.position - transform.position;
    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.tag == "player")
        {
            player.Move(new_place);   
        }
    }

}
