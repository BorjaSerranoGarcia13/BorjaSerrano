using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class movFATBIRD : MonoBehaviour
{
    Rigidbody rb;
    GameObject player;

    // ANIMATION
    private Animator animator;

    scoreCounter script;
    PlayerDead script2;

    [SerializeField]
    float speed = 50.0f;

    [SerializeField]
    float gravity = 400.0f;

    public short direction = 1;

    private Vector3 pos;

    [SerializeField]
    bool activate_mov = true;

    public float time_;

    bool jump = false;

    float tmp_gravity;

    float distance = 0.0f;

    // Start is called before the first frame update
    void Start()
    {
        rb = GetComponent<Rigidbody>();
        player = GameObject.FindWithTag("Player");

        animator = GetComponent<Animator>();

        script = GameObject.Find("CountScore").GetComponent<scoreCounter>();

        tmp_gravity = gravity;

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
        distance = player.transform.position.x - transform.position.x;
        float distanceY = player.transform.position.y - transform.position.y;
        if ( distance < 15.0f && distance > -15.0f)
        {
          if (!activate_mov) StartCoroutine(WaitForMove(time_));
          activate_mov = true;
        }
        if (activate_mov)
        {
          Movement(distance);

        }
      }

    }

    void Movement(float distance)
    {

      if (jump)
      {
        rb.AddForce(0, 70, 0, ForceMode.Impulse);
      }
      else
      {
        rb.AddForce(0, -90, 0, ForceMode.Impulse);
      }

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

    IEnumerator WaitForMove(float time)
    {
      jump = true;
      pos.x = speed;
      animator.SetBool("move", true);

      yield return new WaitForSeconds(time);
      jump = false;

      StartCoroutine(WaitForMove2(1));
    }

    IEnumerator WaitForMove2(float time)
    {
      animator.SetBool("move", false);
      pos.x = 0.0f;

      yield return new WaitForSeconds(time);
      if (distance < 0) direction = -1;
      else direction = 1;
      StartCoroutine(WaitForMove(time_));
    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.CompareTag("LimitEnemy"))
        {
            direction *= (-1);
        }

        DeadHead myscript = GetComponentInChildren<DeadHead>();
        if (other.gameObject.CompareTag("Player") && !script2.player_dead && !myscript.deadhead)
        {
          script2.player_dead = true;
          myscript.deadhead = true;
          foreach (Transform child in transform)
          {
             Destroy(child.gameObject);
          }
        }
    }



}
