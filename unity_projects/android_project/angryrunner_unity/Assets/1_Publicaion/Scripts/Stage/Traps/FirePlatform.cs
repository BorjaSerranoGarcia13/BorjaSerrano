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
    PJ_Movement script;
    public float jumpForce;

    CharacterController player;

    void Start()
    {
        ps = GetComponent<ParticleSystem>();
        fire_particles = 100.0f;
        fire_ON = true;
        burned = false;
        player = GameObject.Find("Player").GetComponent<CharacterController>();
        script = GameObject.Find("Player").GetComponent<PJ_Movement>();
    }

    // Update is called once per frame
    void Update()
    { 
        if (fire_ON)
        {         
            if (fire_particles < 200)
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
            if (fire_particles > -100)
            {
                fire_particles -= 1.0f;
            }
            else
            { 
                StopCoroutine(WaitForMove(time_fire));
            }      
        }
        
        if (burned)
        {
            script.fallVelocity = jumpForce;
            script.movePlayer.y = jumpForce * Time.deltaTime;

            if (player.isGrounded)
            {
                player.Move(script.movePlayer * Time.deltaTime);
            }
        }
        else
        {
            burned = false;
        }
        
        var main = ps.main;
        main.maxParticles = Mathf.RoundToInt(fire_particles);
    }

    void OnTriggerStay(Collider other)
    {
        if (other == player && fire_particles > 10)
        {
            burned = true;
        }
    }

    void OnTriggerExit(Collider other)
    {
        burned = false;
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
