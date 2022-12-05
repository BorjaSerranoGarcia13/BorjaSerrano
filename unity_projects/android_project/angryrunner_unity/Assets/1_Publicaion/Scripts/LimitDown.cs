using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LimitDown : MonoBehaviour
{
    GameObject player;
    PlayerDead script2;

    // Start is called before the first frame update
    void Start()
    {
        player = GameObject.FindWithTag("Player");
        script2 = GameObject.Find("Player").GetComponent<PlayerDead>();
    }

    // Update is called once per frame
    void Update()
    {

    }

    private void OnTriggerEnter(Collider other)
    {
        DeadHead myscript = GetComponentInChildren<DeadHead>();
        if (other.gameObject.CompareTag("Player") && !script2.player_dead)
        {
          script2.player_dead = true;
        }
        else
        {
          Destroy(other.gameObject);
        }
    }
}
