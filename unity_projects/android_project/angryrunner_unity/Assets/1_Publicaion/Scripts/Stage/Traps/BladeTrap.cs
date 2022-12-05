using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BladeTrap : MonoBehaviour
{
    CharacterController player;
    
    // Start is called before the first frame update
    void Start()
    {
        player = GameObject.Find("Player").GetComponent<CharacterController>();
    }

    void OnTriggerEnter(Collider other)
    {
        if (other == player)
        {
            Debug.Log("ss");
        }
    }
}
