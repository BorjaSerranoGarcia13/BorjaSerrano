using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class JumpPlatform : MonoBehaviour
{
    CharacterController player;
    bool jumping;
    public float jumpForce;

    PJ_Movement script;
    // ANIMATION
    private Animator animator;

    public AudioSource aa;

    void Start()
    {
        player = GameObject.Find("Player").GetComponent<CharacterController>();
        jumping = false;

        script = GameObject.Find("Player").GetComponent<PJ_Movement>();

        animator = GetComponent<Animator>();
    }

    void Update()
    {
        if (jumping)
        {
            script.fallVelocity = jumpForce;
            script.movePlayer.y = jumpForce * Time.deltaTime;

            if (player.isGrounded)
            {
                player.Move(script.movePlayer * Time.deltaTime);
            }
            else
            {
                jumping = false;
            }
        }
    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.tag == "Player")
        {
            jumping = true;
            animator.SetBool("jump", true);
            aa.Play();
        }
    }

    private void OnTriggerExit(Collider other)
    {
        animator.SetBool("jump", false);
    }
}
