using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TeleportPlatform : MonoBehaviour
{
    GameObject player;
    public GameObject teleport;
    Vector3 new_place;

    void Start()
    {
        player = GameObject.FindWithTag("Player");
        new_place = teleport.transform.position;
    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.tag == "Player")
        {
            player.transform.position = new_place;
        }
    }

}
