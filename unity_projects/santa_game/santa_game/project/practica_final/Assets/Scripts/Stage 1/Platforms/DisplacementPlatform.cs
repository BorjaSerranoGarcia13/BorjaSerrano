using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DisplacementPlatform : MonoBehaviour
{
    GameObject player;
    movement2 script;

    bool displacement;
    public float displacementForce;
    float original_speed;
    public GameObject a;
    public GameObject b;
    Vector3 direction;

    void Start()
    {
        player = GameObject.FindWithTag("Player");
        script = player.GetComponent<movement2>();
        displacement = false;

        original_speed = script.speed;
    }

    void Update()
    {
        if (displacement)
        {
          player.GetComponent<Rigidbody>().AddForce(direction.x * 10, 0, direction.z * 10);
        }
    }

    private void OnTriggerStay(Collider other)
    {
        if (script.ground)
        {
            if (other.tag == "Player")
            {
                script.speed = 0;
                displacement = true;
                script.jumping = false;
                direction = (b.transform.position - a.transform.position).normalized;
                direction = direction * displacementForce;
                
            }
        }
    }

    private void OnTriggerExit(Collider other)
    {
        script.jumping = true;
        script.speed = original_speed;
        displacement = false;
    }

}
