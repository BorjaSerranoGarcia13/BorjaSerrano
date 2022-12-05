using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FirePlatform : MonoBehaviour
{
    private ParticleSystem ps;
    public float fire_particles;
    private bool fire_ON;
    public float time_fire;
    public bool burned;
    public int option_fire = 0;

    GameObject player;

    void Start()
    {
        ps = GetComponent<ParticleSystem>();
        fire_particles = 100.0f;
        fire_ON = true;
        burned = false;

        player = GameObject.FindWithTag("Player");

    }

    // Update is called once per frame
    void Update()
    {
      int option = 0;
        if (fire_ON)
        {

          switch(option_fire)
          {
            case 0: option = 200; break;
            case 1: option = 150; break;
            case 2: option = 100; break;

          }
            if (fire_particles < option)
            {
                fire_particles += 1.0f;
            }
            else
            {
                StartCoroutine(WaitForMove(time_fire));
            }
        }
        else
        {
            if (fire_particles > option)
            {
                fire_particles -= 1.0f;
            }
            else
            {
                StopCoroutine(WaitForMove(time_fire));
            }
        }

        var main = ps.main;
        main.maxParticles = Mathf.RoundToInt(fire_particles);
    }

    void OnTriggerStay(Collider other)
    {
        if (other.tag == "Player" && fire_particles > 10)
        {
          player.GetComponent<Rigidbody>().velocity = new Vector3(0, 8, 0);
            LifeController lc = other.GetComponent<LifeController>(); 
            lc.TakeDamage(1);
        }
    }


    IEnumerator WaitForMove(float time)
    {
        if (fire_ON) fire_ON = false;
        else fire_ON = true;

        yield return new WaitForSeconds(time);

        if (fire_ON) fire_ON = false;
        else fire_ON = true;
    }
}
