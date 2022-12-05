using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GravityChange : MonoBehaviour
{
    PJ_Movement script;
    CharacterController player;
    bool change_gravity;
    float actual_gravity;
    public bool floor = true;
    public float rotation;

    void Start()
    {
        script = GameObject.Find("Player").GetComponent<PJ_Movement>();
        player = GameObject.Find("Player").GetComponent<CharacterController>();
        change_gravity = false;
        actual_gravity = script.gravity;
    }

    // Update is called once per frame
    void Update()
    {        
        if (change_gravity)
        {
            if (floor)
            {
                if (script.gravity != -actual_gravity)
                {
                    script.gravity -= 2.0f;

                }
                else
                {
                    change_gravity = false;
                }
            }
            else
            {
                if (script.gravity != -actual_gravity)
                {
                    script.gravity += 2.0f;

                }
                else
                {
                    change_gravity = false;
                }
            }
        }
    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.tag == "player")
        {     
            change_gravity = true;      
        }
    }

}
