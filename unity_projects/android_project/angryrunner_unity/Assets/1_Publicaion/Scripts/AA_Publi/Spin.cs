using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Spin : MonoBehaviour
{
    public AudioSource aa;
    PlayerDead script2;

    // Start is called before the first frame update
    void Start()
    {
          aa.Play();
          script2 = GameObject.Find("Player").GetComponent<PlayerDead>();
    }

    // Update is called once per frame
    void Update()
    {

    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.tag == "Player")
        {
            script2.player_dead = true;
        }
    }

}
