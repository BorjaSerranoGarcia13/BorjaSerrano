using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GhostEnemy : MonoBehaviour
{
    [SerializeField]
    bool activate_mov = false;
    public float DistanceToPlayer;
    public AudioSource sound_;
    float look_direction_;
    [SerializeField]
    float speed = 1.0f;
    public float EnemyDamage;
    private bool Attacked;
    public float AttackCooldown;
    private float tmptime;
    private float tmp_posX = 0.0f;

    // ANIMATION
    private Animator animator;

    short direction;
    // Start is called before the first frame update
    void Start()
    {
        AttackCooldown = 2.0f;
        tmptime = Time.time;
        tmp_posX = transform.position.x;
        animator = GetComponent<Animator>();
    }

    // Update is called once per frame
    void Update()
    {
      if (animator.GetBool("dead")) {Explosion();}
      else{
        DistanceEnemyPlayer();


        if ((GameObject.FindWithTag("Player").GetComponent<CharacterController>().transform.position.x - transform.position.x) < 0) direction = -1;
        else direction  =  1;

        if(direction > 0)
        {
            transform.eulerAngles = new Vector3(0.0f, 0.0f, 0.0f);
        }
        else
        {
            transform.eulerAngles = new Vector3(0.0f, 180.0f, 0.0f);
        }

        if (activate_mov)
        {
            transform.position = Vector3.MoveTowards(transform.position, GameObject.FindWithTag("Player").GetComponent<CharacterController>().transform.position, speed * Time.deltaTime);

            tmp_posX = transform.position.x;

            if (direction == -1) transform.eulerAngles = new Vector3(0.0f, 0.0f, 0.0f);
            else transform.eulerAngles = new Vector3(0.0f, 180.0f, 0.0f);
        }
        else
        {
          transform.position = new Vector3(tmp_posX, transform.position.y, transform.position.z);

        }
      }
        Attack();
}

    void DistanceEnemyPlayer()
    {
        Vector3 mouse_position = Input.mousePosition;
        mouse_position.z = 10.0f;
        mouse_position = Camera.main.ScreenToWorldPoint(mouse_position);

        if ((mouse_position.x - GameObject.FindWithTag("Player").GetComponent<CharacterController>().transform.position.x) > 0.0f)
        {
            look_direction_ = 1.0f;
        }
        else
        {
            look_direction_ = -1.0f;
        }

        float distance = transform.position.x - GameObject.FindWithTag("Player").GetComponent<CharacterController>().transform.position.x;

        if (direction == -1)
        {
            look_direction_ *= -1;
        }

        if (distance >= (-DistanceToPlayer) && distance <= DistanceToPlayer && look_direction_ == 1.0f)
        {
            activate_mov = true;
        }
        else {
            activate_mov = false;
        }
    }

    void Explosion()
     {
       activate_mov = false;

       Rigidbody enemy = gameObject.GetComponent<Rigidbody>();
       enemy.constraints = RigidbodyConstraints.FreezePosition;
       enemy.isKinematic = true;
       enemy.detectCollisions = false;
     }
    void Attack()
    {

        if (!Attacked && tmptime < Time.time && activate_mov)
        {
            tmptime = Time.time;
            Attacked = true;
            animator.SetBool("attack", false);

        }
        if(animator.GetBool("attack"))animator.SetBool("attack", false);
        if (Vector3.Distance(transform.position, GameObject.FindWithTag("Player").GetComponent<CharacterController>().transform.position) < 2.0f && Attacked)
        {
            animator.SetBool("attack", true);
            Attacked = false;
            tmptime += AttackCooldown;
        }
    }

    private void OnTriggerEnter(Collider col)
    {
      if (col.gameObject.CompareTag("Player") && !col.gameObject.CompareTag("Enemy"))
      {
          if (!animator.GetBool("dead"))
          {
            col.gameObject.GetComponent<HealthScript>().Damage(EnemyDamage);
          }
          //sound_.Play();
          //Explosion();
          //animator.SetBool("dead", true);
      }
    }
}
