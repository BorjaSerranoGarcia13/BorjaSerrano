
﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class movPIG : MonoBehaviour
{
    [SerializeField]
    bool activate_mov = true;

    [SerializeField]
    float speed = 50.0f;

    [SerializeField]
    float gravity = 400.0f;

    public short direction = 1;

    private Vector3 pos;

    public float EnemyDamage;

    GameObject player;
    // ANIMATION
    private Animator animator;

    scoreCounter script;
    PlayerDead script2;

    Rigidbody rb;

    // Start is called before the first frame update
    void Start()
    {
        rb = GetComponent<Rigidbody>();

        pos = new Vector3(speed, 120.0f, 0.0f);
        player = GameObject.FindWithTag("Player");

        animator = GetComponent<Animator>();

        script = GameObject.Find("CountScore").GetComponent<scoreCounter>();

        script2 = GameObject.Find("Player").GetComponent<PlayerDead>();

    }

    // Update is called once per frame
    void Update()
    {
      if (animator.GetBool("dead"))
      {
        rb.isKinematic = true;
        rb.detectCollisions = false;
      }
      else
      {
        float distance = player.transform.position.x - transform.position.x;
        float distanceY = player.transform.position.y - transform.position.y;
        if ( distance < 15.0f && distance > -15.0f)
        {
          activate_mov = true;
          animator.SetBool("walk", true);
          
          if ( direction < 0 && distance > -5.0f && distance < -0.50f
            && distanceY < 1.0f && distanceY > -1.0f)
          {

            animator.SetBool("run", true);
            pos.x = speed + 200.0f;
          }
          else if ( direction > 0 && distance < 5.0f && distance > 0.50f
                    && distanceY < 1.0f && distanceY > -1.0f)
          {
            animator.SetBool("run", true);
            pos.x = speed + 200.0f;
          }
          else
          {
            animator.SetBool("run", false);
            pos.x = speed;
          }
        }
        else
        {
          activate_mov = false;
        }

        if (activate_mov)
        {
          rb.velocity = direction * pos * Time.deltaTime;

          if (direction == -1)
          {
            pos = new Vector3(speed, gravity, 0.0f);
            transform.eulerAngles = new Vector3(0.0f, 0.0f, 0.0f);
          }
          if (direction == 1)
          {
            pos = new Vector3(speed, -gravity, 0.0f);
            transform.eulerAngles = new Vector3(0.0f,180.0f, 0.0f);
          }
        }
      }
    }

    void OnCollisionEnter(Collision other)
    {
      if (other.gameObject.CompareTag("LimitEnemy"))
      {
          direction *= (-1);
      }
    }


    private void OnTriggerEnter(Collider other)
    {
        DeadHead myscript = GetComponentInChildren<DeadHead>();
        if (other.gameObject.CompareTag("Player") && !script2.player_dead && !myscript.deadhead)
        {
          myscript.deadhead = true;
          script2.player_dead = true;
          foreach (Transform child in transform)
          {
             Destroy(child.gameObject);
          }
        }
    }

}
