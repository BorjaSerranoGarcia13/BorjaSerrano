using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DisplacementPlatform : MonoBehaviour
{
    CharacterController player;
    bool displacement;
    public float displacementForce;
    float original_jump;
    public GameObject a;
    public GameObject b;
    Vector3 direction;
    float speed;

    PJ_Movement script;

    void Start()
    {
        player = GameObject.Find("Player").GetComponent<CharacterController>();
        script = GameObject.Find("Player").GetComponent<PJ_Movement>();
        displacement = false;
        original_jump = script.jumpForce;
        speed = script.playerSpeed;
    }

    void Update()
    {
        if (displacement)
        {
            if (player.isGrounded)
            {
                player.Move(direction * Time.deltaTime);
            }
            else
            {
                displacement = false;
            }
        }
    }

    private void OnTriggerStay(Collider other)
    {
        if (player.isGrounded)
        {
            if (other.tag == "player" && player.isGrounded)
            {
                displacement = true;
                script.jumpForce = 0;
                direction = (b.transform.position - a.transform.position).normalized;
                direction = direction * displacementForce;
                script.playerSpeed = 0;
            }
        }
    }

    private void OnTriggerExit(Collider other)
    {
        if (other == player)
        { 
            script.jumpForce = original_jump;
            displacement = false;
            script.playerSpeed = speed;
        }
    }

}
