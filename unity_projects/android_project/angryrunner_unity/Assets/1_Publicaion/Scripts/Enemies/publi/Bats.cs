using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bats : MonoBehaviour
{
    [SerializeField]
    bool active_mov = true;

    [SerializeField]
    float speed_horizontal = 50.0f,
          speed_vertical = 0.0f,
          distanceToPlayer = 100.0f;

    public short direction = 1;

    private Vector3 pos;


    public GameObject follow;


    public float EnemyDamage;
    // ANIMATION
    private Animator animator;

    // Start is called before the first frame update
    void Start()
    {
      animator = GetComponent<Animator>();
      follow = GameObject.FindWithTag("EndBat");

    }

    // Update is called once per
    void Update()
    {
      if (transform.position.x < follow.transform.position.x)
      {
        transform.eulerAngles = new Vector3(0.0f, 180.0f, 0.0f);
      }
      else
      {
        transform.eulerAngles = new Vector3(0.0f, 0.0f, 0.0f);
      }

      if (animator.GetBool("dead"))
      {
        Explosion();
      }
      else
      {
        DistanceEnemyPlayer();

        if (active_mov)
        {
          transform.position = Vector3.MoveTowards(transform.position, follow.transform.position, speed_horizontal * Time.deltaTime);
        }
      }
    }

    void DistanceEnemyPlayer()
    {
      float distance = transform.position.x - GameObject.FindWithTag("Player").GetComponent<CharacterController>().transform.position.x;

      if (distance >= (-distanceToPlayer) && distance <= distanceToPlayer) {
        active_mov = true;}
      else {active_mov = false;}
    }

    void Explosion()
     {
       active_mov = false;

       Rigidbody enemy = gameObject.GetComponent<Rigidbody>();
       enemy.constraints = RigidbodyConstraints.FreezePosition;
       enemy.isKinematic = true;
       enemy.detectCollisions = false;
     }

     private void OnTriggerEnter(Collider other)
     {
         if (other.gameObject.CompareTag("Player") && !other.gameObject.CompareTag("Enemy"))
         {
           if (!animator.GetBool("dead"))
           {
             other.gameObject.GetComponent<HealthScript>().Damage(EnemyDamage);
           }
           Explosion();
           animator.SetBool("dead", true);
         }

         if (other.gameObject.CompareTag("EndBat"))
         {
           Destroy(gameObject);
         }
     }
}
