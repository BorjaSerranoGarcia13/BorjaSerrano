using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class JumpEnemy : MonoBehaviour
{
    public float DistanceToPlayer = 0;
    private bool Active;
    public float JumpCooldown;
    private bool Jumpped;
    private float tmptime;
    public float JumpSpeed;
    public float EnemyDamage;
    private short direction = 0;

    public float pushPower = 2.0F;

    // ANIMATION
    private Animator animator;
    // Start is called before the first frame update
    void Start()
    {
        Active = false;
        tmptime = Time.time;
        JumpCooldown = 3.0f;
        JumpSpeed = 300.0f;
        Jumpped = false;
        EnemyDamage = 25.0f;
        //animator = GetComponent<Animator>();
        direction = 0;
    }

    // Update is called once per frame
    void Update()
    {
        gameObject.GetComponent<Rigidbody>().WakeUp();
        //if (animator.GetBool("dead"))
        //{
        //Explosion();
        //  }
        //else
        //  {
        DistanceEnemyPlayer();
        if (Active) {
          Jump();
        }
        gameObject.GetComponent<Rigidbody>().WakeUp();
        //}
    }

    void DistanceEnemyPlayer()
    {
      float distance = transform.position.x - GameObject.FindWithTag("Player").GetComponent<CharacterController>().transform.position.x;

      if (distance < 0) direction = 1;
      else direction = (-1);

      if (distance >= (-DistanceToPlayer) && distance <= DistanceToPlayer) {
        Active = true;}
      else {Active = false;}
    }

    public void Jump()
    {
        if (!Jumpped && tmptime < Time.time)
        {
            tmptime = Time.time;
            Jumpped = true;
        }

        if (direction > 0)
        {
          transform.eulerAngles = new Vector3(0.0f, 180.0f, 0.0f);
          direction *= (-1);
        }
        else transform.eulerAngles = new Vector3(0.0f, 0.0f, 0.0f);

        if (Jumpped)
        {
            Vector3 tmp = new Vector3(0.0f, 1.0f, 0.0f);
            GetComponent<Rigidbody>().velocity = JumpSpeed * ((direction * transform.right) + tmp) * Time.deltaTime;
            Jumpped = false;
            tmptime += JumpCooldown;

            //animator.SetBool("hitterrain", false);
            //animator.SetBool("jumping", true);
        } else {
          //animator.SetBool("jumping", false);
        }
    }

    void Explosion()
     {
       Active = false;

       Rigidbody enemy = gameObject.GetComponent<Rigidbody>();
       enemy.constraints = RigidbodyConstraints.FreezePosition;
       enemy.isKinematic = true;
       enemy.detectCollisions = false;
     }

    void OnCollisionStay(Collision col)
    {
        if (col.gameObject.CompareTag("Player"))
            {
               
            }

    }

    void OnControllerColliderHit(ControllerColliderHit hit)
    {
        if (hit.gameObject.CompareTag("Player"))  Debug.Log("ehhh");
        Rigidbody body = hit.collider.attachedRigidbody;

        // no rigidbody
        if (body == null || body.isKinematic)
            return;

        // We dont want to push objects below us
        if (hit.moveDirection.y < -0.3f)
            return;

        // Calculate push direction from move direction,
        // we only push objects to the sides never up and down
        Vector3 pushDir = new Vector3(hit.moveDirection.x, 0, hit.moveDirection.z);

        // If you know how fast your character is trying to move,
        // then you can also multiply the push velocity by that.

        // Apply the push
        body.velocity = pushDir * pushPower;
    }

        private void OnTriggerEnter(Collider col)
    {
      if (col.gameObject.CompareTag("Player") && !col.gameObject.CompareTag("Enemy"))
      {
        if (!animator.GetBool("dead"))
        {
          col.gameObject.GetComponent<HealthScript>().Damage(EnemyDamage);
        }
        Explosion();
        animator.SetBool("dead", true);
      }

      if (col.gameObject.CompareTag("Terrain"))
      {
        animator.SetBool("hitterrain", true);
      }
    }


    }
